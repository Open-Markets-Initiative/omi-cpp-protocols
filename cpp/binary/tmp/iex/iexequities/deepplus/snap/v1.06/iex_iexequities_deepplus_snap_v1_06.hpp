// Iex IexEquities DeepPlus Snap 1.06 Template Meta Programming

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
#ifndef SNAPFIELD
#define SNAPFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef SNAPSEQUENCE
#define SNAPSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace iex::iexequities::deepplus::snap::v1_06 {

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

// Adjusted Poc Price: Corporate action adjusted previous official closing price
struct adjusted_poc_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Authentication Token: Token supplied by Iex Market Ops, left justified and space padded on the right
struct authentication_token {
    using type = std::string_view;
    static constexpr std::size_t size = 40;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 40> value_;
};

// Channel Id: Channel identifier from the Deep Plus feed IexTp header
struct channel_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Detail: Detail of the Reg. SHO short sale price test restriction status
struct detail {
    enum class type : char {
        no_price_test_in_place = ' ',
        short_sale_price_test_restriction_in_effect_due_to_an_intraday_price_drop_in_the_security = 'A',
        short_sale_price_test_restriction_remains_in_effect_from_prior_day = 'C',
        short_sale_price_test_restriction_deactivated = 'D',
        not_available = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Etp: Symbol is an ETP
struct etp {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Extended Hours: Extended Hours Trade
struct extended_hours {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// First Message Sequence Number: Sequence of the first message in the segment
struct first_message_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Iex Tp Message Block Length: Length in bytes of the IexTp message block that follows this field: the IexTp Message Length field and the message
struct iex_tp_message_block_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Iex Tp Message Length: Length of the wrapped Deep Plus message in bytes not including this field
struct iex_tp_message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Iex Tp Message Type: Code identifying the wrapped Deep Plus message type
struct iex_tp_message_type {
    enum class type : char {
        system_event_message = 'S',
        security_directory_message = 'D',
        trading_status_message = 'H',
        retail_liquidity_indicator_message = 'I',
        operational_halt_status_message = 'O',
        short_sale_price_test_status_message = 'P',
        security_event_message = 'E',
        add_order_message = 'a',
        order_modify_message = 'M',
        order_delete_message = 'R',
        order_executed_message = 'L',
        trade_message = 'T',
        trade_break_message = 'B',
        clear_book_message = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Intermarket Sweep: Intermarket Sweep Order
struct intermarket_sweep {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Luld Tier: Indicates which Limit Up-Limit Down price band calculation parameter is to be used
struct luld_tier {
    enum class type : std::uint8_t {
        not_applicable = 0,
        tier_1_nms_stock = 1,
        tier_2_nms_stock = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Count: Number of messages in the payload
struct message_count {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Length of message in bytes not including this field
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Protocol Id: Unique identifier of the higher layer protocol
struct message_protocol_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: Code identifying this message type
struct message_type {
    enum class type : char {
        snapshot_request_message = 'r',
        error_response_message = 'e',
        snapshot_start_message = 's',
        snapshot_data_message = 'd',
        snapshot_end_message = 'x',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Minimum Sequence Number: Minimum sequence number useable by the client, zero returns the latest snapshot available
struct minimum_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Odd Lot
struct odd_lot {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Operational Halt Status: Operational halt status identifier
struct operational_halt_status {
    enum class type : char {
        iex_specific_operational_trading_halt = 'O',
        not_operationally_halted_on_iex = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Id: Order ID of new order
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id Reference: Order ID of the referenced order
struct order_id_reference {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Payload Length: Byte length of the payload
struct payload_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: Booking price on the IEX Order Book
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Priority: Order Priority
struct priority {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Reason: Reason for the trading status change
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reject Reason Code: Reason the Snapshot Request was rejected
struct reject_reason_code {
    enum class type : char {
        authentication_failure = 'A',
        incorrect_channel_id = 'C',
        snapshot_request_already_active = 'E',
        quota_exceeded = 'Q',
        snapshot_not_yet_available = 'R',
        incorrect_session_id = 'S',
        unknown_message = 'U',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reserved: Reserved byte
struct reserved {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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

// Retail Liquidity Indicator: Retail Liquidity Indicator identifier
struct retail_liquidity_indicator {
    enum class type : char {
        not_applicable = ' ',
        buy_interest = 'A',
        sell_interest = 'B',
        buy_and_sell_interest = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Round Lot Size: Number of shares that represent a round lot
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Event: Security event identifier
struct security_event {
    enum class type : char {
        opening_process_complete = 'O',
        closing_process_complete = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Send Time: Send time of segment
struct send_time {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: Session identifier from the Deep Plus feed IexTp header
struct session_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Short Sale Price Test Status: Reg. SHO short sale price test restriction status
struct short_sale_price_test_status {
    enum class type : std::uint8_t {
        not_in_effect = 0,
        in_effect = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side: Side of order
struct side {
    enum class type : char {
        buy = '8',
        sell = '5',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Single Price Cross Trade: Trade resulting from a single-price cross
struct single_price_cross_trade {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Size: Quoted size
struct size_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Snapshot Length: Length in bytes of the complete Snapshot Response including the Snapshot Start message, all Snapshot Data messages, and the Snapshot End message
struct snapshot_length {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Snapshot Sequence Number: Sequence at which the snapshot was created
struct snapshot_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stream Offset: Byte offset of the data stream
struct stream_offset {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol: Security identifier
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// System Event: System event identifier
struct system_event {
    enum class type : char {
        start_of_messages = 'O',
        start_of_system_hours = 'S',
        start_of_regular_market_hours = 'R',
        end_of_regular_market_hours = 'M',
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

// Test Security: Symbol is a test security
struct test_security {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Timestamp: Time stamp of the system event
struct timestamp {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: IEX Generated Identifier
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Through Exempt: Trade is not subject to Rule 611
struct trade_through_exempt {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Trading Status: Trading status identifier
struct trading_status {
    enum class type : char {
        trading_halted_across_all_us_equity_markets = 'H',
        trading_halt_released_into_an_order_acceptance_period_on_iex = 'O',
        trading_paused_and_order_acceptance_period_on_iex = 'P',
        trading_on_iex = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Unused 3: Unused
struct unused_3 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x7ULL;
    static constexpr int shift = 0;
};

// Unused 5: Unused
struct unused_5 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x1FULL;
    static constexpr int shift = 0;
};

// Unused 7: Unused
struct unused_7 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x7FULL;
    static constexpr int shift = 0;
};

// Version: Version of transport specification
struct version {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// When Issued: Symbol is a when issued security
struct when_issued {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Snapshot End Message: Final message of a Snapshot Response, carries the sequence number at which the snapshot was created
struct snapshot_end_message {
    static constexpr std::string_view name = "Snapshot End Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        snapshot_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(snapshot_sequence_number);
};

static_assert(sizeof(snapshot_end_message) == snapshot_end_message::size, "snapshot_end_message lies over its bytes exactly");

// Clear Book Message: This message is used to indicate that the IEX Book for a symbol has been cleared of all orders
struct clear_book_message {
    static constexpr std::string_view name = "Clear Book Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reserved_1,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(reserved_1);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
};

static_assert(sizeof(clear_book_message) == clear_book_message::size, "clear_book_message lies over its bytes exactly");

// Sale Condition Flags
struct sale_condition_flags {
    static constexpr std::string_view name = "Sale Condition Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(sale_condition_flags) == sale_condition_flags::size, "sale_condition_flags lies over its bytes exactly");

// Trade Break Message: Trade Break Messages are sent when an execution on IEX is broken on that same trading day
struct trade_break_message {
    static constexpr std::string_view name = "Trade Break Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_condition_flags,
        timestamp,
        symbol,
        size_type,
        price,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(sale_condition_flags);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(size_type);
    SNAPFIELD(price);
    SNAPFIELD(trade_id);
};

static_assert(sizeof(trade_break_message) == trade_break_message::size, "trade_break_message lies over its bytes exactly");

// Trade Message: A non-displayed order on the book that executed against another non-displayed order on the book
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_condition_flags,
        timestamp,
        symbol,
        size_type,
        price,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(sale_condition_flags);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(size_type);
    SNAPFIELD(price);
    SNAPFIELD(trade_id);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Executed Message: A displayed order that was executed against
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 45;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_condition_flags,
        timestamp,
        symbol,
        order_id_reference,
        size_type,
        price,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(sale_condition_flags);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(order_id_reference);
    SNAPFIELD(size_type);
    SNAPFIELD(price);
    SNAPFIELD(trade_id);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Order Delete Message: A displayed order that was removed from the IEX Book
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reserved_1,
        timestamp,
        symbol,
        order_id_reference>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(reserved_1);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(order_id_reference);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Modify Flags
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

// Order Modify Message: A displayed order that had its Price, Size, or Priority component changed as a result of user or system action
struct order_modify_message {
    static constexpr std::string_view name = "Order Modify Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        modify_flags,
        timestamp,
        symbol,
        order_id_reference,
        size_type,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(modify_flags);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(order_id_reference);
    SNAPFIELD(size_type);
    SNAPFIELD(price);
};

static_assert(sizeof(order_modify_message) == order_modify_message::size, "order_modify_message lies over its bytes exactly");

// Add Order Message: A displayed order that has been added to the IEX Book
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        timestamp,
        symbol,
        order_id,
        size_type,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(side);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(order_id);
    SNAPFIELD(size_type);
    SNAPFIELD(price);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Security Event Message: The Security Event Message is used to indicate events that apply to a security
struct security_event_message {
    static constexpr std::string_view name = "Security Event Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_event,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(security_event);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
};

static_assert(sizeof(security_event_message) == security_event_message::size, "security_event_message lies over its bytes exactly");

// Short Sale Price Test Status Message: The Short Sale Price Test Message is used to indicate when a short sale price test restriction is in effect for a security.
struct short_sale_price_test_status_message {
    static constexpr std::string_view name = "Short Sale Price Test Status Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        short_sale_price_test_status,
        timestamp,
        symbol,
        detail>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(short_sale_price_test_status);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(detail);
};

static_assert(sizeof(short_sale_price_test_status_message) == short_sale_price_test_status_message::size, "short_sale_price_test_status_message lies over its bytes exactly");

// Operational Halt Status Message: The Exchange may suspend trading of one or more securities on IEX for operational reasons and indicates such operational halt using the Operational Halt Status Message.
struct operational_halt_status_message {
    static constexpr std::string_view name = "Operational Halt Status Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        operational_halt_status,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(operational_halt_status);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
};

static_assert(sizeof(operational_halt_status_message) == operational_halt_status_message::size, "operational_halt_status_message lies over its bytes exactly");

// Retail Liquidity Indicator Message: broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to IEX's eligible retail liquidity interest during the trading day
struct retail_liquidity_indicator_message {
    static constexpr std::string_view name = "Retail Liquidity Indicator Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        retail_liquidity_indicator,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(retail_liquidity_indicator);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
};

static_assert(sizeof(retail_liquidity_indicator_message) == retail_liquidity_indicator_message::size, "retail_liquidity_indicator_message lies over its bytes exactly");

// Trading Status Message: The Trading Status Message is used to indicate the current trading status of a security.
struct trading_status_message {
    static constexpr std::string_view name = "Trading Status Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trading_status,
        timestamp,
        symbol,
        reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(trading_status);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(reason);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Security Directory Flags
struct security_directory_flags {
    static constexpr std::string_view name = "Security Directory Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(security_directory_flags) == security_directory_flags::size, "security_directory_flags lies over its bytes exactly");

// Security Directory Message: The System Event Message is used to indicate events that apply to the market or the data feed.
struct security_directory_message {
    static constexpr std::string_view name = "Security Directory Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_directory_flags,
        timestamp,
        symbol,
        round_lot_size,
        adjusted_poc_price,
        luld_tier>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(security_directory_flags);
    SNAPFIELD(timestamp);
    SNAPFIELD(symbol);
    SNAPFIELD(round_lot_size);
    SNAPFIELD(adjusted_poc_price);
    SNAPFIELD(luld_tier);
};

static_assert(sizeof(security_directory_message) == security_directory_message::size, "security_directory_message lies over its bytes exactly");

// System Event Message: The System Event Message is used to indicate events that apply to the market or the data feed.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        system_event,
        timestamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(system_event);
    SNAPFIELD(timestamp);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Iex Tp Message Data: One complete Iex Deep Plus formatted message, may be any Deep Plus message type, see the Iex Transport specification
struct iex_tp_message_data {
    static constexpr std::string_view name = "Iex Tp Message Data";
    static constexpr bool is_message = false;
};

// Iextp Header: IexTp header of the wrapped feed message
struct iextp_header {
    static constexpr std::string_view name = "Iextp Header";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        version,
        reserved,
        message_protocol_id,
        channel_id,
        session_id,
        payload_length,
        message_count,
        stream_offset,
        first_message_sequence_number,
        send_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(version);
    SNAPFIELD(reserved);
    SNAPFIELD(message_protocol_id);
    SNAPFIELD(channel_id);
    SNAPFIELD(session_id);
    SNAPFIELD(payload_length);
    SNAPFIELD(message_count);
    SNAPFIELD(stream_offset);
    SNAPFIELD(first_message_sequence_number);
    SNAPFIELD(send_time);
};

static_assert(sizeof(iextp_header) == iextp_header::size, "iextp_header lies over its bytes exactly");

// Snapshot Data Message Section 1
struct snapshot_data_message_section_1 {
    static constexpr std::string_view name = "Snapshot Data Message Section 1";
    static constexpr std::size_t size = 45;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        iextp_header,
        iex_tp_message_block_length,
        iex_tp_message_length,
        iex_tp_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(iextp_header);
    SNAPFIELD(iex_tp_message_block_length);
    SNAPFIELD(iex_tp_message_length);
    SNAPFIELD(iex_tp_message_type);
};

static_assert(sizeof(snapshot_data_message_section_1) == snapshot_data_message_section_1::size, "snapshot_data_message_section_1 lies over its bytes exactly");

// Snapshot Data Message: Carries one complete Deep Plus feed message wrapped with an IexTp header providing Deep Plus feed sequencing and timing information
struct snapshot_data_message {
    static constexpr std::string_view name = "Snapshot Data Message";
    static constexpr bool is_message = false;
};

// Snapshot Start Message: First message of a Snapshot Response sent from the Deep Plus Snap server when a Snapshot Request is successful
struct snapshot_start_message {
    static constexpr std::string_view name = "Snapshot Start Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        snapshot_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(snapshot_length);
};

static_assert(sizeof(snapshot_start_message) == snapshot_start_message::size, "snapshot_start_message lies over its bytes exactly");

// Error Response Message: Sent by the Deep Plus Snap server to the client when a Snapshot Request is rejected
struct error_response_message {
    static constexpr std::string_view name = "Error Response Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reject_reason_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(reject_reason_code);
};

static_assert(sizeof(error_response_message) == error_response_message::size, "error_response_message lies over its bytes exactly");

// Snapshot Request Message: The Snapshot Request message is sent from the client to the Deep Plus Snap server to authenticate and request a Snapshot Response
struct snapshot_request_message {
    static constexpr std::string_view name = "Snapshot Request Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        authentication_token,
        channel_id,
        session_id,
        minimum_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    SNAPFIELD(authentication_token);
    SNAPFIELD(channel_id);
    SNAPFIELD(session_id);
    SNAPFIELD(minimum_sequence_number);
};

static_assert(sizeof(snapshot_request_message) == snapshot_request_message::size, "snapshot_request_message lies over its bytes exactly");

// Message Data: Branch
struct message_data {
    static constexpr std::string_view name = "Message Data";
    static constexpr bool is_message = false;
};

// Message Header: Snap message header
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
    SNAPFIELD(message_length);
    SNAPFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Snap message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Packet: Snap Tcp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace iex::iexequities::deepplus::snap::v1_06
