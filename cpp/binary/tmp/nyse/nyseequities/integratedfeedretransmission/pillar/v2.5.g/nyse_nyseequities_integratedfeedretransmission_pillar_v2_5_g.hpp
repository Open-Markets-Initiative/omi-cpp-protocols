// Nyse NyseEquities IntegratedFeedRetransmission Pillar 2.5.g Template Meta Programming

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
#ifndef PILLARFIELD
#define PILLARFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef PILLARSEQUENCE
#define PILLARSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

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

// Auction Interest Clearing Price: The price at which auction only interest would trade.
struct auction_interest_clearing_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Status: Indicates whether the auction will run.
struct auction_status {
    enum class type : std::uint8_t {
        will_run_as_always_for_open_and_close = 0,
        will_run_interest_exists_inside_or_at_the_collars_or_is_fully_paired_off = 1,
        will_not_run_because_there_is_an_imbalance_through_the_collars = 2,
        will_not_run_will_transition_to_the_closing_auction_instead = 3,
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

// Auction Type: Auction type indicator.
struct auction_type {
    enum class type : char {
        early_opening_auction = 'O',
        core_opening_auction = 'M',
        reopening_auction_halt_resume = 'H',
        closing_auction = 'C',
        extreme_closing_imbalance = 'P',
        significant_closing_imbalance = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Begin Seq Num: The beginning sequence number of the unavailable range of messages.
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

// Continuous Book Clearing Price: The price closest to the reference price where the imbalance is 0.
struct continuous_book_clearing_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Id: Unique identifier for this Cross Trade.
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
        market_center_early_opening_auction = 'E',
        market_center_opening_auction = 'O',
        market_center_reopening_auction = '5',
        market_center_closing_auction = '6',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Delivery Flag: A flag that indicates whether this is an original, retransmitted, or ‘replayed’ message
struct delivery_flag {
    enum class type : std::uint8_t {
        heartbeat = 1,
        pillar_failover = 10,
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

// End Seq Num: The ending sequence number of the unavailable range of messages.
struct end_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exchange Code: For listed equity markets, the market where this symbol is listed.
struct exchange_code {
    enum class type : char {
        nyse_american = 'A',
        ltse = 'L',
        nyse_texas = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        iex = 'V',
        cboe = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Firm Id: The market participant's firm ID.
struct firm_id {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Freeze Status: Indicates an Imbalance Freeze for the auction.
struct freeze_status {
    enum class type : std::uint8_t {
        imbalance_freeze_not_in_effect = 0,
        imbalance_freeze_is_in_effect = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Halt Condition: The halt or other condition associated with the security status change.
struct halt_condition {
    enum class type : char {
        security_not_delayedhalted = '~',
        news_released_news_dissemination = 'D',
        order_imbalance = 'I',
        news_pending = 'P',
        luld_pause = 'M',
        equipment_changeover = 'X',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        corporate_action = 'N',
        new_security_offering = 'O',
        intraday_indicative_value_not_available = 'V',
        suspend = '6',
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
        buy_side = 'B',
        sell_side = 'S',
        no_imbalance = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Indicative Match Price: The best price at which the maximum volume of shares is executable in the applicable auction, subject to Auction Collars.
struct indicative_match_price {
    using type = std::int32_t;
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

// Lower Collar: Lower boundary for the Indicative Match Price.
struct lower_collar {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Id: ID of the Originating Market.
struct market_id {
    enum class type : std::uint16_t {
        nyse_equities = 1,
        nyse_arca_equities = 3,
        nyse_arca_options = 4,
        nyse_bonds = 5,
        nyse_american_options = 8,
        nyse_american_equities = 9,
        nyse_national_equities = 10,
        nyse_texas_equities = 11,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Imbalance Qty: The total market order imbalance quantity at the Reference Price.
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
        late_session_non_nyse_only = 'L',
        closed = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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
        symbol_clear_message = 32,
        security_status_message = 34,
        message_unavailable_message = 31,
        add_order_message = 100,
        modify_order_message = 101,
        delete_order_message = 102,
        order_execution_message = 103,
        replace_order_message = 104,
        imbalance_message = 105,
        add_order_refresh_message = 106,
        non_displayed_trade_message = 110,
        cross_trade_message = 111,
        trade_cancel_message = 112,
        cross_correction_message = 113,
        retail_price_improvement_message = 114,
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

// Next Source Seq Num: The sequence number in the next message for this symbol.
struct next_source_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Num Extensions: The number of times a halt period has been extended
struct num_extensions {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Msgs: The number of messages in this packet
struct number_msgs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: The unique ID assigned by the matching engine to this order.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Qty: Number of shares paired at the Reference Price.
struct paired_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pkt Size: The size of the packet in bytes, including this 16 byte packet header
struct pkt_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Position Change: Currently defaulted to 0.
struct position_change {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Close Price: The previous day's closing price for this security.
struct prev_close_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Close Volume: The previous day's closing volume for the security.
struct prev_close_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: The order price. Use with the Price Scale from the symbol-mapping index.
struct price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price 1: Default value is 0. If securityStatus = A and this security is listed on this exchange, then this field is the SSR Triggering Trade Price. If securityStatus = G or I, then this field is the Indication Low Price.
struct price_1 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price 2: Default value is 0. If securityStatus = G or I, then this field is the Indication High Price.
struct price_2 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Resolution: Minimum price increment: 0 - All Penny, 1 - Penny/Nickel, 5 - Nickel/Dime.
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

// Printable Flag: 0 = Not Printed to the SIP. 1 = Printed to the SIP.
struct printable_flag {
    enum class type : std::uint8_t {
        not_printed_to_the_sip = 0,
        printed_to_the_sip = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Product Id: The unique ID for this NYSE feed listed in the feed's client specification.
struct product_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reference Price: The price at which imbalances are calculated.
struct reference_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: Defaulted to 0. Future use only.
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

// Round Lot: Round Lots Accepted: Y - Yes, N - No.
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
        no_retail_interest_default = ' ',
        retail_interest_on_the_bid_side = 'A',
        retail_interest_on_the_offer_side = 'B',
        retail_interest_on_the_bid_and_offer_sides = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seconds: Seconds since Jan 1, 1970 00:00:00 UTC
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
        trading_halt = '4',
        resume = '5',
        suspend = '6',
        short_sale_restriction_activated_day_1 = 'A',
        short_sale_restriction_continued_day_2 = 'C',
        short_sale_restriction_deactivated = 'D',
        pre_opening = 'P',
        begin_accepting_orders = 'B',
        early_session = 'E',
        core_session = 'O',
        late_session_non_nyse_only = 'L',
        closed = 'X',
        halt_resume_price_indication = 'I',
        pre_opening_price_indication = 'G',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type: Type of Security used by Pillar-powered markets.
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
        closed_end_fund = 'U',
        warrant = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seq Num: The message sequence number of the first message in this packet
struct seq_num {
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

// Side: The side of the order (Buy/Sell).
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

// Source Time: The time when this msg was generated in the order book, in secs since 1/1/1970 00:00:00 UTC
struct source_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Source Time Ns: The nanosecond offset from the Time Reference second.
struct source_time_ns {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ssr Filing Price: For NYSE non-Significant imbalances, if a Sell Short Restriction is in effect, the price at which Sell Short interest will be filed.
struct ssr_filing_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ssr State: The current SSR state, which this msg updates if the Security Status field contains an SSR Code.
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
        n24x = 'G',
        miami_peral = 'H',
        nasdaq_ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_texas = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        nasdaq_omx = 'T',
        memx = 'U',
        iex = 'V',
        cbsx = 'W',
        nasdaq_omx_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z',
        no_value_value = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ssr Triggering Volume: Default value is 0. This field is only populated when securityStatus = A and this security is listed on this exchange.
struct ssr_triggering_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Symbol Index: The ID of the symbol in the Symbol Index msg
struct symbol_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Seq Num: The sequence number of this message in the set of all messages for this symbol
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

// Time: Default value is 0. Format: HHMMSSmmm (mmm = milliseconds). If securityStatus = A and this security is listed on this exchange, then this field is the SSR Trigger Time.
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

// Total Imbalance Qty: The total imbalance quantity at the Reference Price.
struct total_imbalance_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Cond 1: Settlement related conditions.
struct trade_cond_1 {
    enum class type : char {
        regular_sale = '@',
        cash_texas_only = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Cond 2: The reason for Trade Through Exemptions.
struct trade_cond_2 {
    enum class type : char {
        na = ' ',
        intermarket_sweep_order = 'F',
        market_center_opening_trade_arca_american_and_nyse_only = 'O',
        reopening_trade_arca_american_and_nyse_only = '5',
        market_center_closing_trade_arca_american_and_nyse_only = '6',
        qualified_contingent_trade_texas_only = '7',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Cond 3: Extended hours/sequencing related conditions.
struct trade_cond_3 {
    enum class type : char {
        na = ' ',
        extended_hours_trade = 'T',
        extended_hours_sold_out_of_sequence = 'U',
        sold = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Cond 4: SRO Required Detail.
struct trade_cond_4 {
    enum class type : char {
        na = ' ',
        odd_lot_trade = 'I',
        contingent_trade_texas_only = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Id: Unique ID assigned by the matching engine to this execution.
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unit Of Trade: This field specifies the security Unit of Trade in shares. Valid values are 1, 10, 50 and 100.
struct unit_of_trade {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unpaired Qty: The number of unpaired shares priced at or better than the Reference Price.
struct unpaired_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unpaired Side: The side of the Unpaired Qty
struct unpaired_side {
    enum class type : char {
        buy_side = 'B',
        sell_side = 'S',
        not_applicable = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Upper Collar: Upper boundary for the Indicative Match Price.
struct upper_collar {
    using type = std::int32_t;
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

// Retail Price Improvement Message: Published when RPI interest is added or removed between the best bid and best offer price.
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
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(rpi_indicator);
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
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(cross_id);
    PILLARFIELD(volume);
};

static_assert(sizeof(cross_correction_message) == cross_correction_message::size, "cross_correction_message lies over its bytes exactly");

// Trade Cancel Message: In the event that an earlier trade has been reported in error, a Trade Cancel message is sent.
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
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(trade_id);
};

static_assert(sizeof(trade_cancel_message) == trade_cancel_message::size, "trade_cancel_message lies over its bytes exactly");

// Cross Trade Message: A Cross Trade message is published on completion of a crossing auction.
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
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(cross_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(cross_type);
};

static_assert(sizeof(cross_trade_message) == cross_trade_message::size, "cross_trade_message lies over its bytes exactly");

// Non Displayed Trade Message: A Non Displayed Trade message is sent as a result of a match between two non-displayed orders.
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
        trade_cond_1,
        trade_cond_2,
        trade_cond_3,
        trade_cond_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(trade_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(printable_flag);
    PILLARFIELD(trade_cond_1);
    PILLARFIELD(trade_cond_2);
    PILLARFIELD(trade_cond_3);
    PILLARFIELD(trade_cond_4);
};

static_assert(sizeof(non_displayed_trade_message) == non_displayed_trade_message::size, "non_displayed_trade_message lies over its bytes exactly");

// Add Order Refresh Message: The Add Order Refresh message can be sent in either of two contexts: refresh response or symbol refresh.
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
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(order_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(side);
    PILLARFIELD(firm_id);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(add_order_refresh_message) == add_order_refresh_message::size, "add_order_refresh_message lies over its bytes exactly");

// Imbalance Message: Imbalance messages are published once a second during auctions to update price and volume information.
struct imbalance_message {
    static constexpr std::string_view name = "Imbalance Message";
    static constexpr std::size_t size = 69;
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
        auction_interest_clearing_price,
        ssr_filing_price,
        indicative_match_price,
        upper_collar,
        lower_collar,
        auction_status,
        freeze_status,
        num_extensions,
        unpaired_qty,
        unpaired_side,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(reference_price);
    PILLARFIELD(paired_qty);
    PILLARFIELD(total_imbalance_qty);
    PILLARFIELD(market_imbalance_qty);
    PILLARFIELD(auction_time);
    PILLARFIELD(auction_type);
    PILLARFIELD(imbalance_side);
    PILLARFIELD(continuous_book_clearing_price);
    PILLARFIELD(auction_interest_clearing_price);
    PILLARFIELD(ssr_filing_price);
    PILLARFIELD(indicative_match_price);
    PILLARFIELD(upper_collar);
    PILLARFIELD(lower_collar);
    PILLARFIELD(auction_status);
    PILLARFIELD(freeze_status);
    PILLARFIELD(num_extensions);
    PILLARFIELD(unpaired_qty);
    PILLARFIELD(unpaired_side);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(imbalance_message) == imbalance_message::size, "imbalance_message lies over its bytes exactly");

// Replace Order Message: A Replace Order message is published when a cancel/replace order is received and executed.
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
        side,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(order_id);
    PILLARFIELD(new_order_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(side);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(replace_order_message) == replace_order_message::size, "replace_order_message lies over its bytes exactly");

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
        reserved_1,
        trade_cond_1,
        trade_cond_2,
        trade_cond_3,
        trade_cond_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(order_id);
    PILLARFIELD(trade_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(printable_flag);
    PILLARFIELD(reserved_1);
    PILLARFIELD(trade_cond_1);
    PILLARFIELD(trade_cond_2);
    PILLARFIELD(trade_cond_3);
    PILLARFIELD(trade_cond_4);
};

static_assert(sizeof(order_execution_message) == order_execution_message::size, "order_execution_message lies over its bytes exactly");

// Delete Order Message: A Delete Order message is published when an order is taken off of the book.
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
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(order_id);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(delete_order_message) == delete_order_message::size, "delete_order_message lies over its bytes exactly");

// Modify Order Message: A Modify Order message is sent when the price or volume of an order is changed.
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
        side,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(order_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(position_change);
    PILLARFIELD(side);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(modify_order_message) == modify_order_message::size, "modify_order_message lies over its bytes exactly");

// Add Order Message: An Add Order message is published when a new visible order has been received and added to the book.
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
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(order_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(side);
    PILLARFIELD(firm_id);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

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
    PILLARFIELD(begin_seq_num);
    PILLARFIELD(end_seq_num);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
};

static_assert(sizeof(message_unavailable_message) == message_unavailable_message::size, "message_unavailable_message lies over its bytes exactly");

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
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(security_status);
    PILLARFIELD(halt_condition);
    PILLARFIELD(reserved_4);
    PILLARFIELD(price_1);
    PILLARFIELD(price_2);
    PILLARFIELD(ssr_triggering_exchange_id);
    PILLARFIELD(ssr_triggering_volume);
    PILLARFIELD(time);
    PILLARFIELD(ssr_state);
    PILLARFIELD(market_state);
    PILLARFIELD(session_state);
};

static_assert(sizeof(security_status_message) == security_status_message::size, "security_status_message lies over its bytes exactly");

// Symbol Clear Message: In case of a failure and recovery of a Matching Engine or an Pillar Publisher, the publisher may send a full state refresh for every symbol affected. This unrequested refresh is preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear message by clearing all state information for the specified symbol in anticipation of receiving a full state refresh.
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
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(next_source_seq_num);
};

static_assert(sizeof(symbol_clear_message) == symbol_clear_message::size, "symbol_clear_message lies over its bytes exactly");

// Symbol Index Mapping Message: This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or Pillar Publisher failover. It provides referential data for a single specified symbol.
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
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol);
    PILLARFIELD(reserved_1);
    PILLARFIELD(market_id);
    PILLARFIELD(system_id);
    PILLARFIELD(exchange_code);
    PILLARFIELD(price_scale_code);
    PILLARFIELD(security_type);
    PILLARFIELD(lot_size);
    PILLARFIELD(prev_close_price);
    PILLARFIELD(prev_close_volume);
    PILLARFIELD(price_resolution);
    PILLARFIELD(round_lot);
    PILLARFIELD(mpv);
    PILLARFIELD(unit_of_trade);
    PILLARFIELD(reserved_2);
};

static_assert(sizeof(symbol_index_mapping_message) == symbol_index_mapping_message::size, "symbol_index_mapping_message lies over its bytes exactly");

// Source Time Reference Message: For high-volume feeds, this message is sent at the start of every second during periods of active data publication. The client can concatenate the SourceTime field with the SourceTimeNS field in subsequent market data messages to get full 8-byte Matching Engine event timestamps.
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
    PILLARFIELD(id);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(source_time);
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
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
};

static_assert(sizeof(sequence_number_reset_message) == sequence_number_reset_message::size, "sequence_number_reset_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Pillar message header
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
    PILLARFIELD(message_size);
    PILLARFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Pillar message
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
    PILLARSEQUENCE(message);
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
    PILLARFIELD(seconds);
    PILLARFIELD(nanoseconds);
};

static_assert(sizeof(send_time) == send_time::size, "send_time lies over its bytes exactly");

// Packet Header: Pillar common client udp packet header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        pkt_size,
        delivery_flag,
        number_msgs,
        seq_num,
        send_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(pkt_size);
    PILLARFIELD(delivery_flag);
    PILLARFIELD(number_msgs);
    PILLARFIELD(seq_num);
    PILLARFIELD(send_time);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Pillar common client udp packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
