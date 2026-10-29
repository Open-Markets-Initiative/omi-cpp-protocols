// CixAts CixAspen MarketDataFeed Aspen 1.4 Template Meta Programming

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
#ifndef ASPENFIELD
#define ASPENFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef ASPENSEQUENCE
#define ASPENSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

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

// Board Lot Size: Board Lot Size in Shares
struct board_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Broker: Three digit number Broker Number or 001 for anonymous
struct broker {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Contra Broker: Three digit number Broker Number of the contra order or 001 for anonymous
struct contra_broker {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Corrected Trade Price: Price the trade is being amended/corrected to
struct corrected_trade_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Trade Quantity: Quantity the trade is being amended/corrected to
struct corrected_trade_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Count: Number of messages in packet
struct count_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event: Session state event code
struct event {
    enum class type : char {
        start_of_session = 'O',
        market_accepting_orders = 'S',
        market_open_for_trading = 'Q',
        market_closed_for_trading = 'E',
        end_of_session = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Execution Id: Market Issued Unique Execution ID
struct execution_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Feed Identifier: Unique code for feed
struct feed_identifier {
    enum class type : char {
        aspen = 'A',
        aspen_vert = 'V',
        midpoint = 'M',
        aspen_uat = 'B',
        aspen_vert_uat = 'W',
        midpoint_uat = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Info: optional text
struct info {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Length: Length of data message not including this field
struct length_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Listing Market: Code identifying the primary listing market
struct listing_market {
    enum class type : char {
        tsx = 'T',
        venture = 'V',
        cse = 'C',
        neo = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Day Identifier: Unique identifier for trading day
struct market_day_identifier {
    using type = std::uint64_t;
    static constexpr std::size_t size = 9;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::number<type>(raw(), fill); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::string_view raw() const noexcept { return tmp::trimmed_front(value_, fill); }

  protected:
    std::array<char, 9> value_;
};

// Message Type: Code identifying message type
struct message_type {
    enum class type : char {
        market_event_message = 'A',
        symbol_information_message = 'B',
        symbol_state_message = 'C',
        new_order_add_message = 'D',
        order_partial_cancel_message = 'F',
        order_cancel_all_message = 'G',
        order_executed_message = 'J',
        trade_message = 'K',
        trade_cancel_message = 'L',
        trade_correct_message = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Id: Market Issued Unique Order ID
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Execution Id: Execution ID of the original trade being corrected
struct original_execution_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Trade Price: Price of the trade being corrected
struct original_trade_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Trade Quantity: Quantity of the trade being corrected
struct original_trade_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: Price - 6 implied decimals
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity: Quantity - 6 implied decimals
struct quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity Canceled: Quantity canceled - Quantity 6 implied decimals
struct quantity_canceled {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: Reserved for future use
struct reserved_1 {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Reserved 2: Reserved for future use
struct reserved_2 {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Reserved 8: Reserved for future use
struct reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence: Sequence number for next message
struct sequence {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Shares: Qty Executed - 6 implied decimals
struct shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side: Side of the order
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

// State: Symbol trading state
struct state {
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

// Symbol: Stock Symbol
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Symbol Id: Symbol Index
struct symbol_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Timestamp: Nanoseconds Since Epoch (UTC)
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
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

// Trade Correct Message: Sent whenever an execution on CIX ATS is amended
struct trade_correct_message {
    static constexpr std::string_view name = "Trade Correct Message";
    static constexpr std::size_t size = 84;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_id,
        timestamp,
        reserved_8,
        reserved_1,
        symbol,
        execution_id,
        broker,
        contra_broker,
        original_execution_id,
        original_trade_price,
        original_trade_quantity,
        corrected_trade_price,
        corrected_trade_quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(symbol_id);
    ASPENFIELD(timestamp);
    ASPENFIELD(reserved_8);
    ASPENFIELD(reserved_1);
    ASPENFIELD(symbol);
    ASPENFIELD(execution_id);
    ASPENFIELD(broker);
    ASPENFIELD(contra_broker);
    ASPENFIELD(original_execution_id);
    ASPENFIELD(original_trade_price);
    ASPENFIELD(original_trade_quantity);
    ASPENFIELD(corrected_trade_price);
    ASPENFIELD(corrected_trade_quantity);
};

static_assert(sizeof(trade_correct_message) == trade_correct_message::size, "trade_correct_message lies over its bytes exactly");

// Trade Cancel Message: Sent whenever an execution on CIX ATS is cancelled
struct trade_cancel_message {
    static constexpr std::string_view name = "Trade Cancel Message";
    static constexpr std::size_t size = 60;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_id,
        timestamp,
        reserved_8,
        reserved_1,
        shares,
        symbol,
        price,
        execution_id,
        broker,
        contra_broker>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(symbol_id);
    ASPENFIELD(timestamp);
    ASPENFIELD(reserved_8);
    ASPENFIELD(reserved_1);
    ASPENFIELD(shares);
    ASPENFIELD(symbol);
    ASPENFIELD(price);
    ASPENFIELD(execution_id);
    ASPENFIELD(broker);
    ASPENFIELD(contra_broker);
};

static_assert(sizeof(trade_cancel_message) == trade_cancel_message::size, "trade_cancel_message lies over its bytes exactly");

// Trade Message: Sent when a hidden order is executed
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 60;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_id,
        timestamp,
        reserved_8,
        side,
        shares,
        symbol,
        price,
        execution_id,
        broker,
        contra_broker>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(symbol_id);
    ASPENFIELD(timestamp);
    ASPENFIELD(reserved_8);
    ASPENFIELD(side);
    ASPENFIELD(shares);
    ASPENFIELD(symbol);
    ASPENFIELD(price);
    ASPENFIELD(execution_id);
    ASPENFIELD(broker);
    ASPENFIELD(contra_broker);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Executed Message: Sent when an order is executed
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 47;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        order_id,
        quantity,
        execution_id,
        side,
        price,
        broker,
        contra_broker>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(timestamp);
    ASPENFIELD(order_id);
    ASPENFIELD(quantity);
    ASPENFIELD(execution_id);
    ASPENFIELD(side);
    ASPENFIELD(price);
    ASPENFIELD(broker);
    ASPENFIELD(contra_broker);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Order Cancel All Message: Sent when the order is canceled in its entirety
struct order_cancel_all_message {
    static constexpr std::string_view name = "Order Cancel All Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(timestamp);
    ASPENFIELD(order_id);
};

static_assert(sizeof(order_cancel_all_message) == order_cancel_all_message::size, "order_cancel_all_message lies over its bytes exactly");

// Order Partial Cancel Message: Part of a resting order is canceled
struct order_partial_cancel_message {
    static constexpr std::string_view name = "Order Partial Cancel Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        order_id,
        quantity_canceled>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(timestamp);
    ASPENFIELD(order_id);
    ASPENFIELD(quantity_canceled);
};

static_assert(sizeof(order_partial_cancel_message) == order_partial_cancel_message::size, "order_partial_cancel_message lies over its bytes exactly");

// New Order Add Message: A new resting order added to the book
struct new_order_add_message {
    static constexpr std::string_view name = "New Order Add Message";
    static constexpr std::size_t size = 50;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        symbol_id,
        order_id,
        side,
        quantity,
        symbol,
        price,
        broker,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(timestamp);
    ASPENFIELD(symbol_id);
    ASPENFIELD(order_id);
    ASPENFIELD(side);
    ASPENFIELD(quantity);
    ASPENFIELD(symbol);
    ASPENFIELD(price);
    ASPENFIELD(broker);
    ASPENFIELD(reserved_1);
};

static_assert(sizeof(new_order_add_message) == new_order_add_message::size, "new_order_add_message lies over its bytes exactly");

// Symbol State Message: Individual symbol trading state (halts)
struct symbol_state_message {
    static constexpr std::string_view name = "Symbol State Message";
    static constexpr std::size_t size = 27;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        symbol_id,
        symbol,
        state,
        reserved_1,
        info>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(timestamp);
    ASPENFIELD(symbol_id);
    ASPENFIELD(symbol);
    ASPENFIELD(state);
    ASPENFIELD(reserved_1);
    ASPENFIELD(info);
};

static_assert(sizeof(symbol_state_message) == symbol_state_message::size, "symbol_state_message lies over its bytes exactly");

// Symbol Information Message: Reference data for each symbol that may be traded
struct symbol_information_message {
    static constexpr std::string_view name = "Symbol Information Message";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        symbol_id,
        symbol,
        listing_market,
        board_lot_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(timestamp);
    ASPENFIELD(symbol_id);
    ASPENFIELD(symbol);
    ASPENFIELD(listing_market);
    ASPENFIELD(board_lot_size);
};

static_assert(sizeof(symbol_information_message) == symbol_information_message::size, "symbol_information_message lies over its bytes exactly");

// Market Event Message: Transitions in the overall session state
struct market_event_message {
    static constexpr std::string_view name = "Market Event Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reserved_2,
        timestamp,
        event>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(reserved_2);
    ASPENFIELD(timestamp);
    ASPENFIELD(event);
};

static_assert(sizeof(market_event_message) == market_event_message::size, "market_event_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Length of the message
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        length_type,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(length_type);
    ASPENFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        market_day_identifier,
        feed_identifier,
        sequence,
        count_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ASPENFIELD(market_day_identifier);
    ASPENFIELD(feed_identifier);
    ASPENFIELD(sequence);
    ASPENFIELD(count_type);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Aspen Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    ASPENSEQUENCE(message);
};

#pragma pack(pop)

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
