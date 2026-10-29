// Bse BseIndia Eobi Fbe 1.4 Template Meta Programming

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
#ifndef EOBIFIELD
#define EOBIFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef EOBISEQUENCE
#define EOBISEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace bse::bseindia::eobi::fbe::v1_4 {

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

// Aggressor Side: Side of the incoming order.
struct aggressor_side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Aggressor Timestamp: Always identical to the matching engine in timestamp.
struct aggressor_timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Appl Seq Num: Packet sequence number, contiguous and incremented per multicast address and port
struct appl_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Appl Seq Reset Indicator: Set in the first packet header after a market data fail over or restart, 0 No Reset and 1 Reset
struct appl_seq_reset_indicator {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Px: Bid price/rate.
struct bid_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Body Len: Number of bytes for the message, including this field
struct body_len {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Close Price
struct close_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Completion Indicator: Indicates whether a unit of work fits into a single datagram, 0 Incomplete and 1 Complete
struct completion_indicator {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Display Qty: Quantity.
struct display_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exec Id: Matching timestamp.
struct exec_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Fast Market Indicator: Indicates if product is in the state Fast Market.
struct fast_market_indicator {
    enum class type : std::uint8_t {
        no = 0,
        yes = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Implied Market Indicator: Indicates that an implied market to be created for either the legs of a multi-leg instrument or for the multi-leg instrument based on the existence of the legs.
struct implied_market_indicator {
    enum class type : std::uint8_t {
        not_implied = 0,
        implied_in_out = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Msg Seq Num Processed: Last Message Sequence number that was processed.
struct last_msg_seq_num_processed {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Px: Indicating the potential Auction price for a crossed order book.
struct last_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Qty: The potential matchable quantity for the auction.
struct last_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Update Time: Last update time of the corresponding order book.
struct last_update_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio Qty: The ratio of quantity for this individual leg relative to the entire multi-leg security.
struct leg_ratio_qty {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-2147483648LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Id: Instrument identifier of the leg security.
struct leg_security_id {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Side: The side of the individual leg of a strategy as defined in signature.
struct leg_side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Lower Ckt Limit: Lower Circuit Limit Price
struct lower_ckt_limit {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lower Exec Limit: Lower Limit Execution Price
struct lower_exec_limit {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Segment Id: Product identifier
struct market_segment_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Px: Price.
struct md_entry_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size: Quantity.
struct md_entry_size {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Type: Type of market data entry.
struct md_entry_type {
    enum class type : std::uint8_t {
        trade = 2,
        opening_price = 4,
        closing_price = 5,
        high_price = 7,
        low_price = 8,
        previous_closing_price = 101,
        opening_auction = 200,
        intraday_auction = 201,
        circuit_breaker_auction = 202,
        closing_auction = 203,
        upper_ckt_limit = 204,
        lower_ckt_limit = 205,
        gross_trade_amt = 206,
        upper_exec_limit = 208,
        lower_exec_limit = 209,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Msg Seq Num: Message sequence number, incremented per product across all message types
struct msg_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Legs: Number of Legs repeating group instances.
struct no_legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Md Entries: Number of entries in Market Data message for MDEntryGrp.
struct no_md_entries {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Of Trades: Total number of trades.
struct no_of_trades {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Px: Offer price/rate.
struct offer_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pad 1: not used
struct pad_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pad 3: not used
struct pad_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Pad 4: not used
struct pad_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pad 5: not used
struct pad_5 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 5;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 5> value_;
};

// Pad 6: not used
struct pad_6 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Pad 7: not used
struct pad_7 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 7;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 7> value_;
};

// Partition Id: Grouping of Bse products
struct partition_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Close Price: Previous Close Price
struct prev_close_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Display Qty: Previous display quantity
struct prev_display_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Price: Previous order price.
struct prev_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: Reserved for future use.
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

// Product Complex: This field qualifies an instrument type on BSE.
struct product_complex {
    enum class type : std::uint8_t {
        futures_spread = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Resting Hidden Qty: Quantity of matched passive orders that is not displayed to the market.
struct resting_hidden_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Id: Unique instrument identifier.
struct security_id {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Status: Instrument status.
struct security_status {
    enum class type : std::uint8_t {
        active = 1,
        inactive = 2,
        expired = 4,
        suspended = 9,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Sub Type: Strategy Type.
struct security_sub_type {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-2147483648LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Trading Status: Instrument state status.
struct security_trading_status {
    enum class type : std::uint8_t {
        closed = 200,
        restricted = 201,
        book = 202,
        continuous = 203,
        opening_auction = 204,
        opening_auction_freeze = 205,
        intraday_auction = 206,
        intraday_auction_freeze = 207,
        circuit_breaker_auction = 208,
        circuit_breaker_auction_freeze = 209,
        closing_auction = 210,
        closing_auction_freeze = 211,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side: Side of the order.
struct side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Template Id: Unique identifier for a Bse Eobi message layout
struct template_id {
    enum class type : std::uint16_t {
        heartbeat_message = 13001,
        product_summary_message = 13600,
        snapshot_order_message = 13602,
        instrument_summary_message = 13601,
        auction_best_bid_offer_message = 13500,
        auction_clearing_price_message = 13501,
        top_of_book_message = 13504,
        order_add_message = 13100,
        order_modify_message = 13101,
        order_modify_same_priority_message = 13106,
        order_delete_message = 13102,
        order_mass_delete_message = 13103,
        partial_order_execution_message = 13105,
        full_order_execution_message = 13104,
        trade_reversal_message = 13200,
        execution_summary_message = 13202,
        instrument_info_message = 13203,
        lpp_range_message = 13204,
        product_state_change_message = 13300,
        instrument_state_change_message = 13301,
        add_complex_instrument_message = 13400,
        packet_header = 13002,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Tot No Orders: Corresponding number of orders for this instrument.
struct tot_no_orders {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trad Ses Status: Miscellaneous state information.
struct trad_ses_status {
    enum class type : std::uint8_t {
        halted = 1,
        open = 2,
        closed = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Condition: Indicates whether a synthetic match is occured.
struct trade_condition {
    enum class type : std::uint8_t {
        implied_trade = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Volume: Cumulative volume of units traded in the day.
struct trade_volume {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Session Id: Miscellaneous state information.
struct trading_session_id {
    enum class type : std::uint8_t {
        day = 1,
        morning = 3,
        evening = 5,
        holiday = 7,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Session Sub Id: Product state information.
struct trading_session_sub_id {
    enum class type : std::uint8_t {
        pre_trading = 1,
        trading = 3,
        closing = 4,
        post_trading = 5,
        post_closing = 6,
        quiescent = 7,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Transact Time: Transaction timestamp.
struct transact_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Match Id: Unique identifier for each price level of a match event.
struct trd_match_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Execution Time: Last matching execution timestamp.
struct trd_reg_ts_execution_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Prev Time Priority: Previous order priority timestamp.
struct trd_reg_ts_prev_time_priority {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Time In: Matching engine In timestamp.
struct trd_reg_ts_time_in {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Time Priority: Priority timestamp.
struct trd_reg_ts_time_priority {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Upper Ckt Limit: Upper Circuit Limit Price
struct upper_ckt_limit {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Upper Exec Limit: Upper Limit Execution Price
struct upper_exec_limit {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Instrmt Leg Grp: Leg definitions repeated NoLegs times in the Add Complex Instrument Message.
struct instrmt_leg_grp {
    static constexpr std::string_view name = "Instrmt Leg Grp";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_security_id,
        leg_ratio_qty,
        leg_side,
        pad_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(leg_security_id);
    EOBIFIELD(leg_ratio_qty);
    EOBIFIELD(leg_side);
    EOBIFIELD(pad_3);
};

static_assert(sizeof(instrmt_leg_grp) == instrmt_leg_grp::size, "instrmt_leg_grp lies over its bytes exactly");

// Add Complex Instrument Message: Published whenever a new complex instrument is created intraday or an existing complex instrument is modified.
struct add_complex_instrument_message {
    static constexpr std::string_view name = "Add Complex Instrument Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        security_sub_type,
        product_complex,
        implied_market_indicator,
        no_legs,
        pad_1,
        instrmt_leg_grp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(security_sub_type);
    EOBIFIELD(product_complex);
    EOBIFIELD(implied_market_indicator);
    EOBIFIELD(no_legs);
    EOBIFIELD(pad_1);
    EOBIFIELD(instrmt_leg_grp);
};

static_assert(sizeof(add_complex_instrument_message) == add_complex_instrument_message::size, "add_complex_instrument_message lies over its bytes exactly");

// Instrument State Change Message: Provides state information for a single instrument.
struct instrument_state_change_message {
    static constexpr std::string_view name = "Instrument State Change Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        security_status,
        security_trading_status,
        fast_market_indicator,
        pad_5,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(security_status);
    EOBIFIELD(security_trading_status);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(pad_5);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(instrument_state_change_message) == instrument_state_change_message::size, "instrument_state_change_message lies over its bytes exactly");

// Product State Change Message: Provides updates on the trading state for all instruments in a particular product.
struct product_state_change_message {
    static constexpr std::string_view name = "Product State Change Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trading_session_id,
        trading_session_sub_id,
        trad_ses_status,
        fast_market_indicator,
        pad_4,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trading_session_id);
    EOBIFIELD(trading_session_sub_id);
    EOBIFIELD(trad_ses_status);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(pad_4);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(product_state_change_message) == product_state_change_message::size, "product_state_change_message lies over its bytes exactly");

// Lpp Range Message: Published whenever there is a change in the limit price protection range of the instrument.
struct lpp_range_message {
    static constexpr std::string_view name = "Lpp Range Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        upper_exec_limit,
        lower_exec_limit>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(upper_exec_limit);
    EOBIFIELD(lower_exec_limit);
};

static_assert(sizeof(lpp_range_message) == lpp_range_message::size, "lpp_range_message lies over its bytes exactly");

// Instrument Info Message: Published whenever there is a change in the daily price range of the instrument.
struct instrument_info_message {
    static constexpr std::string_view name = "Instrument Info Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        close_price,
        prev_close_price,
        upper_ckt_limit,
        lower_ckt_limit>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(close_price);
    EOBIFIELD(prev_close_price);
    EOBIFIELD(upper_ckt_limit);
    EOBIFIELD(lower_ckt_limit);
};

static_assert(sizeof(instrument_info_message) == instrument_info_message::size, "instrument_info_message lies over its bytes exactly");

// Execution Summary Message: Published whenever an incoming order is executed, carrying information on the execution of that incoming order.
struct execution_summary_message {
    static constexpr std::string_view name = "Execution Summary Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        aggressor_timestamp,
        exec_id,
        last_qty,
        aggressor_side,
        trade_condition,
        pad_6,
        last_px,
        resting_hidden_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(aggressor_timestamp);
    EOBIFIELD(exec_id);
    EOBIFIELD(last_qty);
    EOBIFIELD(aggressor_side);
    EOBIFIELD(trade_condition);
    EOBIFIELD(pad_6);
    EOBIFIELD(last_px);
    EOBIFIELD(resting_hidden_qty);
};

static_assert(sizeof(execution_summary_message) == execution_summary_message::size, "execution_summary_message lies over its bytes exactly");

// Md Trade Entry Grp: Trade statistics repeated NoMDEntries times in the Trade Reversal Message.
struct md_trade_entry_grp {
    static constexpr std::string_view name = "Md Trade Entry Grp";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        md_entry_size,
        md_entry_type,
        pad_7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(md_entry_px);
    EOBIFIELD(md_entry_size);
    EOBIFIELD(md_entry_type);
    EOBIFIELD(pad_7);
};

static_assert(sizeof(md_trade_entry_grp) == md_trade_entry_grp::size, "md_trade_entry_grp lies over its bytes exactly");

// Trade Reversal Message: Published when a trade is reversed.
struct trade_reversal_message {
    static constexpr std::string_view name = "Trade Reversal Message";
    static constexpr std::size_t size = 80;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        trd_match_id,
        pad_4,
        last_qty,
        last_px,
        trd_reg_ts_execution_time,
        no_md_entries,
        pad_7,
        md_trade_entry_grp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(pad_4);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
    EOBIFIELD(trd_reg_ts_execution_time);
    EOBIFIELD(no_md_entries);
    EOBIFIELD(pad_7);
    EOBIFIELD(md_trade_entry_grp);
};

static_assert(sizeof(trade_reversal_message) == trade_reversal_message::size, "trade_reversal_message lies over its bytes exactly");

// Full Order Execution Message: Published whenever a visible order is fully executed at its displayed price.
struct full_order_execution_message {
    static constexpr std::string_view name = "Full Order Execution Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        pad_7,
        price,
        trd_reg_ts_time_priority,
        security_id,
        trd_match_id,
        pad_4,
        last_qty,
        last_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(side);
    EOBIFIELD(pad_7);
    EOBIFIELD(price);
    EOBIFIELD(trd_reg_ts_time_priority);
    EOBIFIELD(security_id);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(pad_4);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
};

static_assert(sizeof(full_order_execution_message) == full_order_execution_message::size, "full_order_execution_message lies over its bytes exactly");

// Partial Order Execution Message: Published whenever a visible order is partially executed at its displayed price.
struct partial_order_execution_message {
    static constexpr std::string_view name = "Partial Order Execution Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        pad_7,
        price,
        trd_reg_ts_time_priority,
        security_id,
        trd_match_id,
        pad_4,
        last_qty,
        last_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(side);
    EOBIFIELD(pad_7);
    EOBIFIELD(price);
    EOBIFIELD(trd_reg_ts_time_priority);
    EOBIFIELD(security_id);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(pad_4);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
};

static_assert(sizeof(partial_order_execution_message) == partial_order_execution_message::size, "partial_order_execution_message lies over its bytes exactly");

// Order Mass Delete Message: Published when the order book is expected to be emptied.
struct order_mass_delete_message {
    static constexpr std::string_view name = "Order Mass Delete Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(order_mass_delete_message) == order_mass_delete_message::size, "order_mass_delete_message lies over its bytes exactly");

// Order Details: OrderDetails
struct order_details {
    static constexpr std::string_view name = "Order Details";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_time_priority,
        display_qty,
        side,
        pad_7,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_time_priority);
    EOBIFIELD(display_qty);
    EOBIFIELD(side);
    EOBIFIELD(pad_7);
    EOBIFIELD(price);
};

static_assert(sizeof(order_details) == order_details::size, "order_details lies over its bytes exactly");

// Order Delete Message: Published whenever an existing order is deleted from the order book.
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_time_in,
        transact_time,
        security_id,
        order_details>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_time_in);
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Order Modify Same Priority Message: Published if the time priority of an existing order is not changed.
struct order_modify_same_priority_message {
    static constexpr std::string_view name = "Order Modify Same Priority Message";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_time_in,
        transact_time,
        prev_display_qty,
        security_id,
        order_details>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_time_in);
    EOBIFIELD(transact_time);
    EOBIFIELD(prev_display_qty);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details);
};

static_assert(sizeof(order_modify_same_priority_message) == order_modify_same_priority_message::size, "order_modify_same_priority_message lies over its bytes exactly");

// Order Modify Message: Published if an existing order in the book is modified, whereby the new parameters might cause a change in time priority.
struct order_modify_message {
    static constexpr std::string_view name = "Order Modify Message";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_time_in,
        trd_reg_ts_prev_time_priority,
        prev_price,
        prev_display_qty,
        security_id,
        order_details>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_time_in);
    EOBIFIELD(trd_reg_ts_prev_time_priority);
    EOBIFIELD(prev_price);
    EOBIFIELD(prev_display_qty);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details);
};

static_assert(sizeof(order_modify_message) == order_modify_message::size, "order_modify_message lies over its bytes exactly");

// Order Add Message: Published for each new order that was entered in the order book.
struct order_add_message {
    static constexpr std::string_view name = "Order Add Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_time_in,
        security_id,
        order_details>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_time_in);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details);
};

static_assert(sizeof(order_add_message) == order_add_message::size, "order_add_message lies over its bytes exactly");

// Top Of Book Message: Carries the best bid and offer of an order book outside continuous trading.
struct top_of_book_message {
    static constexpr std::string_view name = "Top Of Book Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_id,
        bid_px,
        offer_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(bid_px);
    EOBIFIELD(offer_px);
};

static_assert(sizeof(top_of_book_message) == top_of_book_message::size, "top_of_book_message lies over its bytes exactly");

// Auction Clearing Price Message: Published for a crossed order book in an auction, indicating the potential auction price.
struct auction_clearing_price_message {
    static constexpr std::string_view name = "Auction Clearing Price Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_id,
        last_px,
        last_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(last_px);
    EOBIFIELD(last_qty);
};

static_assert(sizeof(auction_clearing_price_message) == auction_clearing_price_message::size, "auction_clearing_price_message lies over its bytes exactly");

// Auction Best Bid Offer Message: Carries the best bid and offer of a non crossed order book during an auction call phase.
struct auction_best_bid_offer_message {
    static constexpr std::string_view name = "Auction Best Bid Offer Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_id,
        bid_px,
        offer_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(bid_px);
    EOBIFIELD(offer_px);
};

static_assert(sizeof(auction_best_bid_offer_message) == auction_best_bid_offer_message::size, "auction_best_bid_offer_message lies over its bytes exactly");

// Md Instrument Entry Grp: Instrument trade statistics repeated NoMDEntries times in the Instrument Summary Message. The group is not cut off by design.
struct md_instrument_entry_grp {
    static constexpr std::string_view name = "Md Instrument Entry Grp";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        md_entry_size,
        md_entry_type,
        pad_7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(md_entry_px);
    EOBIFIELD(md_entry_size);
    EOBIFIELD(md_entry_type);
    EOBIFIELD(pad_7);
};

static_assert(sizeof(md_instrument_entry_grp) == md_instrument_entry_grp::size, "md_instrument_entry_grp lies over its bytes exactly");

// Instrument Summary Message: Published for each instrument in one snapshot cycle, carrying instrument state information and trade statistics.
struct instrument_summary_message {
    static constexpr std::string_view name = "Instrument Summary Message";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        last_update_time,
        trd_reg_ts_execution_time,
        tot_no_orders,
        security_status,
        security_trading_status,
        fast_market_indicator,
        no_md_entries,
        trade_volume,
        no_of_trades,
        pad_4,
        md_instrument_entry_grp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(last_update_time);
    EOBIFIELD(trd_reg_ts_execution_time);
    EOBIFIELD(tot_no_orders);
    EOBIFIELD(security_status);
    EOBIFIELD(security_trading_status);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(no_md_entries);
    EOBIFIELD(trade_volume);
    EOBIFIELD(no_of_trades);
    EOBIFIELD(pad_4);
    EOBIFIELD(md_instrument_entry_grp);
};

static_assert(sizeof(instrument_summary_message) == instrument_summary_message::size, "instrument_summary_message lies over its bytes exactly");

// Snapshot Order Message: Represents each individual order or quote in a snapshot cycle on the snapshot channel.
struct snapshot_order_message {
    static constexpr std::string_view name = "Snapshot Order Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_details>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(order_details);
};

static_assert(sizeof(snapshot_order_message) == snapshot_order_message::size, "snapshot_order_message lies over its bytes exactly");

// Product Summary Message: Published once each snapshot cycle, carrying attributes that are equal for all instruments in the product.
struct product_summary_message {
    static constexpr std::string_view name = "Product Summary Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_msg_seq_num_processed,
        trading_session_id,
        trading_session_sub_id,
        trad_ses_status,
        fast_market_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(last_msg_seq_num_processed);
    EOBIFIELD(trading_session_id);
    EOBIFIELD(trading_session_sub_id);
    EOBIFIELD(trad_ses_status);
    EOBIFIELD(fast_market_indicator);
};

static_assert(sizeof(product_summary_message) == product_summary_message::size, "product_summary_message lies over its bytes exactly");

// Heartbeat Message: Published regularly when there is no activity on the snapshot or the incremental channel.
struct heartbeat_message {
    static constexpr std::string_view name = "Heartbeat Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_msg_seq_num_processed,
        pad_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(last_msg_seq_num_processed);
    EOBIFIELD(pad_4);
};

static_assert(sizeof(heartbeat_message) == heartbeat_message::size, "heartbeat_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Body Len, Template Id, and Msg Seq Num opening every message behind the Packet Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        body_len,
        template_id,
        msg_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(body_len);
    EOBIFIELD(template_id);
    EOBIFIELD(msg_seq_num);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Bse Eobi Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Eobi Header: Body Len, Template Id, and Msg Seq Num opening the Packet Header
struct eobi_header {
    static constexpr std::string_view name = "Eobi Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        body_len,
        template_id,
        msg_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(body_len);
    EOBIFIELD(template_id);
    EOBIFIELD(msg_seq_num);
};

static_assert(sizeof(eobi_header) == eobi_header::size, "eobi_header lies over its bytes exactly");

// Packet Header: Technical header delivered in every Udp datagram, identifying the product, the partition, and the send time
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        eobi_header,
        appl_seq_num,
        market_segment_id,
        partition_id,
        completion_indicator,
        appl_seq_reset_indicator,
        pad_5,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(eobi_header);
    EOBIFIELD(appl_seq_num);
    EOBIFIELD(market_segment_id);
    EOBIFIELD(partition_id);
    EOBIFIELD(completion_indicator);
    EOBIFIELD(appl_seq_reset_indicator);
    EOBIFIELD(pad_5);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Bse Eobi Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace bse::bseindia::eobi::fbe::v1_4
