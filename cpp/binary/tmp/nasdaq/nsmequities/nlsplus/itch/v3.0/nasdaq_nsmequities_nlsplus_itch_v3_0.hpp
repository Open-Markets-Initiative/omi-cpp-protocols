// Nasdaq NsmEquities NlsPlus Itch 3.0 Template Meta Programming

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
#ifndef ITCHFIELD
#define ITCHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef ITCHSEQUENCE
#define ITCHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

// a day is placed in its timezone by the C++20 time zone database (std::chrono::locate_zone),
// which needs nothing installed: MSVC reads the ICU data Windows 10 (1903) and later ship;
// libstdc++ 14 and libc++ read the system's IANA data
#if !defined(__cpp_lib_chrono) || __cpp_lib_chrono < 201907L
#error "a time of day placed on a day needs the C++20 time zone database (std::chrono::locate_zone)"
#endif

// A time of day counted from midnight (Epoch Midnight) names no day: placed on one, in the zone the
// model states its midnight in, it is an instant, UTC Unix nanoseconds
namespace nasdaq::nsmequities::nlsplus::itch::v3_0::calendar {

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

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

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

// Adjusted Closing Price: Denotes the adjusted previous close price for the issue
struct adjusted_closing_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Adjusted Closing Price Long: Denotes the adjusted previous close price for the issue
struct adjusted_closing_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Authenticity: Denotes if an issue or quoting participant record is set up in Nasdaq systems in a live, test or demo state
struct authenticity {
    enum class type : char {
        production = 'P',
        test = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bloomberg Id: Bloomberg global identifier for the issue
struct bloomberg_id {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Breached Level: Denotes the Mwcb level that was breached
struct breached_level {
    enum class type : char {
        level_1 = '1',
        level_2 = '2',
        level_3 = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Consolidated Closing Price: The consolidated closing price for the issue for the trading day
struct consolidated_closing_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Closing Price Long: The consolidated closing price for the issue for the trading day
struct consolidated_closing_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated High Price: The consolidated high price for the issue for the trading day
struct consolidated_high_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated High Price Long: The consolidated high price for the issue for the trading day
struct consolidated_high_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Low Price: The consolidated low price for the issue for the trading day
struct consolidated_low_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Low Price Long: The consolidated low price for the issue for the trading day
struct consolidated_low_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Open Price: The consolidated opening price for the issue for the trading day
struct consolidated_open_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Open Price Long: The consolidated opening price for the issue for the trading day
struct consolidated_open_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Volume: Reflects the volume for the Issue Symbol as reported on the consolidated market data feed at the time the trade message was generated
struct consolidated_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Extended Hours Or Sold Code: Used for Extended Hours or Sold codes
struct corrected_extended_hours_or_sold_code {
    enum class type : char {
        extended_hours_trade = 'T',
        extended_hours_trade_reported_late = 'U',
        sold_last = 'L',
        sold_out_of_sequence = 'Z',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Corrected Nav Offset Amount: The corrected Nav offset applied to the Proxy Price
struct corrected_nav_offset_amount {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Proxy Price: The proxy price reported on the corrected trade transaction
struct corrected_proxy_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Settlement Type: Used for Settlement Type information
struct corrected_settlement_type {
    enum class type : char {
        regular_settlement = '@',
        cash_settlement = 'C',
        next_day_settlement = 'N',
        seller_settlement = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Corrected Special Sale Condition: Used for special sale condition codes. This field is case sensitive
struct corrected_special_sale_condition {
    enum class type : char {
        acquisition = 'A',
        bunched = 'B',
        distribution = 'D',
        price_variation_transaction = 'H',
        nasdaq_official_close_price = 'M',
        prior_reference_price = 'P',
        nasdaq_official_opening_price = 'Q',
        split_trade = 'S',
        contingent_trade = 'V',
        average_price_trade = 'W',
        cross_trade = 'X',
        odd_lot_execution = 'o',
        odd_lot_cross_execution = 'x',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Corrected Trade Control Number: Indicates the source's internal control number associated with the corrected trade transaction
struct corrected_trade_control_number {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Corrected Trade Price: The price reported on the corrected trade transaction
struct corrected_trade_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Trade Price Long: The price reported on the corrected trade transaction
struct corrected_trade_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Trade Size: The number of shares reported on the corrected trade transaction
struct corrected_trade_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Trade Through Exemption: Used for Sec Regulation Nms Trade Through Exemption codes
struct corrected_trade_through_exemption {
    enum class type : char {
        intermarket_sweep = 'F',
        opening_print = 'O',
        derivative_priced = '4',
        re_opening_print = '5',
        closing_print = '6',
        qualified_contingent_trade = '7',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Current Trading State: Reflects the current trading state for the issue
struct current_trading_state {
    enum class type : char {
        halted = 'H',
        paused = 'P',
        quotation_only = 'Q',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Etp Flag: Indicates whether the security is an exchange traded product
struct etp_flag {
    enum class type : char {
        etp = 'Y',
        not_etp = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Etp Leverage Factor: Tracks the integral relationship of the Etp to the underlying index
struct etp_leverage_factor {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code: Denotes the Nls Plus type of system event for which the message is being generated
struct event_code {
    enum class type : char {
        start_of_transmissions = 'O',
        start_of_system_hours = 'S',
        start_of_market_hours = 'Q',
        end_of_market_hours = 'M',
        end_of_system_hours = 'E',
        end_of_transmissions = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Extended Hours Or Sold Code: Used for Extended Hours or Sold codes
struct extended_hours_or_sold_code {
    enum class type : char {
        extended_hours_trade = 'T',
        extended_hours_trade_reported_late = 'U',
        sold_last = 'L',
        sold_out_of_sequence = 'Z',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Financial Status Indicator: For Nasdaq listed issues, denotes when an issue is flagged as deficient, delinquent, bankrupt or in a compliance period
struct financial_status_indicator {
    enum class type : char {
        deficient = 'D',
        delinquent = 'E',
        bankrupt = 'Q',
        suspended = 'S',
        deficient_and_bankrupt = 'G',
        deficient_and_delinquent = 'H',
        delinquent_and_bankrupt = 'J',
        deficient_delinquent_and_bankrupt = 'K',
        creations_or_redemptions_suspended = 'C',
        normal = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Inverse Indicator: Indicates the directional relationship between the Etp and the underlying index
struct inverse_indicator {
    enum class type : char {
        inverse = 'Y',
        not_inverse = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Flag: Indicates if the Nasdaq security is set up for Ipo release
struct ipo_flag {
    enum class type : char {
        new_ipo = 'Y',
        not_new_ipo = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Price: Denotes the Ipo price to be used for intraday net change calculations
struct ipo_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ipo Quotation Release Qualifier: Denotes whether the release time is anticipated or the release has been cancelled or postponed
struct ipo_quotation_release_qualifier {
    enum class type : char {
        anticipated = 'A',
        cancelled = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Quotation Release Time: Denotes the Ipo release time, in seconds since midnight, for quotation to the nearest second
struct ipo_quotation_release_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Issue Classification: Identifies the security class for the issue as assigned by Nasdaq
struct issue_classification {
    enum class type : char {
        american_depositary_share = 'A',
        bond = 'B',
        common_stock = 'C',
        depository_receipt = 'F',
        rule_144_a = 'I',
        limited_partnership = 'L',
        notes = 'N',
        ordinary_share = 'O',
        preferred_stock = 'P',
        other_securities = 'Q',
        right = 'R',
        shares_of_beneficial_interest = 'S',
        convertible_debenture = 'T',
        unit = 'U',
        units_of_beneficial_interest = 'V',
        warrant = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Issue Sub Type: Identifies the security sub type for the issue as assigned by Nasdaq
struct issue_sub_type {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the trade report is being generated
struct issue_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Level 1: Denotes the Mwcb Level 1 value
struct level_1 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Level 2: Denotes the Mwcb Level 2 value
struct level_2 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Level 3: Denotes the Mwcb Level 3 value
struct level_3 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Luld Reference Price Tier: Indicates which Limit Up / Limit Down price band calculation parameter is to be used for the instrument
struct luld_reference_price_tier {
    enum class type : char {
        tier_1 = '1',
        tier_2 = '2',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Category: Indicates the listing market or listing market tier for the issue
struct market_category {
    enum class type : char {
        nasdaq_global_select_market = 'Q',
        nasdaq_global_market = 'G',
        nasdaq_capital_market = 'S',
        nyse = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        nyse_texas = 'M',
        bats = 'Z',
        iex = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Center: Denotes the Nasdaq market system that generated the original trade report message
struct market_center {
    enum class type : char {
        nasdaq = 'Q',
        trf_carteret = 'L',
        trf_chicago = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Code: Denotes the market centre for which the operational halt is declared
struct market_code {
    enum class type : char {
        nasdaq = 'Q',
        bx = 'B',
        psx = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Count: Number of messages to follow this header
struct message_count {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Length of data message not including this field
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: Code identifying this message type
struct message_type {
    enum class type : char {
        system_event_message = 'S',
        trade_report_message = 'T',
        long_form_trade_report_message = 't',
        next_shares_trade_report_message = 'M',
        trade_cancel_error_message = 'X',
        long_form_trade_cancel_error_message = 'x',
        next_shares_trade_cancel_error_message = 'O',
        trade_correction_message = 'C',
        long_form_trade_correction_message = 'c',
        next_shares_trade_correction_message = 'Z',
        stock_trading_action_message = 'H',
        stock_directory_message = 'R',
        reg_sho_short_sale_price_test_restricted_indicator_message = 'Y',
        adjusted_closing_price_message = 'G',
        long_form_adjusted_closing_price_message = 'g',
        end_of_day_trade_summary_message = 'J',
        long_form_end_of_day_trade_summary_message = 'j',
        next_shares_end_of_day_trade_summary_message = 'N',
        ipo_information_message = 'I',
        mwcb_decline_level_message = 'V',
        mwcb_status_message = 'W',
        ipo_quoting_period_update_message = 'K',
        operational_halt_message = 'h',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Nav Offset Amount: The Nav offset that should be applied to the Proxy Price
struct nav_offset_amount {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nav Offset Amount Closing: The Nav offset that should be applied to the consolidated closing proxy price
struct nav_offset_amount_closing {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nav Offset Amount High: The Nav offset that should be applied to the consolidated high proxy price
struct nav_offset_amount_high {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nav Offset Amount Low: The Nav offset that should be applied to the consolidated low proxy price
struct nav_offset_amount_low {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nav Offset Amount Open: The Nav offset that should be applied to the consolidated opening proxy price
struct nav_offset_amount_open {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Next Shares Symbol: Denotes the NextShares symbol for which the trade report is being generated
struct next_shares_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Operational Halt Action: Denotes whether the issue is operationally halted on the identified market or has resumed trading
struct operational_halt_action {
    enum class type : char {
        halted = 'H',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Original Extended Hours Or Sold Code: Used for Extended Hours or Sold codes
struct original_extended_hours_or_sold_code {
    enum class type : char {
        extended_hours_trade = 'T',
        extended_hours_trade_reported_late = 'U',
        sold_last = 'L',
        sold_out_of_sequence = 'Z',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Original Nav Offset Amount: The Nav offset originally applied to the Proxy Price
struct original_nav_offset_amount {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Proxy Price: The proxy price reported on the original trade transaction
struct original_proxy_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Settlement Type: Used for Settlement Type information
struct original_settlement_type {
    enum class type : char {
        regular_settlement = '@',
        cash_settlement = 'C',
        next_day_settlement = 'N',
        seller_settlement = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Original Special Sale Condition: Used for special sale condition codes. This field is case sensitive
struct original_special_sale_condition {
    enum class type : char {
        acquisition = 'A',
        bunched = 'B',
        distribution = 'D',
        price_variation_transaction = 'H',
        nasdaq_official_close_price = 'M',
        prior_reference_price = 'P',
        nasdaq_official_opening_price = 'Q',
        split_trade = 'S',
        contingent_trade = 'V',
        average_price_trade = 'W',
        cross_trade = 'X',
        odd_lot_execution = 'o',
        odd_lot_cross_execution = 'x',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Original Trade Control Number: Indicates the source's internal control number associated with the original trade transaction
struct original_trade_control_number {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Original Trade Price: The price reported on the original trade transaction
struct original_trade_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Trade Price Long: The price reported on the original trade transaction
struct original_trade_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Trade Size: The number of shares reported on the original trade transaction
struct original_trade_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Trade Through Exemption: Used for Sec Regulation Nms Trade Through Exemption codes
struct original_trade_through_exemption {
    enum class type : char {
        intermarket_sweep = 'F',
        opening_print = 'O',
        derivative_priced = '4',
        re_opening_print = '5',
        closing_print = '6',
        qualified_contingent_trade = '7',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Originating Market Center Identifier: Denotes the Nasdaq market system that generated the trade report message
struct originating_market_center_identifier {
    enum class type : char {
        nasdaq = 'Q',
        trf_carteret = 'L',
        trf_chicago = '2',
        bx = 'B',
        psx = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Proxy Price: Reported proxy price for the transaction
struct proxy_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reason: Reflects the Market Ops or Market Watch code for the trading state change
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reference For Net Change: Indicates the basis of the reference price for net change calculations
struct reference_for_net_change {
    enum class type : char {
        first_trade_price = 'F',
        underwriter_price = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reference Price: Denotes the reference price to be used for intraday net change calculations
struct reference_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reg Sho Action: Denotes the Reg Sho short sale price test restriction status for the issue
struct reg_sho_action {
    enum class type : char {
        no_price_test = '0',
        restriction_in_effect = '1',
        restriction_remains = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reserved: Reserved for future use; space filled in the initial release
struct reserved {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Round Lot Size: Denotes the number of shares that represent a round lot for the issue
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Round Lots Only: Indicates if Nasdaq system limits order entry for the issue
struct round_lots_only {
    enum class type : char {
        round_lots_only = 'Y',
        no_restriction = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Class: Indicates the primary listing market for the issue
struct security_class {
    enum class type : char {
        nasdaq = 'Q',
        nyse = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        nyse_texas = 'M',
        bats = 'Z',
        iex = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sequence Number: Sequence number of the first message to follow this header
struct sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session: Identity of the multicast session
struct session {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Settlement Type: Used for Settlement Type information
struct settlement_type {
    enum class type : char {
        regular_settlement = '@',
        cash_settlement = 'C',
        next_day_settlement = 'N',
        seller_settlement = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Short Sale Threshold Indicator: Indicates if a security is subject to mandatory close-out of short sales under Sec Rule 203(b)(3)
struct short_sale_threshold_indicator {
    enum class type : char {
        restricted = 'Y',
        not_restricted = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Special Sale Condition: Used for special sale condition codes. This field is case sensitive
struct special_sale_condition {
    enum class type : char {
        acquisition = 'A',
        bunched = 'B',
        distribution = 'D',
        price_variation_transaction = 'H',
        nasdaq_official_close_price = 'M',
        prior_reference_price = 'P',
        nasdaq_official_opening_price = 'Q',
        split_trade = 'S',
        contingent_trade = 'V',
        average_price_trade = 'W',
        cross_trade = 'X',
        odd_lot_execution = 'o',
        odd_lot_cross_execution = 'x',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stock: Denotes the security symbol for the issue in the Nasdaq execution system
struct stock {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Timestamp: Number of nanoseconds past midnight
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

    // timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(value())); }

  protected:
    std::array<std::byte, 6> value_;
};

// Tracking Number: Internal tracking number
struct tracking_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Control Number: Indicates the source's internal control number associated with the given trade transaction
struct trade_control_number {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Trade Price: The price associated with the trade transaction being reported
struct trade_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price Long: The price associated with the trade transaction being reported
struct trade_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Size: Indicates the reported number of shares on the trade transaction
struct trade_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Through Exemption: Used for Sec Regulation Nms Trade Through Exemption codes
struct trade_through_exemption {
    enum class type : char {
        intermarket_sweep = 'F',
        opening_print = 'O',
        derivative_priced = '4',
        re_opening_print = '5',
        closing_print = '6',
        qualified_contingent_trade = '7',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Operational Halt Message: Indicates the current operational status of a security to the trading community. An operational halt is specific to the market centre for which it is declared and does not interrupt trading of the instrument on any other market place.
struct operational_halt_message {
    static constexpr std::string_view name = "Operational Halt Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock,
        market_code,
        operational_halt_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock);
    ITCHFIELD(market_code);
    ITCHFIELD(operational_halt_action);
};

static_assert(sizeof(operational_halt_message) == operational_halt_message::size, "operational_halt_message lies over its bytes exactly");

// Ipo Quoting Period Update Message: Indicates the anticipated Ipo quotation release time of a security.
struct ipo_quoting_period_update_message {
    static constexpr std::string_view name = "Ipo Quoting Period Update Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock,
        ipo_quotation_release_time,
        ipo_quotation_release_qualifier,
        ipo_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock);
    ITCHFIELD(ipo_quotation_release_time);
    ITCHFIELD(ipo_quotation_release_qualifier);
    ITCHFIELD(ipo_price);
};

static_assert(sizeof(ipo_quoting_period_update_message) == ipo_quoting_period_update_message::size, "ipo_quoting_period_update_message lies over its bytes exactly");

// Mwcb Status Message: Informs the market that a market wide circuit breaker decline level has been breached.
struct mwcb_status_message {
    static constexpr std::string_view name = "Mwcb Status Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        breached_level>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(breached_level);
};

static_assert(sizeof(mwcb_status_message) == mwcb_status_message::size, "mwcb_status_message lies over its bytes exactly");

// Mwcb Decline Level Message: Informs the market of the daily market wide circuit breaker decline levels, disseminated at the start of the trading day.
struct mwcb_decline_level_message {
    static constexpr std::string_view name = "Mwcb Decline Level Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        level_1,
        level_2,
        level_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(level_1);
    ITCHFIELD(level_2);
    ITCHFIELD(level_3);
};

static_assert(sizeof(mwcb_decline_level_message) == mwcb_decline_level_message::size, "mwcb_decline_level_message lies over its bytes exactly");

// Ipo Information Message: Denotes the reference price to be used for intraday net change calculations for an issue.
struct ipo_information_message {
    static constexpr std::string_view name = "Ipo Information Message";
    static constexpr std::size_t size = 14;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        security_class,
        reference_for_net_change,
        reference_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(reference_for_net_change);
    ITCHFIELD(reference_price);
};

static_assert(sizeof(ipo_information_message) == ipo_information_message::size, "ipo_information_message lies over its bytes exactly");

// Next Shares End Of Day Trade Summary Message: Summarises the consolidated trading activity for a NextShares issue, each price paired with the Nav offset to apply to it.
struct next_shares_end_of_day_trade_summary_message {
    static constexpr std::string_view name = "Next Shares End Of Day Trade Summary Message";
    static constexpr std::size_t size = 49;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        market_category,
        consolidated_high_price,
        nav_offset_amount_high,
        consolidated_low_price,
        nav_offset_amount_low,
        consolidated_closing_price,
        nav_offset_amount_closing,
        consolidated_volume,
        consolidated_open_price,
        nav_offset_amount_open>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(market_category);
    ITCHFIELD(consolidated_high_price);
    ITCHFIELD(nav_offset_amount_high);
    ITCHFIELD(consolidated_low_price);
    ITCHFIELD(nav_offset_amount_low);
    ITCHFIELD(consolidated_closing_price);
    ITCHFIELD(nav_offset_amount_closing);
    ITCHFIELD(consolidated_volume);
    ITCHFIELD(consolidated_open_price);
    ITCHFIELD(nav_offset_amount_open);
};

static_assert(sizeof(next_shares_end_of_day_trade_summary_message) == next_shares_end_of_day_trade_summary_message::size, "next_shares_end_of_day_trade_summary_message lies over its bytes exactly");

// Long Form End Of Day Trade Summary Message: End of Day Trade Summary carrying eight byte prices.
struct long_form_end_of_day_trade_summary_message {
    static constexpr std::string_view name = "Long Form End Of Day Trade Summary Message";
    static constexpr std::size_t size = 49;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        market_category,
        consolidated_high_price_long,
        consolidated_low_price_long,
        consolidated_closing_price_long,
        consolidated_volume,
        consolidated_open_price_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(market_category);
    ITCHFIELD(consolidated_high_price_long);
    ITCHFIELD(consolidated_low_price_long);
    ITCHFIELD(consolidated_closing_price_long);
    ITCHFIELD(consolidated_volume);
    ITCHFIELD(consolidated_open_price_long);
};

static_assert(sizeof(long_form_end_of_day_trade_summary_message) == long_form_end_of_day_trade_summary_message::size, "long_form_end_of_day_trade_summary_message lies over its bytes exactly");

// End Of Day Trade Summary Message: Summarises the consolidated trading activity for an issue at the end of the trading day.
struct end_of_day_trade_summary_message {
    static constexpr std::string_view name = "End Of Day Trade Summary Message";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        market_category,
        consolidated_high_price,
        consolidated_low_price,
        consolidated_closing_price,
        consolidated_volume,
        consolidated_open_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(market_category);
    ITCHFIELD(consolidated_high_price);
    ITCHFIELD(consolidated_low_price);
    ITCHFIELD(consolidated_closing_price);
    ITCHFIELD(consolidated_volume);
    ITCHFIELD(consolidated_open_price);
};

static_assert(sizeof(end_of_day_trade_summary_message) == end_of_day_trade_summary_message::size, "end_of_day_trade_summary_message lies over its bytes exactly");

// Long Form Adjusted Closing Price Message: Adjusted Closing Price carrying an eight byte price.
struct long_form_adjusted_closing_price_message {
    static constexpr std::string_view name = "Long Form Adjusted Closing Price Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        security_class,
        adjusted_closing_price_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(adjusted_closing_price_long);
};

static_assert(sizeof(long_form_adjusted_closing_price_message) == long_form_adjusted_closing_price_message::size, "long_form_adjusted_closing_price_message lies over its bytes exactly");

// Adjusted Closing Price Message: Denotes the adjusted previous close price to be used for intraday net change calculations.
struct adjusted_closing_price_message {
    static constexpr std::string_view name = "Adjusted Closing Price Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        security_class,
        adjusted_closing_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(adjusted_closing_price);
};

static_assert(sizeof(adjusted_closing_price_message) == adjusted_closing_price_message::size, "adjusted_closing_price_message lies over its bytes exactly");

// Reg Sho Short Sale Price Test Restricted Indicator Message: Indicates the Reg Sho short sale price test restriction status for an issue, under Rule 201 of Regulation Sho.
struct reg_sho_short_sale_price_test_restricted_indicator_message {
    static constexpr std::string_view name = "Reg Sho Short Sale Price Test Restricted Indicator Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issue_symbol,
        reg_sho_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(issue_symbol);
    ITCHFIELD(reg_sho_action);
};

static_assert(sizeof(reg_sho_short_sale_price_test_restricted_indicator_message) == reg_sho_short_sale_price_test_restricted_indicator_message::size, "reg_sho_short_sale_price_test_restricted_indicator_message lies over its bytes exactly");

// Stock Directory Message: Identifies the securities eligible for the trading session, disseminated at the start of each day.
struct stock_directory_message {
    static constexpr std::string_view name = "Stock Directory Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock,
        market_category,
        financial_status_indicator,
        round_lot_size,
        round_lots_only,
        issue_classification,
        issue_sub_type,
        authenticity,
        short_sale_threshold_indicator,
        ipo_flag,
        luld_reference_price_tier,
        etp_flag,
        etp_leverage_factor,
        inverse_indicator,
        bloomberg_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock);
    ITCHFIELD(market_category);
    ITCHFIELD(financial_status_indicator);
    ITCHFIELD(round_lot_size);
    ITCHFIELD(round_lots_only);
    ITCHFIELD(issue_classification);
    ITCHFIELD(issue_sub_type);
    ITCHFIELD(authenticity);
    ITCHFIELD(short_sale_threshold_indicator);
    ITCHFIELD(ipo_flag);
    ITCHFIELD(luld_reference_price_tier);
    ITCHFIELD(etp_flag);
    ITCHFIELD(etp_leverage_factor);
    ITCHFIELD(inverse_indicator);
    ITCHFIELD(bloomberg_id);
};

static_assert(sizeof(stock_directory_message) == stock_directory_message::size, "stock_directory_message lies over its bytes exactly");

// Stock Trading Action Message: Indicates the current trading status of a security to the trading community. Clients should initialize all securities as halted at the start of the session.
struct stock_trading_action_message {
    static constexpr std::string_view name = "Stock Trading Action Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reserved,
        issue_symbol,
        security_class,
        current_trading_state,
        reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(reserved);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(current_trading_state);
    ITCHFIELD(reason);
};

static_assert(sizeof(stock_trading_action_message) == stock_trading_action_message::size, "stock_trading_action_message lies over its bytes exactly");

// Corrected Sale Condition Modifier: The sale condition modifier reported on the corrected trade transaction
struct corrected_sale_condition_modifier {
    static constexpr std::string_view name = "Corrected Sale Condition Modifier";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        corrected_settlement_type,
        corrected_trade_through_exemption,
        corrected_extended_hours_or_sold_code,
        corrected_special_sale_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(corrected_settlement_type);
    ITCHFIELD(corrected_trade_through_exemption);
    ITCHFIELD(corrected_extended_hours_or_sold_code);
    ITCHFIELD(corrected_special_sale_condition);
};

static_assert(sizeof(corrected_sale_condition_modifier) == corrected_sale_condition_modifier::size, "corrected_sale_condition_modifier lies over its bytes exactly");

// Original Sale Condition Modifier: The sale condition modifier reported on the original trade transaction
struct original_sale_condition_modifier {
    static constexpr std::string_view name = "Original Sale Condition Modifier";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        original_settlement_type,
        original_trade_through_exemption,
        original_extended_hours_or_sold_code,
        original_special_sale_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(original_settlement_type);
    ITCHFIELD(original_trade_through_exemption);
    ITCHFIELD(original_extended_hours_or_sold_code);
    ITCHFIELD(original_special_sale_condition);
};

static_assert(sizeof(original_sale_condition_modifier) == original_sale_condition_modifier::size, "original_sale_condition_modifier lies over its bytes exactly");

// Next Shares Trade Correction Message: Indicates that a previously reported NextShares trade transaction has been corrected.
struct next_shares_trade_correction_message {
    static constexpr std::string_view name = "Next Shares Trade Correction Message";
    static constexpr std::size_t size = 70;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        market_center,
        issue_symbol,
        security_class,
        original_trade_control_number,
        original_proxy_price,
        original_nav_offset_amount,
        original_trade_size,
        original_sale_condition_modifier,
        corrected_trade_control_number,
        corrected_proxy_price,
        corrected_nav_offset_amount,
        corrected_trade_size,
        corrected_sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(market_center);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(original_trade_control_number);
    ITCHFIELD(original_proxy_price);
    ITCHFIELD(original_nav_offset_amount);
    ITCHFIELD(original_trade_size);
    ITCHFIELD(original_sale_condition_modifier);
    ITCHFIELD(corrected_trade_control_number);
    ITCHFIELD(corrected_proxy_price);
    ITCHFIELD(corrected_nav_offset_amount);
    ITCHFIELD(corrected_trade_size);
    ITCHFIELD(corrected_sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(next_shares_trade_correction_message) == next_shares_trade_correction_message::size, "next_shares_trade_correction_message lies over its bytes exactly");

// Long Form Trade Correction Message: Trade Correction carrying eight byte original and corrected trade prices.
struct long_form_trade_correction_message {
    static constexpr std::string_view name = "Long Form Trade Correction Message";
    static constexpr std::size_t size = 70;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        issue_symbol,
        security_class,
        original_trade_control_number,
        original_trade_price_long,
        original_trade_size,
        original_sale_condition_modifier,
        corrected_trade_control_number,
        corrected_trade_price_long,
        corrected_trade_size,
        corrected_sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(original_trade_control_number);
    ITCHFIELD(original_trade_price_long);
    ITCHFIELD(original_trade_size);
    ITCHFIELD(original_sale_condition_modifier);
    ITCHFIELD(corrected_trade_control_number);
    ITCHFIELD(corrected_trade_price_long);
    ITCHFIELD(corrected_trade_size);
    ITCHFIELD(corrected_sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(long_form_trade_correction_message) == long_form_trade_correction_message::size, "long_form_trade_correction_message lies over its bytes exactly");

// Trade Correction Message: Indicates that a previously reported trade transaction has been corrected, carrying both the original and the corrected transaction.
struct trade_correction_message {
    static constexpr std::string_view name = "Trade Correction Message";
    static constexpr std::size_t size = 62;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        issue_symbol,
        security_class,
        original_trade_control_number,
        original_trade_price,
        original_trade_size,
        original_sale_condition_modifier,
        corrected_trade_control_number,
        corrected_trade_price,
        corrected_trade_size,
        corrected_sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(original_trade_control_number);
    ITCHFIELD(original_trade_price);
    ITCHFIELD(original_trade_size);
    ITCHFIELD(original_sale_condition_modifier);
    ITCHFIELD(corrected_trade_control_number);
    ITCHFIELD(corrected_trade_price);
    ITCHFIELD(corrected_trade_size);
    ITCHFIELD(corrected_sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(trade_correction_message) == trade_correction_message::size, "trade_correction_message lies over its bytes exactly");

// Next Shares Trade Cancel Error Message: Indicates that a previously reported NextShares trade transaction has been cancelled or was reported in error.
struct next_shares_trade_cancel_error_message {
    static constexpr std::string_view name = "Next Shares Trade Cancel Error Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        market_center,
        issue_symbol,
        security_class,
        original_trade_control_number,
        original_proxy_price,
        original_nav_offset_amount,
        original_trade_size,
        original_sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(market_center);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(original_trade_control_number);
    ITCHFIELD(original_proxy_price);
    ITCHFIELD(original_nav_offset_amount);
    ITCHFIELD(original_trade_size);
    ITCHFIELD(original_sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(next_shares_trade_cancel_error_message) == next_shares_trade_cancel_error_message::size, "next_shares_trade_cancel_error_message lies over its bytes exactly");

// Long Form Trade Cancel Error Message: Trade Cancel/Error carrying an eight byte original trade price.
struct long_form_trade_cancel_error_message {
    static constexpr std::string_view name = "Long Form Trade Cancel Error Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        issue_symbol,
        security_class,
        original_trade_control_number,
        original_trade_price_long,
        original_trade_size,
        original_sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(original_trade_control_number);
    ITCHFIELD(original_trade_price_long);
    ITCHFIELD(original_trade_size);
    ITCHFIELD(original_sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(long_form_trade_cancel_error_message) == long_form_trade_cancel_error_message::size, "long_form_trade_cancel_error_message lies over its bytes exactly");

// Trade Cancel Error Message: Indicates that a previously reported trade transaction has been cancelled or was reported in error.
struct trade_cancel_error_message {
    static constexpr std::string_view name = "Trade Cancel Error Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        issue_symbol,
        security_class,
        original_trade_control_number,
        original_trade_price,
        original_trade_size,
        original_sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(original_trade_control_number);
    ITCHFIELD(original_trade_price);
    ITCHFIELD(original_trade_size);
    ITCHFIELD(original_sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(trade_cancel_error_message) == trade_cancel_error_message::size, "trade_cancel_error_message lies over its bytes exactly");

// Sale Condition Modifier: Sale condition modifier, consisting of four levels
struct sale_condition_modifier {
    static constexpr std::string_view name = "Sale Condition Modifier";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        settlement_type,
        trade_through_exemption,
        extended_hours_or_sold_code,
        special_sale_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(settlement_type);
    ITCHFIELD(trade_through_exemption);
    ITCHFIELD(extended_hours_or_sold_code);
    ITCHFIELD(special_sale_condition);
};

static_assert(sizeof(sale_condition_modifier) == sale_condition_modifier::size, "sale_condition_modifier lies over its bytes exactly");

// Next Shares Trade Report Message: Relays trade transactions for NextShares exchange traded managed funds, reported as a proxy price with the Nav offset to apply to it.
struct next_shares_trade_report_message {
    static constexpr std::string_view name = "Next Shares Trade Report Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        next_shares_symbol,
        security_class,
        trade_control_number,
        proxy_price,
        trade_size,
        nav_offset_amount,
        sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(next_shares_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(trade_control_number);
    ITCHFIELD(proxy_price);
    ITCHFIELD(trade_size);
    ITCHFIELD(nav_offset_amount);
    ITCHFIELD(sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(next_shares_trade_report_message) == next_shares_trade_report_message::size, "next_shares_trade_report_message lies over its bytes exactly");

// Long Form Trade Report Message: Trade Report carrying an eight byte trade price, used when the price breaches the maximum value the four byte form can carry.
struct long_form_trade_report_message {
    static constexpr std::string_view name = "Long Form Trade Report Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        issue_symbol,
        security_class,
        trade_control_number,
        trade_price_long,
        trade_size,
        sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(trade_control_number);
    ITCHFIELD(trade_price_long);
    ITCHFIELD(trade_size);
    ITCHFIELD(sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(long_form_trade_report_message) == long_form_trade_report_message::size, "long_form_trade_report_message lies over its bytes exactly");

// Trade Report Message: Relays Nasdaq execution system and Trf trade transactions reported for the current business day. Nasdaq reports only one side of a trade execution on the Nls Plus feed.
struct trade_report_message {
    static constexpr std::string_view name = "Trade Report Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        originating_market_center_identifier,
        issue_symbol,
        security_class,
        trade_control_number,
        trade_price,
        trade_size,
        sale_condition_modifier,
        consolidated_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(originating_market_center_identifier);
    ITCHFIELD(issue_symbol);
    ITCHFIELD(security_class);
    ITCHFIELD(trade_control_number);
    ITCHFIELD(trade_price);
    ITCHFIELD(trade_size);
    ITCHFIELD(sale_condition_modifier);
    ITCHFIELD(consolidated_volume);
};

static_assert(sizeof(trade_report_message) == trade_report_message::size, "trade_report_message lies over its bytes exactly");

// System Event Message: System Event Messages is used to signal key market or data feed control events.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(event_code);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        tracking_number,
        timestamp,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(message_length);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Itch Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// End Of Session
struct end_of_session {
    static constexpr std::string_view name = "End Of Session";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
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
    ITCHSEQUENCE(message);
};

// Packet Header: Itch Mold Udp 64 Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        session,
        sequence_number,
        message_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(session);
    ITCHFIELD(sequence_number);
    ITCHFIELD(message_count);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Itch Mold Udp 64 Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
