// Cboe EdgxOptions MulticastDepthOfBook Pitch 2.41.80 Template Meta Programming

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

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

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

// Aon: Options only. 0 = Order is a firm quote, 1 = Order is AON (All or None).
struct aon {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

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

// Auction Only Price: Uncollared VMIM price computed on the queuing book only.
struct auction_only_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Type: G = GTH Opening (C1 Only), O = RTH Opening (C1 Only), H = Halt Re-Opening, V = Volatility Opening.
struct auction_type {
    enum class type : char {
        opening_auction = 'O',
        closing_auction = 'C',
        gth_opening = 'G',
        halt_auction = 'H',
        ipo_auction = 'I',
        cboe_market_close = 'M',
        volitility_auction = 'V',
        periodic_auction = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Buy Contracts: Cumulative Buy contracts at the Reference Price and above.
struct buy_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canceled Quantity Long: Number of shares/contracts canceled.
struct canceled_quantity_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Canceled Quantity Short: Number of shares/contracts canceled.
struct canceled_quantity_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Client Id: Options Only. Optional user specified value attributed to this quote. Space filled otherwise.
struct client_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Composite Market Bid Price: Bid Price of the prevailing Composite Market.
struct composite_market_bid_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Composite Market Offer Price: Offer Price of the prevailing Composite Market.
struct composite_market_offer_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contracts: Number of contracts available in the auction.
struct contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Customer Indicator: BZX/C1/EDGX Options Only (space filled on C2 Options and all equities markets). N = Non-Customer, C = Customer, R = Retail Priority order (EDGX Equities only).
struct customer_indicator {
    enum class type : char {
        non_customer = 'N',
        customer = 'C',
        retail_priority_order = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Display: 0 = Order is not aggregated in the Cboe SIP quote, 1 = Order is aggregated in the Cboe SIP quote.
struct display {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Executed Quantity: Number of shares/contracts executed.
struct executed_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Execution Id: Cboe generated day-unique execution identifier of this execution. Execution Id is also referenced in the Trade Break message.
struct execution_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expanded Symbol: Symbol right padded with spaces.
struct expanded_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
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

// Gth Trading Status: C1 Only. H = Halted, Q = Quote-Only, R = Opening Rotation, T = Trading.
struct gth_trading_status {
    enum class type : char {
        halted = 'H',
        quote_only = 'Q',
        opening_rotation = 'R',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Indicative Price: Collared VMIM price computed on the combined queueing book and the continuous book. Equal to Reference Price for options that do not have a GTH trading session.
struct indicative_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Lower Strike Price: SOQ lower strike price.
struct lower_strike_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maintain Priority: 0 = Reset Priority, 1 = Maintain Priority.
struct maintain_priority {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
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
        transaction_begin_message = 188,
        transaction_end_message = 189,
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
        trade_expanded_message = 48,
        trade_break_message = 44,
        end_of_session_message = 45,
        symbol_mapping_message = 46,
        trading_status_message = 49,
        width_update_message = 210,
        options_auction_update_message = 209,
        auction_summary_message = 150,
        auction_notification_message = 173,
        auction_cancel_message = 174,
        auction_trade_message = 175,
        soq_strike_range_update_message = 157,
        constituent_symbol_mapping_message = 158,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Multiplier: Width multiplier.
struct multiplier {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -1;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opening Condition: O = Would open, Q = Need quote to open, B = Need more buyers (C1 Only), S = Need more sellers (C1 Only), C = Crossed Composite Market.
struct opening_condition {
    enum class type : char {
        would_open = 'O',
        need_quote_to_open = 'Q',
        need_more_buyers = 'B',
        need_more_sellers = 'S',
        crossed_composite_market = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Osi Symbol: OSI Symbol.
struct osi_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 21;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 21> value_;
};

// Participant Id: Optionally specified. If specified, MPID (equities) or Executing Firm ID (options) of firm attributed to this quote. Alternatively "RTAL" for retail specified orders (equities). Space filled otherwise.
struct participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
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

// Quantity Long: Number of shares/contracts being added to the book (may be less than the number entered).
struct quantity_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity Short: Number of shares/contracts being added to the book (may be less than the number entered).
struct quantity_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reference Price: Collared VMIM price computed on the queuing book only.
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

// Remaining Quantity: Number of shares/contracts remaining after the execution.
struct remaining_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: Reserved.
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 2: Reserved.
struct reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 3: Bits 0-2 Reserved (Bit 0 set to 1).
struct reserved_3 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x7ULL;
    static constexpr int shift = 0;
};

// Reserved 4: Bits 4-7 Reserved.
struct reserved_4 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xF0ULL;
    static constexpr int shift = 4;
};

// Reserved 5: Options Only. Reserved.
struct reserved_5 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 5;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 5> value_;
};

// Reserved 6: Bits 2-7 Reserved.
struct reserved_6 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFCULL;
    static constexpr int shift = 2;
};

// Second Reserved 1: Reserved.
struct second_reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sell Contracts: Cumulative Sell contracts at the Reference Price and below.
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

// Shares Contracts: Cumulative number of shares/contracts executed during the auction or CMC matching.
struct shares_contracts {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side: B or S.
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

// Side Indicator: B = Buy Order, S = Sell Order.
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

// Soq Identifier: Dissemination symbol of the final SOQ right padded with spaces.
struct soq_identifier {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Stock Symbol: Stock Symbol right padded with spaces.
struct stock_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Symbol: Symbol right padded with spaces.
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Symbol Condition: N = Normal, C = Closing Only.
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

// Time: Number of whole seconds elapsed since the start of the current Eastern Time calendar day, derived by converting the current Eastern wall clock time (HH:MM:SS) to seconds. On Daylight Saving Time transition days, Time reflects wall clock seconds and does not adjust for the UTC offset change. On a DST spring-forward day, the maximum value will be 82,799 (23 hours). On a DST fall-back day, values between 3,600 and 7,199 will appear twice. Recipients requiring unambiguous absolute timestamps should use Epoch Time (where available) or Midnight Reference in the Time Reference message.
struct time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Trade Condition: Options Only (byte not sent in Equities). See Options Trade Condition Codes on page 180 section for details about new codes.
struct trade_condition {
    enum class type : char {
        single_leg_auction_non_iso_cboe_auction_types_include_aim_sam = 'a',
        single_leg_auction_iso_cboe_auction_types_are_aim_iso_sam_iso = 'b',
        single_leg_cross_non_iso_cboe_auction_types_include_cust_to_cust_aim_qcc = 'c',
        single_leg_cross_iso_cboe_order_type_is_cust_to_cust_aim_iso = 'd',
        single_leg_floor_trade = 'e',
        complex_to_complex_electronic_trade = 'f',
        complex_auction_trade = 'g',
        complex_cross = 'h',
        complex_electronic_trade_against_single_legs = 'j',
        complex_with_stock_options_auction_trade = 'k',
        complex_floor_trade_against_single_legs = 'm',
        complex_with_stock_electronic_trade = 'n',
        complex_with_stock_cross = 'o',
        complex_with_stock_floor_trade = 'p',
        complex_floor_trade_of_proprietary_products_marked_as_combo_order = 't',
        multilateral_compression_trade_of_proprietary_products = 'u',
        extended_hours_trade = 'v',
        electronic_trade = 'I',
        cabinet_order = 'K',
        future_options_auction_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_auction = 'M',
        future_options_auto_electronic_trade_electronic_execution_of_a_multi_leg_futureoptions_order_traded_on_the_complex_book_or_in_a_coa = 'N',
        future_options_cross_electronic_execution_of_a_multi_leg_futureoptions_order_traded_in_a_two_sided_crossing_mechanism_that_does_not_go_through_an_exposure_period = 'P',
        opening_trade = 'O',
        iso = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Status: H = Halted, L = Curb Trading (C1 Only), Q = Quote-Only, R = Opening Rotation, T = RTH Trading.
struct trading_status {
    enum class type : char {
        halted = 'H',
        curb_trading = 'L',
        quote_only = 'Q',
        opening_rotation = 'R',
        rth_trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying: Symbol of underlying equity right padded with spaces.
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

// Upper Strike Price: SOQ upper strike price.
struct upper_strike_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Width Type: R = Regular, V = Volatility.
struct width_type {
    enum class type : char {
        regular = 'R',
        volatility = 'V',
        max_quote_width = 'Q',
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

// Constituent Symbol Mapping Message: C1 Only. The Constituent Symbol Mapping message is only available on the C1 Exchange. This message is used to communicate which options series (if any) are Constituent Series in a Volatility Settlement Special Opening Quote (SOQ). The message is identical to the Symbol Mapping message with the addition of the SOQ Identifier field, which is set to the CSMi symbol on which the final settlement SOQ value is disseminated. The Constituent Symbol Mapping message is sent as an unsequenced message with one message sent for each Constituent Series in a continuous loop as bandwidth allows.
struct constituent_symbol_mapping_message {
    static constexpr std::string_view name = "Constituent Symbol Mapping Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        feed_symbol,
        osi_symbol,
        symbol_condition,
        underlying,
        soq_identifier>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(feed_symbol);
    PITCHFIELD(osi_symbol);
    PITCHFIELD(symbol_condition);
    PITCHFIELD(underlying);
    PITCHFIELD(soq_identifier);
};

static_assert(sizeof(constituent_symbol_mapping_message) == constituent_symbol_mapping_message::size, "constituent_symbol_mapping_message lies over its bytes exactly");

// Soq Strike Range Update Message: C1 Only. The SOQ Strike Range Update message is only available on the C1 Exchange. This message disseminates the minimum and maximum strike prices of the strike price range used to calculate the Special Opening Quote (SOQ) on a Volatility Settlement date. In the event that multiple distinct SOQ calculations occur on the same day, the applicable SOQ is differentiated by the SOQ Identifier field, which is set to the CSMi symbol on which the final settlement SOQ value is disseminated.
struct soq_strike_range_update_message {
    static constexpr std::string_view name = "Soq Strike Range Update Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        soq_identifier,
        lower_strike_price,
        upper_strike_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(soq_identifier);
    PITCHFIELD(lower_strike_price);
    PITCHFIELD(upper_strike_price);
};

static_assert(sizeof(soq_strike_range_update_message) == soq_strike_range_update_message::size, "soq_strike_range_update_message lies over its bytes exactly");

// Auction Trade Message: C1 and EDGX Options Only. Auction Trade messages are used to disseminate executions resulting from an options auction.
struct auction_trade_message {
    static constexpr std::string_view name = "Auction Trade Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        auction_id,
        execution_id,
        price_long,
        contracts>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(auction_id);
    PITCHFIELD(execution_id);
    PITCHFIELD(price_long);
    PITCHFIELD(contracts);
};

static_assert(sizeof(auction_trade_message) == auction_trade_message::size, "auction_trade_message lies over its bytes exactly");

// Auction Cancel Message: C1 and EDGX Options Only. Auction Cancel messages are used to disseminate the cancelation of an earlier Auction Notification message as a result of a user cancelation of the original order, a user modification request to change the price or increase the original order quantity, a fading of the NBBO or to cancel any remaining order quantity from the original Auction Notification messages following the auction termination. A user request to modify the order price or to increase the original order quantity will result in a cancelation of the auction followed by a new Auction Notification message. Auction Cancel messages will not be issued for order quantity decrements.
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

// Auction Notification Message: C1 and EDGX Options Only. Auction Notification messages are used to disseminate order details of an auction. Auctions will be available for a defined period of time known as the exposure period.
struct auction_notification_message {
    static constexpr std::string_view name = "Auction Notification Message";
    static constexpr std::size_t size = 45;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        symbol,
        auction_id,
        auction_type,
        side,
        price_long,
        contracts,
        customer_indicator,
        participant_id,
        auction_end_offset,
        client_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(auction_id);
    PITCHFIELD(auction_type);
    PITCHFIELD(side);
    PITCHFIELD(price_long);
    PITCHFIELD(contracts);
    PITCHFIELD(customer_indicator);
    PITCHFIELD(participant_id);
    PITCHFIELD(auction_end_offset);
    PITCHFIELD(client_id);
};

static_assert(sizeof(auction_notification_message) == auction_notification_message::size, "auction_notification_message lies over its bytes exactly");

// Auction Summary Message: Auction Summary messages are used to disseminate the results of an auction of a Cboe listed security on BZX, the results of an Opening or Re-Opening of any options series on C1, and for Periodic Auctions on BYX. Auction Summary messages are also used in support of Opening and Re-Openings on the Cboe Options Exchange, including those for both GTH and RTH sessions. These messages indicate the price and size executed in such an Opening or Re-Opening.
struct auction_summary_message {
    static constexpr std::string_view name = "Auction Summary Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        stock_symbol,
        auction_type,
        price_long,
        shares_contracts>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(stock_symbol);
    PITCHFIELD(auction_type);
    PITCHFIELD(price_long);
    PITCHFIELD(shares_contracts);
};

static_assert(sizeof(auction_summary_message) == auction_summary_message::size, "auction_summary_message lies over its bytes exactly");

// Options Auction Update Message: Options Only. Options Auction Update messages are used to disseminate price and size information and Composite Market bid and offer prices during Opening and Re-Opening (halt) auctions on the Cboe Options Exchange. Options Auction Update messages are sent every five seconds during an opening period provided that one of the field values has changed. When no values have changed, a message is sent once every 60 seconds. Refer to the Cboe Options Opening Process specification for more information.
struct options_auction_update_message {
    static constexpr std::string_view name = "Options Auction Update Message";
    static constexpr std::size_t size = 62;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        expanded_symbol,
        auction_type,
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
    PITCHFIELD(expanded_symbol);
    PITCHFIELD(auction_type);
    PITCHFIELD(reference_price);
    PITCHFIELD(buy_contracts);
    PITCHFIELD(sell_contracts);
    PITCHFIELD(indicative_price);
    PITCHFIELD(auction_only_price);
    PITCHFIELD(opening_condition);
    PITCHFIELD(composite_market_bid_price);
    PITCHFIELD(composite_market_offer_price);
};

static_assert(sizeof(options_auction_update_message) == options_auction_update_message::size, "options_auction_update_message lies over its bytes exactly");

// Width Update Message: Options Only. The Width Update message is used to communicate opening quote width multiplier. This message will be sent in the event that the exchange decides to change the quote width multiplier on a per underlying basis. For complete details on the opening collars see the US Options Opening Process Specification.
struct width_update_message {
    static constexpr std::string_view name = "Width Update Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        underlying,
        width_type,
        multiplier>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(underlying);
    PITCHFIELD(width_type);
    PITCHFIELD(multiplier);
};

static_assert(sizeof(width_update_message) == width_update_message::size, "width_update_message lies over its bytes exactly");

// Trading Status Message: The Trading Status message is used to indicate the current trading status of a security. A Trading Status message will be sent whenever a security's trading status changes. The Trading Status field will be used to represent the status of the RTH (9:30 a.m. ET - 4:15 p.m. ET) and Curb sessions. The GTH Trading Status field will be used to represent the status of series that trade during the GTH session. The GTH session runs from 8:15 p.m. to 9:25 a.m. ET for GTH-eligible Products (C1 Options Only).
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
        reserved_1,
        gth_trading_status,
        second_reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(symbol);
    PITCHFIELD(reserved_2);
    PITCHFIELD(trading_status);
    PITCHFIELD(reserved_1);
    PITCHFIELD(gth_trading_status);
    PITCHFIELD(second_reserved_1);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Symbol Mapping Message: Options Only. A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying. These messages are not sequenced (sequence = 0) and are sent continuously through the day at variable rates as bandwidth allows. Members who consume the 5 Gig or 8 Gig-Shaped Multicast PITCH feeds will be able to receive the full list of symbols in approximately 5 minutes.
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

// Trade Break Message: The Trade Break message is sent whenever an execution on Cboe is broken. Trade breaks are rare and only affect applications that rely upon Cboe execution-based data. Applications that simply build a Cboe book can ignore Trade Break messages.
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

// Trade Expanded Message: The expanded version of the Trade message has been made available to accommodate larger symbol sizes possible through the ISRA plan.
struct trade_expanded_message {
    static constexpr std::string_view name = "Trade Expanded Message";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_long,
        expanded_symbol,
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
    PITCHFIELD(expanded_symbol);
    PITCHFIELD(price_long);
    PITCHFIELD(execution_id);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(trade_expanded_message) == trade_expanded_message::size, "trade_expanded_message lies over its bytes exactly");

// Trade Short Message: The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. The Short variant uses a Binary Short Price and 2-byte Quantity.
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

// Trade Long Message: The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. In options a Trade message can also be sent when an auction executes against a non-displayed order, such as a contra response. Trade messages are necessary to calculate Cboe execution-based data. Trade messages do not alter the book and can be ignored if messages are being used solely to build a book. The Order ID of a hidden order is obfuscated by default in the Trade message, but may be optionally disseminated for a member's own orders upon request.
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

// Delete Order Message: The Delete Order message is sent whenever a booked order is cancelled or leaves the order book. The Order Id refers to the Order Id of the original Add Order message. An order that is deleted from the book may return to the book later under certain circumstances. Therefore, a Delete Order message does not indicate that a given Order Id will not be sent again on a subsequent Add Order message.
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

// Modify Flags: Modify Flags bit field used in Modify Order messages. Bit 0 indicates whether the order is aggregated in the Cboe SIP quote; Bit 1 indicates whether priority is maintained or reset.
struct modify_flags {
    static constexpr std::string_view name = "Modify Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(modify_flags) == modify_flags::size, "modify_flags lies over its bytes exactly");

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
        modify_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(quantity_short);
    PITCHFIELD(price_short);
    PITCHFIELD(modify_flags);
};

static_assert(sizeof(modify_order_short_message) == modify_order_short_message::size, "modify_order_short_message lies over its bytes exactly");

// Modify Order Long Message: The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message. Note that Modify Order messages that appear to be "No Ops" (i.e. they do not appear to modify any relevant fields) will still lose priority.
struct modify_order_long_message {
    static constexpr std::string_view name = "Modify Order Long Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        quantity_long,
        price_long,
        modify_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(quantity_long);
    PITCHFIELD(price_long);
    PITCHFIELD(modify_flags);
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

// Order Executed At Price Size Message: Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id. If the Remaining Quantity field contains a 0 the order should be completely removed from the book. Order Executed at Price/Size messages may also be sent in cases where the Executed Quantity is greater than the current booked size for Order Id due to Exchange features that allow a portion of an order to be hidden while another portion is displayed.
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
        price_long,
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
    PITCHFIELD(price_long);
    PITCHFIELD(trade_condition);
};

static_assert(sizeof(order_executed_at_price_size_message) == order_executed_at_price_size_message::size, "order_executed_at_price_size_message lies over its bytes exactly");

// Order Executed Message: Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part. The execution price equals the limit order price found in the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id.
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

// Add Flags: Add Flags bit field used in Add Order messages. Bit 3 indicates AON (All or None) status (Options only).
struct add_flags {
    static constexpr std::string_view name = "Add Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(add_flags) == add_flags::size, "add_flags lies over its bytes exactly");

// Add Order Expanded Message: The expanded version of the Add Order message has been made available to accommodate larger symbol sizes possible through the ISRA plan.
struct add_order_expanded_message {
    static constexpr std::string_view name = "Add Order Expanded Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_long,
        expanded_symbol,
        price_long,
        add_flags,
        participant_id,
        customer_indicator,
        client_id,
        reserved_5>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PITCHFIELD(time_offset);
    PITCHFIELD(order_id);
    PITCHFIELD(side_indicator);
    PITCHFIELD(quantity_long);
    PITCHFIELD(expanded_symbol);
    PITCHFIELD(price_long);
    PITCHFIELD(add_flags);
    PITCHFIELD(participant_id);
    PITCHFIELD(customer_indicator);
    PITCHFIELD(client_id);
    PITCHFIELD(reserved_5);
};

static_assert(sizeof(add_order_expanded_message) == add_order_expanded_message::size, "add_order_expanded_message lies over its bytes exactly");

// Add Order Short Message: An Add Order message represents a newly accepted visible order on the Cboe book. It includes a day-specific Order Id assigned by Cboe to the order.
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
        symbol,
        price_short,
        add_flags>;

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
    PITCHFIELD(add_flags);
};

static_assert(sizeof(add_order_short_message) == add_order_short_message::size, "add_order_short_message lies over its bytes exactly");

// Add Order Long Message: An Add Order message represents a newly accepted visible order on the Cboe book. It includes a day-specific Order Id assigned by Cboe to the order.
struct add_order_long_message {
    static constexpr std::string_view name = "Add Order Long Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        time_offset,
        order_id,
        side_indicator,
        quantity_long,
        symbol,
        price_long,
        add_flags>;

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
    PITCHFIELD(add_flags);
};

static_assert(sizeof(add_order_long_message) == add_order_long_message::size, "add_order_long_message lies over its bytes exactly");

// Transaction End Message: Options Only. The Transaction End message indicates that a transaction indicated by a previous Transaction Begin message has completed. Transaction End messages do not alter the book and can be ignored if messages are being used solely to build a book.
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

// Transaction Begin Message: Options Only. The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block. All PITCH messages corresponding to such an event would be included between a Transaction Begin message and Transaction End message. It is important to note that transaction blocks are currently used in US Options for symbol state transitions only, but may be expanded to other use cases with notice. Transaction Begin messages do not alter the book and can be ignored if messages are being used solely to build a book.
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

// Unit Clear Message: The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header message. For Equities only, this message will be sent at startup each day. It would also be distributed in certain recovery events such as a data center fail-over.
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

// Time Message: A Time message is immediately generated and sent when there is a PITCH event for a given clock second. If there is no PITCH event for a given clock second, then no Time message is sent for that second. The Time field is the number of seconds relative to midnight Eastern Time. All subsequent time offset fields for the same unit will use the new Time message value as the base until another Time message is received for the same unit.
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

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
