// Miax OnyxFutures TopOfMarket Mach 1.0.b Template Meta Programming

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

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

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

// Correction Number: The latest correction number of the given Trade id
struct correction_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Currency: The currency in which all Futures Instruments of the Futures Product will trade
struct currency {
    enum class type : char {
        usd = 'U',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Exchange
struct exchange {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// High Limit Price: The Upper Band of the Daily Trading Limit of a Futures Product
struct high_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Instrument Id: Unique ID assigned by MIAX Futures Onyx
struct instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Instrument Id Source: Indicates whether the Instrument ID has been assigned by the exchange or from an external industry source
struct instrument_id_source {
    enum class type : char {
        exchange = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Instrument Type: ‘F’ = Futures
struct instrument_type {
    enum class type : char {
        futures = 'F',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Ratio And Side: Leg ratio for the specified instrument
struct leg_ratio_and_side {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Limit Price: The Lower Band of the Daily Trading Limit of a Futures Product
struct low_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market State
struct market_state {
    enum class type : std::uint8_t {
        pre_opening = 1,
        extended_1_trading_session = 2,
        regular_trading_session = 3,
        extended_2_trading_session = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Algorithm: The allocation model used by the MIAX Futures Onyx Trading Platform for the Product
struct match_algorithm {
    enum class type : char {
        price_then_time = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Maturity Month Year: Maturity Month-Year is the expiration date of a Simple Instrument
struct maturity_month_year {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maximum Size: Maximum Order Size
struct maximum_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mbb Price: Will be provided for updates as a result of any changes to the prices or sizes of the MBBO for an Simple Instrument or a Complex Instrument
struct mbb_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mbb Size: Aggregate size in contracts at the displayed offer price
struct mbb_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mbo Price: Will be provided for updates as a result of any changes to the prices or sizes of the MBBO for an Simple Instrument or a Complex Instrumen
struct mbo_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mbo Size: Aggregate size in contracts at the displayed offer price
struct mbo_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: Code identifying this message type
struct message_type {
    enum class type : std::uint8_t {
        simple_instrument_definition_message = 1,
        complex_instrument_definition_message = 2,
        system_state_message = 3,
        instrument_trading_status_notification_message = 4,
        best_bid_and_offer_message = 15,
        last_sale_message = 16,
        trade_cancel_message = 14,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Minimum Size: Minimum Order Size
struct minimum_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Legs: Number of strategy legs
struct number_of_legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Interest Quantity: The amount of aggregate open contracts in a Simple Instrument
struct open_interest_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Length: Length of the packet. This includes the header and application data
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

// Price: Execution price
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Product Group Code
struct product_group_code {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
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

// Session Id: Current trading session identifier
struct session_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Number: The Session this packet was generated from
struct session_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settlement Currency: The Currency in which the Product settles
struct settlement_currency {
    enum class type : char {
        usd = 'U',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Settlement Price: The previous day’s Settlement Price
struct settlement_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settlement Price Type Calc Method: Actual or Theoretical Settlement Price Indicator
struct settlement_price_type_calc_method {
    enum class type : char {
        actual = 'A',
        theoretical = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Size: Number of shares executed
struct size_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Spread Type
struct spread_type {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Strategy Id: Unique ID assigned by MIAX Futures Onyx for a Complex instrument and is permanent for the life of an instrument
struct strategy_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Status
struct system_status {
    enum class type : char {
        start_of_system_hours = 'S',
        end_of_system_hours = 'C',
        start_of_test_session = '1',
        end_of_test_session = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Tick: Order Entry Price Tick of the Product
struct tick {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Timestamp: Matching Engine time
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tom Version: Protocol Version
struct tom_version {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Total Volume: The aggregate amount of volume that has traded from the prior Trading Day
struct total_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Date: Business Trade Date
struct trade_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: Unique ID assigned by the Matching Engine
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Collar Variation: The Dollar Value or Percentage Value used in the calculation of theTrading Collar
struct trading_collar_variation {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Collar Variation Type
struct trading_collar_variation_type {
    enum class type : char {
        product_dollar_collar_value = 'D',
        product_collar_percentage_value = 'P',
        standard_calendar_spread = 'S',
        equity_calendar_spread = 'E',
        butterfly_spread = 'B',
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
    enum class type : std::uint8_t {
        pre_open = 1,
        opening_freeze = 2,
        trading = 3,
        halt = 4,
        operational_halt = 5,
        closed = 6,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Asset: Underlying Asset Code
struct underlying_asset {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Underlying Asset Type: Underlying Asset Type of this instrument
struct underlying_asset_type {
    enum class type : char {
        equity_index = 'E',
        commodity_agriculture = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Unit Of Measure: Individual unit of the Deliverable of the Underlying Asset associated with the Futures Contract
struct unit_of_measure {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Unit Of Measure Quantity: The quantity of the Underlying Asset that is required for the Deliverable associated with the Futures Contract
struct unit_of_measure_quantity {
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

// Trade Cancel Message: used to publish cancellation of a Simple Instrument trade which was previously published via an Order Execution Message
struct trade_cancel_message {
    static constexpr std::string_view name = "Trade Cancel Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        trade_date,
        instrument_id,
        trade_id,
        correction_number,
        price,
        size_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(trade_date);
    MACHFIELD(instrument_id);
    MACHFIELD(trade_id);
    MACHFIELD(correction_number);
    MACHFIELD(price);
    MACHFIELD(size_type);
};

static_assert(sizeof(trade_cancel_message) == trade_cancel_message::size, "trade_cancel_message lies over its bytes exactly");

// Last Sale Message: used to disseminate trades that are resulting from executions on MIAX Futures Onyx during the current trading session
struct last_sale_message {
    static constexpr std::string_view name = "Last Sale Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument_id,
        trade_id,
        price,
        size_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(instrument_id);
    MACHFIELD(trade_id);
    MACHFIELD(price);
    MACHFIELD(size_type);
};

static_assert(sizeof(last_sale_message) == last_sale_message::size, "last_sale_message lies over its bytes exactly");

// Best Bid And Offer Message: used to publish MIAX Futures Onyx Best Bid and Offer (MBBO) of a Simple Instrument or Complex Instrument
struct best_bid_and_offer_message {
    static constexpr std::string_view name = "Best Bid And Offer Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument_id,
        mbb_price,
        mbb_size,
        mbo_price,
        mbo_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(instrument_id);
    MACHFIELD(mbb_price);
    MACHFIELD(mbb_size);
    MACHFIELD(mbo_price);
    MACHFIELD(mbo_size);
};

static_assert(sizeof(best_bid_and_offer_message) == best_bid_and_offer_message::size, "best_bid_and_offer_message lies over its bytes exactly");

// Instrument Trading Status Notification Message: Used to notify firms of changes to the trading status of a particular Simple or Complex instrument
struct instrument_trading_status_notification_message {
    static constexpr std::string_view name = "Instrument Trading Status Notification Message";
    static constexpr std::size_t size = 14;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument_id,
        trading_status,
        market_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(instrument_id);
    MACHFIELD(trading_status);
    MACHFIELD(market_state);
};

static_assert(sizeof(instrument_trading_status_notification_message) == instrument_trading_status_notification_message::size, "instrument_trading_status_notification_message lies over its bytes exactly");

// System State Message
struct system_state_message {
    static constexpr std::string_view name = "System State Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tom_version,
        session_id,
        system_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(tom_version);
    MACHFIELD(session_id);
    MACHFIELD(system_status);
};

static_assert(sizeof(system_state_message) == system_state_message::size, "system_state_message lies over its bytes exactly");

// Instrument Leg: Complex Strategy Number of Legs
struct instrument_leg {
    static constexpr std::string_view name = "Instrument Leg";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        instrument_id,
        leg_ratio_and_side,
        maturity_month_year,
        reserved_8>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(instrument_id);
    MACHFIELD(leg_ratio_and_side);
    MACHFIELD(maturity_month_year);
    MACHFIELD(reserved_8);
};

static_assert(sizeof(instrument_leg) == instrument_leg::size, "instrument_leg lies over its bytes exactly");

// Complex Instrument Definition Message Section 1
struct complex_instrument_definition_message_section_1 {
    static constexpr std::string_view name = "Complex Instrument Definition Message Section 1";
    static constexpr std::size_t size = 84;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        strategy_id,
        underlying_asset_type,
        underlying_asset,
        product_group_code,
        spread_type,
        exchange,
        instrument_id_source,
        instrument_type,
        currency,
        settlement_currency,
        match_algorithm,
        minimum_size,
        maximum_size,
        tick,
        unit_of_measure,
        unit_of_measure_quantity,
        trading_collar_variation_type,
        trading_collar_variation,
        reserved_16,
        number_of_legs>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(strategy_id);
    MACHFIELD(underlying_asset_type);
    MACHFIELD(underlying_asset);
    MACHFIELD(product_group_code);
    MACHFIELD(spread_type);
    MACHFIELD(exchange);
    MACHFIELD(instrument_id_source);
    MACHFIELD(instrument_type);
    MACHFIELD(currency);
    MACHFIELD(settlement_currency);
    MACHFIELD(match_algorithm);
    MACHFIELD(minimum_size);
    MACHFIELD(maximum_size);
    MACHFIELD(tick);
    MACHFIELD(unit_of_measure);
    MACHFIELD(unit_of_measure_quantity);
    MACHFIELD(trading_collar_variation_type);
    MACHFIELD(trading_collar_variation);
    MACHFIELD(reserved_16);
    MACHFIELD(number_of_legs);
};

static_assert(sizeof(complex_instrument_definition_message_section_1) == complex_instrument_definition_message_section_1::size, "complex_instrument_definition_message_section_1 lies over its bytes exactly");

// Complex Instrument Definition Message: Used to disseminate all Complex Instruments traded on MIAX Futures Onyx for the current trading session
struct complex_instrument_definition_message {
    static constexpr std::string_view name = "Complex Instrument Definition Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    MACHSEQUENCE(instrument_leg);
};

// Simple Instrument Definition Message: used to disseminate all Simple Instruments traded on MIAX FuturesOnyx for the current trading session
struct simple_instrument_definition_message {
    static constexpr std::string_view name = "Simple Instrument Definition Message";
    static constexpr std::size_t size = 119;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument_id,
        underlying_asset_type,
        underlying_asset,
        product_group_code,
        exchange,
        instrument_id_source,
        instrument_type,
        maturity_month_year,
        currency,
        settlement_currency,
        match_algorithm,
        minimum_size,
        maximum_size,
        tick,
        unit_of_measure,
        unit_of_measure_quantity,
        settlement_price,
        settlement_price_type_calc_method,
        total_volume,
        open_interest_quantity,
        high_limit_price,
        low_limit_price,
        trading_collar_variation_type,
        trading_collar_variation,
        reserved_16>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(timestamp);
    MACHFIELD(instrument_id);
    MACHFIELD(underlying_asset_type);
    MACHFIELD(underlying_asset);
    MACHFIELD(product_group_code);
    MACHFIELD(exchange);
    MACHFIELD(instrument_id_source);
    MACHFIELD(instrument_type);
    MACHFIELD(maturity_month_year);
    MACHFIELD(currency);
    MACHFIELD(settlement_currency);
    MACHFIELD(match_algorithm);
    MACHFIELD(minimum_size);
    MACHFIELD(maximum_size);
    MACHFIELD(tick);
    MACHFIELD(unit_of_measure);
    MACHFIELD(unit_of_measure_quantity);
    MACHFIELD(settlement_price);
    MACHFIELD(settlement_price_type_calc_method);
    MACHFIELD(total_volume);
    MACHFIELD(open_interest_quantity);
    MACHFIELD(high_limit_price);
    MACHFIELD(low_limit_price);
    MACHFIELD(trading_collar_variation_type);
    MACHFIELD(trading_collar_variation);
    MACHFIELD(reserved_16);
};

static_assert(sizeof(simple_instrument_definition_message) == simple_instrument_definition_message::size, "simple_instrument_definition_message lies over its bytes exactly");

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

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
