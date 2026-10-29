// OtcMarkets LinkAts Multicast Link 4.3 Template Meta Programming

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
#ifndef LINKFIELD
#define LINKFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef LINKSEQUENCE
#define LINKSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

// a day is placed in its timezone by the C++20 time zone database (std::chrono::locate_zone),
// which needs nothing installed: MSVC reads the ICU data Windows 10 (1903) and later ship;
// libstdc++ 14 and libc++ read the system's IANA data
#if !defined(__cpp_lib_chrono) || __cpp_lib_chrono < 201907L
#error "a time of day placed on a day needs the C++20 time zone database (std::chrono::locate_zone)"
#endif

// A time of day counted from midnight (Epoch Midnight) names no day: placed on one, in the zone the
// model states its midnight in, it is an instant, UTC Unix nanoseconds
namespace otcmarkets::linkats::multicast::link::v4_3::calendar {

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

namespace otcmarkets::linkats::multicast::link::v4_3 {

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

// Adr Level: ADR level. Applies to ADR/GDR/NYRS securities only.
struct adr_level {
    using type = std::string_view;
    static constexpr std::size_t size = 15;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 15> value_;
};

// Adr Ratio: ADR ratio with 6 decimal places assumed. Applies to ADR/GDR/NYRS securities only.
struct adr_ratio {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Bid Wanted
struct ask_bid_wanted {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Ask Num Priced Mp: Number of market participants at the inside ask price level.
struct ask_num_priced_mp {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Price: Ask price, with 6 decimal places assumed.
struct ask_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Priced
struct ask_priced {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Ask Qap: Specifies the access fee or rebate for the ask. Positive values (1 to 30) indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates no rebate or access fee.
struct ask_qap {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Size: Number of shares on the ask.
struct ask_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Time Milli: Ask timestamp in milliseconds from UTC epoch.
struct ask_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Unsolicited
struct ask_unsolicited {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Asset Class: Asset class indicator.
struct asset_class {
    enum class type : std::uint8_t {
        equity = 1,
        fixed_income = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bb Quoted: Indicates if the security is quoted on the OTC Bulletin Board interdealer quotation system.
struct bb_quoted {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Bid Ask Wanted
struct bid_ask_wanted {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Bid Auto Ex: Bid Auto Execution enabled
struct bid_auto_ex {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Bid Num Priced Mp: Number of market participants at the inside bid price level.
struct bid_num_priced_mp {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price: Bid price, with 6 decimal places assumed.
struct bid_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Priced
struct bid_priced {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Bid Qap: Specifies the access fee or rebate for the bid. Positive values (1 to 30) indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates no rebate or access fee.
struct bid_qap {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size: Number of shares on the bid.
struct bid_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Time Milli: Bid timestamp in milliseconds from UTC epoch.
struct bid_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Unsolicited
struct bid_unsolicited {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Callable: Security is callable
struct callable {
    using type = bool;
    static constexpr std::uint64_t mask = 0x400ULL;
    static constexpr int shift = 10;
};

// Callable Date Milli: Callable date in milliseconds from UTC epoch. Applies to fixed income securities only.
struct callable_date_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Caveat Emptor Warning: Indicates whether a Caveat Emptor warning has been applied to the security.
struct caveat_emptor_warning {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Channel Seq Num: Monotonically increasing message sequence number at the channel level.
struct channel_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Coupon: Coupon with 6 decimal places assumed. Applies to fixed income securities only.
struct coupon {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cusip: CUSIP identifier.
struct cusip {
    using type = std::string_view;
    static constexpr std::size_t size = 9;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 9> value_;
};

// Deprecated: Deprecated field. Spaces will be sent in the message.
struct deprecated {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Disclosure Status: Current disclosure status of the issuer.
struct disclosure_status {
    enum class type : std::uint8_t {
        no_disclosure = 0,
        current_information = 2,
        limited_information = 3,
        no_information = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Heartbeat: A Heartbeat is sent if no business level message has been published for more than a second
struct heartbeat {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Inside Action: Inside action indicator.
struct inside_action {
    enum class type : std::uint8_t {
        add = 2,
        delete_value = 3,
        spin = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Inside Id: Unique Inside ID.
struct inside_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Inside Time Milli: Inside timestamp in milliseconds from UTC epoch.
struct inside_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Investment Grade: Security is investment grade
struct investment_grade {
    using type = bool;
    static constexpr std::uint64_t mask = 0x100ULL;
    static constexpr int shift = 8;
};

// Irregular: Indicates an irregular trade
struct irregular {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Issuer Name
struct issuer_name {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr issuer_name(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Issuer Size: Size of the IssuerName field. If zero, IssuerName is not present.
struct issuer_size {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Update Milli: Milliseconds from UTC epoch.
struct last_update_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Close: Anticipated market close time in milliseconds since UTC epoch.
struct market_close {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Close Time Milli: Market close time in milliseconds since UTC epoch midnight.
struct market_close_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Msg Ct: Total message count for the trading day.
struct market_msg_ct {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Open: Market open time in milliseconds since UTC epoch.
struct market_open {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maturity Date Milli: Maturity date in milliseconds from UTC epoch. Applies to fixed income securities only.
struct maturity_date_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Count: Number of messages in packet
struct message_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Size: Size of message in bytes
struct message_size {
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
    enum class type : std::uint8_t {
        start_of_spin_message = 11,
        end_of_spin_message = 12,
        market_open_message = 13,
        market_close_message = 14,
        security_message = 9,
        quote_message = 1,
        quote_update_message = 2,
        inside_message = 3,
        inside_update_message = 4,
        reference_price_message = 7,
        reference_price_update_message = 8,
        extended_security_message = 15,
        extended_security_no_cusip_message = 16,
        trade_message = 17,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mpid: Market Participant ID owning the quote (always 4 characters).
struct mpid {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Nms Conditional Quote: Displayed quote size is a round lot at least two times greater than the minimum round lot size and cannot be partially filled.
struct nms_conditional_quote {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Num Priced Mp: Number of market participants at the inside price level.
struct num_priced_mp {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Auto Ex: Offer Auto Execution enabled
struct offer_auto_ex {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Otc Issuer Id: Unique issuer ID.
struct otc_issuer_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Otc Link Ecn Eligible: Indicates if the security is eligible for OTC Link ECN.
struct otc_link_ecn_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Otc Link Messaging Disabled: Indicates whether OTC Link messaging is disabled for the security.
struct otc_link_messaging_disabled {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Packet Milli: Milliseconds since local time midnight (EST/EDT)
struct packet_milli {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

    // packet_milli on a day: its milliseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(value()) * 1000000); }

  protected:
    type value_;
};

// Packet Size: Size of packet in bytes
struct packet_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Par Value: Par value with 6 decimal places assumed. 0 indicates not available.
struct par_value {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Piggyback: Rule 15c2-11 “Piggyback” exempt security status flag.
struct piggyback {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Price: Price with 6 decimal places assumed.
struct price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Primary Market: Primary trading market or exchange.
struct primary_market {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Qap: Specifies the access fee or rebate for the bid/offer. Positive values (1 to 30) indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates no rebate or access fee.
struct qap {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Qualified Institutional Buyers Only: Indicates if the security may only be quoted unsolicited for Qualified Institutional Buyers.
struct qualified_institutional_buyers_only {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Quote Action: Quote action indicator.
struct quote_action {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Id: Unique Quote ID.
struct quote_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Reference Id: Numeric value (0–64,999) assigned by the quote owner (FIX Tag 9670), used for correlation purposes.
struct quote_reference_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Saturated: Quote should be considered for inside price
struct quote_saturated {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Quote Time Milli: Quote timestamp in milliseconds from UTC epoch.
struct quote_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reference Price Action: Reference price action indicator.
struct reference_price_action {
    enum class type : std::uint8_t {
        add = 2,
        delete_value = 3,
        spin = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reference Price Id: Unique Reference Price ID.
struct reference_price_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Replay: Packet contains replay messages
struct replay {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Reporting Status: Reporting status.
struct reporting_status {
    enum class type : char {
        alternative_reporting = 'A',
        bank_thrift = 'B',
        sec_reporting = 'F',
        international_reporting = 'G',
        insurance_company = 'I',
        no_reporting = 'N',
        other_reporting = 'O',
        finra_reporting = 'R',
        sec_investment_company = 'V',
        sec_reg_a = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reserved 4: Reserved Extended Quote Flag Bits
struct reserved_4 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xF0ULL;
    static constexpr int shift = 4;
};

// Reserved 5: Reserved for future use
struct reserved_5 {
    using type = std::uint16_t;
    static constexpr std::uint64_t mask = 0xF800ULL;
    static constexpr int shift = 11;
};

// Reserved 7: Reserved Trade Status Bits
struct reserved_7 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFEULL;
    static constexpr int shift = 1;
};

// Saturation Eligible: Indicates if a security is eligible to have their quotes saturated.
struct saturation_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Security Action: Security action indicator.
struct security_action {
    enum class type : std::uint8_t {
        update = 1,
        add = 2,
        delete_value = 3,
        spin = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Desc: Security description.
struct security_desc {
    using type = std::string_view;
    static constexpr std::size_t size = 25;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 25> value_;
};

// Security Detail Name
struct security_detail_name {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr security_detail_name(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Security Detail Size: Size of the SecurityDetail field. If zero, SecurityDetail is not present.
struct security_detail_size {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Id: Unique security ID issued by OTC Markets.
struct security_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Status: Security status.
struct security_status {
    enum class type : char {
        active = 'A',
        quote_only = 'Q',
        suspended = 'S',
        halted = 'H',
        internal_halt = 'I',
        revoked = 'R',
        deleted = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type: Indicates the type of security.
struct security_type {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Seq Num: Channel specific Sequence number of packet
struct seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seq Num Reset: indicates that the channel sequence numbers are being reset to 1
struct seq_num_reset {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Short Name: Short name of the security.
struct short_name {
    using type = std::string_view;
    static constexpr std::size_t size = 25;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 25> value_;
};

// Size: Number of shares.
struct size_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Spin End Time Milli: Milliseconds since UTC epoch.
struct spin_end_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Spin Last Seq Num: Last sequence number applied to this spin.
struct spin_last_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Spin Msg Ct: Total number of messages in the spin.
struct spin_msg_ct {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Spin Start Time Milli: Milliseconds since UTC epoch.
struct spin_start_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Spin Type
struct spin_type {
    enum class type : std::uint8_t {
        reference = 1,
        market_data = 2,
        opening = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sponsored Status: Security is sponsored
struct sponsored_status {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// State: Open or Closed
struct state {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Symbol: Ticker symbol. Fixed income symbols may not have a symbol. For these securities, the security ID or CUSIP (Reference Data Security Message) must be used as an identifier.
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Test: Packet contains test messages
struct test {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Tier: The market tier assigned by OTC Markets Group.
struct tier {
    enum class type : std::uint8_t {
        no_tier = 0,
        otcqxus_premier = 1,
        otcqxus = 2,
        otcqx_international_premier = 5,
        otcqx_international = 6,
        otcqb = 10,
        otcbb_only = 11,
        pink_current = 20,
        pink_limited = 21,
        pink_no_information = 22,
        grey_market = 30,
        expert_market = 40,
        otc_bonds = 50,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Time Milli: Timestamp in milliseconds from UTC epoch.
struct time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Action: Trade action indicator.
struct trade_action {
    enum class type : std::uint8_t {
        add = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Flags: Trade flags bitmap.
struct trade_flags {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: Unique Trade ID.
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price: Trade price with 6 decimal places assumed.
struct trade_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Size: Number of shares traded.
struct trade_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Time Milli: Trade timestamp in milliseconds from UTC epoch.
struct trade_time_milli {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Flat: Security is trading flat
struct trading_flat {
    using type = bool;
    static constexpr std::uint64_t mask = 0x200ULL;
    static constexpr int shift = 9;
};

// Unsolicited Only: Indicates if the security may only be quoted unsolicited.
struct unsolicited_only {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Update Side: Ask or Bid
struct update_side {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Trade Status: Trade Status Information
struct trade_status {
    static constexpr std::string_view name = "Trade Status";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(trade_status) == trade_status::size, "trade_status lies over its bytes exactly");

// Trade Message: A Trade Message is created for every trade that occurs on OTC Markets OTC Link ATS.
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        trade_id,
        trade_action,
        trade_flags,
        security_id,
        trade_status,
        deprecated,
        trade_price,
        trade_size,
        trade_time_milli>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(trade_id);
    LINKFIELD(trade_action);
    LINKFIELD(trade_flags);
    LINKFIELD(security_id);
    LINKFIELD(trade_status);
    LINKFIELD(deprecated);
    LINKFIELD(trade_price);
    LINKFIELD(trade_size);
    LINKFIELD(trade_time_milli);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Issuer Section 1
struct issuer_section_1 {
    static constexpr std::string_view name = "Issuer Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        issuer_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(issuer_size);
};

static_assert(sizeof(issuer_section_1) == issuer_section_1::size, "issuer_section_1 lies over its bytes exactly");

// Issuer
struct issuer {
    static constexpr std::string_view name = "Issuer";
    static constexpr bool is_message = false;
};

// Security Detail Section 1
struct security_detail_section_1 {
    static constexpr std::string_view name = "Security Detail Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_detail_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(security_detail_size);
};

static_assert(sizeof(security_detail_section_1) == security_detail_section_1::size, "security_detail_section_1 lies over its bytes exactly");

// Security Detail: SecurityDetail
struct security_detail {
    static constexpr std::string_view name = "Security Detail";
    static constexpr bool is_message = false;
};

// Security Flags: Notes security level attributes
struct security_flags {
    static constexpr std::string_view name = "Security Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(security_flags) == security_flags::size, "security_flags lies over its bytes exactly");

// Extended Security No Cusip Message Section 1
struct extended_security_no_cusip_message_section_1 {
    static constexpr std::string_view name = "Extended Security No Cusip Message Section 1";
    static constexpr std::size_t size = 150;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        symbol,
        last_update_milli,
        security_action,
        otc_issuer_id,
        security_desc,
        short_name,
        asset_class,
        security_type,
        primary_market,
        security_id,
        security_flags,
        tier,
        reporting_status,
        disclosure_status,
        security_status,
        par_value,
        coupon,
        maturity_date_milli,
        callable_date_milli,
        adr_ratio,
        adr_level>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(symbol);
    LINKFIELD(last_update_milli);
    LINKFIELD(security_action);
    LINKFIELD(otc_issuer_id);
    LINKFIELD(security_desc);
    LINKFIELD(short_name);
    LINKFIELD(asset_class);
    LINKFIELD(security_type);
    LINKFIELD(primary_market);
    LINKFIELD(security_id);
    LINKFIELD(security_flags);
    LINKFIELD(tier);
    LINKFIELD(reporting_status);
    LINKFIELD(disclosure_status);
    LINKFIELD(security_status);
    LINKFIELD(par_value);
    LINKFIELD(coupon);
    LINKFIELD(maturity_date_milli);
    LINKFIELD(callable_date_milli);
    LINKFIELD(adr_ratio);
    LINKFIELD(adr_level);
};

static_assert(sizeof(extended_security_no_cusip_message_section_1) == extended_security_no_cusip_message_section_1::size, "extended_security_no_cusip_message_section_1 lies over its bytes exactly");

// Extended Security No Cusip Message: Extended Security message without CUSIP information. This message may be sent at system startup or intraday following a technical outage.
struct extended_security_no_cusip_message {
    static constexpr std::string_view name = "Extended Security No Cusip Message";
    static constexpr bool is_message = true;
};

// Extended Security Flags: Notes security level attributes
struct extended_security_flags {
    static constexpr std::string_view name = "Extended Security Flags";
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    type value_;
};

static_assert(sizeof(extended_security_flags) == extended_security_flags::size, "extended_security_flags lies over its bytes exactly");

// Extended Security Message Section 1
struct extended_security_message_section_1 {
    static constexpr std::string_view name = "Extended Security Message Section 1";
    static constexpr std::size_t size = 151;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        symbol,
        last_update_milli,
        security_action,
        otc_issuer_id,
        security_desc,
        short_name,
        asset_class,
        security_type,
        primary_market,
        security_id,
        extended_security_flags,
        tier,
        reporting_status,
        disclosure_status,
        security_status,
        par_value,
        coupon,
        maturity_date_milli,
        callable_date_milli,
        adr_ratio,
        adr_level>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(symbol);
    LINKFIELD(last_update_milli);
    LINKFIELD(security_action);
    LINKFIELD(otc_issuer_id);
    LINKFIELD(security_desc);
    LINKFIELD(short_name);
    LINKFIELD(asset_class);
    LINKFIELD(security_type);
    LINKFIELD(primary_market);
    LINKFIELD(security_id);
    LINKFIELD(extended_security_flags);
    LINKFIELD(tier);
    LINKFIELD(reporting_status);
    LINKFIELD(disclosure_status);
    LINKFIELD(security_status);
    LINKFIELD(par_value);
    LINKFIELD(coupon);
    LINKFIELD(maturity_date_milli);
    LINKFIELD(callable_date_milli);
    LINKFIELD(adr_ratio);
    LINKFIELD(adr_level);
};

static_assert(sizeof(extended_security_message_section_1) == extended_security_message_section_1::size, "extended_security_message_section_1 lies over its bytes exactly");

// Extended Security Message Section 2
struct extended_security_message_section_2 {
    static constexpr std::string_view name = "Extended Security Message Section 2";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        cusip>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(cusip);
};

static_assert(sizeof(extended_security_message_section_2) == extended_security_message_section_2::size, "extended_security_message_section_2 lies over its bytes exactly");

// Extended Security Message: Extended Security message providing additional security and issuer attributes.
struct extended_security_message {
    static constexpr std::string_view name = "Extended Security Message";
    static constexpr bool is_message = true;
};

// Quote Flags: Quote Information
struct quote_flags {
    static constexpr std::string_view name = "Quote Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(quote_flags) == quote_flags::size, "quote_flags lies over its bytes exactly");

// Reference Price Update Message: Quote update information for the Reference Price channel.
struct reference_price_update_message {
    static constexpr std::string_view name = "Reference Price Update Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        reference_price_id,
        quote_flags,
        price,
        size_type,
        time_milli>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(reference_price_id);
    LINKFIELD(quote_flags);
    LINKFIELD(price);
    LINKFIELD(size_type);
    LINKFIELD(time_milli);
};

static_assert(sizeof(reference_price_update_message) == reference_price_update_message::size, "reference_price_update_message lies over its bytes exactly");

// Reference Price Message: This message is sent on the Reference Prices Channel. Size will always be set to 1.
struct reference_price_message {
    static constexpr std::string_view name = "Reference Price Message";
    static constexpr std::size_t size = 54;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        reference_price_id,
        reference_price_action,
        quote_flags,
        security_id,
        ask_price,
        ask_size,
        ask_time_milli,
        bid_price,
        bid_size,
        bid_time_milli>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(reference_price_id);
    LINKFIELD(reference_price_action);
    LINKFIELD(quote_flags);
    LINKFIELD(security_id);
    LINKFIELD(ask_price);
    LINKFIELD(ask_size);
    LINKFIELD(ask_time_milli);
    LINKFIELD(bid_price);
    LINKFIELD(bid_size);
    LINKFIELD(bid_time_milli);
};

static_assert(sizeof(reference_price_message) == reference_price_message::size, "reference_price_message lies over its bytes exactly");

// Inside Update Message: Quote update information for the Quote Inside channel and the Quote Inside with Global OTC data channel.
struct inside_update_message {
    static constexpr std::string_view name = "Inside Update Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        inside_id,
        quote_flags,
        price,
        size_type,
        inside_time_milli,
        num_priced_mp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(inside_id);
    LINKFIELD(quote_flags);
    LINKFIELD(price);
    LINKFIELD(size_type);
    LINKFIELD(inside_time_milli);
    LINKFIELD(num_priced_mp);
};

static_assert(sizeof(inside_update_message) == inside_update_message::size, "inside_update_message lies over its bytes exactly");

// Inside Message: This message is sent on the Quote Inside Channel and the Quote Inside with Global OTC data channel.
struct inside_message {
    static constexpr std::string_view name = "Inside Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        inside_id,
        inside_action,
        quote_flags,
        security_id,
        ask_price,
        ask_size,
        ask_time_milli,
        bid_price,
        bid_size,
        bid_time_milli,
        ask_num_priced_mp,
        bid_num_priced_mp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(inside_id);
    LINKFIELD(inside_action);
    LINKFIELD(quote_flags);
    LINKFIELD(security_id);
    LINKFIELD(ask_price);
    LINKFIELD(ask_size);
    LINKFIELD(ask_time_milli);
    LINKFIELD(bid_price);
    LINKFIELD(bid_size);
    LINKFIELD(bid_time_milli);
    LINKFIELD(ask_num_priced_mp);
    LINKFIELD(bid_num_priced_mp);
};

static_assert(sizeof(inside_message) == inside_message::size, "inside_message lies over its bytes exactly");

// Extended Quote Flags: Extended Quote Information
struct extended_quote_flags {
    static constexpr std::string_view name = "Extended Quote Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(extended_quote_flags) == extended_quote_flags::size, "extended_quote_flags lies over its bytes exactly");

// Quote Update Message: Quote update information for the Quote Book channel and the Quote Book with Global OTC data channel.
struct quote_update_message {
    static constexpr std::string_view name = "Quote Update Message";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        quote_id,
        quote_flags,
        price,
        size_type,
        qap,
        quote_time_milli,
        quote_reference_id,
        extended_quote_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(quote_id);
    LINKFIELD(quote_flags);
    LINKFIELD(price);
    LINKFIELD(size_type);
    LINKFIELD(qap);
    LINKFIELD(quote_time_milli);
    LINKFIELD(quote_reference_id);
    LINKFIELD(extended_quote_flags);
};

static_assert(sizeof(quote_update_message) == quote_update_message::size, "quote_update_message lies over its bytes exactly");

// Quote Message: This message is sent on the Quote Book channel and the Quote Book with Global OTC data channel.
struct quote_message {
    static constexpr std::string_view name = "Quote Message";
    static constexpr std::size_t size = 63;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        quote_id,
        quote_action,
        quote_flags,
        security_id,
        mpid,
        ask_price,
        ask_size,
        ask_qap,
        ask_time_milli,
        bid_price,
        bid_size,
        bid_qap,
        bid_time_milli,
        quote_reference_id,
        extended_quote_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(quote_id);
    LINKFIELD(quote_action);
    LINKFIELD(quote_flags);
    LINKFIELD(security_id);
    LINKFIELD(mpid);
    LINKFIELD(ask_price);
    LINKFIELD(ask_size);
    LINKFIELD(ask_qap);
    LINKFIELD(ask_time_milli);
    LINKFIELD(bid_price);
    LINKFIELD(bid_size);
    LINKFIELD(bid_qap);
    LINKFIELD(bid_time_milli);
    LINKFIELD(quote_reference_id);
    LINKFIELD(extended_quote_flags);
};

static_assert(sizeof(quote_message) == quote_message::size, "quote_message lies over its bytes exactly");

// Security Message: The Security Message is included in all the quote channels and provides basic security attribute information.
struct security_message {
    static constexpr std::string_view name = "Security Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        symbol,
        last_update_milli,
        security_action,
        asset_class,
        security_id,
        security_flags,
        tier,
        reporting_status,
        security_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(symbol);
    LINKFIELD(last_update_milli);
    LINKFIELD(security_action);
    LINKFIELD(asset_class);
    LINKFIELD(security_id);
    LINKFIELD(security_flags);
    LINKFIELD(tier);
    LINKFIELD(reporting_status);
    LINKFIELD(security_status);
};

static_assert(sizeof(security_message) == security_message::size, "security_message lies over its bytes exactly");

// Market Close Message: This message is sent out at 5 PM on all channels. The message can also be sent mid-day if a technical outage causes a temporary closure of the market.
struct market_close_message {
    static constexpr std::string_view name = "Market Close Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        market_close_time_milli,
        market_msg_ct>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(market_close_time_milli);
    LINKFIELD(market_msg_ct);
};

static_assert(sizeof(market_close_message) == market_close_message::size, "market_close_message lies over its bytes exactly");

// Market Open Message: This message is sent out at 6 AM on all channels. The message can also be sent mid-day if a technical outage caused a temporary closure of the market.
struct market_open_message {
    static constexpr std::string_view name = "Market Open Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        market_open,
        market_close>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(market_open);
    LINKFIELD(market_close);
};

static_assert(sizeof(market_open_message) == market_open_message::size, "market_open_message lies over its bytes exactly");

// End Of Spin Message: This message appears on all quote channels and indicates the end of a spin message cycle.
struct end_of_spin_message {
    static constexpr std::string_view name = "End Of Spin Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        spin_type,
        spin_msg_ct,
        spin_end_time_milli,
        spin_last_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(spin_type);
    LINKFIELD(spin_msg_ct);
    LINKFIELD(spin_end_time_milli);
    LINKFIELD(spin_last_seq_num);
};

static_assert(sizeof(end_of_spin_message) == end_of_spin_message::size, "end_of_spin_message lies over its bytes exactly");

// Start Of Spin Message: This message appears on all quote channels and indicates the beginning of a spin message cycle.
struct start_of_spin_message {
    static constexpr std::string_view name = "Start Of Spin Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_seq_num,
        spin_type,
        spin_start_time_milli,
        spin_last_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(channel_seq_num);
    LINKFIELD(spin_type);
    LINKFIELD(spin_start_time_milli);
    LINKFIELD(spin_last_seq_num);
};

static_assert(sizeof(start_of_spin_message) == start_of_spin_message::size, "start_of_spin_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Otc Udp Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_size,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(message_size);
    LINKFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Heartbeat Packet
struct heartbeat_packet {
    static constexpr std::string_view name = "Heartbeat Packet";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Message Block: Branch
struct message_block {
    static constexpr std::string_view name = "Message Block";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    LINKSEQUENCE(message);
};

// Packet Flag: Packet Flags
struct packet_flag {
    static constexpr std::string_view name = "Packet Flag";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(packet_flag) == packet_flag::size, "packet_flag lies over its bytes exactly");

// Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_size,
        seq_num,
        packet_flag,
        message_count,
        packet_milli>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    LINKFIELD(packet_size);
    LINKFIELD(seq_num);
    LINKFIELD(packet_flag);
    LINKFIELD(message_count);
    LINKFIELD(packet_milli);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Otc Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace otcmarkets::linkats::multicast::link::v4_3
