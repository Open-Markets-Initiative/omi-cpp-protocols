// Nyse AmexOptions DeepFeed Xdp 1.3.a Template Meta Programming

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

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

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

// Channel Id: Multicast channel ID of the symbols being provided.
struct channel_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier: Contract quantity
struct contract_multiplier {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Exchange Code: Exchanges where it is listed
struct exchange_code {
    enum class type : char {
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        nyse_mkt = 'A',
        global_otc = '1',
        arca_local_non_tape_b_index = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// First Level Customer Volume: Total volume of customer orders at the first level
struct first_level_customer_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// First Level Price: Price of first buy level
struct first_level_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// First Level Volume: Total volume at first price level
struct first_level_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// First Volume: Total volume at First price level
struct first_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Group Id: Used by Market Makers. Predefined group of series within a given underlying symbol.
struct group_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Maturity Date: YY MM DD
struct maturity_date {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
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
        outright_market_depth_buy_message = 403,
        outright_market_depth_sell_message = 405,
        underlying_status_message = 419,
        outright_series_status_message = 421,
        refresh_outright_market_depth_buy_message = 503,
        refresh_outright_market_depth_sell_message = 505,
        underlying_index_mapping_message = 435,
        series_index_mapping_message = 437,
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

// Option Symbol Root: OCC root of option symbol
struct option_symbol_root {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
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

// Price Resolution: Price Resolution value
struct price_resolution {
    enum class type : std::uint8_t {
        all_penny = 0,
        penny_nickel = 1,
        nickel_dime = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price Scale Code: Price Scale Code for price conversion of the symbol. See Price Formats.
struct price_scale_code {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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

// Put Or Call
struct put_or_call {
    enum class type : std::uint8_t {
        put = 0,
        call = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quote Condition: QuoteCondition values
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

// Reserved A 1: Filler
struct reserved_a_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved B 1: Filler
struct reserved_b_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Level Customer Volume: Total volume of customer orders at the second level
struct second_level_customer_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Level Price: Price of second buy level
struct second_level_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Level Volume: Total volume at second price level
struct second_level_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Volume: Total volume at Second price level
struct second_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

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

// Security Type: Type of Security
struct security_type {
    enum class type : char {
        adr = 'A',
        common_stock = 'C',
        debentures = 'D',
        etf = 'E',
        foreign = 'F',
        american_depository_shares = 'H',
        units = 'I',
        miscliquid_trust = 'M',
        ordinary_shares = 'O',
        preferred_stock = 'P',
        rights = 'R',
        shares_of_beneficiary_interest = 'S',
        test = 'T',
        units_2 = 'U',
        warrant = 'W',
        index = 'X',
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

// Series Index: The unique ID of the symbol in the Series Index message
struct series_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Strike Price: Strike price. ASCII 0-9 with optional decimal point. EG: 51.75, 123
struct strike_price {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Symbol Seq Num: Sequence number of messages for the Outright options symbol.
struct symbol_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Id: ID of the Originating System
struct system_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Third Level Customer Volume: Total volume of customer orders at the third level
struct third_level_customer_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Third Level Price: Price of third buy level
struct third_level_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Third Level Volume: Total volume at third price level
struct third_level_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Third Volume: Total volume at Third price level
struct third_volume {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Index: The unique ID of the symbol in the Series Index message
struct underlying_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Seq Num: Sequence number of messages for the underlying symbol.
struct underlying_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Symbol: Full symbol in NYSE Symbology.
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
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

// Series Index Mapping Message: On system startup, each multicast channel sends all the symbols on its channel. Underlying Index Mapping messages are published first, followed by all Series Index Mapping messages, and for the Complex feed, Complex Symbol Definitions last of all.
struct series_index_mapping_message {
    static constexpr std::string_view name = "Series Index Mapping Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        series_index,
        channel_id,
        reserved_a_1,
        market_id,
        system_id,
        reserved_b_1,
        stream_id,
        underlying_index,
        contract_multiplier,
        maturity_date,
        put_or_call,
        strike_price,
        price_scale_code,
        underlying_symbol,
        option_symbol_root,
        group_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(series_index);
    XDPFIELD(channel_id);
    XDPFIELD(reserved_a_1);
    XDPFIELD(market_id);
    XDPFIELD(system_id);
    XDPFIELD(reserved_b_1);
    XDPFIELD(stream_id);
    XDPFIELD(underlying_index);
    XDPFIELD(contract_multiplier);
    XDPFIELD(maturity_date);
    XDPFIELD(put_or_call);
    XDPFIELD(strike_price);
    XDPFIELD(price_scale_code);
    XDPFIELD(underlying_symbol);
    XDPFIELD(option_symbol_root);
    XDPFIELD(group_id);
};

static_assert(sizeof(series_index_mapping_message) == series_index_mapping_message::size, "series_index_mapping_message lies over its bytes exactly");

// Underlying Index Mapping Message: On system startup, each multicast channel sends all the symbols on its channel. Underlying Index Mapping messages are published first, followed by all Series Index Mapping messages, and for the Complex feed, Complex Symbol Definitions last of all.
struct underlying_index_mapping_message {
    static constexpr std::string_view name = "Underlying Index Mapping Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_index,
        underlying_symbol,
        channel_id,
        market_id,
        system_id,
        exchange_code,
        price_scale_code,
        security_type,
        price_resolution,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(underlying_index);
    XDPFIELD(underlying_symbol);
    XDPFIELD(channel_id);
    XDPFIELD(market_id);
    XDPFIELD(system_id);
    XDPFIELD(exchange_code);
    XDPFIELD(price_scale_code);
    XDPFIELD(security_type);
    XDPFIELD(price_resolution);
    XDPFIELD(reserved_1);
};

static_assert(sizeof(underlying_index_mapping_message) == underlying_index_mapping_message::size, "underlying_index_mapping_message lies over its bytes exactly");

// Refresh Outright Market Depth Sell Message: The Refresh Market Depth Sell message is sent in the event no Sell Market Depth messages are published for the symbol for 2 consecutive minutes.
struct refresh_outright_market_depth_sell_message {
    static constexpr std::string_view name = "Refresh Outright Market Depth Sell Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        symbol_seq_num,
        first_level_price,
        second_level_price,
        third_level_price,
        first_volume,
        second_volume,
        third_volume,
        quote_condition,
        reserved_1,
        first_level_customer_volume,
        second_level_customer_volume,
        third_level_customer_volume,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(series_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(first_level_price);
    XDPFIELD(second_level_price);
    XDPFIELD(third_level_price);
    XDPFIELD(first_volume);
    XDPFIELD(second_volume);
    XDPFIELD(third_volume);
    XDPFIELD(quote_condition);
    XDPFIELD(reserved_1);
    XDPFIELD(first_level_customer_volume);
    XDPFIELD(second_level_customer_volume);
    XDPFIELD(third_level_customer_volume);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(refresh_outright_market_depth_sell_message) == refresh_outright_market_depth_sell_message::size, "refresh_outright_market_depth_sell_message lies over its bytes exactly");

// Refresh Outright Market Depth Buy Message: The Refresh Market Depth Buy message is sent in the event no Buy Market Depth messages are published for the symbol for 2 consecutive minutes.
struct refresh_outright_market_depth_buy_message {
    static constexpr std::string_view name = "Refresh Outright Market Depth Buy Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_ns,
        series_index,
        symbol_seq_num,
        first_level_price,
        second_level_price,
        third_level_price,
        first_volume,
        second_volume,
        third_volume,
        quote_condition,
        reserved_1,
        first_level_customer_volume,
        second_level_customer_volume,
        third_level_customer_volume,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_ns);
    XDPFIELD(series_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(first_level_price);
    XDPFIELD(second_level_price);
    XDPFIELD(third_level_price);
    XDPFIELD(first_volume);
    XDPFIELD(second_volume);
    XDPFIELD(third_volume);
    XDPFIELD(quote_condition);
    XDPFIELD(reserved_1);
    XDPFIELD(first_level_customer_volume);
    XDPFIELD(second_level_customer_volume);
    XDPFIELD(third_level_customer_volume);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(refresh_outright_market_depth_buy_message) == refresh_outright_market_depth_buy_message::size, "refresh_outright_market_depth_buy_message lies over its bytes exactly");

// Outright Series Status Message: The Series Status message is used to inform the subscribers of changes in symbol status of an outright symbol.
struct outright_series_status_message {
    static constexpr std::string_view name = "Outright Series Status Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
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
    XDPFIELD(series_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(security_status);
    XDPFIELD(halt_condition);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(outright_series_status_message) == outright_series_status_message::size, "outright_series_status_message lies over its bytes exactly");

// Underlying Status Message: The Underlying Status message is used to inform the subscribers of changes in the status of an Underlying symbol.
struct underlying_status_message {
    static constexpr std::string_view name = "Underlying Status Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        underlying_index,
        underlying_seq_num,
        security_status,
        halt_condition,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(underlying_index);
    XDPFIELD(underlying_seq_num);
    XDPFIELD(security_status);
    XDPFIELD(halt_condition);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(underlying_status_message) == underlying_status_message::size, "underlying_status_message lies over its bytes exactly");

// Outright Market Depth Sell Message: The Sell Market Depth message provides prices and aggregated volumes for each of the best three Sell levels.
struct outright_market_depth_sell_message {
    static constexpr std::string_view name = "Outright Market Depth Sell Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_ns,
        series_index,
        symbol_seq_num,
        first_level_price,
        second_level_price,
        third_level_price,
        first_volume,
        second_volume,
        third_volume,
        quote_condition,
        reserved_1,
        first_level_customer_volume,
        second_level_customer_volume,
        third_level_customer_volume,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_ns);
    XDPFIELD(series_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(first_level_price);
    XDPFIELD(second_level_price);
    XDPFIELD(third_level_price);
    XDPFIELD(first_volume);
    XDPFIELD(second_volume);
    XDPFIELD(third_volume);
    XDPFIELD(quote_condition);
    XDPFIELD(reserved_1);
    XDPFIELD(first_level_customer_volume);
    XDPFIELD(second_level_customer_volume);
    XDPFIELD(third_level_customer_volume);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(outright_market_depth_sell_message) == outright_market_depth_sell_message::size, "outright_market_depth_sell_message lies over its bytes exactly");

// Outright Market Depth Buy Message: The Buy Market Depth message provides prices and aggregated volumes for each of the best three Buy levels.
struct outright_market_depth_buy_message {
    static constexpr std::string_view name = "Outright Market Depth Buy Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_ns,
        series_index,
        symbol_seq_num,
        first_level_price,
        second_level_price,
        third_level_price,
        first_level_volume,
        second_level_volume,
        third_level_volume,
        quote_condition,
        reserved_1,
        first_level_customer_volume,
        second_level_customer_volume,
        third_level_customer_volume,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_ns);
    XDPFIELD(series_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(first_level_price);
    XDPFIELD(second_level_price);
    XDPFIELD(third_level_price);
    XDPFIELD(first_level_volume);
    XDPFIELD(second_level_volume);
    XDPFIELD(third_level_volume);
    XDPFIELD(quote_condition);
    XDPFIELD(reserved_1);
    XDPFIELD(first_level_customer_volume);
    XDPFIELD(second_level_customer_volume);
    XDPFIELD(third_level_customer_volume);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(outright_market_depth_buy_message) == outright_market_depth_buy_message::size, "outright_market_depth_buy_message lies over its bytes exactly");

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

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
