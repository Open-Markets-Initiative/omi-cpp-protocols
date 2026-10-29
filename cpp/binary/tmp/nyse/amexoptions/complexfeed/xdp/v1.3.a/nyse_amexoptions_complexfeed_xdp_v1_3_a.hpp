// Nyse AmexOptions ComplexFeed Xdp 1.3.a Template Meta Programming

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
#ifndef XDPFIELD
#define XDPFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef XDPSEQUENCE
#define XDPSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

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

// Ask Customer Volume: Total quantity of ‘Customer’ orders available at the above Ask price.
struct ask_customer_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Price: Best Ask price*. Should be used with the Price Scale Code from the Underlying Index Mapping message.
struct ask_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Volume: Total quantity available at the above Ask price.
struct ask_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Customer Volume: Total quantity of ‘Customer’ orders available at the above Bid price.
struct bid_customer_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price: Best Bid price*. Should be used with the Price Scale Code from the Underlying Index Mapping message.
struct bid_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Volume: Total quantity available at the above Bid price.
struct bid_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Channel Id: Multicast channel ID of the symbols being provided.
struct channel_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Complex Index: The unique ID of the symbol in the Complex Index msg
struct complex_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Complex Symbol: Complex Symbol. This is an alpha numeric symbol which can be used for a unique strategy until one of the legs expire.
struct complex_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 21;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 21> value_;
};

// Delivery Flag: A flag that indicates whether this is an original, retransmitted, or ‘replayed’ message.
struct delivery_flag {
    enum class type : std::uint8_t {
        heartbeat = 1,
        contains_original_and_refresh_msgs = 2,
        contains_only_refresh_messages = 3,
        xdp_failover = 10,
        contains_only_original_messages = 11,
        sequence_number_reset_message = 12,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Halt Condition: Not applicable
struct halt_condition {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Leg Ratio Qty: Leg ratio
struct leg_ratio_qty {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Type
struct leg_security_type {
    enum class type : char {
        options_series_leg = 'O',
        equity_stock_leg = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Id: Identifies originating market
struct market_id {
    enum class type : std::uint16_t {
        nyse_cash = 1,
        europe_cash = 2,
        nyse_arca_cash = 3,
        nyse_arca_options = 4,
        nyse_arca_bonds = 5,
        arca_edge = 6,
        liffe = 7,
        nyse_american_options = 8,
        nyse_mkt_cash = 9,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Count: The number of messages in this packet
struct message_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Size: Size of the message body in bytes including this field.
struct message_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: The type of this message
struct message_type {
    enum class type : std::uint16_t {
        complex_quote_message = 423,
        complex_trade_message = 425,
        complex_crossing_rfq_message = 429,
        complex_cube_rfq_message = 472,
        complex_status_message = 433,
        refresh_complex_quote_message = 511,
        refresh_complex_trade_message = 513,
        complex_symbol_definition_message = 439,
        stream_id_message = 455,
        sequence_number_reset_message = 1,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Nanoseconds: The nanosecond offset from the Send Time
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Of Legs: Number of legs in complex symbol: 1 – 5
struct no_of_legs {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Size: The size of the packet in bytes, including this 16 byte packet header
struct packet_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: The net amount of money made by the Seller* (the price of the Sell legs minus the price of the Buy legs).
struct price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Product Id: The unique ID for this NYSE feed listed in the feed’s client specification.
struct product_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Condition: QuoteCondition value
struct quote_condition {
    enum class type : char {
        regular_trading = '1',
        rotation = '2',
        trading_halted = '3',
        pre_open = '4',
        rotation_legal_width_quote_pending = '5',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reserved 1: Filler
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 2: Filler
struct reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seconds: The time when this packet was published to the multicast channel, in seconds since Jan 1, 1970 00:00:00 UTC.
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Status: SecurityStatus value
struct security_status {
    enum class type : char {
        light_up_a_dark_series = 'L',
        open_a_dark_series = 'N',
        open = 'O',
        close = 'X',
        halt = 'S',
        unhalt = 'U',
        unhalt_a_dark_series = 'T',
        end_of_rfq_auction = 'Q',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sequence Number: The message sequence number of the first message in this packet
struct sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side: Side of the RFQ
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

// Source Ns: The nanosecond offset from the SourceTime.
struct source_ns {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Source Time: The time when this msg was generated in the order book, in seconds since Jan 1, 1970 00:00:00 UTC.
struct source_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Source Time Ns: The nanosecond offset from the SourceTime.
struct source_time_ns {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stream Id: Identifies Stream on which this symbol will be updated
struct stream_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Index: Series index if Security type is Option. Underlying index if Security type is Equity
struct symbol_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Seq Num: Sequence number of messages for the complex symbol.
struct symbol_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Id: Identifies Trading unit (TU)
struct system_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Cond 1: TradeCond1 value
struct trade_cond_1 {
    enum class type : char {
        regular_trade = ' ',
        late_report = 'I',
        floor_trade = 'R',
        so_sweep_trade = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Cond 2: (blank) n/a for complex symbols
struct trade_cond_2 {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Trade Id: n/a for complex symbols
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume 2: Total quantity
struct volume_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume 4: Volume of the trade in actual number of contracts
struct volume_4 {
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

// Sequence Number Reset Message: This message is sent to reset the Message Sequence Number at start of day, or in response to failures.
struct sequence_number_reset_message {
    static constexpr std::string_view name = "Sequence Number Reset Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        product_id,
        channel_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(product_id);
    XDPFIELD(channel_id);
};

static_assert(sizeof(sequence_number_reset_message) == sequence_number_reset_message::size, "sequence_number_reset_message lies over its bytes exactly");

// Stream Id Message: In all multicast channels, a Stream ID Message is sent immediately after each packet header to uniquely identify the source or Stream ID of the data in the packet.
struct stream_id_message {
    static constexpr std::string_view name = "Stream Id Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stream_id,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(stream_id);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(stream_id_message) == stream_id_message::size, "stream_id_message lies over its bytes exactly");

// Leg Definition
struct leg_definition {
    static constexpr std::string_view name = "Leg Definition";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_index,
        leg_ratio_qty,
        side,
        leg_security_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(symbol_index);
    XDPFIELD(leg_ratio_qty);
    XDPFIELD(side);
    XDPFIELD(leg_security_type);
};

static_assert(sizeof(leg_definition) == leg_definition::size, "leg_definition lies over its bytes exactly");

// Complex Symbol Definition Message Section 1
struct complex_symbol_definition_message_section_1 {
    static constexpr std::string_view name = "Complex Symbol Definition Message Section 1";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        complex_index,
        complex_symbol,
        channel_id,
        market_id,
        system_id,
        reserved_1,
        stream_id,
        no_of_legs,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(complex_index);
    XDPFIELD(complex_symbol);
    XDPFIELD(channel_id);
    XDPFIELD(market_id);
    XDPFIELD(system_id);
    XDPFIELD(reserved_1);
    XDPFIELD(stream_id);
    XDPFIELD(no_of_legs);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(complex_symbol_definition_message_section_1) == complex_symbol_definition_message_section_1::size, "complex_symbol_definition_message_section_1 lies over its bytes exactly");

// Complex Symbol Definition Message: The Complex Symbol Definition message provides a description of the legs in a Complex symbol, and specifies its Complex symbol ID, which is unique for its stream. If the same symbol ID appears in a different stream, it represents a different Complex symbol.
struct complex_symbol_definition_message {
    static constexpr std::string_view name = "Complex Symbol Definition Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    XDPSEQUENCE(leg_definition);
};

// Refresh Complex Trade Message: The Refresh Complex Trade message is sent in the event no Complex Trade messages are published for the symbol for 2 consecutive minutes.
struct refresh_complex_trade_message {
    static constexpr std::string_view name = "Refresh Complex Trade Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        complex_index,
        symbol_seq_num,
        trade_id,
        price,
        volume_4,
        trade_cond_1,
        trade_cond_2,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(trade_id);
    XDPFIELD(price);
    XDPFIELD(volume_4);
    XDPFIELD(trade_cond_1);
    XDPFIELD(trade_cond_2);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(refresh_complex_trade_message) == refresh_complex_trade_message::size, "refresh_complex_trade_message lies over its bytes exactly");

// Refresh Complex Quote Message: The Refresh Complex Quote message is sent in the event no quote messages are published for the symbol for 2 consecutive minutes.
struct refresh_complex_quote_message {
    static constexpr std::string_view name = "Refresh Complex Quote Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        complex_index,
        symbol_seq_num,
        ask_price,
        bid_price,
        ask_volume,
        bid_volume,
        ask_customer_volume,
        bid_customer_volume,
        quote_condition,
        reserved_1,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(ask_price);
    XDPFIELD(bid_price);
    XDPFIELD(ask_volume);
    XDPFIELD(bid_volume);
    XDPFIELD(ask_customer_volume);
    XDPFIELD(bid_customer_volume);
    XDPFIELD(quote_condition);
    XDPFIELD(reserved_1);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(refresh_complex_quote_message) == refresh_complex_quote_message::size, "refresh_complex_quote_message lies over its bytes exactly");

// Complex Status Message: The Complex Status message is used to inform the subscribers of changes in symbol status of a complex symbol.
struct complex_status_message {
    static constexpr std::string_view name = "Complex Status Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        complex_index,
        symbol_seq_num,
        security_status,
        halt_condition,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(security_status);
    XDPFIELD(halt_condition);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(complex_status_message) == complex_status_message::size, "complex_status_message lies over its bytes exactly");

// Complex Cube Rfq Message
struct complex_cube_rfq_message {
    static constexpr std::string_view name = "Complex Cube Rfq Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_ns,
        complex_index,
        symbol_seq_num,
        side,
        reserved_1,
        volume_2,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(side);
    XDPFIELD(reserved_1);
    XDPFIELD(volume_2);
    XDPFIELD(price);
};

static_assert(sizeof(complex_cube_rfq_message) == complex_cube_rfq_message::size, "complex_cube_rfq_message lies over its bytes exactly");

// Complex Crossing Rfq Message: The Complex Crossing RFQ (Request for Quote) message is sent out in the event of a COA auction on a complex order.
struct complex_crossing_rfq_message {
    static constexpr std::string_view name = "Complex Crossing Rfq Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_ns,
        complex_index,
        symbol_seq_num,
        side,
        reserved_1,
        volume_2,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(side);
    XDPFIELD(reserved_1);
    XDPFIELD(volume_2);
    XDPFIELD(price);
};

static_assert(sizeof(complex_crossing_rfq_message) == complex_crossing_rfq_message::size, "complex_crossing_rfq_message lies over its bytes exactly");

// Complex Trade Message: The Complex Trade message is used to publish all complex Last Sales.
struct complex_trade_message {
    static constexpr std::string_view name = "Complex Trade Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        complex_index,
        symbol_seq_num,
        trade_id,
        price,
        volume_4,
        trade_cond_1,
        trade_cond_2,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(trade_id);
    XDPFIELD(price);
    XDPFIELD(volume_4);
    XDPFIELD(trade_cond_1);
    XDPFIELD(trade_cond_2);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(complex_trade_message) == complex_trade_message::size, "complex_trade_message lies over its bytes exactly");

// Complex Quote Message: The Complex Quote message is a two-sided message providing best bid and offer limits of orders on complex symbols with aggregated volumes at each limit.
struct complex_quote_message {
    static constexpr std::string_view name = "Complex Quote Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        complex_index,
        symbol_seq_num,
        ask_price,
        bid_price,
        ask_volume,
        bid_volume,
        ask_customer_volume,
        bid_customer_volume,
        quote_condition,
        reserved_1,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(complex_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(ask_price);
    XDPFIELD(bid_price);
    XDPFIELD(ask_volume);
    XDPFIELD(bid_volume);
    XDPFIELD(ask_customer_volume);
    XDPFIELD(bid_customer_volume);
    XDPFIELD(quote_condition);
    XDPFIELD(reserved_1);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(complex_quote_message) == complex_quote_message::size, "complex_quote_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_size,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(message_size);
    XDPFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Send Time: The time when this packet was published to the multicast channel
struct send_time {
    static constexpr std::string_view name = "Send Time";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        seconds,
        nanoseconds>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(seconds);
    XDPFIELD(nanoseconds);
};

static_assert(sizeof(send_time) == send_time::size, "send_time lies over its bytes exactly");

// Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_size,
        delivery_flag,
        message_count,
        sequence_number,
        send_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(packet_size);
    XDPFIELD(delivery_flag);
    XDPFIELD(message_count);
    XDPFIELD(sequence_number);
    XDPFIELD(send_time);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Xdp Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    XDPSEQUENCE(message);
};

#pragma pack(pop)

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
