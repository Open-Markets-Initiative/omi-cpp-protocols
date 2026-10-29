// Miax MiaxOptions ComplexTopOfMarket Mach 1.1 Template Meta Programming

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

// A member of a struct laid over its bytes: the overload get<Field>() finds it by, and the member
#ifndef MACHFIELD
#define MACHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef MACHSEQUENCE
#define MACHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

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

// Active On Miax: Indicates if this symbol is tradable on MIAX in the current session: “A” = Active (tradable) on MIAX “I” = Inactive (not tradable) on MIAX
struct active_on_miax {
    enum class type : char {
        active = 'A',
        inactive = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bid Condition: Top of Strategy Market Quote Conditions
struct bid_condition {
    enum class type : char {
        regular = 'A',
        trading_halt = 'T',
        wide = 'W',
        simple_auction = 'S',
        complex_auction = 'C',
        simple_market_protection = 'M',
        leg_market_protection = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// C To M Version: Eg: CTOM01.01
struct c_to_m_version {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Call Or Put: Option Type: “C” = Call, “P” = Put
struct call_or_put {
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

// Closing Time: Expressed in HH:MM:SS format. Eg: 16:15:00
struct closing_time {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Compact Bid Price: MIAX Best Bid net price.
struct compact_bid_price {
    using type = std::int16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Compact Bid Size: Aggregate size at MIAX Best Bid Net Price
struct compact_bid_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Compact Offer Price: MIAX Best Offer net price
struct compact_offer_price {
    using type = std::int16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Compact Offer Size: Aggregate size at MIAX Best Bid Net Price
struct compact_offer_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Compact Price: MIAX Best price at the time stated in Timestamp and side specified in Message Type.
struct compact_price {
    using type = std::int16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Compact Size: Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct compact_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Reason: Values: “A” = This event resulted from automatic/market driven event “M” = MIAX manually initiated this event
struct event_reason {
    enum class type : char {
        automatic = 'A',
        manual = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Expected Event Time Nano Seconds Part: Nano-seconds portion of the expected time of the event. Specifies number of nano-seconds since the seconds specified in “Expected Event Time Seconds” field.
struct expected_event_time_nano_seconds_part {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Date: Expiration date of the option in YYYYMMDD format
struct expiration_date {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Leg Ratio Qty: The ratio of this individual leg
struct leg_ratio_qty {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Side: The side of this individual leg
struct leg_side {
    enum class type : char {
        bid = 'B',
        ask = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Liquidity Acceptance Increment Indicator: This is the Minimum Price Variation for Quote/Order acceptance as per MIAX rules
struct liquidity_acceptance_increment_indicator {
    enum class type : char {
        penny = 'P',
        nickel = 'N',
        dime = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Long Term Option
struct long_term_option {
    enum class type : char {
        yes = 'Y',
        no = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Type: Code identifying this message type
struct message_type {
    enum class type : char {
        system_time_message = '1',
        series_update = 'P',
        complex_strategy_definition_message = 'C',
        system_state_message = 'S',
        compact_complex_top_of_market_bid_message = 'b',
        compact_complex_top_of_market_offer_message = 'o',
        wide_complex_top_of_market_bid_message = 'e',
        wide_complex_top_of_market_offer_message = 'f',
        compact_complex_double_sided_top_of_market_message = 'm',
        wide_complex_double_sided_top_of_market_message = 'w',
        strategy_trade_message = 't',
        underlying_trading_status_message = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Miax Bbo Posting Increment Indicator: This is the Minimum Price Variation as agreed to by the Options industry (penny pilot program) and as published by MIAX
struct miax_bbo_posting_increment_indicator {
    enum class type : char {
        penny = 'P',
        nickel = 'N',
        dime = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Nanoseconds: Time at which this product is added/updated on MIAX system today.
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Net Price: The net transaction price of the complex package. (Leg component prices times base sizes +/- other leg component prices times their base sizes, split pricing accounted for)
struct net_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Legs: Number of Legs. Variable from 2 to 8
struct number_of_legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Condition: Top of Strategy Market Quote Conditions
struct offer_condition {
    enum class type : char {
        regular = 'A',
        trading_halt = 'T',
        wide = 'W',
        simple_auction = 'S',
        complex_auction = 'C',
        simple_market_protection = 'M',
        leg_market_protection = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Opening Time: Expressed in HH:MM:SS format. Eg: 09:30:00
struct opening_time {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Opening Underlying Market Code: Options opening will be triggered on receipt of Opening quote/trade from this Underlying market:
struct opening_underlying_market_code {
    enum class type : char {
        nyse_amex = 'A',
        nasdaq_omx_bx = 'B',
        nse = 'C',
        finra_adf = 'D',
        market_independent = 'E',
        ise = 'I',
        edga = 'J',
        edgx = 'K',
        cse = 'M',
        nyse_euronext = 'N',
        nyse_arca = 'P',
        nasdaq_omx_utp = 'Q',
        nasdaq_omx_cta = 'T',
        iex = 'V',
        nasdaq_omx_phlx = 'X',
        bats_y = 'Y',
        bats = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Packet Length: Length of the packet, including the header and application data
struct packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Type: protocol packet type
struct packet_type {
    enum class type : std::uint8_t {
        heartbeat = 0,
        start_of_session = 1,
        end_of_session = 2,
        application_message = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Priority Quote Width: Maximum allowable width for a quote for this Option during regular trading in order to be considered as Priority Quote. 0 when Priority Quote Width is not applicable.
struct priority_quote_width {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session and is valid for that session.
struct product_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: Reserved for future use
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 10: Reserved for future use **
struct reserved_10 {
    using type = std::span<const std::byte, 10>;
    static constexpr std::size_t size = 10;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 10> value_;
};

// Reserved 16: Reserved for future use
struct reserved_16 {
    using type = std::span<const std::byte, 16>;
    static constexpr std::size_t size = 16;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 16> value_;
};

// Reserved 2: Reserved for future use
struct reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 4: Reserved for future use
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 8: Reserved for future use
struct reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Restricted Option
struct restricted_option {
    enum class type : char {
        yes = 'Y',
        no = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seconds: Seconds part of the time that applies to all messages that gets disseminated until this message gets sent again.
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seconds Part: Seconds portion of the expected time of the event. Always use in conjunction with the Nano-seconds part field.
struct seconds_part {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Symbol: Option Security Symbol
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Sequence Number: Sequence number of this data packet
struct sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: MIAX assigned ID for the current trading session
struct session_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Number: protocol packet type
struct session_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strategy Id: MIAX Strategy ID is assigned per trading day and is valid only for that day.
struct strategy_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price: Explicit strike price of the option. Refer to data types for field processing notes
struct strike_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Status: Current system status: “S” = Start of System hours “C” = End of System hours, “1” = Start of Test Session (sent before tests). “2” = End of Test Session.
struct system_status {
    enum class type : char {
        start_of_system_hours = 'S',
        end_of_system_hours = 'C',
        start_test_session = '1',
        end_of_test_session = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Top Of Market Quote Condition: Top of Strategy Market Quote Conditions
struct top_of_market_quote_condition {
    enum class type : char {
        halted = 'H',
        resumed = 'R',
        opened = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Condition: Trade Condition Type
struct trade_condition {
    enum class type : char {
        matched = 'S',
        legged = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Id: Unique Complex Trade ID assigned to every trade.
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Size: Number of strategies executed in this trade
struct trade_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Status: “H” = MIAX has halted trading for this Underlying Symbol, “R” = MIAX will resume trading (reopen) for this Underlying Symbol, “O” = MIAX will open trading for this Underlying Symbol
struct trading_status {
    enum class type : char {
        halted = 'H',
        resumed = 'R',
        opened = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Symbol: Stock Symbol for the option.
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Update Reason: “N” – New strategy created
struct update_reason {
    enum class type : char {
        new_strategy_created = 'N',
        updated = 'U',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Wide Bid Price: MIAX Best Bid net price.
struct wide_bid_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Wide Bid Size: Aggregate size at MIAX Best Bid Net Price
struct wide_bid_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Wide Offer Price: MIAX Best Offer net price
struct wide_offer_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Wide Offer Size: Aggregate size at MIAX Best Bid Net Price
struct wide_offer_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Wide Price: MIAX Best price at the time stated in Timestamp and side specified in Message Type.
struct wide_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Wide Size: Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct wide_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Underlying Trading Status Message: This message format will be used to notify firms of changes to the trading status of all the options of an underlying
struct underlying_trading_status_message {
    static constexpr std::string_view name = "Underlying Trading Status Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        underlying_symbol,
        trading_status,
        event_reason,
        seconds_part,
        expected_event_time_nano_seconds_part>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(underlying_symbol);
    MACHFIELD(trading_status);
    MACHFIELD(event_reason);
    MACHFIELD(seconds_part);
    MACHFIELD(expected_event_time_nano_seconds_part);
};

static_assert(sizeof(underlying_trading_status_message) == underlying_trading_status_message::size, "underlying_trading_status_message lies over its bytes exactly");

// Strategy Trade Message: This is the message format that will be used to disseminate Trades that are resulting from executions on MIAX during the current trading session
struct strategy_trade_message {
    static constexpr std::string_view name = "Strategy Trade Message";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        trade_id,
        net_price,
        trade_size,
        trade_condition,
        reserved_16>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(trade_id);
    MACHFIELD(net_price);
    MACHFIELD(trade_size);
    MACHFIELD(trade_condition);
    MACHFIELD(reserved_16);
};

static_assert(sizeof(strategy_trade_message) == strategy_trade_message::size, "strategy_trade_message lies over its bytes exactly");

// Wide Offer
struct wide_offer {
    static constexpr std::string_view name = "Wide Offer";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        wide_offer_price,
        wide_offer_size,
        reserved_4,
        offer_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(wide_offer_price);
    MACHFIELD(wide_offer_size);
    MACHFIELD(reserved_4);
    MACHFIELD(offer_condition);
};

static_assert(sizeof(wide_offer) == wide_offer::size, "wide_offer lies over its bytes exactly");

// Wide Bid
struct wide_bid {
    static constexpr std::string_view name = "Wide Bid";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        wide_bid_price,
        wide_bid_size,
        reserved_4,
        bid_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(wide_bid_price);
    MACHFIELD(wide_bid_size);
    MACHFIELD(reserved_4);
    MACHFIELD(bid_condition);
};

static_assert(sizeof(wide_bid) == wide_bid::size, "wide_bid lies over its bytes exactly");

// Wide Complex Double Sided Top Of Market Message: This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with net prices or aggregate sizes which cannot be specified in the compact format.
struct wide_complex_double_sided_top_of_market_message {
    static constexpr std::string_view name = "Wide Complex Double Sided Top Of Market Message";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        wide_bid,
        wide_offer>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(wide_bid);
    MACHFIELD(wide_offer);
};

static_assert(sizeof(wide_complex_double_sided_top_of_market_message) == wide_complex_double_sided_top_of_market_message::size, "wide_complex_double_sided_top_of_market_message lies over its bytes exactly");

// Compact Offer
struct compact_offer {
    static constexpr std::string_view name = "Compact Offer";
    static constexpr std::size_t size = 7;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        compact_offer_price,
        compact_offer_size,
        reserved_2,
        offer_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(compact_offer_price);
    MACHFIELD(compact_offer_size);
    MACHFIELD(reserved_2);
    MACHFIELD(offer_condition);
};

static_assert(sizeof(compact_offer) == compact_offer::size, "compact_offer lies over its bytes exactly");

// Compact Bid
struct compact_bid {
    static constexpr std::string_view name = "Compact Bid";
    static constexpr std::size_t size = 7;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        compact_bid_price,
        compact_bid_size,
        reserved_2,
        bid_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(compact_bid_price);
    MACHFIELD(compact_bid_size);
    MACHFIELD(reserved_2);
    MACHFIELD(bid_condition);
};

static_assert(sizeof(compact_bid) == compact_bid::size, "compact_bid lies over its bytes exactly");

// Compact Complex Double Sided Top Of Market Message: This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with low net price and small aggregate size.
struct compact_complex_double_sided_top_of_market_message {
    static constexpr std::string_view name = "Compact Complex Double Sided Top Of Market Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        compact_bid,
        compact_offer>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(compact_bid);
    MACHFIELD(compact_offer);
};

static_assert(sizeof(compact_complex_double_sided_top_of_market_message) == compact_complex_double_sided_top_of_market_message::size, "compact_complex_double_sided_top_of_market_message lies over its bytes exactly");

// Wide Complex Top Of Market Offer Message: This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Offer (MBBO) size.
struct wide_complex_top_of_market_offer_message {
    static constexpr std::string_view name = "Wide Complex Top Of Market Offer Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        wide_price,
        wide_size,
        reserved_4,
        top_of_market_quote_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(wide_price);
    MACHFIELD(wide_size);
    MACHFIELD(reserved_4);
    MACHFIELD(top_of_market_quote_condition);
};

static_assert(sizeof(wide_complex_top_of_market_offer_message) == wide_complex_top_of_market_offer_message::size, "wide_complex_top_of_market_offer_message lies over its bytes exactly");

// Wide Complex Top Of Market Bid Message: This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Bid or Offer (MBBO) size.
struct wide_complex_top_of_market_bid_message {
    static constexpr std::string_view name = "Wide Complex Top Of Market Bid Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        wide_price,
        wide_size,
        reserved_4,
        top_of_market_quote_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(wide_price);
    MACHFIELD(wide_size);
    MACHFIELD(reserved_4);
    MACHFIELD(top_of_market_quote_condition);
};

static_assert(sizeof(wide_complex_top_of_market_bid_message) == wide_complex_top_of_market_bid_message::size, "wide_complex_top_of_market_bid_message lies over its bytes exactly");

// Compact Complex Top Of Market Offer Message: This is the message format that will be used to disseminate each side of the MIAX Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size
struct compact_complex_top_of_market_offer_message {
    static constexpr std::string_view name = "Compact Complex Top Of Market Offer Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        compact_price,
        compact_size,
        reserved_2,
        top_of_market_quote_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(compact_price);
    MACHFIELD(compact_size);
    MACHFIELD(reserved_2);
    MACHFIELD(top_of_market_quote_condition);
};

static_assert(sizeof(compact_complex_top_of_market_offer_message) == compact_complex_top_of_market_offer_message::size, "compact_complex_top_of_market_offer_message lies over its bytes exactly");

// Compact Complex Top Of Market Bid Message: This is the message format that will be used to disseminate each side of the MIAX Complex Top of Market for options with low Net Price and small aggregate MIAX Best Bid or Offer (MBBO) size
struct compact_complex_top_of_market_bid_message {
    static constexpr std::string_view name = "Compact Complex Top Of Market Bid Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        compact_price,
        compact_size,
        top_of_market_quote_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(compact_price);
    MACHFIELD(compact_size);
    MACHFIELD(top_of_market_quote_condition);
};

static_assert(sizeof(compact_complex_top_of_market_bid_message) == compact_complex_top_of_market_bid_message::size, "compact_complex_top_of_market_bid_message lies over its bytes exactly");

// System State Message: This message format is used to notify the firms of the state changes of the system. This is a notification that applies to each Underlying group. Firms can use notifications as triggers in their system to ensure electronic synchronization of systems.
struct system_state_message {
    static constexpr std::string_view name = "System State Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        c_to_m_version,
        session_id,
        system_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(c_to_m_version);
    MACHFIELD(session_id);
    MACHFIELD(system_status);
};

static_assert(sizeof(system_state_message) == system_state_message::size, "system_state_message lies over its bytes exactly");

// Leg Definition: Complex Strategy Number of Legs
struct leg_definition {
    static constexpr std::string_view name = "Leg Definition";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        product_id,
        leg_ratio_qty,
        leg_side,
        reserved_8>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(product_id);
    MACHFIELD(leg_ratio_qty);
    MACHFIELD(leg_side);
    MACHFIELD(reserved_8);
};

static_assert(sizeof(leg_definition) == leg_definition::size, "leg_definition lies over its bytes exactly");

// Complex Strategy Definition Message Section 1
struct complex_strategy_definition_message_section_1 {
    static constexpr std::string_view name = "Complex Strategy Definition Message Section 1";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        strategy_id,
        underlying_symbol,
        active_on_miax,
        reserved_1,
        update_reason,
        reserved_10,
        number_of_legs>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(strategy_id);
    MACHFIELD(underlying_symbol);
    MACHFIELD(active_on_miax);
    MACHFIELD(reserved_1);
    MACHFIELD(update_reason);
    MACHFIELD(reserved_10);
    MACHFIELD(number_of_legs);
};

static_assert(sizeof(complex_strategy_definition_message_section_1) == complex_strategy_definition_message_section_1::size, "complex_strategy_definition_message_section_1 lies over its bytes exactly");

// Complex Strategy Definition Message: This is the message format that will be used to disseminate stock option strategies traded on MIAX for the current session.
struct complex_strategy_definition_message {
    static constexpr std::string_view name = "Complex Strategy Definition Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    MACHSEQUENCE(leg_definition);
};

// Series Update: This is the message format that will be used to disseminate all Option series traded on MIAX for the current session. The product ID sent in this message is what will be disseminated in Top of Market BBO and Last Sale messages.
struct series_update {
    static constexpr std::string_view name = "Series Update";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        underlying_symbol,
        security_symbol,
        expiration_date,
        strike_price,
        call_or_put,
        opening_time,
        closing_time,
        restricted_option,
        long_term_option,
        active_on_miax,
        miax_bbo_posting_increment_indicator,
        liquidity_acceptance_increment_indicator,
        opening_underlying_market_code,
        priority_quote_width,
        reserved_8>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(underlying_symbol);
    MACHFIELD(security_symbol);
    MACHFIELD(expiration_date);
    MACHFIELD(strike_price);
    MACHFIELD(call_or_put);
    MACHFIELD(opening_time);
    MACHFIELD(closing_time);
    MACHFIELD(restricted_option);
    MACHFIELD(long_term_option);
    MACHFIELD(active_on_miax);
    MACHFIELD(miax_bbo_posting_increment_indicator);
    MACHFIELD(liquidity_acceptance_increment_indicator);
    MACHFIELD(opening_underlying_market_code);
    MACHFIELD(priority_quote_width);
    MACHFIELD(reserved_8);
};

static_assert(sizeof(series_update) == series_update::size, "series_update lies over its bytes exactly");

// System Time Message: This is the message format that will be used to disseminate the “seconds” part of the timestamp that is applicable to all messages that are sent in the current second.
struct system_time_message {
    static constexpr std::string_view name = "System Time Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        seconds>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(seconds);
};

static_assert(sizeof(system_time_message) == system_time_message::size, "system_time_message lies over its bytes exactly");

// Data: Branch
struct data_type {
    static constexpr std::string_view name = "Data";
    static constexpr bool is_message = false;
};

// Application Message Section 1
struct application_message_section_1 {
    static constexpr std::string_view name = "Application Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(message_type);
};

static_assert(sizeof(application_message_section_1) == application_message_section_1::size, "application_message_section_1 lies over its bytes exactly");

// Application Message
struct application_message {
    static constexpr std::string_view name = "Application Message";
    static constexpr bool is_message = false;
};

// End Of Session
struct end_of_session {
    static constexpr std::string_view name = "End Of Session";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Start Of Session
struct start_of_session {
    static constexpr std::string_view name = "Start Of Session";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Heartbeat
struct heartbeat {
    static constexpr std::string_view name = "Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Mach Packet Header: Mach packet header (12 bytes)
struct mach_packet_header {
    static constexpr std::string_view name = "Mach Packet Header";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequence_number,
        packet_length,
        packet_type,
        session_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sequence_number);
    MACHFIELD(packet_length);
    MACHFIELD(packet_type);
    MACHFIELD(session_number);
};

static_assert(sizeof(mach_packet_header) == mach_packet_header::size, "mach_packet_header lies over its bytes exactly");

// Mach Message
struct mach_message {
    static constexpr std::string_view name = "Mach Message";
    static constexpr bool is_message = false;
};

// Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
