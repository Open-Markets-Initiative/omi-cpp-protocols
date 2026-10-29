// Cboe C1Options MarketDataFeed Csm 1.4.2 Template Meta Programming

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
#ifndef CSMFIELD
#define CSMFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef CSMSEQUENCE
#define CSMSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

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

// Appl Seq Num: Sequence number for Refresh message, will be set per line and reset to 1 (one) when refresh is completed
struct appl_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Class Key
struct class_key {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Size: The number of contracts per unit of size
struct contract_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Currency Code Length: Not used
struct currency_code_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Currency Code Text: Not used
struct currency_code_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr currency_code_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Eop Exponent: The expected opening price
struct eop_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Eop Mantissa: The expected opening price
struct eop_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Eop Type
struct eop_type {
    enum class type : std::uint8_t {
        undefined = 0,
        opening_price = 1,
        need_more_sellers = 2,
        need_more_buyers = 3,
        no_opening_trades = 4,
        multiple_opening_prices = 5,
        need_quote_to_open = 6,
        price_not_in_quote_range = 7,
        need_dpm_quote_to_open = 8,
        dpm_quote_invalid = 9,
        price_not_in_botr_range = 10,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Eos: The expected opening size
struct eos {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exercise Style
struct exercise_style {
    enum class type : std::uint8_t {
        american = 0,
        european = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// First Msg Seq Num: The sequence number on the first message in this packet
struct first_msg_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio Qty: Leg ratio
struct leg_ratio_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Id: SecurityID of the leg
struct leg_security_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Side
struct leg_side {
    enum class type : char {
        buy_bid = 'B',
        sell_ask = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Legal Market
struct legal_market {
    enum class type : std::uint8_t {
        not_a_legal_market = 0,
        legal_market = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Maturity Date: Expiration date: Format is “YYYYMMDD”. This field is required for options and futures
struct maturity_date {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Strike Price Exponent: The maximum allowable strike price.
struct max_strike_price_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Strike Price Mantissa: The maximum allowable strike price.
struct max_strike_price_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Control Type
struct md_control_type {
    enum class type : std::uint8_t {
        start_of_summary = 0,
        end_of_summary = 1,
        start_of_settlement = 2,
        end_of_settlement = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Entry Px Exponent: Price at this level and side of book.
struct md_entry_px_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Px Mantissa: Price at this level and side of book.
struct md_entry_px_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size: Quote Quantity
struct md_entry_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Type: Side of book for this entry.
struct md_entry_type {
    enum class type : char {
        bid = '0',
        ask = '1',
        trade = '2',
        index_value = '3',
        opening_price = '4',
        settlement_value = '6',
        high = '7',
        low = '8',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Volume Type: Volume Types
struct md_volume_type {
    enum class type : std::uint8_t {
        total_limit = 0,
        customer_limit = 1,
        total_contingency_all_or_none = 2,
        customer_contingency_all_or_none = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

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

// Message Length: Length of the message in bytes
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
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Minimum Above Premium Fraction Exponent: The multiple that premium can be when above the break point.
struct minimum_above_premium_fraction_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Minimum Above Premium Fraction Mantissa: The multiple that premium can be when above the break point.
struct minimum_above_premium_fraction_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Minimum Below Premium Fraction Exponent: The multiple that premium can be when below the break point.
struct minimum_below_premium_fraction_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Minimum Below Premium Fraction Mantissa: The multiple that premium can be when below the break point.
struct minimum_below_premium_fraction_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Minimum Strike Price Fraction Exponent: The multiple by which the strike price can be
struct minimum_strike_price_fraction_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Minimum Strike Price Fraction Mantissa: The multiple by which the strike price can be
struct minimum_strike_price_fraction_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Msg Seq Num: Message Sequence Number
struct msg_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Net Chg Prev Day Exponent: Net change of last sale price relative to previous close price. Sign of this value implies direction of change.
struct net_chg_prev_day_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Net Chg Prev Day Mantissa: Net change of last sale price relative to previous close price. Sign of this value implies direction of change.
struct net_chg_prev_day_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Entries: Number of MDEntries in this message. Will not exceed 255
struct no_entries {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Legs: Num. of Legs in a strategy product. Only used for products that contain legs such as strategies. Will not exceed 255.
struct no_legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Interest
struct open_interest {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Length: Length of the packet including this length field and the version
struct packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Premium Break Point Exponent: The premium price where above and below fractions take effect.
struct premium_break_point_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Premium Break Point Mantissa: The premium price where above and below fractions take effect.
struct premium_break_point_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Close Px Exponent: Previous day’s close price for security.
struct prev_close_px_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Close Px Mantissa: Previous day’s close price for security.
struct prev_close_px_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Type: Specifies how to interpret the value in the StrikePrice field.
struct price_type {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Put Or Call: This field is required for options.
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

// Security Exchange
struct security_exchange {
    enum class type : char {
        cboe = 'C',
        one_chicago_not_supported = 'O',
        cbsx_not_supported = 'W',
        cfecof = 'F',
        cboe_2_options = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Id: Product key
struct security_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Trading Status
struct security_trading_status {
    enum class type : std::uint8_t {
        halted = 2,
        open = 17,
        closed = 18,
        pre_open = 21,
        opening_rotation = 22,
        fast_market = 23,
        strategy_market_in_opening_rotation = 24,
        strategy_market_quotes_non_firm = 25,
        suspended = 26,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type Length
struct security_type_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Type Text
struct security_type_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr security_type_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Sending Time: The time that this packet was sent. It applies to all messages in this packet.
struct sending_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Exponent: First byte is the exponent, last 4 bytes are the mantissa. This field is required for options
struct strike_price_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Mantissa: First byte is the exponent, last 4 bytes are the mantissa. This field is required for options
struct strike_price_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Length: Symbol of the class
struct symbol_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Text: Symbol of the class
struct symbol_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr symbol_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Target Location Id Length
struct target_location_id_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Target Location Id Text
struct target_location_id_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr target_location_id_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Template Id: The Template ID is for decoding the message.
struct template_id {
    enum class type : std::uint8_t {
        security_definition_message = 13,
        current_market_refresh_message = 11,
        market_data_refresh_message = 20,
        current_market_update_message = 12,
        recap_update_message = 21,
        ticker_message = 14,
        expected_opening_price_and_size_message = 15,
        index_value_message = 22,
        settlement_value_message = 23,
        summary_message = 24,
        market_data_control_message = 25,
        heartbeat_message = 16,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Condition Length
struct trade_condition_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Condition Text
struct trade_condition_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr trade_condition_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Trade Volume: Total trade volume for security
struct trade_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Px Exponent: Price of underlying security
struct underlying_px_exponent {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Px Mantissa: Price of underlying security
struct underlying_px_mantissa {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Symbol Length: The underlying symbol
struct underlying_symbol_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Symbol Text: The underlying symbol
struct underlying_symbol_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr underlying_symbol_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Underlying Type Length
struct underlying_type_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Type Text
struct underlying_type_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr underlying_type_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Version: The version associated with the contents and format of this header. Currently, this will be a constant value of 1.
struct version {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Heartbeat Message
struct heartbeat_message {
    static constexpr std::string_view name = "Heartbeat Message";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Market Data Control Message: Market Data Control messages mark the start and end of the end of session Summary and the end of session Settlement data transmissions.
struct market_data_control_message {
    static constexpr std::string_view name = "Market Data Control Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_control_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_control_type);
};

static_assert(sizeof(market_data_control_message) == market_data_control_message::size, "market_data_control_message lies over its bytes exactly");

// Md Entry Px
struct md_entry_px {
    static constexpr std::string_view name = "Md Entry Px";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px_exponent,
        md_entry_px_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_px_exponent);
    CSMFIELD(md_entry_px_mantissa);
};

static_assert(sizeof(md_entry_px) == md_entry_px::size, "md_entry_px lies over its bytes exactly");

// Summary Md Entry: Summary market data
struct summary_md_entry {
    static constexpr std::string_view name = "Summary Md Entry";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_type,
        md_entry_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_type);
    CSMFIELD(md_entry_px);
};

static_assert(sizeof(summary_md_entry) == summary_md_entry::size, "summary_md_entry lies over its bytes exactly");

// Underlying Px
struct underlying_px {
    static constexpr std::string_view name = "Underlying Px";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_px_exponent,
        underlying_px_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(underlying_px_exponent);
    CSMFIELD(underlying_px_mantissa);
};

static_assert(sizeof(underlying_px) == underlying_px::size, "underlying_px lies over its bytes exactly");

// Net Chg Prev Day
struct net_chg_prev_day {
    static constexpr std::string_view name = "Net Chg Prev Day";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        net_chg_prev_day_exponent,
        net_chg_prev_day_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(net_chg_prev_day_exponent);
    CSMFIELD(net_chg_prev_day_mantissa);
};

static_assert(sizeof(net_chg_prev_day) == net_chg_prev_day::size, "net_chg_prev_day lies over its bytes exactly");

// Summary Message Section 1
struct summary_message_section_1 {
    static constexpr std::string_view name = "Summary Message Section 1";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        price_type,
        trade_volume,
        open_interest,
        net_chg_prev_day,
        underlying_px,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(price_type);
    CSMFIELD(trade_volume);
    CSMFIELD(open_interest);
    CSMFIELD(net_chg_prev_day);
    CSMFIELD(underlying_px);
    CSMFIELD(no_entries);
};

static_assert(sizeof(summary_message_section_1) == summary_message_section_1::size, "summary_message_section_1 lies over its bytes exactly");

// Summary Message: Summary messages contain the end of session market data for each product.
struct summary_message {
    static constexpr std::string_view name = "Summary Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(summary_md_entry);
};

// Settlement Value Md Entry: The settlement price
struct settlement_value_md_entry {
    static constexpr std::string_view name = "Settlement Value Md Entry";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_type,
        md_entry_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_type);
    CSMFIELD(md_entry_px);
};

static_assert(sizeof(settlement_value_md_entry) == settlement_value_md_entry::size, "settlement_value_md_entry lies over its bytes exactly");

// Settlement Value Message Section 1
struct settlement_value_message_section_1 {
    static constexpr std::string_view name = "Settlement Value Message Section 1";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        price_type,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(price_type);
    CSMFIELD(no_entries);
};

static_assert(sizeof(settlement_value_message_section_1) == settlement_value_message_section_1::size, "settlement_value_message_section_1 lies over its bytes exactly");

// Settlement Value Message: Index value messages contain the values associated with a calculated index. They are transmitted when an index is calculated.
struct settlement_value_message {
    static constexpr std::string_view name = "Settlement Value Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(settlement_value_md_entry);
};

// Index Value Md Entry: Market data associated with the index
struct index_value_md_entry {
    static constexpr std::string_view name = "Index Value Md Entry";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_type,
        md_entry_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_type);
    CSMFIELD(md_entry_px);
};

static_assert(sizeof(index_value_md_entry) == index_value_md_entry::size, "index_value_md_entry lies over its bytes exactly");

// Symbol Section 1
struct symbol_section_1 {
    static constexpr std::string_view name = "Symbol Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(symbol_length);
};

static_assert(sizeof(symbol_section_1) == symbol_section_1::size, "symbol_section_1 lies over its bytes exactly");

// Symbol
struct symbol {
    static constexpr std::string_view name = "Symbol";
    static constexpr bool is_message = false;
};

// Index Value Message Section 1
struct index_value_message_section_1 {
    static constexpr std::string_view name = "Index Value Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(no_entries);
};

static_assert(sizeof(index_value_message_section_1) == index_value_message_section_1::size, "index_value_message_section_1 lies over its bytes exactly");

// Index Value Message: Index value messages contain the values associated with a calculated index. They are transmitted when an index is calculated.
struct index_value_message {
    static constexpr std::string_view name = "Index Value Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(index_value_md_entry);
};

// Eop
struct eop {
    static constexpr std::string_view name = "Eop";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        eop_exponent,
        eop_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(eop_exponent);
    CSMFIELD(eop_mantissa);
};

static_assert(sizeof(eop) == eop::size, "eop lies over its bytes exactly");

// Expected Opening Price And Size Message: The EOP message contains expected opening price and size information for a security.
struct expected_opening_price_and_size_message {
    static constexpr std::string_view name = "Expected Opening Price And Size Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        eop,
        eos,
        eop_type,
        legal_market>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(eop);
    CSMFIELD(eos);
    CSMFIELD(eop_type);
    CSMFIELD(legal_market);
};

static_assert(sizeof(expected_opening_price_and_size_message) == expected_opening_price_and_size_message::size, "expected_opening_price_and_size_message lies over its bytes exactly");

// Trade Condition Section 1
struct trade_condition_section_1 {
    static constexpr std::string_view name = "Trade Condition Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trade_condition_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(trade_condition_length);
};

static_assert(sizeof(trade_condition_section_1) == trade_condition_section_1::size, "trade_condition_section_1 lies over its bytes exactly");

// Trade Condition
struct trade_condition {
    static constexpr std::string_view name = "Trade Condition";
    static constexpr bool is_message = false;
};

// Ticker Md Entry Section 1
struct ticker_md_entry_section_1 {
    static constexpr std::string_view name = "Ticker Md Entry Section 1";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_type,
        md_entry_px,
        md_entry_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_type);
    CSMFIELD(md_entry_px);
    CSMFIELD(md_entry_size);
};

static_assert(sizeof(ticker_md_entry_section_1) == ticker_md_entry_section_1::size, "ticker_md_entry_section_1 lies over its bytes exactly");

// Ticker Md Entry: Volume Entry for this price level.
struct ticker_md_entry {
    static constexpr std::string_view name = "Ticker Md Entry";
    static constexpr bool is_message = false;
};

// Ticker Message Section 1
struct ticker_message_section_1 {
    static constexpr std::string_view name = "Ticker Message Section 1";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        price_type,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(price_type);
    CSMFIELD(no_entries);
};

static_assert(sizeof(ticker_message_section_1) == ticker_message_section_1::size, "ticker_message_section_1 lies over its bytes exactly");

// Ticker Message: A Ticker message indicates that a trade or cancel has occurred.
struct ticker_message {
    static constexpr std::string_view name = "Ticker Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(ticker_md_entry);
};

// Recap Update Md Entry: MDEntry indicating market data
struct recap_update_md_entry {
    static constexpr std::string_view name = "Recap Update Md Entry";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_type,
        md_entry_px,
        md_entry_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_type);
    CSMFIELD(md_entry_px);
    CSMFIELD(md_entry_size);
};

static_assert(sizeof(recap_update_md_entry) == recap_update_md_entry::size, "recap_update_md_entry lies over its bytes exactly");

// Prev Close Px
struct prev_close_px {
    static constexpr std::string_view name = "Prev Close Px";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        prev_close_px_exponent,
        prev_close_px_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(prev_close_px_exponent);
    CSMFIELD(prev_close_px_mantissa);
};

static_assert(sizeof(prev_close_px) == prev_close_px::size, "prev_close_px lies over its bytes exactly");

// Recap Update Message Section 1
struct recap_update_message_section_1 {
    static constexpr std::string_view name = "Recap Update Message Section 1";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        price_type,
        prev_close_px,
        trade_volume,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(price_type);
    CSMFIELD(prev_close_px);
    CSMFIELD(trade_volume);
    CSMFIELD(no_entries);
};

static_assert(sizeof(recap_update_message_section_1) == recap_update_message_section_1::size, "recap_update_message_section_1 lies over its bytes exactly");

// Recap Update Message: The Recap Update message contains the latest Last Sale price, Last Sale size, Total Volume, Open price, High price, Low price, and Previous close price. It is sent as a result of a trade or cancel.
struct recap_update_message {
    static constexpr std::string_view name = "Recap Update Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(recap_update_md_entry);
};

// Md Entry: MDEntry
struct md_entry {
    static constexpr std::string_view name = "Md Entry";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_type,
        md_entry_px,
        md_entry_size,
        md_volume_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(md_entry_type);
    CSMFIELD(md_entry_px);
    CSMFIELD(md_entry_size);
    CSMFIELD(md_volume_type);
};

static_assert(sizeof(md_entry) == md_entry::size, "md_entry lies over its bytes exactly");

// Current Market Update Message Section 1
struct current_market_update_message_section_1 {
    static constexpr std::string_view name = "Current Market Update Message Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        security_trading_status,
        price_type,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(security_trading_status);
    CSMFIELD(price_type);
    CSMFIELD(no_entries);
};

static_assert(sizeof(current_market_update_message_section_1) == current_market_update_message_section_1::size, "current_market_update_message_section_1 lies over its bytes exactly");

// Current Market Update Message: The Current Market Update message contains real-time top of book market updates for a security.
struct current_market_update_message {
    static constexpr std::string_view name = "Current Market Update Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(md_entry);
};

// Market Data Refresh Message Section 1
struct market_data_refresh_message_section_1 {
    static constexpr std::string_view name = "Market Data Refresh Message Section 1";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        security_trading_status,
        price_type,
        appl_seq_num,
        prev_close_px,
        trade_volume,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(security_trading_status);
    CSMFIELD(price_type);
    CSMFIELD(appl_seq_num);
    CSMFIELD(prev_close_px);
    CSMFIELD(trade_volume);
    CSMFIELD(no_entries);
};

static_assert(sizeof(market_data_refresh_message_section_1) == market_data_refresh_message_section_1::size, "market_data_refresh_message_section_1 lies over its bytes exactly");

// Market Data Refresh Message: The Market Data Refresh message contains a snapshot / refresh of the Current Market and Recap information (Last Sale, Last Sale Size, Open, High, Low, Previous Close Price) for one product.
struct market_data_refresh_message {
    static constexpr std::string_view name = "Market Data Refresh Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(md_entry);
};

// Current Market Refresh Message Section 1
struct current_market_refresh_message_section_1 {
    static constexpr std::string_view name = "Current Market Refresh Message Section 1";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        security_trading_status,
        price_type,
        appl_seq_num,
        no_entries>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(security_trading_status);
    CSMFIELD(price_type);
    CSMFIELD(appl_seq_num);
    CSMFIELD(no_entries);
};

static_assert(sizeof(current_market_refresh_message_section_1) == current_market_refresh_message_section_1::size, "current_market_refresh_message_section_1 lies over its bytes exactly");

// Current Market Refresh Message: The Current Market Refresh message contains a snapshot of the current market information for one security along with the quantities and volume types for that particular security.
struct current_market_refresh_message {
    static constexpr std::string_view name = "Current Market Refresh Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(md_entry);
};

// Security Definition Leg
struct security_definition_leg {
    static constexpr std::string_view name = "Security Definition Leg";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_ratio_qty,
        leg_security_id,
        leg_side>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(leg_ratio_qty);
    CSMFIELD(leg_security_id);
    CSMFIELD(leg_side);
};

static_assert(sizeof(security_definition_leg) == security_definition_leg::size, "security_definition_leg lies over its bytes exactly");

// Underlying Type Section 1
struct underlying_type_section_1 {
    static constexpr std::string_view name = "Underlying Type Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_type_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(underlying_type_length);
};

static_assert(sizeof(underlying_type_section_1) == underlying_type_section_1::size, "underlying_type_section_1 lies over its bytes exactly");

// Underlying Type
struct underlying_type {
    static constexpr std::string_view name = "Underlying Type";
    static constexpr bool is_message = false;
};

// Underlying Symbol Section 1
struct underlying_symbol_section_1 {
    static constexpr std::string_view name = "Underlying Symbol Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_symbol_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(underlying_symbol_length);
};

static_assert(sizeof(underlying_symbol_section_1) == underlying_symbol_section_1::size, "underlying_symbol_section_1 lies over its bytes exactly");

// Underlying Symbol
struct underlying_symbol {
    static constexpr std::string_view name = "Underlying Symbol";
    static constexpr bool is_message = false;
};

// Currency Code Section 1
struct currency_code_section_1 {
    static constexpr std::string_view name = "Currency Code Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        currency_code_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(currency_code_length);
};

static_assert(sizeof(currency_code_section_1) == currency_code_section_1::size, "currency_code_section_1 lies over its bytes exactly");

// Currency Code
struct currency_code {
    static constexpr std::string_view name = "Currency Code";
    static constexpr bool is_message = false;
};

// Minimum Below Premium Fraction
struct minimum_below_premium_fraction {
    static constexpr std::string_view name = "Minimum Below Premium Fraction";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        minimum_below_premium_fraction_exponent,
        minimum_below_premium_fraction_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(minimum_below_premium_fraction_exponent);
    CSMFIELD(minimum_below_premium_fraction_mantissa);
};

static_assert(sizeof(minimum_below_premium_fraction) == minimum_below_premium_fraction::size, "minimum_below_premium_fraction lies over its bytes exactly");

// Minimum Above Premium Fraction
struct minimum_above_premium_fraction {
    static constexpr std::string_view name = "Minimum Above Premium Fraction";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        minimum_above_premium_fraction_exponent,
        minimum_above_premium_fraction_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(minimum_above_premium_fraction_exponent);
    CSMFIELD(minimum_above_premium_fraction_mantissa);
};

static_assert(sizeof(minimum_above_premium_fraction) == minimum_above_premium_fraction::size, "minimum_above_premium_fraction lies over its bytes exactly");

// Premium Break Point
struct premium_break_point {
    static constexpr std::string_view name = "Premium Break Point";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        premium_break_point_exponent,
        premium_break_point_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(premium_break_point_exponent);
    CSMFIELD(premium_break_point_mantissa);
};

static_assert(sizeof(premium_break_point) == premium_break_point::size, "premium_break_point lies over its bytes exactly");

// Max Strike Price
struct max_strike_price {
    static constexpr std::string_view name = "Max Strike Price";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        max_strike_price_exponent,
        max_strike_price_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(max_strike_price_exponent);
    CSMFIELD(max_strike_price_mantissa);
};

static_assert(sizeof(max_strike_price) == max_strike_price::size, "max_strike_price lies over its bytes exactly");

// Minimum Strike Price Fraction
struct minimum_strike_price_fraction {
    static constexpr std::string_view name = "Minimum Strike Price Fraction";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        minimum_strike_price_fraction_exponent,
        minimum_strike_price_fraction_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(minimum_strike_price_fraction_exponent);
    CSMFIELD(minimum_strike_price_fraction_mantissa);
};

static_assert(sizeof(minimum_strike_price_fraction) == minimum_strike_price_fraction::size, "minimum_strike_price_fraction lies over its bytes exactly");

// Strike Price
struct strike_price {
    static constexpr std::string_view name = "Strike Price";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        strike_price_exponent,
        strike_price_mantissa>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(strike_price_exponent);
    CSMFIELD(strike_price_mantissa);
};

static_assert(sizeof(strike_price) == strike_price::size, "strike_price lies over its bytes exactly");

// Target Location Id Section 1
struct target_location_id_section_1 {
    static constexpr std::string_view name = "Target Location Id Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        target_location_id_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(target_location_id_length);
};

static_assert(sizeof(target_location_id_section_1) == target_location_id_section_1::size, "target_location_id_section_1 lies over its bytes exactly");

// Target Location Id
struct target_location_id {
    static constexpr std::string_view name = "Target Location Id";
    static constexpr bool is_message = false;
};

// Security Type Section 1
struct security_type_section_1 {
    static constexpr std::string_view name = "Security Type Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_type_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(security_type_length);
};

static_assert(sizeof(security_type_section_1) == security_type_section_1::size, "security_type_section_1 lies over its bytes exactly");

// Security Type
struct security_type {
    static constexpr std::string_view name = "Security Type";
    static constexpr bool is_message = false;
};

// Security Definition Message Section 1
struct security_definition_message_section_1 {
    static constexpr std::string_view name = "Security Definition Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_exchange>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(security_exchange);
};

static_assert(sizeof(security_definition_message_section_1) == security_definition_message_section_1::size, "security_definition_message_section_1 lies over its bytes exactly");

// Security Definition Message Section 2
struct security_definition_message_section_2 {
    static constexpr std::string_view name = "Security Definition Message Section 2";
    static constexpr std::size_t size = 49;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        class_key,
        security_id,
        maturity_date,
        price_type,
        strike_price,
        put_or_call,
        minimum_strike_price_fraction,
        max_strike_price,
        premium_break_point,
        minimum_above_premium_fraction,
        minimum_below_premium_fraction,
        exercise_style>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(class_key);
    CSMFIELD(security_id);
    CSMFIELD(maturity_date);
    CSMFIELD(price_type);
    CSMFIELD(strike_price);
    CSMFIELD(put_or_call);
    CSMFIELD(minimum_strike_price_fraction);
    CSMFIELD(max_strike_price);
    CSMFIELD(premium_break_point);
    CSMFIELD(minimum_above_premium_fraction);
    CSMFIELD(minimum_below_premium_fraction);
    CSMFIELD(exercise_style);
};

static_assert(sizeof(security_definition_message_section_2) == security_definition_message_section_2::size, "security_definition_message_section_2 lies over its bytes exactly");

// Security Definition Message Section 3
struct security_definition_message_section_3 {
    static constexpr std::string_view name = "Security Definition Message Section 3";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        contract_size,
        no_legs>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(contract_size);
    CSMFIELD(no_legs);
};

static_assert(sizeof(security_definition_message_section_3) == security_definition_message_section_3::size, "security_definition_message_section_3 lies over its bytes exactly");

// Security Definition Message: Security definitions describe an exchange’s products by name and trading parameters and associates those products with a product security ID.
struct security_definition_message {
    static constexpr std::string_view name = "Security Definition Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(security_definition_leg);
};

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        template_id,
        message_type,
        msg_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(message_length);
    CSMFIELD(template_id);
    CSMFIELD(message_type);
    CSMFIELD(msg_seq_num);
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
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        version,
        packet_length,
        sending_time,
        message_count,
        first_msg_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CSMFIELD(version);
    CSMFIELD(packet_length);
    CSMFIELD(sending_time);
    CSMFIELD(message_count);
    CSMFIELD(first_msg_seq_num);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Csm Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    CSMSEQUENCE(message);
};

#pragma pack(pop)

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
