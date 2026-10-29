// Nasdaq NomOptions Itto Itch 4.0.2025 Template Meta Programming

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
namespace nasdaq::nomoptions::itto::itch::v4_0_2025::calendar {

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

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

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

// Accepted Sequence Number: The sequence number in ASCII of the next Sequenced Message to be sent. Left padded with spaces.
struct accepted_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::number<type>(raw(), fill); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::string_view raw() const noexcept { return tmp::trimmed_front(value_, fill); }

  protected:
    std::array<char, 20> value_;
};

// Accepted Session: The session ID of the session that is now logged into. Left padded with spaces.
struct accepted_session {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed_front(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Ask: The display ask price of the new quote.
struct ask {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Price Long: The display ask price of the replaced quote.
struct ask_price_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Price Short: The display ask price of the new quote. NOTE: When converted to a decimal format, this price is in fixed point format with 3 whole number places followed by 2 decimal digits.
struct ask_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Reference Number: The ask reference number associated with the new quote
struct ask_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Size Long: The ask contracts of the new quote.
struct ask_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Size Short: The ask contracts of the new quote.
struct ask_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Id: Uniquely identifies the Auction for the trading day.
struct auction_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Type: Type of Auction:
struct auction_type {
    enum class type : char {
        opening = 'O',
        reopening = 'R',
        price_improvement = 'P',
        exposure = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bid: The display bid price of the new quote.
struct bid {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Long: The display bid price of the replaced quote.
struct bid_price_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Short: The display bid price of the new quote. NOTE: When converted to a decimal format, this price is in fixed point format with 3 whole number places followed by 2 decimal digits.
struct bid_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Reference Number: The bid reference number associated with the new quote.
struct bid_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Long: The bid contracts of the new quote.
struct bid_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Short: The bid contracts of the new quote.
struct bid_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Sell Indicator: The type of non-display order on the book being matched.
struct buy_sell_indicator {
    enum class type : char {
        buy = 'B',
        sell = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Cancelled Contracts: The number of contracts to be removed from the display size of the order as the result of a cancellation.
struct cancelled_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Change Reason
struct change_reason {
    enum class type : char {
        user = 'U',
        reprice = 'R',
        suspend = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Client Packet Type: Code identifying this packet type sent by the client
struct client_packet_type {
    enum class type : char {
        debug_packet = '+',
        login_request_packet = 'L',
        unsequenced_data_packet = 'U',
        client_heartbeat_packet = 'R',
        logout_request_packet = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Cross Number: Trade Group Id. Ties together all trades of a given atomic transaction in the matching engine.
struct cross_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Type: The NASDAQ auction session for which the message is being generated.
struct cross_type {
    enum class type : char {
        nasdaq_opening_reopening = 'O',
        price_improvement = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Current Trading State: Reflects the current trading state for the options security in the NASDAQ Options Market. The allowable values are:
struct current_trading_state {
    enum class type : char {
        halt = 'H',
        trading = 'T',
        buy_side_trading_suspended = 'B',
        sell_side_trading_suspended = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Customer Firm Indicator: For Order Exposure (AuctionType=I) only. Indicates the order capacity:
struct customer_firm_indicator {
    enum class type : char {
        customer = 'C',
        firm_joint = 'F',
        on_floor = 'M',
        professional = 'P',
        broker_dealer_non_registered = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Debug Text: Free form human readable text
struct debug_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr debug_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// End Of Replay Sequence Number: Use this sequence number to resume on the real time Mold channel.
struct end_of_replay_sequence_number {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Event Code: Refer to System Event Codes below
struct event_code {
    enum class type : char {
        start_of_messages = 'O',
        start_of_system_hours = 'S',
        start_of_opening_process = 'Q',
        end_of_normal_hours_processing = 'N',
        end_of_late_hours_processing = 'L',
        end_of_system_hours = 'E',
        end_of_messages = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Contracts: The number of contracts executed.
struct executed_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Date: Day of the Month of expiration (1-31)
struct expiration_date {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Month: Expiration Month (1-12)
struct expiration_month {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Year: Last two digits of the year of the option expiration
struct expiration_year {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Explicit Strike Price: Explicit strike price. Refer to Data Types for field processing notes.
struct explicit_strike_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Direction: Indicates the market side of the imbalance
struct imbalance_direction {
    enum class type : char {
        buy = 'B',
        sell = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Price: The imbalance price. 0 for Price Improvement (PRISM) Auction
struct imbalance_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Volume: The imbalance volume.
struct imbalance_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Side: The type of order being added.
struct market_side {
    enum class type : char {
        buy = 'B',
        sell = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Number: Execution Id. Identifies the component of an execution. Unique for a given day. The match number is also referenced in the Trade Break Message.
struct match_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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
        options_directory_message = 'R',
        trading_action_message = 'H',
        security_open_message = 'O',
        add_order_message_short_message_form = 'a',
        add_order_message_long_form_message = 'A',
        add_quote_message_short_form_message = 'j',
        add_quote_message_long_form_message = 'J',
        single_side_executed_message = 'E',
        single_side_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        single_side_replace_message_short_form = 'u',
        single_side_replace_message_long_form = 'U',
        single_side_delete_message = 'D',
        single_side_change_message = 'G',
        quote_replace_message_short_form = 'k',
        quote_replace_message_long_form = 'K',
        quote_delete_message = 'Y',
        options_trade_messages_non_auction = 'P',
        options_cross_trade_message = 'Q',
        broken_trade_order_executed_message = 'B',
        noii_message = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mpv: Minimum Price Variation for this option. See Notes below for further explanation:
struct mpv {
    enum class type : char {
        everywhere = 'E',
        scaled = 'S',
        pilot = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// New Reference Number: The new reference number associated with the new order.
struct new_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open State: The allowable values are:
struct open_state {
    enum class type : char {
        open = 'Y',
        closed = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Option Id: Option ID assigned daily, valid for trading day.
struct option_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Option Type
struct option_type {
    enum class type : char {
        call = 'C',
        put = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Options Closing Type: Denotes which System Event is used to trigger the option closing process.
struct options_closing_type {
    enum class type : char {
        normal = 'N',
        late = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Reference Number: The unique reference number assigned to the new order. The order reference number is Increasing, but not necessarily sequential.
struct order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Ask Reference Number: The original ask reference number that is replaced
struct original_ask_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Bid Reference Number: The original bid reference number that is replaced
struct original_bid_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Reference Number: The original reference number associated with the order being replaced.
struct original_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Length: Length of data message not including this field
struct packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Contracts: The total number of contracts that are eligible to be matched at the Current Reference Price. 0 for Price Improvement (PRISM) Auction.
struct paired_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Password: Login password
struct password {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Price Long: The display price of the new order being added to the book.
struct price_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Short: The display price of the new order being added to the book. NOTE: When converted to a decimal format, this price is in fixed point format with 3 whole number places followed by 2 decimal digits.
struct price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Printable: Indicates if the execution should be reflected on time and sale displays and volume calculations.
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

// Reference Number: The order/quote reference number associated with the executed order.
struct reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reject Reason Code: Login Reject Codes
struct reject_reason_code {
    enum class type : char {
        not_authorized = 'A',
        session_not_available = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Requested Sequence Number: Specifies the next sequence number in ASCII the client wants to receive upon connection, or 0 to start receiving the most recently generated message.
struct requested_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::number<type>(raw(), fill); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::string_view raw() const noexcept { return tmp::trimmed_front(value_, fill); }

  protected:
    std::array<char, 20> value_;
};

// Requested Session: Specifies the session the client would like to log into, or all blanks to log into the currently active session.
struct requested_session {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed_front(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Reserved 3: Reserved for future use
struct reserved_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Security Symbol: Denotes the security symbol.
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
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

// Sequenced Message Type: Value identifying sequenced message type
struct sequenced_message_type {
    enum class type : char {
        system_event_message = 'S',
        options_directory_message = 'R',
        trading_action_message = 'H',
        security_open_message = 'O',
        add_order_message_short_message_form = 'a',
        add_order_message_long_form_message = 'A',
        add_quote_message_short_form_message = 'j',
        add_quote_message_long_form_message = 'J',
        single_side_executed_message = 'E',
        single_side_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        single_side_replace_message_short_form = 'u',
        single_side_replace_message_long_form = 'U',
        single_side_delete_message = 'D',
        single_side_change_message = 'G',
        quote_replace_message_short_form = 'k',
        quote_replace_message_long_form = 'K',
        quote_delete_message = 'Y',
        options_trade_messages_non_auction = 'P',
        options_cross_trade_message = 'Q',
        broken_trade_order_executed_message = 'B',
        noii_message = 'I',
        end_of_replay_sequence_message = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Server Packet Type: Code identifying this packet type sent by the server
struct server_packet_type {
    enum class type : char {
        debug_packet = '+',
        login_accepted_packet = 'A',
        login_rejected_packet = 'J',
        sequenced_data_packet = 'S',
        server_heartbeat_packet = 'H',
        end_of_session_packet = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Source: Identifies the source of the Option, valid for the trading day
struct source {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Timestamp: Nanoseconds since midnight
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

// Tracking Number: Nasdaq Internal tracking number
struct tracking_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tradable: Denotes whether or not this option is tradable at the exchange. The allowable values are:
struct tradable {
    enum class type : char {
        not_tradable = 'N',
        is_tradable = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Symbol: Denotes the unique symbol assigned to the underlying security within exchange.
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 13;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 13> value_;
};

// Unsequenced Message: The unsequenced (client to server) message carried by the packet, opaque bytes unless an application source dispatches it
struct unsequenced_message {
    using type = std::span<const std::byte>;
    static constexpr bool dynamic = true;

    constexpr unsequenced_message(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { data_, length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Unsequenced Message Type: Value identifying unsequenced message type
struct unsequenced_message_type {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Username: Session username
struct username {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Volume Long: The total number of contracts of the new order being added to the book.
struct volume_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume Short: The total number of contracts of the new order being added to the book.
struct volume_short {
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

// Noii Message: For the NASDAQ Opening Auction, NASDAQ will begin the dissemination of NOII messages for a put or a call option five minutes prior to the start of opening process event and two minutes prior to the halt resumption (reopening) process event.
struct noii_message {
    static constexpr std::string_view name = "Noii Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        auction_id,
        auction_type,
        paired_contracts,
        imbalance_direction,
        option_id,
        imbalance_price,
        imbalance_volume,
        customer_firm_indicator,
        reserved_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(auction_id);
    ITCHFIELD(auction_type);
    ITCHFIELD(paired_contracts);
    ITCHFIELD(imbalance_direction);
    ITCHFIELD(option_id);
    ITCHFIELD(imbalance_price);
    ITCHFIELD(imbalance_volume);
    ITCHFIELD(customer_firm_indicator);
    ITCHFIELD(reserved_3);
};

static_assert(sizeof(noii_message) == noii_message::size, "noii_message lies over its bytes exactly");

// Broken Trade Order Executed Message: The Broken Trade Message is sent whenever an execution on NASDAQ is broken. An execution may be broken if it is found to be “clearly erroneous” pursuant to NASDAQ’s Clearly Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated.
struct broken_trade_order_executed_message {
    static constexpr std::string_view name = "Broken Trade Order Executed Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        cross_number,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(cross_number);
    ITCHFIELD(match_number);
};

static_assert(sizeof(broken_trade_order_executed_message) == broken_trade_order_executed_message::size, "broken_trade_order_executed_message lies over its bytes exactly");

// Options Cross Trade Message: This message will also be used to report all executions within a price improvement (PRISM) auction.
struct options_cross_trade_message {
    static constexpr std::string_view name = "Options Cross Trade Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        option_id,
        cross_number,
        match_number,
        cross_type,
        price_long,
        volume_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(option_id);
    ITCHFIELD(cross_number);
    ITCHFIELD(match_number);
    ITCHFIELD(cross_type);
    ITCHFIELD(price_long);
    ITCHFIELD(volume_long);
};

static_assert(sizeof(options_cross_trade_message) == options_cross_trade_message::size, "options_cross_trade_message lies over its bytes exactly");

// Options Trade Messages Non Auction: This Options Trade Message is designed to provide execution details for normal match events involving non-displayable order types. (Note: There is a separate message for NASDAQ Option auction events.)
struct options_trade_messages_non_auction {
    static constexpr std::string_view name = "Options Trade Messages Non Auction";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        buy_sell_indicator,
        option_id,
        cross_number,
        match_number,
        price_long,
        volume_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(buy_sell_indicator);
    ITCHFIELD(option_id);
    ITCHFIELD(cross_number);
    ITCHFIELD(match_number);
    ITCHFIELD(price_long);
    ITCHFIELD(volume_long);
};

static_assert(sizeof(options_trade_messages_non_auction) == options_trade_messages_non_auction::size, "options_trade_messages_non_auction lies over its bytes exactly");

// Quote Delete Message: The message is sent when a single quote is being cancelled. All remaining contracts are no longer accessible so the quote should be removed from the book.
struct quote_delete_message {
    static constexpr std::string_view name = "Quote Delete Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        bid_reference_number,
        ask_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(bid_reference_number);
    ITCHFIELD(ask_reference_number);
};

static_assert(sizeof(quote_delete_message) == quote_delete_message::size, "quote_delete_message lies over its bytes exactly");

// Quote Replace Message Long Form: This message is sent whenever a quote on the book is replaced. The replaced quote has new sequence numbers on both sides. These new sequence numbers replace the prior sequence numbers on the quote.
struct quote_replace_message_long_form {
    static constexpr std::string_view name = "Quote Replace Message Long Form";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        original_bid_reference_number,
        bid_reference_number,
        original_ask_reference_number,
        ask_reference_number,
        bid_price_long,
        bid_size_long,
        ask_price_long,
        ask_size_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(original_bid_reference_number);
    ITCHFIELD(bid_reference_number);
    ITCHFIELD(original_ask_reference_number);
    ITCHFIELD(ask_reference_number);
    ITCHFIELD(bid_price_long);
    ITCHFIELD(bid_size_long);
    ITCHFIELD(ask_price_long);
    ITCHFIELD(ask_size_long);
};

static_assert(sizeof(quote_replace_message_long_form) == quote_replace_message_long_form::size, "quote_replace_message_long_form lies over its bytes exactly");

// Quote Replace Message Short Form: This message is sent whenever a quote on the book is replaced. The replaced quote has new sequence numbers on both sides. These new sequence numbers replace the prior sequence numbers on the quote.
struct quote_replace_message_short_form {
    static constexpr std::string_view name = "Quote Replace Message Short Form";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        original_bid_reference_number,
        bid_reference_number,
        original_ask_reference_number,
        ask_reference_number,
        bid_price_short,
        bid_size_short,
        ask_price_short,
        ask_size_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(original_bid_reference_number);
    ITCHFIELD(bid_reference_number);
    ITCHFIELD(original_ask_reference_number);
    ITCHFIELD(ask_reference_number);
    ITCHFIELD(bid_price_short);
    ITCHFIELD(bid_size_short);
    ITCHFIELD(ask_price_short);
    ITCHFIELD(ask_size_short);
};

static_assert(sizeof(quote_replace_message_short_form) == quote_replace_message_short_form::size, "quote_replace_message_short_form lies over its bytes exactly");

// Single Side Change Message: This message is sent whenever an order or a side of a quote is being updated for price and (or) contracts. The reference number associated with the order quote is unchanged.
struct single_side_change_message {
    static constexpr std::string_view name = "Single Side Change Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        reference_number,
        change_reason,
        price_long,
        volume_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(reference_number);
    ITCHFIELD(change_reason);
    ITCHFIELD(price_long);
    ITCHFIELD(volume_long);
};

static_assert(sizeof(single_side_change_message) == single_side_change_message::size, "single_side_change_message lies over its bytes exactly");

// Single Side Delete Message: The message is sent when an order or a side of a quote is being cancelled. All remaining contracts are no longer accessible so the side should be removed from the book.
struct single_side_delete_message {
    static constexpr std::string_view name = "Single Side Delete Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(reference_number);
};

static_assert(sizeof(single_side_delete_message) == single_side_delete_message::size, "single_side_delete_message lies over its bytes exactly");

// Single Side Replace Message Long Form: This message is sent whenever an order or one side of a quote on the book is replaced. The replacement has a new sequence number and replaces the prior sequence number.
struct single_side_replace_message_long_form {
    static constexpr std::string_view name = "Single Side Replace Message Long Form";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        original_reference_number,
        new_reference_number,
        price_long,
        volume_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(original_reference_number);
    ITCHFIELD(new_reference_number);
    ITCHFIELD(price_long);
    ITCHFIELD(volume_long);
};

static_assert(sizeof(single_side_replace_message_long_form) == single_side_replace_message_long_form::size, "single_side_replace_message_long_form lies over its bytes exactly");

// Single Side Replace Message Short Form: This message is sent whenever an order or one side of a quote on the book is replaced. The replacement has a new sequence number and replaces the prior sequence number.
struct single_side_replace_message_short_form {
    static constexpr std::string_view name = "Single Side Replace Message Short Form";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        original_reference_number,
        new_reference_number,
        price_short,
        volume_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(original_reference_number);
    ITCHFIELD(new_reference_number);
    ITCHFIELD(price_short);
    ITCHFIELD(volume_short);
};

static_assert(sizeof(single_side_replace_message_short_form) == single_side_replace_message_short_form::size, "single_side_replace_message_short_form lies over its bytes exactly");

// Order Cancel Message: This message is sent whenever an order on the book is modified as a result of a partial cancellation.
struct order_cancel_message {
    static constexpr std::string_view name = "Order Cancel Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        order_reference_number,
        cancelled_contracts>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(cancelled_contracts);
};

static_assert(sizeof(order_cancel_message) == order_cancel_message::size, "order_cancel_message lies over its bytes exactly");

// Single Side Executed With Price Message: These executions may be marked as non-printable. If the execution is marked as non-printed, it means that the contracts will be included into a later bulk print (e.g., in the case of auction executions). If a firm is looking to use the ITTO data in time-and-sales displays or volume calculations, NASDAQ recommends that firms ignore messages marked as non-printable to prevent double counting.
struct single_side_executed_with_price_message {
    static constexpr std::string_view name = "Single Side Executed With Price Message";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        reference_number,
        cross_number,
        match_number,
        printable,
        price_long,
        volume_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(reference_number);
    ITCHFIELD(cross_number);
    ITCHFIELD(match_number);
    ITCHFIELD(printable);
    ITCHFIELD(price_long);
    ITCHFIELD(volume_long);
};

static_assert(sizeof(single_side_executed_with_price_message) == single_side_executed_with_price_message::size, "single_side_executed_with_price_message lies over its bytes exactly");

// Single Side Executed Message: This message is sent whenever a Side order is executed in whole or in part. It is possible to receive several Single Side Executed Messages for the same Side order if that Side order is executed in several parts. The multiple Single Side Executed Messages on the same order are cumulative. By combining the executions received separately via two types of Single Side Executed Messages and Trade Messages, it is possible to build a complete view of all non-auction executions that happen on NASDAQ. Auction execution information is available in one bulk print via the Auction Trade Message.
struct single_side_executed_message {
    static constexpr std::string_view name = "Single Side Executed Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        reference_number,
        executed_contracts,
        cross_number,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(reference_number);
    ITCHFIELD(executed_contracts);
    ITCHFIELD(cross_number);
    ITCHFIELD(match_number);
};

static_assert(sizeof(single_side_executed_message) == single_side_executed_message::size, "single_side_executed_message lies over its bytes exactly");

// Add Quote Message Long Form Message: For bandwidth efficiency reasons, this message can be published in either short or long format.
struct add_quote_message_long_form_message {
    static constexpr std::string_view name = "Add Quote Message Long Form Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        bid_reference_number,
        ask_reference_number,
        option_id,
        bid,
        bid_size_long,
        ask,
        ask_size_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(bid_reference_number);
    ITCHFIELD(ask_reference_number);
    ITCHFIELD(option_id);
    ITCHFIELD(bid);
    ITCHFIELD(bid_size_long);
    ITCHFIELD(ask);
    ITCHFIELD(ask_size_long);
};

static_assert(sizeof(add_quote_message_long_form_message) == add_quote_message_long_form_message::size, "add_quote_message_long_form_message lies over its bytes exactly");

// Add Quote Message Short Form Message: For bandwidth efficiency reasons, this message can be published in either short or long format.
struct add_quote_message_short_form_message {
    static constexpr std::string_view name = "Add Quote Message Short Form Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        bid_reference_number,
        ask_reference_number,
        option_id,
        bid_price_short,
        bid_size_short,
        ask_price_short,
        ask_size_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(bid_reference_number);
    ITCHFIELD(ask_reference_number);
    ITCHFIELD(option_id);
    ITCHFIELD(bid_price_short);
    ITCHFIELD(bid_size_short);
    ITCHFIELD(ask_price_short);
    ITCHFIELD(ask_size_short);
};

static_assert(sizeof(add_quote_message_short_form_message) == add_quote_message_short_form_message::size, "add_quote_message_short_form_message lies over its bytes exactly");

// Add Order Message Long Form Message: For bandwidth efficiency reasons, this message can be published in either short or long format.
struct add_order_message_long_form_message {
    static constexpr std::string_view name = "Add Order Message Long Form Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        order_reference_number,
        market_side,
        option_id,
        price_long,
        volume_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(market_side);
    ITCHFIELD(option_id);
    ITCHFIELD(price_long);
    ITCHFIELD(volume_long);
};

static_assert(sizeof(add_order_message_long_form_message) == add_order_message_long_form_message::size, "add_order_message_long_form_message lies over its bytes exactly");

// Add Order Message Short Message Form: For bandwidth efficiency reasons, this message can be published in either short or long format.
struct add_order_message_short_message_form {
    static constexpr std::string_view name = "Add Order Message Short Message Form";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        order_reference_number,
        market_side,
        option_id,
        price_short,
        volume_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(market_side);
    ITCHFIELD(option_id);
    ITCHFIELD(price_short);
    ITCHFIELD(volume_short);
};

static_assert(sizeof(add_order_message_short_message_form) == add_order_message_short_message_form::size, "add_order_message_short_message_form lies over its bytes exactly");

// Security Open Message: NASDAQ plans to disseminate the Option Open Message for each option as soon as the opening is completed. Upon receipt of the open state message, firms should be advised that the option denoted in the message is now available for auto execution within the NASDAQ Options Market System. Upon receipt of the closed state message, firms should be advised that the option is no longer eligible for auto-execution within the NASDAQ Options Market System.
struct security_open_message {
    static constexpr std::string_view name = "Security Open Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        option_id,
        open_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(option_id);
    ITCHFIELD(open_state);
};

static_assert(sizeof(security_open_message) == security_open_message::size, "security_open_message lies over its bytes exactly");

// Trading Action Message: After the start of system hours, NASDAQ will use the Trading Action message to relay changes in trading status for an individual option. Messages will be sent when an option is halted, is released for quotation, released for trading, or temporarily suspended for trading on the buy or sell side.
struct trading_action_message {
    static constexpr std::string_view name = "Trading Action Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        option_id,
        current_trading_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(option_id);
    ITCHFIELD(current_trading_state);
};

static_assert(sizeof(trading_action_message) == trading_action_message::size, "trading_action_message lies over its bytes exactly");

// Options Directory Message: At the start of each trading day, NASDAQ disseminates options symbol directory messages for all active options symbols in the NASDAQ option system.
struct options_directory_message {
    static constexpr std::string_view name = "Options Directory Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        option_id,
        security_symbol,
        expiration_year,
        expiration_month,
        expiration_date,
        explicit_strike_price,
        option_type,
        source,
        underlying_symbol,
        options_closing_type,
        tradable,
        mpv>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(option_id);
    ITCHFIELD(security_symbol);
    ITCHFIELD(expiration_year);
    ITCHFIELD(expiration_month);
    ITCHFIELD(expiration_date);
    ITCHFIELD(explicit_strike_price);
    ITCHFIELD(option_type);
    ITCHFIELD(source);
    ITCHFIELD(underlying_symbol);
    ITCHFIELD(options_closing_type);
    ITCHFIELD(tradable);
    ITCHFIELD(mpv);
};

static_assert(sizeof(options_directory_message) == options_directory_message::size, "options_directory_message lies over its bytes exactly");

// System Event Message: The system event message type is used to signal a market or data feed handler event.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        timestamp,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(event_code);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Udp Payload: Branch
struct udp_payload {
    static constexpr std::string_view name = "Udp Payload";
    static constexpr bool is_message = false;
};

// Message Header: Mold Udp 64 Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(message_length);
    ITCHFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Mold Udp64 Message
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

// End Of Session Packet
struct end_of_session_packet {
    static constexpr std::string_view name = "End Of Session Packet";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Server Heartbeat Packet
struct server_heartbeat_packet {
    static constexpr std::string_view name = "Server Heartbeat Packet";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// End Of Replay Sequence Message: The End of replay Sequence message reflects the sequence number at the time replay of existing messages is complete. The firms can then use this sequence number to resume on the real time Mold channel.
struct end_of_replay_sequence_message {
    static constexpr std::string_view name = "End Of Replay Sequence Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        end_of_replay_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(end_of_replay_sequence_number);
};

static_assert(sizeof(end_of_replay_sequence_message) == end_of_replay_sequence_message::size, "end_of_replay_sequence_message lies over its bytes exactly");

// Sequenced Message: The sequenced (server to client) message carried by the packet, opaque bytes unless an application source dispatches it
struct sequenced_message {
    static constexpr std::string_view name = "Sequenced Message";
    static constexpr bool is_message = false;
};

// Sequenced Data Packet Section 1
struct sequenced_data_packet_section_1 {
    static constexpr std::string_view name = "Sequenced Data Packet Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequenced_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(sequenced_message_type);
};

static_assert(sizeof(sequenced_data_packet_section_1) == sequenced_data_packet_section_1::size, "sequenced_data_packet_section_1 lies over its bytes exactly");

// Sequenced Data Packet: The Sequenced Data Packets act as an envelope to carry the actual sequenced data messages that are transferred from the server to the client. Each Sequenced Data Packet carries one message from the higher-lever protocol
struct sequenced_data_packet {
    static constexpr std::string_view name = "Sequenced Data Packet";
    static constexpr bool is_message = false;
};

// Login Rejected Packet: The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from the client
struct login_rejected_packet {
    static constexpr std::string_view name = "Login Rejected Packet";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reject_reason_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(reject_reason_code);
};

static_assert(sizeof(login_rejected_packet) == login_rejected_packet::size, "login_rejected_packet lies over its bytes exactly");

// Login Accepted Packet: The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login Request from the client
struct login_accepted_packet {
    static constexpr std::string_view name = "Login Accepted Packet";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        accepted_session,
        accepted_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(accepted_session);
    ITCHFIELD(accepted_sequence_number);
};

static_assert(sizeof(login_accepted_packet) == login_accepted_packet::size, "login_accepted_packet lies over its bytes exactly");

// Debug Packet: Debug packets are intended to provide human readable text that may aid in debugging problems
struct debug_packet {
    static constexpr std::string_view name = "Debug Packet";
    static constexpr bool is_message = true;
};

// Server Payload: Branch
struct server_payload {
    static constexpr std::string_view name = "Server Payload";
    static constexpr bool is_message = false;
};

// Server Packet Header: Packet header of a packet sent by the server
struct server_packet_header {
    static constexpr std::string_view name = "Server Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_length,
        server_packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(packet_length);
    ITCHFIELD(server_packet_type);
};

static_assert(sizeof(server_packet_header) == server_packet_header::size, "server_packet_header lies over its bytes exactly");

// Server Soup Bin Tcp Packet: Soup Bin Tcp Packet sent by the server
struct server_soup_bin_tcp_packet {
    static constexpr std::string_view name = "Server Soup Bin Tcp Packet";
    static constexpr bool is_message = false;
};

// Server Packet: SoupBinTCP Packet sent by the server
struct server_packet {
    static constexpr std::string_view name = "Server Packet";
    static constexpr bool is_message = false;
};

// Logout Request Packet
struct logout_request_packet {
    static constexpr std::string_view name = "Logout Request Packet";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Client Heartbeat Packet
struct client_heartbeat_packet {
    static constexpr std::string_view name = "Client Heartbeat Packet";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Unsequenced Data Packet Section 1
struct unsequenced_data_packet_section_1 {
    static constexpr std::string_view name = "Unsequenced Data Packet Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        unsequenced_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(unsequenced_message_type);
};

static_assert(sizeof(unsequenced_data_packet_section_1) == unsequenced_data_packet_section_1::size, "unsequenced_data_packet_section_1 lies over its bytes exactly");

// Unsequenced Data Packet: The Unsequenced Data Packets act as an envelope to carry the actual data messages that are transferred from the client to the server
struct unsequenced_data_packet {
    static constexpr std::string_view name = "Unsequenced Data Packet";
    static constexpr bool is_message = true;
};

// Login Request Packet: The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server
struct login_request_packet {
    static constexpr std::string_view name = "Login Request Packet";
    static constexpr std::size_t size = 46;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        username,
        password,
        requested_session,
        requested_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(username);
    ITCHFIELD(password);
    ITCHFIELD(requested_session);
    ITCHFIELD(requested_sequence_number);
};

static_assert(sizeof(login_request_packet) == login_request_packet::size, "login_request_packet lies over its bytes exactly");

// Client Payload: Branch
struct client_payload {
    static constexpr std::string_view name = "Client Payload";
    static constexpr bool is_message = false;
};

// Client Packet Header: Packet header of a packet sent by the client
struct client_packet_header {
    static constexpr std::string_view name = "Client Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_length,
        client_packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(packet_length);
    ITCHFIELD(client_packet_type);
};

static_assert(sizeof(client_packet_header) == client_packet_header::size, "client_packet_header lies over its bytes exactly");

// Client Soup Bin Tcp Packet: Soup Bin Tcp Packet sent by the client
struct client_soup_bin_tcp_packet {
    static constexpr std::string_view name = "Client Soup Bin Tcp Packet";
    static constexpr bool is_message = false;
};

// Client Packet: SoupBinTCP Packet sent by the client
struct client_packet {
    static constexpr std::string_view name = "Client Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
