// Lseg Millennium Level2 Mitch 11.9 Template Meta Programming

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
#ifndef MITCHFIELD
#define MITCHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef MITCHSEQUENCE
#define MITCHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

// a day is placed in its timezone by the C++20 time zone database (std::chrono::locate_zone),
// which needs nothing installed: MSVC reads the ICU data Windows 10 (1903) and later ship;
// libstdc++ 14 and libc++ read the system's IANA data
#if !defined(__cpp_lib_chrono) || __cpp_lib_chrono < 201907L
#error "a time of day placed on a day needs the C++20 time zone database (std::chrono::locate_zone)"
#endif

// A time of day counted from midnight (Epoch Midnight) names no day: placed on one, in the zone the
// model states its midnight in, it is an instant, UTC Unix nanoseconds
namespace lseg::millennium::level2::mitch::v11_9::calendar {

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

namespace lseg::millennium::level2::mitch::v11_9 {

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

// Amnd: Amended
struct amnd {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Attribution: Identity of firm that submitted the order.
struct attribution {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Auction Type
struct auction_type {
    enum class type : char {
        closing_auction = 'C',
        opening_auction = 'O',
        aesp = 'A',
        edsp = 'B',
        resume_auction = 'E',
        periodic_auction = 'F',
        scheduled_level_1_only_auction = 'G',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Book Type
struct book_type {
    enum class type : std::uint8_t {
        on_book = 1,
        off_book = 2,
        private_rfq = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Buy Limit Price: Best bid price. Will contain zero if there are no visible limit orders on the buy side
struct buy_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Limit Size: Cumulative visible size at best bid price. Will contain zero if there are no visible limit orders on the buy side
struct buy_limit_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canc: Cancel
struct canc {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Cross Type: The type of the Cross/BTF Order.
struct cross_type {
    enum class type : std::uint8_t {
        internal_cross = 5,
        internal_btf = 6,
        committed_cross = 7,
        committed_btf = 8,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Currency: ISO Currency Code
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Display Quantity: Displayed quantity of the order after the execution.
struct display_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code: Refer to System Event Codes below
struct event_code {
    enum class type : char {
        end_of_day = 'C',
        start_of_day = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Quantity: Quantity executed.
struct executed_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Firm Quote
struct firm_quote {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Instrument Id: Instrument's symbol.
struct instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Isin: Instrument identification number
struct isin {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Length: Length of the message block including the header and all payload messages
struct length_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Data Group: Identity of the market data group the payload messages relate to
struct market_data_group {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Market Order
struct market_order {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Message Count: Number of payload messages that will follow the header
struct message_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Length of message including this field
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
        time_message = 84,
        system_event_message = 83,
        symbol_directory_message = 82,
        symbol_status_message = 72,
        add_order_message = 65,
        add_attributed_order_message = 70,
        order_deleted_message = 68,
        order_modified_message = 85,
        order_book_clear_message = 121,
        order_executed_message = 69,
        order_executed_with_price_size_message = 67,
        trade_message = 80,
        auction_trade_message = 81,
        auction_info_message = 73,
        statistics_message = 119,
        top_of_book_message = 113,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Named Market Order
struct named_market_order {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
struct nanosecond {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New End Time: New time the session will end. Will only be stamped if the session change was not in the original schedule e.g. AESP auction call or unscheduled session.
struct new_end_time {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// New Price: New limit price of the order.
struct new_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New Quantity: New displayed quantity of the order.
struct new_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Close Price Indicator
struct open_close_price_indicator {
    enum class type : char {
        ut = 'A',
        at = 'B',
        mid_of_bbo = 'C',
        last_at = 'D',
        last_ut = 'E',
        manual = 'F',
        derived_from_previous_close = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Id: Unique identifier of the order.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Quantity: Quantity that will be matched at the indicative price.
struct paired_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Previous Close Price: Previous Close Price of instrument
struct previous_close_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: Limit price of the order.
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Printable
struct printable {
    enum class type : char {
        non_printable = 'N',
        printable = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Priority Flag
struct priority_flag {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Private Rfq
struct private_rfq {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Quantity: Displayed quantity of the order.
struct quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reason: Reason for the manual session change or the trading halt.
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reserved 1: Reserved field
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 10: Reserved field
struct reserved_10 {
    using type = std::span<const std::byte, 10>;
    static constexpr std::size_t size = 10;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 10> value_;
};

// Reserved 4: Reserved field
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved A: Reserved field
struct reserved_a {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved B: Reserved field
struct reserved_b {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved Byte: Reserved field
struct reserved_byte {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Unused 1: Unused
struct second_unused_1 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Seconds: Number of seconds since midnight. Midnight will be in terms of the local time for the server (i.e. not UTC).
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

    // seconds on a day: its seconds since midnight, Europe/London, as UTC Unix nanoseconds
    std::int64_t utc(const calendar::Day& day) const { return calendar::midnight(day, "Europe/London").utc(static_cast<std::int64_t>(value()) * 1000000000); }

  protected:
    type value_;
};

// Sedol: Instrument identification number
struct sedol {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Segment: Segment the instrument is assigned to.
struct segment {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Sell Limit Price: Best offer price. Will contain zero if there are no visible limit orders on the sell side
struct sell_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sell Limit Size: Cumulative visible size at best offer price. Will contain zero if there are no visible limit orders on the sell side
struct sell_limit_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence Number: Sequence number of the first payload message
struct sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Change Reason
struct session_change_reason {
    enum class type : std::uint8_t {
        scheduled_transition = 0,
        extended_by_market_ops = 1,
        shortened_by_market_ops = 2,
        market_order_imbalance = 3,
        price_outside_range = 4,
        unavailable_recovery_service_only = 9,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side
struct side {
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

// Statistic Type
struct statistic_type {
    enum class type : char {
        opening_price = 'O',
        closing_price = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sub Book
struct sub_book {
    enum class type : std::uint8_t {
        regular_trades = 0,
        rfq_trades = 11,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Symbol Status: This field will contain a space if the instrument is active.
struct symbol_status {
    enum class type : char {
        active = ' ',
        suspended = 'S',
        inactive = 'a',
        halt = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Match Id: Unique identifier of the trade.
struct trade_match_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Status
struct trading_status {
    enum class type : char {
        active = ' ',
        halt = 'H',
        regular_trading_start_of_trade_reporting = 'T',
        opening_first_auction_call = 'a',
        post_close = 'b',
        market_close_system_shutdown = 'c',
        closing_auction_call = 'd',
        aesp_auction_call = 'e',
        resume_auction_call = 'f',
        pause = 'l',
        pre_mandatory = 'm',
        mandatory = 'n',
        post_mandatory = 'o',
        edsp_auction_call = 'q',
        periodic_auction_call = 'r',
        end_trade_reporting = 't',
        no_active_session = 'w',
        end_of_post_close = 'x',
        closing_price_crossing = 'u',
        scheduled_level_1_only_auction = 'G',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying: Reserved for future use
struct underlying {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Unused 1: Unused
struct unused_1 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Unused 2: Unused
struct unused_2 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xC0ULL;
    static constexpr int shift = 6;
};

// Unused 4: Unused
struct unused_4 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x1EULL;
    static constexpr int shift = 1;
};

// Unused 5: Unused
struct unused_5 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x1FULL;
    static constexpr int shift = 0;
};

// Unused 6: Unused
struct unused_6 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFCULL;
    static constexpr int shift = 2;
};

// Unused 8: Unused
struct unused_8 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFFULL;
    static constexpr int shift = 0;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Top Of Book Message: Used to disseminate top of book changes when the instrument is in a scheduled level 1 only auction.
struct top_of_book_message {
    static constexpr std::string_view name = "Top Of Book Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        instrument_id,
        buy_limit_price,
        buy_limit_size,
        sell_limit_price,
        sell_limit_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(instrument_id);
    MITCHFIELD(buy_limit_price);
    MITCHFIELD(buy_limit_size);
    MITCHFIELD(sell_limit_price);
    MITCHFIELD(sell_limit_size);
};

static_assert(sizeof(top_of_book_message) == top_of_book_message::size, "top_of_book_message lies over its bytes exactly");

// Statistics Reserved: Reserved for future use
struct statistics_reserved {
    static constexpr std::string_view name = "Statistics Reserved";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(statistics_reserved) == statistics_reserved::size, "statistics_reserved lies over its bytes exactly");

// Statistics Message: Used to disseminate official Opening and Closing prices
struct statistics_message {
    static constexpr std::string_view name = "Statistics Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        instrument_id,
        reserved_a,
        reserved_b,
        statistic_type,
        price,
        open_close_price_indicator,
        statistics_reserved>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(statistic_type);
    MITCHFIELD(price);
    MITCHFIELD(open_close_price_indicator);
    MITCHFIELD(statistics_reserved);
};

static_assert(sizeof(statistics_message) == statistics_message::size, "statistics_message lies over its bytes exactly");

// Auction Info Message: 9 Used to disseminate the indicative auction price and the tradable quantity and imbalance at this price.
struct auction_info_message {
    static constexpr std::string_view name = "Auction Info Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        paired_quantity,
        reserved_4,
        reserved_1,
        instrument_id,
        reserved_a,
        reserved_b,
        price,
        auction_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(paired_quantity);
    MITCHFIELD(reserved_4);
    MITCHFIELD(reserved_1);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(price);
    MITCHFIELD(auction_type);
};

static_assert(sizeof(auction_info_message) == auction_info_message::size, "auction_info_message lies over its bytes exactly");

// Pt Mod Flags: Indicates a trade cancellation or amendment
struct pt_mod_flags {
    static constexpr std::string_view name = "Pt Mod Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(pt_mod_flags) == pt_mod_flags::size, "pt_mod_flags lies over its bytes exactly");

// Auction Trade Message: Sent to report details of an auction
struct auction_trade_message {
    static constexpr std::string_view name = "Auction Trade Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        quantity,
        instrument_id,
        reserved_a,
        reserved_b,
        price,
        trade_match_id,
        auction_type,
        pt_mod_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(quantity);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(price);
    MITCHFIELD(trade_match_id);
    MITCHFIELD(auction_type);
    MITCHFIELD(pt_mod_flags);
};

static_assert(sizeof(auction_trade_message) == auction_trade_message::size, "auction_trade_message lies over its bytes exactly");

// Trade Message: Sent if a non-display order is fully or partially filled.
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        executed_quantity,
        instrument_id,
        reserved_a,
        reserved_b,
        price,
        trade_match_id,
        cross_type,
        sub_book,
        pt_mod_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(executed_quantity);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(price);
    MITCHFIELD(trade_match_id);
    MITCHFIELD(cross_type);
    MITCHFIELD(sub_book);
    MITCHFIELD(pt_mod_flags);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Executed With Price Size Message: Sent if a displayed order is fully or partially filled at a price that is different from its displayed price.
struct order_executed_with_price_size_message {
    static constexpr std::string_view name = "Order Executed With Price Size Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        order_id,
        executed_quantity,
        display_quantity,
        trade_match_id,
        printable,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(order_id);
    MITCHFIELD(executed_quantity);
    MITCHFIELD(display_quantity);
    MITCHFIELD(trade_match_id);
    MITCHFIELD(printable);
    MITCHFIELD(price);
};

static_assert(sizeof(order_executed_with_price_size_message) == order_executed_with_price_size_message::size, "order_executed_with_price_size_message lies over its bytes exactly");

// Order Executed Message: Indicates that the displayed portion of an order is fully or partially filled at its displayed price.
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        order_id,
        executed_quantity,
        trade_match_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(order_id);
    MITCHFIELD(executed_quantity);
    MITCHFIELD(trade_match_id);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Order Book Clear Flags
struct order_book_clear_flags {
    static constexpr std::string_view name = "Order Book Clear Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(order_book_clear_flags) == order_book_clear_flags::size, "order_book_clear_flags lies over its bytes exactly");

// Order Book Clear Message: Sent to instruct recipients to remove all orders from the order book for the specified instrument.
struct order_book_clear_message {
    static constexpr std::string_view name = "Order Book Clear Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        instrument_id,
        reserved_a,
        reserved_b,
        order_book_clear_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(order_book_clear_flags);
};

static_assert(sizeof(order_book_clear_message) == order_book_clear_message::size, "order_book_clear_message lies over its bytes exactly");

// Order Modified Flags
struct order_modified_flags {
    static constexpr std::string_view name = "Order Modified Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(order_modified_flags) == order_modified_flags::size, "order_modified_flags lies over its bytes exactly");

// Order Modified Message: Indicates that the displayed quantity or price of a displayed order has been updated.
struct order_modified_message {
    static constexpr std::string_view name = "Order Modified Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        order_id,
        new_quantity,
        new_price,
        order_modified_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(order_id);
    MITCHFIELD(new_quantity);
    MITCHFIELD(new_price);
    MITCHFIELD(order_modified_flags);
};

static_assert(sizeof(order_modified_message) == order_modified_message::size, "order_modified_message lies over its bytes exactly");

// Order Deleted Flags
struct order_deleted_flags {
    static constexpr std::string_view name = "Order Deleted Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(order_deleted_flags) == order_deleted_flags::size, "order_deleted_flags lies over its bytes exactly");

// Order Deleted Message: Sent to indicate that the remainder of a displayed order is cancelled.
struct order_deleted_message {
    static constexpr std::string_view name = "Order Deleted Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        order_id,
        order_deleted_flags,
        instrument_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(order_id);
    MITCHFIELD(order_deleted_flags);
    MITCHFIELD(instrument_id);
};

static_assert(sizeof(order_deleted_message) == order_deleted_message::size, "order_deleted_message lies over its bytes exactly");

// Add Attributed Order Flags
struct add_attributed_order_flags {
    static constexpr std::string_view name = "Add Attributed Order Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(add_attributed_order_flags) == add_attributed_order_flags::size, "add_attributed_order_flags lies over its bytes exactly");

// Add Attributed Order Message: Indicates that a named order is added to the order book.
struct add_attributed_order_message {
    static constexpr std::string_view name = "Add Attributed Order Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        order_id,
        side,
        quantity,
        instrument_id,
        reserved_a,
        reserved_b,
        price,
        attribution,
        add_attributed_order_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(order_id);
    MITCHFIELD(side);
    MITCHFIELD(quantity);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(price);
    MITCHFIELD(attribution);
    MITCHFIELD(add_attributed_order_flags);
};

static_assert(sizeof(add_attributed_order_message) == add_attributed_order_message::size, "add_attributed_order_message lies over its bytes exactly");

// Add Order Flags
struct add_order_flags {
    static constexpr std::string_view name = "Add Order Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(add_order_flags) == add_order_flags::size, "add_order_flags lies over its bytes exactly");

// Add Order Message: Sent to indicate that an anonymous limit or market order is added to the order book.
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        order_id,
        side,
        quantity,
        instrument_id,
        reserved_a,
        reserved_b,
        price,
        add_order_flags,
        reserved_10>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(order_id);
    MITCHFIELD(side);
    MITCHFIELD(quantity);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(price);
    MITCHFIELD(add_order_flags);
    MITCHFIELD(reserved_10);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Symbol Status Flags
struct symbol_status_flags {
    static constexpr std::string_view name = "Symbol Status Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(symbol_status_flags) == symbol_status_flags::size, "symbol_status_flags lies over its bytes exactly");

// Symbol Status Message: Indicates the trading session (pre-opening, regular trading, etc.) that currently applies to an instrument.
struct symbol_status_message {
    static constexpr std::string_view name = "Symbol Status Message";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        instrument_id,
        reserved_a,
        reserved_b,
        trading_status,
        symbol_status_flags,
        reason,
        session_change_reason,
        new_end_time,
        book_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(trading_status);
    MITCHFIELD(symbol_status_flags);
    MITCHFIELD(reason);
    MITCHFIELD(session_change_reason);
    MITCHFIELD(new_end_time);
    MITCHFIELD(book_type);
};

static_assert(sizeof(symbol_status_message) == symbol_status_message::size, "symbol_status_message lies over its bytes exactly");

// Symbol Directory Message: Used to disseminate information (symbol, segment, ISIN, underlying, etc.) on each instrument
struct symbol_directory_message {
    static constexpr std::string_view name = "Symbol Directory Message";
    static constexpr std::size_t size = 63;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        instrument_id,
        reserved_a,
        reserved_b,
        symbol_status,
        isin,
        sedol,
        segment,
        underlying,
        currency,
        reserved_byte,
        reserved_4,
        previous_close_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(instrument_id);
    MITCHFIELD(reserved_a);
    MITCHFIELD(reserved_b);
    MITCHFIELD(symbol_status);
    MITCHFIELD(isin);
    MITCHFIELD(sedol);
    MITCHFIELD(segment);
    MITCHFIELD(underlying);
    MITCHFIELD(currency);
    MITCHFIELD(reserved_byte);
    MITCHFIELD(reserved_4);
    MITCHFIELD(previous_close_price);
};

static_assert(sizeof(symbol_directory_message) == symbol_directory_message::size, "symbol_directory_message lies over its bytes exactly");

// System Event Message: Sent to indicate the start and end of the day.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanosecond,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(nanosecond);
    MITCHFIELD(event_code);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Time Message: Sent by the server for every second for which at least one application message is generated.
struct time_message {
    static constexpr std::string_view name = "Time Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        seconds>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(seconds);
};

static_assert(sizeof(time_message) == time_message::size, "time_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Mitch Udp Message Header
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
    MITCHFIELD(message_length);
    MITCHFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Unit Header
struct unit_header {
    static constexpr std::string_view name = "Unit Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        length_type,
        message_count,
        market_data_group,
        sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MITCHFIELD(length_type);
    MITCHFIELD(message_count);
    MITCHFIELD(market_data_group);
    MITCHFIELD(sequence_number);
};

static_assert(sizeof(unit_header) == unit_header::size, "unit_header lies over its bytes exactly");

// Packet: Mitch Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MITCHSEQUENCE(message);
};

#pragma pack(pop)

} // namespace lseg::millennium::level2::mitch::v11_9
