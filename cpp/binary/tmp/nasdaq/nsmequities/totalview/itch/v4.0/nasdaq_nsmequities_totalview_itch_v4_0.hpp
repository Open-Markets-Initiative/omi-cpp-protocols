// Nasdaq NsmEquities TotalView Itch 4.0 Template Meta Programming

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
namespace nasdaq::nsmequities::totalview::itch::v4_0::calendar {

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

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

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

// Attribution: NASDAQ market participant identifier associated with the entered order.
struct attribution {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Canceled Shares: The number of shares being removed from the display size of the order as the result of a cancellation.
struct canceled_shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Cross Price: The price at which the cross occurred. Refer to Data Types for field processing notes.
struct cross_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Shares: The number of shares matched in the NASDAQ Cross.
struct cross_shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Type: The NASDAQ cross session for which the message is being generated.
struct cross_type {
    enum class type : char {
        opening = 'O',
        closing = 'C',
        ipo_and_halted = 'H',
        cross_network = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Current Reference Price: The price at which the NOII shares are being calculated. Refer to Data Types for field processing notes.
struct current_reference_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Event Code: See System Event Codes.
struct event_code {
    enum class type : char {
        start_of_messages = 'O',
        start_of_system_hours = 'S',
        start_of_market_hours = 'Q',
        end_of_market_hours = 'M',
        end_of_system_hours = 'E',
        end_of_messages = 'C',
        emergency_market_condition_halt = 'A',
        emergency_market_condition_quote_only_period = 'R',
        emergency_market_condition_resumption = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Shares: The number of shares executed.
struct executed_shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Execution Price: The price at which the order execution occurred. Refer to Data Types for field processing notes.
struct execution_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Far Price: A hypothetical auction-clearing price for cross orders only. Refer to Data Types for field processing notes.
struct far_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Financial Status Indicator: For NASDAQ-listed issues, this field indicates when a firm is not in compliance with NASDAQ continued listing requirements. For CQS issues, this field will also be space-filled. Redistributors should refer to SIAC feeds for code if needed.
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
        in_compliance = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Direction: The market side of the order imbalance.
struct imbalance_direction {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        no_imbalance = 'N',
        insufficient_orders = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Shares: The number of shares not paired at the Current Reference Price.
struct imbalance_shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Category: Indicates Listing market or listing market tier for the issue
struct market_category {
    enum class type : char {
        cqs = 'T',
        nasdaq_global_select_market = 'Q',
        nasdaq_global_market = 'G',
        nasdaq_capital_market = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Maker Mode: Indicates the quoting participant’s registration status in relation to SEC Rules 101 and 104 of Regulation M
struct market_maker_mode {
    enum class type : char {
        normal = 'N',
        passive = 'P',
        syndicate = 'S',
        pre_syndicate = 'R',
        penalty = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Participant State: Indicates the market participant’s current registration status in the issue
struct market_participant_state {
    enum class type : char {
        active = 'A',
        excused_withdrawn = 'E',
        withdrawn = 'W',
        suspended = 'S',
        deleted = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Number: The NASDAQ generated day-unique Match Number of this execution. The match number is also referenced in the Trade Break Message.
struct match_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
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
        timestamp_message = 'T',
        system_event_message = 'S',
        stock_directory_message = 'R',
        stock_trading_action_message = 'H',
        market_participant_position_message = 'L',
        add_order_message = 'A',
        add_order_with_mpid_message = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        order_delete_message = 'D',
        order_replace_message = 'U',
        trade_message = 'P',
        cross_trade_message = 'Q',
        broken_trade_message = 'B',
        net_order_imbalance_indicator_message = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mpid: Denotes the market participant identifier for which the position message is being generated
struct mpid {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Nanoseconds: Nanoseconds portion of the timestamp.
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Near Price: A hypothetical auction-clearing price for cross orders as well as continuous orders. Refer to Data Types for field processing notes.
struct near_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New Order Reference Number: The new reference number for this order at time of replacement. Please note that the NASDAQ system will use this new order reference number for all subsequent updates.
struct new_order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Reference Number: The unique reference number assigned to the new order at the time of receipt.
struct order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Order Reference Number: The original reference number of the order being replaced.
struct original_order_reference_number {
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

// Paired Shares: The total number of shares that are eligible to be matched at the Current Reference Price.
struct paired_shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
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

// Price: The display price of the new order. Refer to Data Types for field processing notes.
struct price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Variation Indicator: This field indicates the absolute value of the percentage of deviation of the Near Indicative Clearing Price to the nearest Current Reference Price.
struct price_variation_indicator {
    enum class type : char {
        less_than_one_percent = 'L',
        one_to_one_point_nine_nine_percent = '1',
        two_to_two_point_nine_nine_percent = '2',
        three_to_three_point_nine_nine_percent = '3',
        four_to_four_point_nine_nine_percent = '4',
        five_to_five_point_nine_nine_percent = '5',
        six_to_six_point_nine_nine_percent = '6',
        seven_to_seven_point_nine_nine_percent = '7',
        eight_to_eight_point_nine_nine_percent = '8',
        nine_to_nine_point_nine_nine_percent = '9',
        ten_to_nineteen_point_nine_nine_percent = 'A',
        twenty_to_twenty_nine_point_nine_nine_percent = 'B',
        thirty_percent_or_greater = 'C',
        cannot_be_calculated = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Primary Market Maker: Indicates if the market participant firm qualifies as a Primary Market Maker in accordance with NASDAQ marketplace rules
struct primary_market_maker {
    enum class type : char {
        primary = 'Y',
        non_primary = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Reason: Trading Action reason.
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
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

// Reserved: Reserved.
struct reserved {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Round Lot Size: Indicates the number of shares that represent a round lot for the issue
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Round Lots Only: Indicates if NASDAQ system limits order entry for issue
struct round_lots_only {
    enum class type : char {
        round_lots_only = 'Y',
        odd_mixed_lots_allowed = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Second: Number of seconds since midnight.
struct second {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

    // second on a day: its seconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(value()) * 1000000000); }

  protected:
    type value_;
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
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
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

// Shares: The total number of shares associated with the order being added to the book.
struct shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side: The type of order being added.
struct side {
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

// Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to Appendix NASDAQ Single Book stock symbol convention information.
struct stock {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Trading State: Indicates the current trading state for the stock.
struct trading_state {
    enum class type : char {
        halted_or_paused = 'H',
        halted_or_paused_on_nasdaq = 'V',
        quotation_only_period = 'Q',
        quotation_only_period_on_nasdaq = 'R',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Net Order Imbalance Indicator Message: NASDAQ disseminates NOII data at 5-second intervals in the minutes leading up to the NASDAQ Opening Cross and NASDAQ Closing Cross.
struct net_order_imbalance_indicator_message {
    static constexpr std::string_view name = "Net Order Imbalance Indicator Message";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        paired_shares,
        imbalance_shares,
        imbalance_direction,
        stock,
        far_price,
        near_price,
        current_reference_price,
        cross_type,
        price_variation_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(paired_shares);
    ITCHFIELD(imbalance_shares);
    ITCHFIELD(imbalance_direction);
    ITCHFIELD(stock);
    ITCHFIELD(far_price);
    ITCHFIELD(near_price);
    ITCHFIELD(current_reference_price);
    ITCHFIELD(cross_type);
    ITCHFIELD(price_variation_indicator);
};

static_assert(sizeof(net_order_imbalance_indicator_message) == net_order_imbalance_indicator_message::size, "net_order_imbalance_indicator_message lies over its bytes exactly");

// Broken Trade Message: The Broken Trade Message is sent whenever an execution on NASDAQ is broken.
struct broken_trade_message {
    static constexpr std::string_view name = "Broken Trade Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(match_number);
};

static_assert(sizeof(broken_trade_message) == broken_trade_message::size, "broken_trade_message lies over its bytes exactly");

// Cross Trade Message: Cross Trade message indicates that NASDAQ has completed its cross process for a specific security.
struct cross_trade_message {
    static constexpr std::string_view name = "Cross Trade Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        cross_shares,
        stock,
        cross_price,
        match_number,
        cross_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(cross_shares);
    ITCHFIELD(stock);
    ITCHFIELD(cross_price);
    ITCHFIELD(match_number);
    ITCHFIELD(cross_type);
};

static_assert(sizeof(cross_trade_message) == cross_trade_message::size, "cross_trade_message lies over its bytes exactly");

// Trade Message: The Trade Message is designed to provide execution details for normal match events involving non-displayable order types.
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number,
        side,
        shares,
        stock,
        price,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(side);
    ITCHFIELD(shares);
    ITCHFIELD(stock);
    ITCHFIELD(price);
    ITCHFIELD(match_number);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Replace Message: This message is sent whenever an order on the book has been cancel-replaced. All remaining shares from the original order are no longer accessible, and must be removed. The new order details are provided for the replacement, along with a new order reference number which will be used henceforth.
struct order_replace_message {
    static constexpr std::string_view name = "Order Replace Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        original_order_reference_number,
        new_order_reference_number,
        shares,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(original_order_reference_number);
    ITCHFIELD(new_order_reference_number);
    ITCHFIELD(shares);
    ITCHFIELD(price);
};

static_assert(sizeof(order_replace_message) == order_replace_message::size, "order_replace_message lies over its bytes exactly");

// Order Delete Message: This message is sent whenever an order on the book is being cancelled. All remaining shares are no longer accessible so the order must be removed from the book.
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Order Cancel Message: This message is sent whenever an order on the book is modified as a result of a partial cancellation.
struct order_cancel_message {
    static constexpr std::string_view name = "Order Cancel Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number,
        canceled_shares>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(canceled_shares);
};

static_assert(sizeof(order_cancel_message) == order_cancel_message::size, "order_cancel_message lies over its bytes exactly");

// Order Executed With Price Message: This message is sent whenever an order on the book is executed in whole or in part at a price different from the initial display price.
struct order_executed_with_price_message {
    static constexpr std::string_view name = "Order Executed With Price Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number,
        executed_shares,
        match_number,
        printable,
        execution_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(executed_shares);
    ITCHFIELD(match_number);
    ITCHFIELD(printable);
    ITCHFIELD(execution_price);
};

static_assert(sizeof(order_executed_with_price_message) == order_executed_with_price_message::size, "order_executed_with_price_message lies over its bytes exactly");

// Order Executed Message: This message is sent whenever an order on the book is executed in whole or in part.
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number,
        executed_shares,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(executed_shares);
    ITCHFIELD(match_number);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Add Order With Mpid Message: This message will be generated for attributed orders and quotations accepted by the NASDAQ system.
struct add_order_with_mpid_message {
    static constexpr std::string_view name = "Add Order With Mpid Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number,
        side,
        shares,
        stock,
        price,
        attribution>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(side);
    ITCHFIELD(shares);
    ITCHFIELD(stock);
    ITCHFIELD(price);
    ITCHFIELD(attribution);
};

static_assert(sizeof(add_order_with_mpid_message) == add_order_with_mpid_message::size, "add_order_with_mpid_message lies over its bytes exactly");

// Add Order Message: This message will be generated for unattributed orders accepted by the NASDAQ system.
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 27;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_reference_number,
        side,
        shares,
        stock,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(side);
    ITCHFIELD(shares);
    ITCHFIELD(stock);
    ITCHFIELD(price);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Market Participant Position Message: At the start of each trading day, NASDAQ disseminates a spin of market participant position messages. Throughout the day, NASDAQ will send out this message only if NASDAQ Operations changes the status of a market participant firm in an issue.
struct market_participant_position_message {
    static constexpr std::string_view name = "Market Participant Position Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        mpid,
        stock,
        primary_market_maker,
        market_maker_mode,
        market_participant_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(mpid);
    ITCHFIELD(stock);
    ITCHFIELD(primary_market_maker);
    ITCHFIELD(market_maker_mode);
    ITCHFIELD(market_participant_state);
};

static_assert(sizeof(market_participant_position_message) == market_participant_position_message::size, "market_participant_position_message lies over its bytes exactly");

// Stock Trading Action Message: NASDAQ uses this administrative message to indicate the current trading status of a security to the trading community.
struct stock_trading_action_message {
    static constexpr std::string_view name = "Stock Trading Action Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        stock,
        trading_state,
        reserved,
        reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(stock);
    ITCHFIELD(trading_state);
    ITCHFIELD(reserved);
    ITCHFIELD(reason);
};

static_assert(sizeof(stock_trading_action_message) == stock_trading_action_message::size, "stock_trading_action_message lies over its bytes exactly");

// Stock Directory Message: Market data redistributors should process this message to populate the Financial Status Indicator (required display field) and the Market Category (recommended display field) for NASDAQ-listed issues.
struct stock_directory_message {
    static constexpr std::string_view name = "Stock Directory Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        stock,
        market_category,
        financial_status_indicator,
        round_lot_size,
        round_lots_only>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(stock);
    ITCHFIELD(market_category);
    ITCHFIELD(financial_status_indicator);
    ITCHFIELD(round_lot_size);
    ITCHFIELD(round_lots_only);
};

static_assert(sizeof(stock_directory_message) == stock_directory_message::size, "stock_directory_message lies over its bytes exactly");

// System Event Message: The system event message type is used to signal a market or data feed handler event.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(event_code);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Timestamp Message: Reflects the number of seconds past midnight that the Timestamp message was generated.
struct timestamp_message {
    static constexpr std::string_view name = "Timestamp Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        second>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(second);
};

static_assert(sizeof(timestamp_message) == timestamp_message::size, "timestamp_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
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

// Server Heartbeat
struct server_heartbeat {
    static constexpr std::string_view name = "Server Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

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

// Logout Request
struct logout_request {
    static constexpr std::string_view name = "Logout Request";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Client Heartbeat
struct client_heartbeat {
    static constexpr std::string_view name = "Client Heartbeat";
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

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
