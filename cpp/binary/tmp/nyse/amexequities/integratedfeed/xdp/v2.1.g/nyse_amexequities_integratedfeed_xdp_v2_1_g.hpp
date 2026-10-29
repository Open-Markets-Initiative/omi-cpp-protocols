// Nyse AmexEquities IntegratedFeed Xdp 2.1.g Template Meta Programming

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

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

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

// Auction Status: Indicates whether the auction will run
struct auction_status {
    enum class type : std::uint8_t {
        will_run_open_close = 0,
        will_run_interest = 1,
        will_not_run_imbalance = 2,
        will_not_run_transition_to_closing = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Time: Projected Auction Time (hhmm)
struct auction_time {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Type: Type of auction
struct auction_type {
    enum class type : char {
        early_opening = 'O',
        core_opening = 'M',
        reopening = 'H',
        closing = 'C',
        regulatory_imbalance = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Begin Seq Num: The beginning sequence number of the range of messages to be retransmitted.
struct begin_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Channel Id: The ID of the multicast channel over which the packet was sent.
struct channel_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Close: The exchange Closing price of this stock for the day. Use the Price Scale in the symbol index msg.
struct close {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Closing Only Clearing Price: For Pillar-powered markets, the price at which all eligible auction-only interest would trade, subject to auction collars For NYSE, the price closest to the reference price where the imbalance of closing-only interest is 0. If a closing-only clearing price is not reached, it is defaulted to 0.
struct closing_only_clearing_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Continuous Book Clearing Price: For Pillar-powered markets, the price at which all interest on the book can trade, including auction and imbalance offset interest, and disregarding auction collars. For NYSE, the indicative matching price, i.e. the price closest to the reference price where the imbalance is 0. If a continuous book clearing price is not reached, it is defaulted to 0.
struct continuous_book_clearing_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Id: Unique identifier for this Cross Trade. Used in Cross Correction message to identify the Cross Trade to correct.
struct cross_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Type: Reason for the crossing auction.
struct cross_type {
    enum class type : char {
        early_opening = 'E',
        opening = 'O',
        reopening = '5',
        closing = '6',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Current Refresh Pkt: The current refresh packet in the update
struct current_refresh_pkt {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Db Exec Id: For Pillar-powered markets, unused, defaulted to 0. For NYSE Tape A symbols, DB ExecID is assigned by the matching engine to all orders that participated in this trade event.
struct db_exec_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
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
        xdp_failover = 10,
        original_message = 11,
        sequence_number_reset_message = 12,
        one_retransmission_packet = 13,
        retransmission_sequence_message = 15,
        one_refresh_packet = 17,
        refresh_sequence_start = 18,
        refresh_sequence_message = 19,
        refresh_sequence_end = 20,
        message_unavailable = 21,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// End Seq Num: The end sequence number of the range of messages to be retransmitted.
struct end_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exchange Code: For listed equity markets, the market where this symbol is listed
struct exchange_code {
    enum class type : char {
        nyse_american = 'A',
        nyse_national = 'C',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        iex = 'V',
        bats = 'Z',
        global_otc = 'B',
        otcbb = 'U',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Firm Id: The market participant’s firm ID. Blank-filled if a firm ID was not specified.
struct firm_id {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Freeze Status: Freeze status code
struct freeze_status {
    enum class type : std::uint8_t {
        no_imbalance_freeze = 0,
        imbalance_freeze = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Halt Condition: Halt condition indicator
struct halt_condition {
    enum class type : char {
        security_not_delayedhalted = '~',
        not_delayedhalted_nyse_tape_a_only = ' ',
        news_dissemination = 'D',
        order_imbalance = 'I',
        news_pending = 'P',
        luld_pause = 'M',
        related_security_not_used = 'S',
        equipment_changeover = 'X',
        no_open_no_resume = 'Z',
        market_wide_circuit_breaker_halt_level_1 = '1',
        market_wide_circuit_breaker_halt_level_2 = '2',
        market_wide_circuit_breaker_halt_level_3 = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// High Price: The exchange high price of this stock for the day. Use the Price Scale in the symbol index msg.
struct high_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Id: ID of the originating Matching Engine partition to which this message applies.
struct id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Side: The side of the TotalImbalanceQty
struct imbalance_side {
    enum class type : char {
        no_imbalance = ' ',
        buy_side = 'B',
        sell_side = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Indicative Match Price: For Pillar-powered markets, the price that has the highest executable volume of auction-eligible shares, subject to auction collars. It includes the non-displayed quantity of Reserve Orders.
struct indicative_match_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Seq Num: The last sequence number sent on the channel for any symbol. The refresh is the state of the order book as of this sequence number.
struct last_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Symbol Seq Num: The last symbol sequence number sent for this symbol. The refresh is the symbol state of this symbol as of this symbol sequence number.
struct last_symbol_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lot Size: Round lot size in shares.
struct lot_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Price: The exchange Low price of this stock for the day. Use the Price Scale in the symbol index msg.
struct low_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lower Collar: If the IndicativeMatchPrice is not strictly between the UpperCollar and the LowerCollar, special auction rules apply. See Rule 7.35P for details.
struct lower_collar {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Id: ID of the Originating Market
struct market_id {
    enum class type : std::uint16_t {
        nyse_equities = 1,
        nyse_arca_equities = 3,
        nyse_arca_options = 4,
        nyse_bonds = 5,
        global_otc = 6,
        nyse_amex_options = 8,
        nyse_american_equities = 9,
        nyse_national_equities = 10,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Imbalance Qty: For Pillar-powered markets, the total market order imbalance quantity at the Indicative Match Price.
struct market_imbalance_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market State: The current Market State, which this msg updates if the Security Status field contains a Market State Code.
struct market_state {
    enum class type : char {
        pre_opening = 'P',
        early_session = 'E',
        core_session = 'O',
        late_session = 'L',
        closed = 'X',
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

// Message Size: The size of this message in bytes
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
        sequence_number_reset_message = 1,
        source_time_reference_message = 2,
        symbol_index_mapping_message = 3,
        retransmission_request_message = 10,
        request_response_message = 11,
        heartbeat_response_message = 12,
        symbol_index_mapping_request_message = 13,
        refresh_request_message = 15,
        message_unavailable_message = 31,
        symbol_clear_message = 32,
        security_status_message = 34,
        refresh_header_message = 35,
        add_order_message = 100,
        modify_order_message = 101,
        replace_order_message = 104,
        delete_order_message = 102,
        trade_cancel_message = 112,
        cross_trade_message = 111,
        cross_correction_message = 113,
        retail_price_improvement_message = 114,
        add_order_refresh_message = 106,
        imbalance_message = 105,
        order_execution_message = 103,
        non_displayed_trade_message = 110,
        stock_summary_message = 223,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Mpv: The minimum increment for a trade price, in 100ths of a cent. Typically 1, or $0.0001, but for some Tick Pilot stocks, can be 500, or $0.05.
struct mpv {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// New Order Id: The new Order ID of the replacement order
struct new_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New Price Parity Splits: Resulting number of splits at the new price. Defaulted to 0. Future use by NYSE only.
struct new_price_parity_splits {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Next Source Seq Num: The sequence number in the next message for this symbol
struct next_source_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Num Extensions: Number of times the halt period has been extended
struct num_extensions {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Num Parity Splits: Resulting number of splits at this price level Defaulted to 0. Future use by NYSE only.
struct num_parity_splits {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open: The exchange Opening price of this stock for the day. Use the Price Scale in the symbol index msg.
struct open {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: The unique ID assigned by the matching engine to this order . Can be used to match this message to the gateway Order Report.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
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

// Paired Qty: For Pillar-powered markets, the number of shares paired off at the Indicative Match Price. For NYSE, the number of shares paired off at the Reference Price, truncated to the nearest round lot quantity.
struct paired_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Position Change: Currently defaulted to 0.
struct position_change {
    enum class type : std::uint8_t {
        kept = 0,
        lost = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Prev Close Price: The previous day’s closing price for this security.
struct prev_close_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Close Volume: The previous day’s closing volume for the security.
struct prev_close_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Price Parity Splits: Resulting number of splits at the previous price Defaulted to 0. Future use by NYSE only.
struct prev_price_parity_splits {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: The order price. Use with the Price Scale from the symbol-mapping index.
struct price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price 1: Default value is 0
struct price_1 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price 2: Default value is 0
struct price_2 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Resolution: All Penny, Penny/Nickel, Nickel/Dime
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

// Price Scale Code: Specifies placement of the decimal point in price fields for this security.
struct price_scale_code {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Printable Flag: Printable flag values
struct printable_flag {
    enum class type : std::uint8_t {
        not_printed = 0,
        printed = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Reference Price: For Pillar-powered markets, the Reference Price is used to calculate the Indicative Match Price. For NYSE Tape A symbols, the Reference Price is the Last Sale if the last sale is at or between the current best quote.
struct reference_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Request Seq Num: The sequence number of the request message sent by the client.
struct request_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: This field is reserved for future use
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 2: Reserved for future use. Disregard any content.
struct reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 4: Future use. Any field content should be ignored.
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Retransmit Method: The delivery method for the requested symbol index mapping information.
struct retransmit_method {
    enum class type : std::uint8_t {
        udp = 0,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Round Lot: Round Lots Accepted
struct round_lot {
    enum class type : char {
        yes = 'Y',
        no = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Rpi Indicator: The side(s) where Retail Price Improvement orders (RPI orders) exist.
struct rpi_indicator {
    enum class type : char {
        no_retail_interest = ' ',
        interest_on_bid = 'A',
        interest_on_offer = 'B',
        interest_on_bid_and_offer = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Security Status: The new status that this security is transitioning to.
struct security_status {
    enum class type : char {
        opening_delay = '3',
        trading_halt = '4',
        resume = '5',
        no_openno_resume = '6',
        short_sale_restriction_activated_day_1 = 'A',
        short_sale_restriction_continued_day_2 = 'C',
        short_sale_restriction_deactivated = 'D',
        pre_opening = 'P',
        early_session = 'E',
        core_session = 'O',
        late_session_non_nyse_only = 'L',
        closed = 'X',
        time = 'T',
        price_indication = 'I',
        pre_opening_price_indication = 'G',
        rule_15_indication = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type: Type of Security used by Arca, National and American
struct security_type {
    enum class type : char {
        adr = 'A',
        common_stock = 'C',
        debentures = 'D',
        etf = 'E',
        foreign = 'F',
        us_depositary_shares = 'H',
        units = 'I',
        index_linked_notes = 'L',
        miscliquid_trust = 'M',
        ordinary_shares = 'O',
        preferred_stock = 'P',
        rights = 'R',
        shares_of_beneficiary_interest = 'S',
        test = 'T',
        units_2 = 'U',
        warrant = 'W',
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

// Session State: Unused. Defaulted to 0x00.
struct session_state {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Side: The side of the order. Valid values: ‘B’ – Buy ‘S’ – Sell
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

// Source Id: The ID of the client requesting this retransmission . This field is up to 9 characters, null terminated.
struct source_id {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
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

// Source Time Ns: The nanosecond offset from the SourceTime
struct source_time_ns {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ssr Filing Price: For Pillar-powered markets, not supported and defaulted to 0. For NYSE, the price at which Sell Short interest in the opening auction will be filed if a Sell Short Restriction is in effect for the security.
struct ssr_filing_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ssr State: The current SSR state, which this msg updates if the Security Status field contains an SSR Code. Valid
struct ssr_state {
    enum class type : char {
        no_short_sale_restriction_in_effect = '~',
        short_sale_restriction_in_effect = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ssr Triggering Exchange Id: This field is only populated when securityStatus = A and this security is listed on this exchange. Otherwise it is defaulted to 0x20.
struct ssr_triggering_exchange_id {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_omx_bx = 'B',
        nyse_national = 'C',
        finra = 'D',
        ise = 'I',
        edga = 'J',
        edgx = 'K',
        chx = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        cts = 'S',
        nasdaq_omx = 'T',
        iex = 'V',
        cbsx = 'W',
        nasdaq_omx_psx = 'X',
        bats_y = 'Y',
        bats = 'Z',
        no_value_value = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ssr Triggering Volume: This field is only populated when securityStatus = A and this security is listed on this exchange
struct ssr_triggering_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Status: The reason why the request was rejected.
struct status {
    enum class type : char {
        message_was_accepted = '0',
        rejected_due_to_an_invalid_source_id = '1',
        invalid_sequence_range = '2',
        maximum_sequence_range = '3',
        maximum_request_in_a_day = '4',
        maximum_refresh_requests_in_a_day = '5',
        old_seq_num_ttl = '6',
        invalid_channel_id = '7',
        invalid_product_id = '8',
        invalid_msg_type_or_msg_size_mismatch = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Symbol: Null-terminated ASCII symbol in NYSE Symbology.
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Symbol Index: The unique ID of this symbol for all products within this market. This ID cannot be used to cross reference a security between markets.
struct symbol_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Seq Num: Reserved for future use. Ignore any content. This usage will become standard across all products in future releases.
struct symbol_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Id: ID of the Originating matching engine server.
struct system_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Time: Format : HHMMSSmmm (mmm = milliseconds)
struct time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Imbalance Qty: For Pillar-powered markets, the total imbalance quantity at the Indicative Match Price. For NYSE, the total imbalance quantity at the Reference Price, truncated to the round lot.
struct total_imbalance_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Refresh Pkts: The total number of refresh packets you should expect in the update
struct total_refresh_pkts {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Volume: The exchange cumulative volume for the stock throughout the day.
struct total_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: The TradeID of the original Trade or Execution message to be cancelled.
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unit Of Trade: This field specifies the security Unit of Trade in shares. Valid values are 1, 10, 50 and 100
struct unit_of_trade {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Upper Collar: If the IndicativeMatchPrice is not strictly between the UpperCollar and the LowerCollar, special auction rules apply. See Rule 7.35P for details.
struct upper_collar {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume: The order quantity in shares
struct volume {
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

// Stock Summary Message: On a separate channel from the main feed, the Stock Summary channel, a Stock Summary message per symbol is sent every 60 seconds. The message is sent regardless of whether there has been a change to the symbol in the last 60 seconds or not.
struct stock_summary_message {
    static constexpr std::string_view name = "Stock Summary Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        symbol_index,
        high_price,
        low_price,
        open,
        close,
        total_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(high_price);
    XDPFIELD(low_price);
    XDPFIELD(open);
    XDPFIELD(close);
    XDPFIELD(total_volume);
};

static_assert(sizeof(stock_summary_message) == stock_summary_message::size, "stock_summary_message lies over its bytes exactly");

// Non Displayed Trade Message: An Non Displayed Trade message is sent as a result of a match between two non-displayed orders.
struct non_displayed_trade_message {
    static constexpr std::string_view name = "Non Displayed Trade Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        trade_id,
        price,
        volume,
        printable_flag,
        db_exec_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(trade_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(printable_flag);
    XDPFIELD(db_exec_id);
};

static_assert(sizeof(non_displayed_trade_message) == non_displayed_trade_message::size, "non_displayed_trade_message lies over its bytes exactly");

// Order Execution Message: An Order Execution message is sent when an order is partially or fully executed.
struct order_execution_message {
    static constexpr std::string_view name = "Order Execution Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        order_id,
        trade_id,
        price,
        volume,
        printable_flag,
        num_parity_splits,
        db_exec_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(order_id);
    XDPFIELD(trade_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(printable_flag);
    XDPFIELD(num_parity_splits);
    XDPFIELD(db_exec_id);
};

static_assert(sizeof(order_execution_message) == order_execution_message::size, "order_execution_message lies over its bytes exactly");

// Imbalance Message: Imbalance messages are sent periodically during auctions to update price and volume information. If there is no change to the calculated fields, no message will be generated.
struct imbalance_message {
    static constexpr std::string_view name = "Imbalance Message";
    static constexpr std::size_t size = 63;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        reference_price,
        paired_qty,
        total_imbalance_qty,
        market_imbalance_qty,
        auction_time,
        auction_type,
        imbalance_side,
        continuous_book_clearing_price,
        closing_only_clearing_price,
        ssr_filing_price,
        indicative_match_price,
        upper_collar,
        lower_collar,
        auction_status,
        freeze_status,
        num_extensions>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(reference_price);
    XDPFIELD(paired_qty);
    XDPFIELD(total_imbalance_qty);
    XDPFIELD(market_imbalance_qty);
    XDPFIELD(auction_time);
    XDPFIELD(auction_type);
    XDPFIELD(imbalance_side);
    XDPFIELD(continuous_book_clearing_price);
    XDPFIELD(closing_only_clearing_price);
    XDPFIELD(ssr_filing_price);
    XDPFIELD(indicative_match_price);
    XDPFIELD(upper_collar);
    XDPFIELD(lower_collar);
    XDPFIELD(auction_status);
    XDPFIELD(freeze_status);
    XDPFIELD(num_extensions);
};

static_assert(sizeof(imbalance_message) == imbalance_message::size, "imbalance_message lies over its bytes exactly");

// Add Order Refresh Message: The Add Order Refresh message can be sent in either of two contexts: 1) If a client sends a Refresh Request to the Request Controller, an Add Order Refresh message is sent over the Refresh channels as part of the refresh response for every order currently sitting on the book. 2) If NYSE Operations refreshes a symbol, a Symbol Clear message is published, followed by a full refresh. The refresh includes an Add Order Refresh message for every order currently sitting on the book of the symbol.
struct add_order_refresh_message {
    static constexpr std::string_view name = "Add Order Refresh Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        order_id,
        price,
        volume,
        side,
        firm_id,
        num_parity_splits>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(order_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(side);
    XDPFIELD(firm_id);
    XDPFIELD(num_parity_splits);
};

static_assert(sizeof(add_order_refresh_message) == add_order_refresh_message::size, "add_order_refresh_message lies over its bytes exactly");

// Retail Price Improvement Message: Published when RPI interest (hidden retail price improvement interest) is added or removed between the best bid and best offer price. When all RPI interest for this security is removed from the book, An RPI message with RPIIndicator = ' ' (space character) is published.
struct retail_price_improvement_message {
    static constexpr std::string_view name = "Retail Price Improvement Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        rpi_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(rpi_indicator);
};

static_assert(sizeof(retail_price_improvement_message) == retail_price_improvement_message::size, "retail_price_improvement_message lies over its bytes exactly");

// Cross Correction Message: In the event that an earlier Cross Trade has been reported in error, a Cross Correction message is sent.
struct cross_correction_message {
    static constexpr std::string_view name = "Cross Correction Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        cross_id,
        volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(cross_id);
    XDPFIELD(volume);
};

static_assert(sizeof(cross_correction_message) == cross_correction_message::size, "cross_correction_message lies over its bytes exactly");

// Cross Trade Message: A Cross Trade message is published on completion of a crossing auction, and shows the bulk volume that traded in the auction. The Reason Code field indicates the auction type. Additionally, a non-printable Order Execution or Trade message will be published for each order that traded.
struct cross_trade_message {
    static constexpr std::string_view name = "Cross Trade Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        cross_id,
        price,
        volume,
        cross_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(cross_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(cross_type);
};

static_assert(sizeof(cross_trade_message) == cross_trade_message::size, "cross_trade_message lies over its bytes exactly");

// Trade Cancel Message: In the event that an earlier trade has been reported in error, a Trade Cancel message is sent. This occurs whether the initial report was an Order Execution or a Non-Displayed Trade message.
struct trade_cancel_message {
    static constexpr std::string_view name = "Trade Cancel Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(trade_id);
};

static_assert(sizeof(trade_cancel_message) == trade_cancel_message::size, "trade_cancel_message lies over its bytes exactly");

// Delete Order Message: A Delete Order message is published when an order is taken off of the book for any reason except for full execution, in which case an Order Execution message is sent.
struct delete_order_message {
    static constexpr std::string_view name = "Delete Order Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        order_id,
        num_parity_splits>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(order_id);
    XDPFIELD(num_parity_splits);
};

static_assert(sizeof(delete_order_message) == delete_order_message::size, "delete_order_message lies over its bytes exactly");

// Replace Order Message: A Replace Order message is published when a cancel/replace order is received and executed. The sitting order is replaced with a new one containing the same symbol, side and attribution, a new Order ID, and the price and size specified. The sitting order must be removed from the book and replaced with the new order.
struct replace_order_message {
    static constexpr std::string_view name = "Replace Order Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        order_id,
        new_order_id,
        price,
        volume,
        prev_price_parity_splits,
        new_price_parity_splits>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(order_id);
    XDPFIELD(new_order_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(prev_price_parity_splits);
    XDPFIELD(new_price_parity_splits);
};

static_assert(sizeof(replace_order_message) == replace_order_message::size, "replace_order_message lies over its bytes exactly");

// Modify Order Message: A Modify Order message is sent when the price or volume of an order is changed due to an event other than a cancel-replace, or full or partial execution. The content of the price and volume fields represent the new values after modification.
struct modify_order_message {
    static constexpr std::string_view name = "Modify Order Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        order_id,
        price,
        volume,
        position_change,
        prev_price_parity_splits,
        new_price_parity_splits>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(order_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(position_change);
    XDPFIELD(prev_price_parity_splits);
    XDPFIELD(new_price_parity_splits);
};

static_assert(sizeof(modify_order_message) == modify_order_message::size, "modify_order_message lies over its bytes exactly");

// Add Order Message: An Add Order message is published when a new visible order has been received and added to the book. The Order ID is assigned by the matching engine and is good for today only. It is unique across all markets, except that for NYSE Tape A symbols, it is only unique per matching engine instance.
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        order_id,
        price,
        volume,
        side,
        firm_id,
        num_parity_splits>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(order_id);
    XDPFIELD(price);
    XDPFIELD(volume);
    XDPFIELD(side);
    XDPFIELD(firm_id);
    XDPFIELD(num_parity_splits);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Full Refresh Header: Sequence number fields that only the full Refresh Header carries.
struct full_refresh_header {
    static constexpr std::string_view name = "Full Refresh Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_seq_num,
        last_symbol_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(last_seq_num);
    XDPFIELD(last_symbol_seq_num);
};

static_assert(sizeof(full_refresh_header) == full_refresh_header::size, "full_refresh_header lies over its bytes exactly");

// Refresh Header Message Section 1
struct refresh_header_message_section_1 {
    static constexpr std::string_view name = "Refresh Header Message Section 1";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        current_refresh_pkt,
        total_refresh_pkts>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(current_refresh_pkt);
    XDPFIELD(total_refresh_pkts);
};

static_assert(sizeof(refresh_header_message_section_1) == refresh_header_message_section_1::size, "refresh_header_message_section_1 lies over its bytes exactly");

// Refresh Header Message: The first message in each packet of refresh messages published over the Refresh multicast channels is of this type.
struct refresh_header_message {
    static constexpr std::string_view name = "Refresh Header Message";
    static constexpr bool is_message = true;
};

// Security Status Message: This message informs clients of changes in the status of a specific security, such as Trading Halts, Short Sale Restriction state changes, etc.
struct security_status_message {
    static constexpr std::string_view name = "Security Status Message";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        security_status,
        halt_condition,
        reserved_4,
        price_1,
        price_2,
        ssr_triggering_exchange_id,
        ssr_triggering_volume,
        time,
        ssr_state,
        market_state,
        session_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(security_status);
    XDPFIELD(halt_condition);
    XDPFIELD(reserved_4);
    XDPFIELD(price_1);
    XDPFIELD(price_2);
    XDPFIELD(ssr_triggering_exchange_id);
    XDPFIELD(ssr_triggering_volume);
    XDPFIELD(time);
    XDPFIELD(ssr_state);
    XDPFIELD(market_state);
    XDPFIELD(session_state);
};

static_assert(sizeof(security_status_message) == security_status_message::size, "security_status_message lies over its bytes exactly");

// Symbol Clear Message: In case of a failure and recovery of a Matching Engine or an XDP Publisher, the publisher may send a full state refresh for every symbol affected. This kind of unrequested refresh is preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear message by clearing all state information for the specified symbol in anticipation of receiving a full state refresh.
struct symbol_clear_message {
    static constexpr std::string_view name = "Symbol Clear Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        symbol_index,
        next_source_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_time);
    XDPFIELD(source_time_ns);
    XDPFIELD(symbol_index);
    XDPFIELD(next_source_seq_num);
};

static_assert(sizeof(symbol_clear_message) == symbol_clear_message::size, "symbol_clear_message lies over its bytes exactly");

// Message Unavailable Message: This message will be sent over the Retransmission multicast channels to inform clients of unavailability of a range of messages (or part of a range) for which they may have requested a retransmission.
struct message_unavailable_message {
    static constexpr std::string_view name = "Message Unavailable Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        begin_seq_num,
        end_seq_num,
        product_id,
        channel_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(begin_seq_num);
    XDPFIELD(end_seq_num);
    XDPFIELD(product_id);
    XDPFIELD(channel_id);
};

static_assert(sizeof(message_unavailable_message) == message_unavailable_message::size, "message_unavailable_message lies over its bytes exactly");

// Refresh Request Message: Clients who have experienced a failure and need a refresh of the state of one or all symbols in a specific channel should send a Retransmission Request message via TCP to the Request Controller. A Request Response message will be sent over the TCP connection back to the client, and if the request was valid, the requested message(s) will be published over the relevant Refresh multicast channel.
struct refresh_request_message {
    static constexpr std::string_view name = "Refresh Request Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_index,
        source_id,
        product_id,
        channel_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(symbol_index);
    XDPFIELD(source_id);
    XDPFIELD(product_id);
    XDPFIELD(channel_id);
};

static_assert(sizeof(refresh_request_message) == refresh_request_message::size, "refresh_request_message lies over its bytes exactly");

// Symbol Index Mapping Request Message: This message is sent by clients via TCP/IP requesting the Symbol Index Mapping messages for one or all symbols in a specified channel.
struct symbol_index_mapping_request_message {
    static constexpr std::string_view name = "Symbol Index Mapping Request Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_index,
        source_id,
        product_id,
        channel_id,
        retransmit_method>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(symbol_index);
    XDPFIELD(source_id);
    XDPFIELD(product_id);
    XDPFIELD(channel_id);
    XDPFIELD(retransmit_method);
};

static_assert(sizeof(symbol_index_mapping_request_message) == symbol_index_mapping_request_message::size, "symbol_index_mapping_request_message lies over its bytes exactly");

// Heartbeat Response Message: Clients who remain connected to the Retransmission Server intraday must respond to a Heartbeat with a Heartbeat Response message within 5 seconds. If no timely client response is received, the connection will be closed.
struct heartbeat_response_message {
    static constexpr std::string_view name = "Heartbeat Response Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(source_id);
};

static_assert(sizeof(heartbeat_response_message) == heartbeat_response_message::size, "heartbeat_response_message lies over its bytes exactly");

// Request Response Message: This message will be sent immediately via TCP/IP in response to the client’s request for retransmission, refresh or Symbol Mapping messages.
struct request_response_message {
    static constexpr std::string_view name = "Request Response Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        request_seq_num,
        begin_seq_num,
        end_seq_num,
        source_id,
        product_id,
        channel_id,
        status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(request_seq_num);
    XDPFIELD(begin_seq_num);
    XDPFIELD(end_seq_num);
    XDPFIELD(source_id);
    XDPFIELD(product_id);
    XDPFIELD(channel_id);
    XDPFIELD(status);
};

static_assert(sizeof(request_response_message) == request_response_message::size, "request_response_message lies over its bytes exactly");

// Retransmission Request Message: Clients who have experienced a sequence number gap and need a retransmission of the missed messages should send a Retransmission Request message via TCP to the Request Controller. A Request Response message will be sent over the TCP connection back to the client, and if the request was valid, the requested message(s) will be re-published over the relevant Retransmission multicast channel.
struct retransmission_request_message {
    static constexpr std::string_view name = "Retransmission Request Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        begin_seq_num,
        end_seq_num,
        source_id,
        product_id,
        channel_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(begin_seq_num);
    XDPFIELD(end_seq_num);
    XDPFIELD(source_id);
    XDPFIELD(product_id);
    XDPFIELD(channel_id);
};

static_assert(sizeof(retransmission_request_message) == retransmission_request_message::size, "retransmission_request_message lies over its bytes exactly");

// Symbol Index Mapping Message: This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or XDP Publisher failover. It provides referential data for a single specified symbol.
struct symbol_index_mapping_message {
    static constexpr std::string_view name = "Symbol Index Mapping Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol_index,
        symbol,
        reserved_1,
        market_id,
        system_id,
        exchange_code,
        price_scale_code,
        security_type,
        lot_size,
        prev_close_price,
        prev_close_volume,
        price_resolution,
        round_lot,
        mpv,
        unit_of_trade,
        reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(symbol_index);
    XDPFIELD(symbol);
    XDPFIELD(reserved_1);
    XDPFIELD(market_id);
    XDPFIELD(system_id);
    XDPFIELD(exchange_code);
    XDPFIELD(price_scale_code);
    XDPFIELD(security_type);
    XDPFIELD(lot_size);
    XDPFIELD(prev_close_price);
    XDPFIELD(prev_close_volume);
    XDPFIELD(price_resolution);
    XDPFIELD(round_lot);
    XDPFIELD(mpv);
    XDPFIELD(unit_of_trade);
    XDPFIELD(reserved_2);
};

static_assert(sizeof(symbol_index_mapping_message) == symbol_index_mapping_message::size, "symbol_index_mapping_message lies over its bytes exactly");

// Source Time Reference Message: This message is sent at the start of every second during periods of active data publication.
struct source_time_reference_message {
    static constexpr std::string_view name = "Source Time Reference Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        id,
        symbol_seq_num,
        source_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XDPFIELD(id);
    XDPFIELD(symbol_seq_num);
    XDPFIELD(source_time);
};

static_assert(sizeof(source_time_reference_message) == source_time_reference_message::size, "source_time_reference_message lies over its bytes exactly");

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

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
