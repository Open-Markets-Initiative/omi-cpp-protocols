// Cboe C1Options Complex Pitch 2.1.18 Template Meta Programming

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <ios>
#include <limits>
#include <optional>
#include <ostream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

// A member of a struct laid over its bytes: the overload get<Field>() finds it by, and the member
#ifndef PITCHFIELD
#define PITCHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef PITCHSEQUENCE
#define PITCHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

// a day is placed in its timezone by the C++20 time zone database (std::chrono::locate_zone),
// which needs nothing installed: MSVC reads the ICU data Windows 10 (1903) and later ship;
// libstdc++ 14 and libc++ read the system's IANA data
#if !defined(__cpp_lib_chrono) || __cpp_lib_chrono < 201907L
#error "a time of day placed on a day needs the C++20 time zone database (std::chrono::locate_zone)"
#endif

// A time of day counted from midnight (Epoch Midnight) names no day: placed on one, in the zone the
// model states its midnight in, it is an instant, UTC Unix nanoseconds
namespace cboe::c1options::complex::pitch::v2_1_18::calendar {

constexpr std::int64_t nanoseconds_per_second = 1'000'000'000;
constexpr std::int64_t seconds_per_day = 86'400;

// division rounding down: the second or day a negative count falls in is the one before
constexpr std::int64_t floor_divide(const std::int64_t value, const std::int64_t divisor) {
    auto quotient = value / divisor;
    if (value % divisor != 0 && (value < 0) != (divisor < 0)) {
        --quotient;
    }
    return quotient;
}

// A calendar day, held as days since 1970-01-01
class Day {
  public:
    // the day a calendar date names; a date that names none (2026-02-30) is refused
    explicit Day(const std::chrono::year_month_day date)
     : days_{ checked(date) } {}

    // the day yyyymmdd text names, or none for text that is not eight digits naming a date
    static std::optional<Day> parse(const std::string_view text) {
        if (text.size() != 8) {
            return std::nullopt;
        }
        for (const char character : text) {
            if (character < '0' || character > '9') {
                return std::nullopt;
            }
        }

        int year = 0;
        unsigned month = 0;
        unsigned day = 0;
        std::from_chars(text.data(), text.data() + 4, year);
        std::from_chars(text.data() + 4, text.data() + 6, month);
        std::from_chars(text.data() + 6, text.data() + 8, day);

        const std::chrono::year_month_day date{ std::chrono::year{ year }, std::chrono::month{ month }, std::chrono::day{ day } };
        if (!date.ok()) {
            return std::nullopt;
        }
        return Day{ date };
    }

    // days since 1970-01-01
    std::chrono::sys_days days() const {
        return days_;
    }

    // the calendar date
    std::chrono::year_month_day date() const {
        return std::chrono::year_month_day{ days_ };
    }

    // the day as ISO 8601 text, yyyy-mm-dd
    std::string text() const {
        const auto ymd = date();
        std::array<char, 16> buffer{};
        auto* end = buffer.data();
        end = digits(end, static_cast<int>(ymd.year()), 4);
        *end++ = '-';
        end = digits(end, static_cast<int>(static_cast<unsigned>(ymd.month())), 2);
        *end++ = '-';
        end = digits(end, static_cast<int>(static_cast<unsigned>(ymd.day())), 2);
        return std::string{ buffer.data(), end };
    }

    friend bool operator==(const Day&, const Day&) = default;

    // a count written at least width digits wide, zeros before it
    static char* digits(char* out, const std::int64_t value, const int width) {
        std::array<char, 24> buffer{};
        auto magnitude = value;
        if (magnitude < 0) {
            *out++ = '-';
            magnitude = -magnitude;
        }
        const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), magnitude);
        for (auto count = result.ptr - buffer.data(); count < width; ++count) {
            *out++ = '0';
        }
        for (const char* at = buffer.data(); at != result.ptr; ++at) {
            *out++ = *at;
        }
        return out;
    }

  private:
    static std::chrono::sys_days checked(const std::chrono::year_month_day date) {
        if (!date.ok()) {
            throw std::invalid_argument{ "not a calendar date" };
        }
        return std::chrono::sys_days{ date };
    }

    std::chrono::sys_days days_;
};

// A day's wall clock in a timezone, as UTC: the offsets in force around the day, looked up once, so
// a time of day is placed on it by arithmetic alone. A time of day is the wall clock's reading, so
// across a daylight saving change 09:30 is 09:30 on the clock: a reading the clock repeats is the
// earlier instant, and one it skips is read at the offset before the skip
class Midnight {
  public:
    // the day in the zone the model names; UTC needs no database
    Midnight(const Day& day, const std::string_view zone)
     : day_{ day }, zone_{ zone }, timezone_{ locate(zone) } {
        const auto midnight = static_cast<std::int64_t>(day.days().time_since_epoch().count()) * seconds_per_day;
        wall_begin_ = midnight - seconds_per_day;
        wall_end_ = midnight + window * seconds_per_day;

        if (timezone_ == nullptr) {
            spans_[0] = Span{ std::numeric_limits<std::int64_t>::min(), std::numeric_limits<std::int64_t>::max(), 0 };
            count_ = 1;
            return;
        }

        // every offset in force from a day before the window to a day after it, which holds every
        // UTC reading of a wall time inside it: no zone is a day from UTC
        auto instant = wall_begin_ - seconds_per_day;
        while (instant < wall_end_ + seconds_per_day) {
            if (count_ == spans_.size()) {
                count_ = 0;
                return;
            }
            const auto info = timezone_->get_info(std::chrono::sys_seconds{ std::chrono::seconds{ instant } });
            const auto end = static_cast<std::int64_t>(info.end.time_since_epoch().count());
            spans_[count_] = Span{ static_cast<std::int64_t>(info.begin.time_since_epoch().count()), end, static_cast<std::int64_t>(info.offset.count()) };
            ++count_;
            instant = end;
        }
    }

    // the day placed on
    const Day& day() const {
        return day_;
    }

    // the zone the day's midnight is in, as the model names it
    std::string_view zone() const {
        return zone_;
    }

    // UTC Unix nanoseconds of a time of day: nanoseconds after the day's local midnight, as the wall
    // clock reads them
    std::int64_t utc(const std::int64_t time) const {
        const auto wall = static_cast<std::int64_t>(day_.days().time_since_epoch().count()) * seconds_per_day + floor_divide(time, nanoseconds_per_second);
        const auto fraction = time - floor_divide(time, nanoseconds_per_second) * nanoseconds_per_second;
        return seconds(wall) * nanoseconds_per_second + fraction;
    }

  private:
    // an offset (seconds east of UTC) and the UTC seconds [begin, end) it is in force for
    struct Span {
        std::int64_t begin;
        std::int64_t end;
        std::int64_t offset;
    };

    // the days after the day's midnight the spans hold its wall clock for: a time of day past
    // midnight is placed by them too
    static constexpr std::int64_t window = 3;

    static const std::chrono::time_zone* locate(const std::string_view zone) {
        if (zone == "UTC") {
            return nullptr;
        }
        return std::chrono::locate_zone(zone);
    }

    // UTC seconds of a wall clock second: the earlier reading of one the clock repeats; the offset
    // before the skip for one it skips. Outside the window, or for a zone whose offsets change too
    // often to hold, the database is asked: its first reading is the same in each case
    std::int64_t seconds(const std::int64_t wall) const {
        if (count_ > 0 && wall >= wall_begin_ && wall < wall_end_) {
            for (std::size_t index = 0; index < count_; ++index) {
                const auto& span = spans_[index];
                const auto reading = wall - span.offset;
                if (reading >= span.begin && reading < span.end) {
                    return reading;
                }
                if (index + 1 < count_ && wall >= span.end + span.offset && wall < spans_[index + 1].begin + spans_[index + 1].offset) {
                    return reading;
                }
            }
        }

        if (timezone_ == nullptr) {
            return wall;
        }
        const auto info = timezone_->get_info(std::chrono::local_seconds{ std::chrono::seconds{ wall } });
        return wall - static_cast<std::int64_t>(info.first.offset.count());
    }

    Day day_;
    std::string zone_;
    const std::chrono::time_zone* timezone_;
    std::int64_t wall_begin_ = 0;
    std::int64_t wall_end_ = 0;
    std::array<Span, 8> spans_{};
    std::size_t count_ = 0;
};

// the Midnight of a day in a zone, looked up once per thread for the zone and the day last asked of
// it, so a field placed on a day row after row asks the database once. It holds until the thread
// next asks this zone for another day
inline const Midnight& midnight(const Day& day, const std::string_view zone) {
    thread_local std::deque<Midnight> held;
    for (auto& each : held) {
        if (each.zone() == zone) {
            if (!(each.day() == day)) {
                each = Midnight{ day, zone };
            }
            return each;
        }
    }
    held.emplace_back(day, zone);
    return held.back();
}

// the count a time of day's text states, all digits; none for text that is anything else
inline std::optional<std::int64_t> count(const std::string_view text) {
    if (text.empty()) {
        return std::nullopt;
    }
    std::int64_t value = 0;
    for (const char character : text) {
        if (character < '0' || character > '9') {
            return std::nullopt;
        }
        value = value * 10 + (character - '0');
    }
    return value;
}

// UTC Unix nanoseconds as ISO 8601 text to the nanosecond: 2026-07-01T13:30:00.000000000Z
inline std::string iso8601(const std::int64_t utc) {
    const auto days = floor_divide(utc, seconds_per_day * nanoseconds_per_second);
    auto within = utc - days * seconds_per_day * nanoseconds_per_second;
    const std::chrono::year_month_day date{ std::chrono::sys_days{ std::chrono::days{ days } } };

    std::array<char, 48> buffer{};
    auto* end = buffer.data();
    end = Day::digits(end, static_cast<int>(date.year()), 4);
    *end++ = '-';
    end = Day::digits(end, static_cast<unsigned>(date.month()), 2);
    *end++ = '-';
    end = Day::digits(end, static_cast<unsigned>(date.day()), 2);
    *end++ = 'T';
    end = Day::digits(end, within / (3'600 * nanoseconds_per_second), 2);
    within %= 3'600 * nanoseconds_per_second;
    *end++ = ':';
    end = Day::digits(end, within / (60 * nanoseconds_per_second), 2);
    within %= 60 * nanoseconds_per_second;
    *end++ = ':';
    end = Day::digits(end, within / nanoseconds_per_second, 2);
    *end++ = '.';
    end = Day::digits(end, within % nanoseconds_per_second, 9);
    *end++ = 'Z';
    return std::string{ buffer.data(), end };
}

// UTC Unix nanoseconds written as ISO 8601 text to the nanosecond
inline void iso8601(std::ostream& out, const std::int64_t utc) {
    out << iso8601(utc);
}

// A stream's print day: written to a stream (out << calendar::on(day)), every time of day a
// generated print() writes to it after is placed on the day, ISO 8601 UTC, where without it the
// time of day prints as its count. Written with no day (out << calendar::On{}), it is taken off
struct On {
    std::optional<Day> day;
};

// the print day of a day
inline On on(const Day& day) {
    return On{ day };
}

// the stream slots a print day is kept in: whether the stream has one, and its days since 1970-01-01
inline int print_day_slot() {
    static const int slot = std::ios_base::xalloc();
    return slot;
}

inline int print_days_slot() {
    static const int slot = std::ios_base::xalloc();
    return slot;
}

inline std::ostream& operator<<(std::ostream& out, const On& on) {
    if (on.day) {
        out.iword(print_day_slot()) = 1;
        out.iword(print_days_slot()) = static_cast<long>(on.day->days().time_since_epoch().count());
    }
    else {
        out.iword(print_day_slot()) = 0;
    }
    return out;
}

// the print day of a stream, where it has one
inline std::optional<Day> print_day(std::ios_base& out) {
    if (out.iword(print_day_slot()) == 0) {
        return std::nullopt;
    }
    const std::chrono::sys_days days{ std::chrono::days{ out.iword(print_days_slot()) } };
    return Day{ std::chrono::year_month_day{ days } };
}

// a count of a time of day's unit, as a generated print() writes it: the count, or on the stream's
// print day the instant, ISO 8601 UTC
template <typename Count>
inline void print(std::ostream& out, const Count count, const std::int64_t nanoseconds, const std::string_view zone) {
    const auto day = print_day(out);
    if (!day) {
        out << count;
        return;
    }
    iso8601(out, midnight(*day, zone).utc(static_cast<std::int64_t>(count) * nanoseconds));
}

}

namespace cboe::c1options::complex::pitch::v2_1_18 {

/////////////////////////////////////////////////////////////////////
// Wire
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // The types of a struct's members, in wire order: what generic code walks a struct by
    template <typename... Fields>
    struct list {};

    // A repeating group of a message: the type of its entries, each laid over its bytes in turn
    template <typename Entry>
    struct sequence {
        using entry = Entry;
    };

    // An integer as the wire holds it, in the host's order: swapped when the wire's order is not the host's
    template <std::endian Order, typename T>
    constexpr T ordered(T value) noexcept {
        if constexpr (sizeof(T) == 1 || Order == std::endian::native) { return value; }
        else { return std::byteswap(value); }
    }

    // An integer of a width no C++ integer has, assembled from its bytes in the wire's order
    template <std::endian Order, typename T, std::size_t N>
    constexpr T assembled(const std::array<std::byte, N>& bytes) noexcept {
        using U = std::make_unsigned_t<T>;
        U value = 0;
        for (std::size_t index = 0; index < N; ++index) {
            const std::size_t at = Order == std::endian::big ? index : N - 1 - index;
            value = static_cast<U>((value << 8) | std::to_integer<U>(bytes[at]));
        }
        if constexpr (std::is_signed_v<T>) {
            constexpr int spare = static_cast<int>(sizeof(T) - N) * 8;
            return static_cast<T>(static_cast<T>(value << spare) >> spare);
        }
        else { return value; }
    }

    // Text of a fixed width, as the characters before its fill
    template <std::size_t N>
    constexpr std::string_view trimmed(const std::array<char, N>& text, char fill) noexcept {
        std::size_t length = N;
        while (length > 0 && text[length - 1] == fill) { --length; }
        return { text.data(), length };
    }

    // Text of a fixed width justified right, as the characters after its fill
    template <std::size_t N>
    constexpr std::string_view trimmed_front(const std::array<char, N>& text, char fill) noexcept {
        std::size_t start = 0;
        while (start < N && text[start] == fill) { ++start; }
        return { text.data() + start, N - start };
    }

    // The integer the digits of text state, its fill skipped; it ends at anything else
    template <typename T>
    constexpr T number(std::string_view text, char fill) noexcept {
        T value = 0;
        for (const char character : text) {
            if (character == fill) { continue; }
            if (character < '0' || character > '9') { break; }
            value = static_cast<T>(value * 10 + static_cast<T>(character - '0'));
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////

// Auction End Offset: Nanosecond offset from last timestamp.
struct auction_end_offset {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Id: Day specific identifier assigned to this auction.
struct auction_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Only Price: Not used for complex series. Will contain zero value.
struct auction_only_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Opening Type
struct auction_opening_type {
    enum class type : char {
        gth = 'G',
        rth = 'O',
        halt_reopening = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Type
struct auction_type {
    enum class type : char {
        complex_auction = 'C',
        complex_solicitation_auction = 'S',
        complex_aim = 'B',
        coa_all_or_none = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Buy Contracts: Cumulative Buy interest at the Indicative Price.
struct buy_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canceled Quantity: Instrument quantity canceled
struct canceled_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canceled Quantity Short: Instrument quantity canceled
struct canceled_quantity_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Client Id: Optional user specified value attributed to this quote. Space filled otherwise.
struct client_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Complex Instrument Id: Complex Instrument Id right padded with spaces.
struct complex_instrument_id {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Complex Instrument Id 8: Complex Instrument Id right padded with spaces.
struct complex_instrument_id_8 {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Complex Instrument Type: 4 character field; each field describes a characteristic.
struct complex_instrument_type {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Complex Instrument Underlying: Complex Instrument Underlying right padded with spaces.
struct complex_instrument_underlying {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Complex Symbol Id: Complex Symbol right padded with spaces.
struct complex_symbol_id {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Composite Market Bid Price: Not used for Complex series. Will contain zero value.
struct composite_market_bid_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Composite Market Offer Price: Not used for complex series. Will contain zero value.
struct composite_market_offer_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Customer Indicator
struct customer_indicator {
    enum class type : char {
        non_customer = 'N',
        customer = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Quantity: Number of shares/contracts executed
struct executed_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Execution Id: Cboe generated day-unique execution identifier of this execution. Execution Id is also referenced in the Trade Break message
struct execution_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Feed Symbol: Symbol right padded with spaces.
struct feed_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Gth Trading Status: GTH Trading Status (C1 Only)
struct gth_trading_status {
    enum class type : char {
        halted = 'H',
        quote_only = 'Q',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Indicative Price: SNBBO Collared Volume Maximizing Imbalance Minimizing Price computed on combined Auction-Only and Continuous Book (if any).
struct indicative_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Count: The number of legs in the complex instrument. The maximum number of legs is 12.
struct leg_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio: Leg ratio (positive for buy-side, negative for sell-side). For options this is the number of contracts, for equities this is the number of shares.
struct leg_ratio {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Type: Option or Equity instrument
struct leg_security_type {
    enum class type : char {
        option = 'O',
        equity = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Symbol: Option or Equity Symbol of leg, right padded with spaces.
struct leg_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Length: Length of entire block of messages. Includes this header and Message Count messages to follow
struct length_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Count: Number of messages to follow this header
struct message_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Current Pitch message length
struct message_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: Code identifying this message type
struct message_type {
    enum class type : std::uint8_t {
        time_message = 32,
        unit_clear_message = 151,
        transaction_begin = 188,
        transaction_end_message = 189,
        complex_instrument_definition_expanded_message = 154,
        symbol_mapping_message = 46,
        add_order_long_message = 33,
        add_order_short_message = 34,
        add_order_expanded_message = 47,
        order_executed_message = 35,
        order_executed_at_price_size_message = 36,
        reduce_size_long_message = 37,
        reduce_size_short_message = 38,
        modify_order_long_message = 39,
        modify_order_short_message = 40,
        delete_order_message = 41,
        trade_long_message = 42,
        trade_short_message = 43,
        auction_notification_message = 173,
        auction_cancel_message = 174,
        auction_trade_message = 175,
        trading_status_message = 49,
        auction_update_message = 209,
        auction_summary_message = 150,
        end_of_session_message = 45,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Opening Condition: Not used for Complex series. Will contain zero value.
struct opening_condition {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Order Id: Day-specific identifier assigned to this order
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Osi Symbol
struct osi_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 21;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 21> value_;
};

// Padding: Reserved
struct padding {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id: Optionally specified. If specified the Executing Broker of firm attributed to this quote.
struct participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Price: The limit order price
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Short: The limit order price
struct price_short {
    using type = std::int16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity: Instrument quantity added to the complex book (may be less than the number entered).
struct quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity Short: Instrument quantity being added to the complex book (may be less than the number entered).
struct quantity_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reference Price: Not used for complex series. Will contain zero value.
struct reference_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Remaining Quantity: Number of shares/contracts remaining after the execution
struct remaining_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: Reserved
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sell Contracts: Cumulative Sell interest at the Indicative Price.
struct sell_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence: Sequence Number of the first message to follow this header
struct sequence {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side Indicator: Order Side
struct side_indicator {
    enum class type : char {
        buy_order = 'B',
        sell_order = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Symbol Condition: N = Normal C = Closing Only
struct symbol_condition {
    enum class type : char {
        normal = 'N',
        closing_only = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Time: Number of whole seconds from midnight Eastern Time
struct time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

    // time on a day: its seconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(value()) * 1000000000); }

  protected:
    type value_;
};

// Time Offset: Nanosecond offset from last unit timestamp
struct time_offset {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Condition: Options Only (byte not sent in Equities) (Space): Normal Trade S: Spread trade
struct trade_condition {
    enum class type : char {
        complex_to_complex_electronic_trade = 'f',
        complex_auction_trade = 'g',
        complex_cross = 'h',
        complex_electronic_trade_against_single = 'j',
        complex_with_stock_options_auction_trade = 'k',
        complex_with_stock_electronic_trade = 'n',
        complex_with_stock_cross = 'o',
        electronic_trade = 'I',
        opening_trade = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Status
struct trading_status {
    enum class type : char {
        halted = 'H',
        quote_only = 'Q',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying: Symbol of underlying equity right padded with spaces. All spaces if not available or not applicable.
struct underlying {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Unit: Unit that applies to messages included in this header
struct unit {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unused: Reserved
struct unused {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// End Of Session Message: The End of Session message is sent for each unit when the unit shuts down. No more sequenced messages will be delivered for this unit, but heartbeats from the unit may be received.
struct end_of_session_message {
    static constexpr std::string_view name = "End Of Session Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
};

static_assert(sizeof(end_of_session_message) == end_of_session_message::size, "end_of_session_message lies over its bytes exactly");

// Auction Summary Message: Auction Summary messages are used to disseminate the results of an auction of a complex instrument. An Opening or Re-Opening Auction Summary message for each complex instrument is sent at the conclusion of its Opening or Re-Opening auction and represents Cboe opening price.
struct auction_summary_message {
    static constexpr std::string_view name = "Auction Summary Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        complex_instrument_id_8,
        auction_opening_type,
        price,
        quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(complex_instrument_id_8);
    PITCHFIELD(auction_opening_type);
    PITCHFIELD(price);
    PITCHFIELD(quantity);
};

static_assert(sizeof(auction_summary_message) == auction_summary_message::size, "auction_summary_message lies over its bytes exactly");

// Auction Update Message: Options Auction Update messages are used to disseminate price and size information during the Opening and Re-Opening (halt) process for complex instruments.
struct auction_update_message {
    static constexpr std::string_view name = "Auction Update Message";
    static constexpr std::size_t size = 62;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        complex_instrument_id_8,
        auction_opening_type,
        reference_price,
        buy_contracts,
        sell_contracts,
        indicative_price,
        auction_only_price,
        opening_condition,
        composite_market_bid_price,
        composite_market_offer_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(complex_instrument_id_8);
    PITCHFIELD(auction_opening_type);
    PITCHFIELD(reference_price);
    PITCHFIELD(buy_contracts);
    PITCHFIELD(sell_contracts);
    PITCHFIELD(indicative_price);
    PITCHFIELD(auction_only_price);
    PITCHFIELD(opening_condition);
    PITCHFIELD(composite_market_bid_price);
    PITCHFIELD(composite_market_offer_price);
};

static_assert(sizeof(auction_update_message) == auction_update_message::size, "auction_update_message lies over its bytes exactly");

// Trading Status Message: The Trading Status message is used to indicate the current trading status of a complex instrument.
struct trading_status_message {
    static constexpr std::string_view name = "Trading Status Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        complex_symbol_id,
        unused,
        trading_status,
        reserved_1,
        gth_trading_status,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(complex_symbol_id);
    PITCHFIELD(unused);
    PITCHFIELD(trading_status);
    PITCHFIELD(reserved_1);
    PITCHFIELD(gth_trading_status);
    PITCHFIELD(padding);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Auction Trade Message: Auction Trade messages are used to disseminate executions resulting from a complex auction.
struct auction_trade_message {
    static constexpr std::string_view name = "Auction Trade Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        auction_id,
        execution_id,
        price,
        quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(auction_id);
    PITCHFIELD(execution_id);
    PITCHFIELD(price);
    PITCHFIELD(quantity);
};

static_assert(sizeof(auction_trade_message) == auction_trade_message::size, "auction_trade_message lies over its bytes exactly");

// Auction Cancel Message: Auction Cancel messages are used to disseminate the cancelation of an earlier Auction Notification message as a result of a user cancelation of the original complex auction, a user modification request to change the complex auction price or increase the original complex auction quantity, a fading of the NBBO or to cancel any remaining complex auction quantity from the original Auction Notification following the complex auction termination.
struct auction_cancel_message {
    static constexpr std::string_view name = "Auction Cancel Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        auction_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(auction_id);
};

static_assert(sizeof(auction_cancel_message) == auction_cancel_message::size, "auction_cancel_message lies over its bytes exactly");

// Auction Notification Message: Auction Notification messages are used to disseminate order details of a complex auction.
struct auction_notification_message {
    static constexpr std::string_view name = "Auction Notification Message";
    static constexpr std::size_t size = 45;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        complex_instrument_id,
        auction_id,
        auction_type,
        side_indicator,
        price,
        quantity,
        customer_indicator,
        participant_id,
        auction_end_offset,
        client_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(complex_instrument_id);
    PITCHFIELD(auction_id);
    PITCHFIELD(auction_type);
    PITCHFIELD(side_indicator);
    PITCHFIELD(price);
    PITCHFIELD(quantity);
    PITCHFIELD(customer_indicator);
    PITCHFIELD(participant_id);
    PITCHFIELD(auction_end_offset);
    PITCHFIELD(client_id);
};

static_assert(sizeof(auction_notification_message) == auction_notification_message::size, "auction_notification_message lies over its bytes exactly");

// Trade Short Message: The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers.
struct trade_short_message {
    static constexpr std::string_view name = "Trade Short Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_short,
        complex_instrument_id,
        price_short,
        execution_id,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity_short);
    PITCHFIELD(complex_instrument_id);
    PITCHFIELD(price_short);
    PITCHFIELD(execution_id);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(trade_short_message) == trade_short_message::size, "trade_short_message lies over its bytes exactly");

// Trade Long Message: The Trade message provides information about executions of complex order auctions on the Cboe complex book.
struct trade_long_message {
    static constexpr std::string_view name = "Trade Long Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity,
        complex_instrument_id,
        price,
        execution_id,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity);
    PITCHFIELD(complex_instrument_id);
    PITCHFIELD(price);
    PITCHFIELD(execution_id);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(trade_long_message) == trade_long_message::size, "trade_long_message lies over its bytes exactly");

// Delete Order Message: The Delete Order message is sent whenever an open order is completely canceled. The Order Id refers to the Order Id of the original Add Order message.
struct delete_order_message {
    static constexpr std::string_view name = "Delete Order Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
};

static_assert(sizeof(delete_order_message) == delete_order_message::size, "delete_order_message lies over its bytes exactly");

// Modify Order Short Message: The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message.
struct modify_order_short_message {
    static constexpr std::string_view name = "Modify Order Short Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        quantity_short,
        price_short,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(quantity_short);
    PITCHFIELD(price_short);
    PITCHFIELD(padding);
};

static_assert(sizeof(modify_order_short_message) == modify_order_short_message::size, "modify_order_short_message lies over its bytes exactly");

// Modify Order Long Message: The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message.
struct modify_order_long_message {
    static constexpr std::string_view name = "Modify Order Long Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        quantity,
        price,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(quantity);
    PITCHFIELD(price);
    PITCHFIELD(padding);
};

static_assert(sizeof(modify_order_long_message) == modify_order_long_message::size, "modify_order_long_message lies over its bytes exactly");

// Reduce Size Short Message: Reduce Size messages are sent when a visible order on the Cboe book is partially reduced.
struct reduce_size_short_message {
    static constexpr std::string_view name = "Reduce Size Short Message";
    static constexpr std::size_t size = 14;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        canceled_quantity_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(canceled_quantity_short);
};

static_assert(sizeof(reduce_size_short_message) == reduce_size_short_message::size, "reduce_size_short_message lies over its bytes exactly");

// Reduce Size Long Message: Reduce Size messages are sent when a visible order on the Cboe book is partially reduced.
struct reduce_size_long_message {
    static constexpr std::string_view name = "Reduce Size Long Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        canceled_quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(canceled_quantity);
};

static_assert(sizeof(reduce_size_long_message) == reduce_size_long_message::size, "reduce_size_long_message lies over its bytes exactly");

// Order Executed At Price Size Message: Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id.
struct order_executed_at_price_size_message {
    static constexpr std::string_view name = "Order Executed At Price Size Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        executed_quantity,
        remaining_quantity,
        execution_id,
        price,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(executed_quantity);
    PITCHFIELD(remaining_quantity);
    PITCHFIELD(execution_id);
    PITCHFIELD(price);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(order_executed_at_price_size_message) == order_executed_at_price_size_message::size, "order_executed_at_price_size_message lies over its bytes exactly");

// Order Executed Message: Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part.
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        executed_quantity,
        execution_id,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(executed_quantity);
    PITCHFIELD(execution_id);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Add Order Expanded Message: An Add Order message represents a newly accepted visible order on the Cboe book. Expanded version accommodates larger symbol sizes possible through the ISRA plan.
struct add_order_expanded_message {
    static constexpr std::string_view name = "Add Order Expanded Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity,
        complex_instrument_id_8,
        price,
        reserved_1,
        participant_id,
        customer_indicator,
        client_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity);
    PITCHFIELD(complex_instrument_id_8);
    PITCHFIELD(price);
    PITCHFIELD(reserved_1);
    PITCHFIELD(participant_id);
    PITCHFIELD(customer_indicator);
    PITCHFIELD(client_id);
};

static_assert(sizeof(add_order_expanded_message) == add_order_expanded_message::size, "add_order_expanded_message lies over its bytes exactly");

// Add Order Short Message: An Add Order message represents a newly accepted visible order on the Cboe book.
struct add_order_short_message {
    static constexpr std::string_view name = "Add Order Short Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_short,
        complex_instrument_id,
        price_short,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity_short);
    PITCHFIELD(complex_instrument_id);
    PITCHFIELD(price_short);
    PITCHFIELD(padding);
};

static_assert(sizeof(add_order_short_message) == add_order_short_message::size, "add_order_short_message lies over its bytes exactly");

// Add Order Long Message: An Add Order message represents a newly accepted visible order on the Cboe book.
struct add_order_long_message {
    static constexpr std::string_view name = "Add Order Long Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity,
        complex_instrument_id,
        price,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity);
    PITCHFIELD(complex_instrument_id);
    PITCHFIELD(price);
    PITCHFIELD(padding);
};

static_assert(sizeof(add_order_long_message) == add_order_long_message::size, "add_order_long_message lies over its bytes exactly");

// Symbol Mapping Message: A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying.
struct symbol_mapping_message {
    static constexpr std::string_view name = "Symbol Mapping Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        feed_symbol,
        osi_symbol,
        symbol_condition,
        underlying>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(feed_symbol);
    PITCHFIELD(osi_symbol);
    PITCHFIELD(symbol_condition);
    PITCHFIELD(underlying);
};

static_assert(sizeof(symbol_mapping_message) == symbol_mapping_message::size, "symbol_mapping_message lies over its bytes exactly");

// Complex Instrument Leg: Leg for multi-leg strategies
struct complex_instrument_leg {
    static constexpr std::string_view name = "Complex Instrument Leg";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_symbol,
        leg_ratio,
        leg_security_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(leg_symbol);
    PITCHFIELD(leg_ratio);
    PITCHFIELD(leg_security_type);
};

static_assert(sizeof(complex_instrument_leg) == complex_instrument_leg::size, "complex_instrument_leg lies over its bytes exactly");

// Complex Instrument Definition Expanded Message Section 1
struct complex_instrument_definition_expanded_message_section_1 {
    static constexpr std::string_view name = "Complex Instrument Definition Expanded Message Section 1";
    static constexpr std::size_t size = 23;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        complex_instrument_id,
        complex_instrument_underlying,
        complex_instrument_type,
        leg_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(complex_instrument_id);
    PITCHFIELD(complex_instrument_underlying);
    PITCHFIELD(complex_instrument_type);
    PITCHFIELD(leg_count);
};

static_assert(sizeof(complex_instrument_definition_expanded_message_section_1) == complex_instrument_definition_expanded_message_section_1::size, "complex_instrument_definition_expanded_message_section_1 lies over its bytes exactly");

// Complex Instrument Definition Expanded Message: A Complex Instrument Definition Expanded message represents a complex instrument that is available to place orders.
struct complex_instrument_definition_expanded_message {
    static constexpr std::string_view name = "Complex Instrument Definition Expanded Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    PITCHSEQUENCE(complex_instrument_leg);
};

// Transaction End Message: The Transaction End message indicates that a transaction indicated by a previous Transaction Begin message has completed.
struct transaction_end_message {
    static constexpr std::string_view name = "Transaction End Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
};

static_assert(sizeof(transaction_end_message) == transaction_end_message::size, "transaction_end_message lies over its bytes exactly");

// Transaction Begin: The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block.
struct transaction_begin {
    static constexpr std::string_view name = "Transaction Begin";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
};

static_assert(sizeof(transaction_begin) == transaction_begin::size, "transaction_begin lies over its bytes exactly");

// Unit Clear Message: The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header. This message will be sent at startup each day.
struct unit_clear_message {
    static constexpr std::string_view name = "Unit Clear Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
};

static_assert(sizeof(unit_clear_message) == unit_clear_message::size, "unit_clear_message lies over its bytes exactly");

// Time Message: A Time message is sent whenever the source time for a unit passes over a second boundary.
struct time_message {
    static constexpr std::string_view name = "Time Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time);
};

static_assert(sizeof(time_message) == time_message::size, "time_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(message_length);
    PITCHFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Heartbeat
struct heartbeat {
    static constexpr std::string_view name = "Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Messages: Branch
struct messages {
    static constexpr std::string_view name = "Messages";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    PITCHSEQUENCE(message);
};

// Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        length_type,
        message_count,
        unit,
        sequence>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(length_type);
    PITCHFIELD(message_count);
    PITCHFIELD(unit);
    PITCHFIELD(sequence);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Pitch Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace cboe::c1options::complex::pitch::v2_1_18
