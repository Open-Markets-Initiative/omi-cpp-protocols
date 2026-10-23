// Cboe CfeFutures MulticastDepthOfBook Pitch 1.2.22 Template Meta Programming

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
#ifndef PITCHFIELD
#define PITCHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef PITCHSEQUENCE
#define PITCHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

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

// Accrued Day Variance: Accrued day variance as of the start of the trading day (signed 64-bit decimal with twelve implied decimal places).
struct accrued_day_variance {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -12;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Volume: Total number of block and derived contracts traded for the day.
struct block_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canceled Quantity Long: Number of contracts canceled.
struct canceled_quantity_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canceled Quantity Short: Number of contracts canceled.
struct canceled_quantity_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Close Price: The last trade on the day (in any session) will set the Close Price for the day (valid only if Total Volume > 0). Block and ECRP trades (Trade Condition=B or E) do not update Close Price.
struct close_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Date: Populated for single leg instruments only. Zero-filled for spread instruments. The date that should be used in describing the future's third party symbol and the measurement period of the contract.
struct contract_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Size: Contract size of Instrument. Contract sizes less than 1 are represented with a 0 value; refer to the product specification for the contract size.
struct contract_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ecrp Volume: Total number of contracts traded for the day.
struct ecrp_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Epoch Time: Number of whole seconds since the Epoch (Midnight January 1, 1970 UTC).
struct epoch_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Executed Quantity: Number of contracts executed.
struct executed_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Execution Id: CFE generated day-unique execution identifier of this execution. Execution Id is also referenced in the Trade Break message.
struct execution_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Date: Expiration Date of Instrument.
struct expiration_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Feed Symbol: Six character, base 62 symbol.
struct feed_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Futures Symbol: Twelve character textual definition of the symbol where the first six characters contain the product symbol, left justified, and padded on the right with spaces, and the right most six characters are the expiration date in YYMMDD format.
struct futures_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// High Price: The higher of highest bid price and highest trade price for the day. Block and ECRP trades (Trade Condition=B or E) do not update High Price.
struct high_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// High Price Is Bid: Set if High Price was set by the highest bid (rather than a trade)
struct high_price_is_bid {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// High Price Valid: Set if High Price is a valid value
struct high_price_valid {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Issue: Issue Values
struct issue {
    enum class type : char {
        periodic_indicative_settlement = 'i',
        indicative_settlement = 'I',
        initial_settlement = 'S',
        reissued_settlement = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Count: Values greater than 0 indicate this is a spread instrument.
struct leg_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Offset: Leg definitions, if any, begin at this offset from the beginning of the message. Possible values are 0 (no legs present) or 45 (spread instrument).
struct leg_offset {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio: Leg ratio (positive for buy, negative for sell).
struct leg_ratio {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Symbol: Symbol of leg.
struct leg_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
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

// Listing State: Listing State Values
struct listing_state {
    enum class type : char {
        active = 'A',
        inactive = 'I',
        test = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Low Price: The lower of lowest offer price and lowest trade price for the day. Block and ECRP trades (Trade Condition=B or E) do not update Low Price.
struct low_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Price Is Offer: Set if Low Price was set by the lowest offer (rather than a trade)
struct low_price_is_offer {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Low Price Valid: Set if Low Price is a valid value
struct low_price_valid {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Lower Price Limit
struct lower_price_limit {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

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
        time_reference_message = 177,
        time_message = 32,
        unit_clear_message = 151,
        futures_instrument_definition_message = 187,
        futures_variance_symbol_mapping_message = 250,
        price_limits_message = 190,
        add_order_long_message = 33,
        add_order_short_message = 34,
        order_executed_message = 35,
        reduce_size_long_message = 37,
        reduce_size_short_message = 38,
        modify_order_long_message = 39,
        modify_order_short_message = 40,
        delete_order_message = 41,
        trade_long_message = 42,
        trade_short_message = 43,
        transaction_begin_message = 188,
        transaction_end_message = 189,
        trade_break_message = 44,
        settlement_message = 185,
        open_interest_message = 211,
        end_of_day_summary_message = 186,
        trading_status_message = 49,
        end_of_session_message = 45,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Midnight Reference: Midnight Central Time reference time for subsequent Time messages, expressed as number of whole seconds since the Epoch (Midnight January 1, 1970 UTC).
struct midnight_reference {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Num Elapsed Returns: Number of elapsed S&P 500 Index returns including the current day.
struct num_elapsed_returns {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Num Final Returns: Number of S&P 500 Index returns used in the Final Settlement Value calculation.
struct num_final_returns {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Close Valid: Set if both Open Price and Close Price fields contain valid values
struct open_close_valid {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Open Interest: Open Interest for this symbol.
struct open_interest {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Price: The first trade on the day (in any session) will set the Open Price for the day (valid only if Total Volume > 0). Block and ECRP trades (Trade Condition=B or E) do not update Open Price.
struct open_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: Day-specific identifier assigned to this order.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Increment: Minimum Price Increment.
struct price_increment {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Long: The limit order price.
struct price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Short: The limit order price.
struct price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity Long: Number of contracts being added to the book (may be less than the number entered).
struct quantity_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity Short: Number of contracts being added to the book (may be less than the number entered).
struct quantity_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Report Symbol: Symbol for product or underlying security.
struct report_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Reserved 1: Reserved. Value will always be zero.
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 2: Reserved
struct reserved_2 {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Reserved 3: Reserved
struct reserved_3 {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Reserved Flags 3: Reserved 5-7 Bits
struct reserved_flags_3 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xE0ULL;
    static constexpr int shift = 5;
};

// Reserved Flags 7: Reserved 1-7 Bits
struct reserved_flags_7 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFEULL;
    static constexpr int shift = 1;
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

// Settlement Price
struct settlement_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side Indicator: Side Indicator Values
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

// Symbol: Six character, base 62 symbol.
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Time Offset: Nanosecond offset from last unit timestamp.
struct time_offset {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Time Reference: Number of whole seconds from midnight Central Time.
struct time_reference {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Volume: Total number of contracts traded for the day, including block and ECRP trades.
struct total_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Condition: Trade Condition Values
struct trade_condition {
    enum class type : char {
        normal_trade = ' ',
        opening_trade = 'O',
        spread_trade = 'S',
        block_trade = 'B',
        ecrp_trade = 'E',
        derived = 'D',
        inter_market_spread_trade = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Date: Current Trade Date
struct trade_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Status: Trading Status Values
struct trading_status {
    enum class type : char {
        suspended = 'S',
        queuing = 'Q',
        trading = 'T',
        halted = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Unit Timestamp: Unit timestamp expressed as number of whole seconds since the Epoch (Midnight, January 1, 1970 UTC).
struct unit_timestamp {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Upper Price Limit
struct upper_price_limit {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Variance: Set for a Variance Future, clear for a Standard Future
struct variance {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
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

// Trading Status Message: The Trading Status message is used to indicate the current trading status of a Futures contract.
struct trading_status_message {
    static constexpr std::string_view name = "Trading Status Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        reserved_2,
        trading_status,
        reserved_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(reserved_2);
    PITCHFIELD(trading_status);
    PITCHFIELD(reserved_3);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Summary Flags: Summary Flags bitfields
struct summary_flags {
    static constexpr std::string_view name = "Summary Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(summary_flags) == summary_flags::size, "summary_flags lies over its bytes exactly");

// End Of Day Summary Message: The End of Day Summary message is sent immediately after trading ends for a symbol. No more Market Update messages will follow an End of Day Summary message for a particular symbol.
struct end_of_day_summary_message {
    static constexpr std::string_view name = "End Of Day Summary Message";
    static constexpr std::size_t size = 63;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        trade_date,
        open_interest,
        high_price,
        low_price,
        open_price,
        close_price,
        total_volume,
        block_volume,
        ecrp_volume,
        summary_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(trade_date);
    PITCHFIELD(open_interest);
    PITCHFIELD(high_price);
    PITCHFIELD(low_price);
    PITCHFIELD(open_price);
    PITCHFIELD(close_price);
    PITCHFIELD(total_volume);
    PITCHFIELD(block_volume);
    PITCHFIELD(ecrp_volume);
    PITCHFIELD(summary_flags);
};

static_assert(sizeof(end_of_day_summary_message) == end_of_day_summary_message::size, "end_of_day_summary_message lies over its bytes exactly");

// Open Interest Message: The Open Interest message is sent to communicate a symbol's open interest, usually for the prior trading date.
struct open_interest_message {
    static constexpr std::string_view name = "Open Interest Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        trade_date,
        open_interest>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(trade_date);
    PITCHFIELD(open_interest);
};

static_assert(sizeof(open_interest_message) == open_interest_message::size, "open_interest_message lies over its bytes exactly");

// Settlement Message: Settlement messages are used to provide information concerning indicative, approved, or corrected daily and final settlement prices for CFE products.
struct settlement_message {
    static constexpr std::string_view name = "Settlement Message";
    static constexpr std::size_t size = 23;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        trade_date,
        settlement_price,
        issue>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(trade_date);
    PITCHFIELD(settlement_price);
    PITCHFIELD(issue);
};

static_assert(sizeof(settlement_message) == settlement_message::size, "settlement_message lies over its bytes exactly");

// Trade Break Message: The Trade Break message is sent whenever an execution on CFE is broken.
struct trade_break_message {
    static constexpr std::string_view name = "Trade Break Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        execution_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(execution_id);
};

static_assert(sizeof(trade_break_message) == trade_break_message::size, "trade_break_message lies over its bytes exactly");

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

// Transaction Begin Message: The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block.
struct transaction_begin_message {
    static constexpr std::string_view name = "Transaction Begin Message";
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

static_assert(sizeof(transaction_begin_message) == transaction_begin_message::size, "transaction_begin_message lies over its bytes exactly");

// Trade Short Message: The Trade message provides information about executions that occur off of the CFE book (such as ECRP/Block trades). Trade messages are necessary to calculate CFE execution data.
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
        symbol,
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
    PITCHFIELD(symbol);
    PITCHFIELD(price_short);
    PITCHFIELD(execution_id);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(trade_short_message) == trade_short_message::size, "trade_short_message lies over its bytes exactly");

// Trade Long Message: The Trade message provides information about executions that occur off of the CFE book (such as ECRP/Block trades). Trade messages are necessary to calculate CFE execution data.
struct trade_long_message {
    static constexpr std::string_view name = "Trade Long Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_long,
        symbol,
        price_long,
        execution_id,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity_long);
    PITCHFIELD(symbol);
    PITCHFIELD(price_long);
    PITCHFIELD(execution_id);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(trade_long_message) == trade_long_message::size, "trade_long_message lies over its bytes exactly");

// Delete Order Message: The Delete Order message is sent whenever a booked order is cancelled or leaves the order book.
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
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        quantity_short,
        price_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(quantity_short);
    PITCHFIELD(price_short);
};

static_assert(sizeof(modify_order_short_message) == modify_order_short_message::size, "modify_order_short_message lies over its bytes exactly");

// Modify Order Long Message: The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message.
struct modify_order_long_message {
    static constexpr std::string_view name = "Modify Order Long Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        quantity_long,
        price_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(quantity_long);
    PITCHFIELD(price_long);
};

static_assert(sizeof(modify_order_long_message) == modify_order_long_message::size, "modify_order_long_message lies over its bytes exactly");

// Reduce Size Short Message: Reduce Size messages are sent when a visible order on the CFE book is partially reduced.
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

// Reduce Size Long Message: Reduce Size messages are sent when a visible order on the CFE book is partially reduced.
struct reduce_size_long_message {
    static constexpr std::string_view name = "Reduce Size Long Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        canceled_quantity_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(canceled_quantity_long);
};

static_assert(sizeof(reduce_size_long_message) == reduce_size_long_message::size, "reduce_size_long_message lies over its bytes exactly");

// Order Executed Message: Order Executed messages are sent when an order on the CFE book is executed in whole or in part.
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

// Add Order Short Message: An Add Order message represents a newly accepted visible order on the CFE book.
struct add_order_short_message {
    static constexpr std::string_view name = "Add Order Short Message";
    static constexpr std::size_t size = 23;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_short,
        symbol,
        price_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity_short);
    PITCHFIELD(symbol);
    PITCHFIELD(price_short);
};

static_assert(sizeof(add_order_short_message) == add_order_short_message::size, "add_order_short_message lies over its bytes exactly");

// Add Order Long Message: An Add Order message represents a newly accepted visible order on the CFE book.
struct add_order_long_message {
    static constexpr std::string_view name = "Add Order Long Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_long,
        symbol,
        price_long>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity_long);
    PITCHFIELD(symbol);
    PITCHFIELD(price_long);
};

static_assert(sizeof(add_order_long_message) == add_order_long_message::size, "add_order_long_message lies over its bytes exactly");

// Price Limits Message: The Price Limits message is sent out at the start of a session for products subject to price limits per the contract specifications.
struct price_limits_message {
    static constexpr std::string_view name = "Price Limits Message";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        upper_price_limit,
        lower_price_limit>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(upper_price_limit);
    PITCHFIELD(lower_price_limit);
};

static_assert(sizeof(price_limits_message) == price_limits_message::size, "price_limits_message lies over its bytes exactly");

// Futures Variance Symbol Mapping Message: The Futures Variance Symbol Mapping message is used to disseminate symbol reference data for S&P 500 Variance Futures (VA Futures) symbols.
struct futures_variance_symbol_mapping_message {
    static constexpr std::string_view name = "Futures Variance Symbol Mapping Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        unit_timestamp,
        feed_symbol,
        futures_symbol,
        accrued_day_variance,
        num_final_returns,
        num_elapsed_returns>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(unit_timestamp);
    PITCHFIELD(feed_symbol);
    PITCHFIELD(futures_symbol);
    PITCHFIELD(accrued_day_variance);
    PITCHFIELD(num_final_returns);
    PITCHFIELD(num_elapsed_returns);
};

static_assert(sizeof(futures_variance_symbol_mapping_message) == futures_variance_symbol_mapping_message::size, "futures_variance_symbol_mapping_message lies over its bytes exactly");

// Future Leg
struct future_leg {
    static constexpr std::string_view name = "Future Leg";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_ratio,
        leg_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(leg_ratio);
    PITCHFIELD(leg_symbol);
};

static_assert(sizeof(future_leg) == future_leg::size, "future_leg lies over its bytes exactly");

// Futures Flags: Futures Flags bitfields
struct futures_flags {
    static constexpr std::string_view name = "Futures Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(futures_flags) == futures_flags::size, "futures_flags lies over its bytes exactly");

// Futures Instrument Definition Message Section 1
struct futures_instrument_definition_message_section_1 {
    static constexpr std::string_view name = "Futures Instrument Definition Message Section 1";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        unit_timestamp,
        report_symbol,
        futures_flags,
        expiration_date,
        contract_size,
        listing_state,
        price_increment,
        leg_count,
        leg_offset,
        reserved_1,
        contract_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(unit_timestamp);
    PITCHFIELD(report_symbol);
    PITCHFIELD(futures_flags);
    PITCHFIELD(expiration_date);
    PITCHFIELD(contract_size);
    PITCHFIELD(listing_state);
    PITCHFIELD(price_increment);
    PITCHFIELD(leg_count);
    PITCHFIELD(leg_offset);
    PITCHFIELD(reserved_1);
    PITCHFIELD(contract_date);
};

static_assert(sizeof(futures_instrument_definition_message_section_1) == futures_instrument_definition_message_section_1::size, "futures_instrument_definition_message_section_1 lies over its bytes exactly");

// Futures Instrument Definition Message: The Futures Instrument Definition message can be sent as a sequenced message or an un-sequenced message. It is sent as a sequenced message when the system starts up at the beginning of a trading session or an the instrument is created or modified during a trading day.
struct futures_instrument_definition_message {
    static constexpr std::string_view name = "Futures Instrument Definition Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    PITCHSEQUENCE(future_leg);
};

// Unit Clear Message: The Unit Clear message instructs feed recipients to clear all orders for the CFE book in the unit specified in the Sequenced Unit Header message header.
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

// Time Message: A Time message is immediately generated and sent when there is a PITCH event for a given clock second.
struct time_message {
    static constexpr std::string_view name = "Time Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_reference,
        epoch_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_reference);
    PITCHFIELD(epoch_time);
};

static_assert(sizeof(time_message) == time_message::size, "time_message lies over its bytes exactly");

// Time Reference Message: The Time Reference message is used to provide a midnight reference point for recipients of the feed. It is sent whenever the system starts up and when the system crosses a midnight boundary.
struct time_reference_message {
    static constexpr std::string_view name = "Time Reference Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        midnight_reference,
        time_reference,
        time_offset,
        trade_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(midnight_reference);
    PITCHFIELD(time_reference);
    PITCHFIELD(time_offset);
    PITCHFIELD(trade_date);
};

static_assert(sizeof(time_reference_message) == time_reference_message::size, "time_reference_message lies over its bytes exactly");

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

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
