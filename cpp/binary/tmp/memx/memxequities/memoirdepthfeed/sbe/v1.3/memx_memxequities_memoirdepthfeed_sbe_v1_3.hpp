// Memx MemxEquities MemoirDepthFeed Sbe 1.3 Template Meta Programming

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
#ifndef MEMOIRDEPTHFEEDFIELD
#define MEMOIRDEPTHFEEDFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef MEMOIRDEPTHFEEDSEQUENCE
#define MEMOIRDEPTHFEEDSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

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

// As Of Sequence Number: AsOfSequenceNumber
struct as_of_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Length: Memx Udp Message Type
struct block_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Price: CorrectedPrice
struct corrected_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Quantity: CorrectedQuantity
struct corrected_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Header Length: Total bytes in this header
struct header_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Is Test Symbol: IsTestSymbol
struct is_test_symbol {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Count: Number of messages in this packet
struct message_count {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Number of bytes in the following message
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type
struct message_type {
    enum class type : std::uint8_t {
        heartbeat_message = 0,
        session_shutdown_message = 1,
        sequenced_message = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mpv
struct mpv {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: OrderId
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Price: OriginalPrice
struct original_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Quantity: OriginalQuantity
struct original_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity
struct quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved
struct reserved {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Round Lot: RoundLot
struct round_lot {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Schema Id: The identifier of a message schema
struct schema_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Id: SecurityID
struct security_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Trading Status: SecurityTradingStatus
struct security_trading_status {
    enum class type : char {
        halted = 'H',
        paused = 'P',
        quoting = 'Q',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Trading Status Reason: SecurityTradingStatusReason
struct security_trading_status_reason {
    enum class type : char {
        none = 'X',
        regulatory = 'R',
        administrative = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sequence Number
struct sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: Session identifier
struct session_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Short Sale Restriction: ShortSaleRestriction
struct short_sale_restriction {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
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

// Symbol
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Symbol Sfx: SymbolSfx
struct symbol_sfx {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Template Id: T8 Identifier of the message template
struct template_id {
    enum class type : std::uint8_t {
        instrument_directory_message = 1,
        reg_sho_restriction_message = 2,
        security_trading_status_message = 3,
        trading_session_status_message = 5,
        order_added_message = 10,
        order_deleted_message = 11,
        order_reduced_message = 12,
        order_executed_message = 13,
        trade_message = 14,
        broken_trade_message = 15,
        corrected_trade_message = 16,
        clear_book_message = 18,
        snapshot_complete_message = 100,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Timestamp
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: TradeId
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Session: TradingSession
struct trading_session {
    enum class type : char {
        opening = '1',
        trading = '2',
        post_trading = '3',
        closed = '4',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Version: The version number of the message schema that was used to encode a message
struct version {
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

// Snapshot Complete Message: SnapshotCompleteMessage
struct snapshot_complete_message {
    static constexpr std::string_view name = "Snapshot Complete Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        as_of_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(as_of_sequence_number);
};

static_assert(sizeof(snapshot_complete_message) == snapshot_complete_message::size, "snapshot_complete_message lies over its bytes exactly");

// Clear Book Message: ClearBookMessage
struct clear_book_message {
    static constexpr std::string_view name = "Clear Book Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
};

static_assert(sizeof(clear_book_message) == clear_book_message::size, "clear_book_message lies over its bytes exactly");

// Corrected Trade Message: CorrectedTradeMessage
struct corrected_trade_message {
    static constexpr std::string_view name = "Corrected Trade Message";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        trade_id,
        original_quantity,
        original_price,
        corrected_quantity,
        corrected_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(trade_id);
    MEMOIRDEPTHFEEDFIELD(original_quantity);
    MEMOIRDEPTHFEEDFIELD(original_price);
    MEMOIRDEPTHFEEDFIELD(corrected_quantity);
    MEMOIRDEPTHFEEDFIELD(corrected_price);
};

static_assert(sizeof(corrected_trade_message) == corrected_trade_message::size, "corrected_trade_message lies over its bytes exactly");

// Broken Trade Message: BrokenTradeMessage
struct broken_trade_message {
    static constexpr std::string_view name = "Broken Trade Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        trade_id,
        original_quantity,
        original_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(trade_id);
    MEMOIRDEPTHFEEDFIELD(original_quantity);
    MEMOIRDEPTHFEEDFIELD(original_price);
};

static_assert(sizeof(broken_trade_message) == broken_trade_message::size, "broken_trade_message lies over its bytes exactly");

// Trade Message: TradeMessage
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        trade_id,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(trade_id);
    MEMOIRDEPTHFEEDFIELD(quantity);
    MEMOIRDEPTHFEEDFIELD(price);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Executed Message: OrderExecutedMessage
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        order_id,
        trade_id,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(order_id);
    MEMOIRDEPTHFEEDFIELD(trade_id);
    MEMOIRDEPTHFEEDFIELD(quantity);
    MEMOIRDEPTHFEEDFIELD(price);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Order Reduced Message: OrderReducedMessage
struct order_reduced_message {
    static constexpr std::string_view name = "Order Reduced Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        order_id,
        quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(order_id);
    MEMOIRDEPTHFEEDFIELD(quantity);
};

static_assert(sizeof(order_reduced_message) == order_reduced_message::size, "order_reduced_message lies over its bytes exactly");

// Order Deleted Message: OrderDeletedMessage
struct order_deleted_message {
    static constexpr std::string_view name = "Order Deleted Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(order_id);
};

static_assert(sizeof(order_deleted_message) == order_deleted_message::size, "order_deleted_message lies over its bytes exactly");

// Order Added Message: OrderAddedMessage
struct order_added_message {
    static constexpr std::string_view name = "Order Added Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        order_id,
        side,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(order_id);
    MEMOIRDEPTHFEEDFIELD(side);
    MEMOIRDEPTHFEEDFIELD(quantity);
    MEMOIRDEPTHFEEDFIELD(price);
};

static_assert(sizeof(order_added_message) == order_added_message::size, "order_added_message lies over its bytes exactly");

// Trading Session Status Message: TradingSessionStatusMessage
struct trading_session_status_message {
    static constexpr std::string_view name = "Trading Session Status Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        trading_session>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(trading_session);
};

static_assert(sizeof(trading_session_status_message) == trading_session_status_message::size, "trading_session_status_message lies over its bytes exactly");

// Security Trading Status Message: SecurityTradingStatusMessage
struct security_trading_status_message {
    static constexpr std::string_view name = "Security Trading Status Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        security_trading_status,
        security_trading_status_reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(security_trading_status);
    MEMOIRDEPTHFEEDFIELD(security_trading_status_reason);
};

static_assert(sizeof(security_trading_status_message) == security_trading_status_message::size, "security_trading_status_message lies over its bytes exactly");

// Reg Sho Restriction Message: RegSHORestrictionMessage
struct reg_sho_restriction_message {
    static constexpr std::string_view name = "Reg Sho Restriction Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        short_sale_restriction>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(short_sale_restriction);
};

static_assert(sizeof(reg_sho_restriction_message) == reg_sho_restriction_message::size, "reg_sho_restriction_message lies over its bytes exactly");

// Instrument Directory Message: InstrumentDirectoryMessage
struct instrument_directory_message {
    static constexpr std::string_view name = "Instrument Directory Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        security_id,
        symbol,
        symbol_sfx,
        round_lot,
        reserved,
        is_test_symbol,
        mpv>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(timestamp);
    MEMOIRDEPTHFEEDFIELD(security_id);
    MEMOIRDEPTHFEEDFIELD(symbol);
    MEMOIRDEPTHFEEDFIELD(symbol_sfx);
    MEMOIRDEPTHFEEDFIELD(round_lot);
    MEMOIRDEPTHFEEDFIELD(reserved);
    MEMOIRDEPTHFEEDFIELD(is_test_symbol);
    MEMOIRDEPTHFEEDFIELD(mpv);
};

static_assert(sizeof(instrument_directory_message) == instrument_directory_message::size, "instrument_directory_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Sbe Header
struct sbe_header {
    static constexpr std::string_view name = "Sbe Header";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        block_length,
        template_id,
        schema_id,
        version>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(block_length);
    MEMOIRDEPTHFEEDFIELD(template_id);
    MEMOIRDEPTHFEEDFIELD(schema_id);
    MEMOIRDEPTHFEEDFIELD(version);
};

static_assert(sizeof(sbe_header) == sbe_header::size, "sbe_header lies over its bytes exactly");

// Sbe Message
struct sbe_message {
    static constexpr std::string_view name = "Sbe Message";
    static constexpr bool is_message = false;
};

// Message Section 1
struct message_section_1 {
    static constexpr std::string_view name = "Message Section 1";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(message_length);
};

static_assert(sizeof(message_section_1) == message_section_1::size, "message_section_1 lies over its bytes exactly");

// Message: Message List Element
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Sequenced Message Section 1
struct sequenced_message_section_1 {
    static constexpr std::string_view name = "Sequenced Message Section 1";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(message_count);
};

static_assert(sizeof(sequenced_message_section_1) == sequenced_message_section_1::size, "sequenced_message_section_1 lies over its bytes exactly");

// Sequenced Message
struct sequenced_message {
    static constexpr std::string_view name = "Sequenced Message";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MEMOIRDEPTHFEEDSEQUENCE(message);
};

// Session Shutdown
struct session_shutdown {
    static constexpr std::string_view name = "Session Shutdown";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Heartbeat
struct heartbeat {
    static constexpr std::string_view name = "Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Sequenced Messages: Branch
struct sequenced_messages {
    static constexpr std::string_view name = "Sequenced Messages";
    static constexpr bool is_message = false;
};

// Common Header
struct common_header {
    static constexpr std::string_view name = "Common Header";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_type,
        header_length,
        session_id,
        sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MEMOIRDEPTHFEEDFIELD(message_type);
    MEMOIRDEPTHFEEDFIELD(header_length);
    MEMOIRDEPTHFEEDFIELD(session_id);
    MEMOIRDEPTHFEEDFIELD(sequence_number);
};

static_assert(sizeof(common_header) == common_header::size, "common_header lies over its bytes exactly");

// Packet: Datagram
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
