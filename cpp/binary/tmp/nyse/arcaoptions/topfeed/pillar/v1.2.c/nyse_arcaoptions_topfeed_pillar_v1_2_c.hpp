// Nyse ArcaOptions TopFeed Pillar 1.2.c Template Meta Programming

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

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

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

// Ask Customer Volume: Total quantity of customer orders at the Ask price
struct ask_customer_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Price: The Ask price. Use the Price scale from the Series Index message.
struct ask_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Volume: Total quantity available at the above Ask price
struct ask_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Id: Auction ID for CUBE/COA
struct auction_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Interest Clearing Price: The price at which all eligible auction-only interest would trade, subject to auction collars.
struct auction_interest_clearing_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Status: Indicates whether the auction will run
struct auction_status {
    enum class type : std::uint8_t {
        usual = 0,
        legal_width_quote_does_not_exist = 4,
        market_maker_quote_is_not_received = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Type: AuctionType
struct auction_type {
    enum class type : char {
        opening = 'O',
        reopening = 'H',
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

// Bid Customer Volume: Total quantity of customer orders at the Bid price
struct bid_customer_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price: The Bid price. Use the Price scale from the Series Index message.
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
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Capacity: Customer or Firm capacity specified with the order. Values include:
struct capacity {
    enum class type : char {
        not_specified = ' ',
        customer = '0',
        firm = '1',
        broker_dealer = '2',
        market_maker = '3',
        professional_customer = '8',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Close: The Last price of the series for the day. Use the Price scale from the series index mapping.
struct close {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Closing Only Indicator
struct closing_only_indicator {
    enum class type : char {
        standard_series = '0',
        call = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Continuous Book Clearing Price: The price at which all interest on the book can trade, including auction and imbalance offset interest, and disregarding auction collars.
struct continuous_book_clearing_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier: Number of Underlying shares per option contract
struct contract_multiplier {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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
        ltse = 'L',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        iex = 'V',
        cboe = 'Z',
        otc_or_indexed_product = ' ',
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
        security_not_delayed_or_halted = '~',
        news_released = 'D',
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

// High Price: The Highest price of the series for the day. Use the Price scale from the series mapping index.
struct high_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Id: ID of the originating Matching Engine partition to which this message applies
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
        buy = 'B',
        sell = 'S',
        no_imbalance = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Indicative Match Price: The price at which the highest number of contracts would trade, subject to auction collars. It includes the non-displayed quantity of Reserve Orders. See Information on Auctions for details.
struct indicative_match_price {
    using type = std::int32_t;
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

// Low Price: The Lowest price of the series for the day. Use the Price scale from the series mapping index.
struct low_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lower Collar: Legal width offer for option
struct lower_collar {
    using type = std::int32_t;
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
        nyse_american_options = 8,
        nyse_american_equities = 9,
        nyse_national_equities = 10,
        nyse_chicago = 11,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Imbalance Qty: The total market order imbalance quantity at the Indicative Match Price.
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

// Maturity Date: Option maturity date - YYMMDD
struct maturity_date {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
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
        time_reference_message = 2,
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
        outright_series_index_mapping_message = 50,
        options_status_message = 51,
        options_quote_message = 340,
        options_trade_message = 320,
        options_trade_cancel_message = 321,
        options_trade_correction_message = 322,
        options_imbalance_message = 305,
        series_rfq_message = 307,
        outright_series_summary_message = 323,
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

// Number Msgs: The number of messages in this packet
struct number_msgs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offical: Reserved for future use
struct offical {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Open: The First price of the series for the day. Use the Price scale from the series mapping index.
struct open {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opening: Reserved for future use
struct opening {
    enum class type : char {
        none = ' ',
        market_center_opening_trade = 'O',
        reopening_trade = '5',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Option Symbol Root: Root symbol for options in OCC symbology
struct option_symbol_root {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Original Trade Id: The original TradeID of the Trade being cancelled.
struct original_trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Qty: The number of contracts paired off at the Indicative Match Price.
struct paired_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant: OCC Number for the Clearing firm specified with the order.
struct participant {
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

// Price: The price of the Trade. Use the Price scale from the series index mapping.
struct price {
    using type = std::int32_t;
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
    enum class type : std::uint8_t {
        low_priced_securities = 6,
        medium_priced_securities = 4,
        high_priced_securities = 3,
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

// Put Or Call: Option Type
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

// Quote Condition
struct quote_condition {
    enum class type : char {
        regular_trading = '1',
        rotation = '2',
        trading_halted = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Reserved 2: Reserved for future use
struct reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 3: Reserved for future use
struct reserved_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Reserved 4: Reserved for future use
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 6: Reserved for future use.
struct reserved_6 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Retransmit Method: The delivery method for the requested symbol index mapping information.
struct retransmit_method {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Rfq Status: This status field is used for CUBE/COA (Type = C).
struct rfq_status {
    enum class type : char {
        start_value = 'O',
        end_value = 'Q',
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

// Second Reserved 4: Reserved for future use
struct second_reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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
        late_session = 'L',
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

// Series: Settlement related conditions. Valid values:
struct series {
    enum class type : char {
        cube = 'a',
        occ = 'c',
        floor_trade = 'e',
        other_outright_series = 'I',
        iso_sweep = 'S',
        after_90_seconds = 'D',
        other_complex_orders = 'f',
        complex_cube = 'g',
        complex_qcc_order = 'H',
        complex_floor_order = 'i',
        complex_order_trading_with_the_outright_series = 'j',
        complex_order_to_outright_series_orderfloor_trade = 'm',
        complex_order_with_stock_to_complex_order_with_stock_floor_trade = 'p',
        complex_order_with_stock_to_outright_series_order_floor_trade = 's',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Series Index: The unique ID of this series for all products within this market
struct series_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Series Seq Num: The unique ID of this message in the sequence of messages published for this specific series
struct series_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Series Status: The new status that this series is transitioning to
struct series_status {
    enum class type : char {
        trading_halt = '4',
        resume = '5',
        suspend = '6',
        pre_opening = 'P',
        begin_accepting_orders = 'B',
        core_session = 'O',
        closed = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Series Type: Identifies series type
struct series_type {
    enum class type : std::uint8_t {
        standard = 0,
        flex = 1,
        flex_percentage = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Session State: Unused
struct session_state {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_chicago = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        cts = 'S',
        nasdaq_omx = 'T',
        iex = 'V',
        cbsx = 'W',
        nasdaq_omx_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z',
        miax = 'H',
        memx = 'U',
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
        accepted = '0',
        rejected = '1',
        invalid_sequence_range = '2',
        maximum_sequence_range = '3',
        maximum_request_in_a_day = '4',
        maximum_refresh_requests_in_a_day = '5',
        old_seq_num_ttl = '6',
        invalid_channel_id = '7',
        invalid_product_id = '8',
        invalid_msg_type_or_msg_size = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Strike Price
struct strike_price {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
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

// Symbol Seq Num: The unique ID of this message in the sequence of messages published for this specific symbol.
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

// Total Imbalance Qty: The total imbalance quantity at the Indicative Match Price.
struct total_imbalance_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Quantity
struct total_quantity {
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

// Total Volume: The cumulative volume for the outright series throughout the day.
struct total_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: Unique identifier for this trade.
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transaction: Settlement related conditions. Valid values:
struct transaction {
    enum class type : char {
        opening_trade_in_sequence = 'H',
        opening_trade_out_of_sequence = 'F',
        in_sequence = 'D',
        out_of_sequence = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Type: Order Type of CUBE/Bold/COA
struct type_type {
    enum class type : char {
        price_improvement = 'P',
        facilitation = 'F',
        solicitation = 'S',
        bold = 'B',
        coa = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Index: Underlying stock mapping index
struct underlying_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Symbol: Underlying symbol for options in NYSE symbology
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Upper Collar: Legal width bid for option
struct upper_collar {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume: The volume of the trade in contracts.
struct volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Working Price: RFQ Price
struct working_price {
    using type = std::int32_t;
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

// Outright Series Summary Message: The Series Summary message will provide the following trade statistics per series: high, low, open, close and total volume
struct outright_series_summary_message {
    static constexpr std::string_view name = "Outright Series Summary Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        high_price,
        low_price,
        open,
        close,
        total_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(high_price);
    PILLARFIELD(low_price);
    PILLARFIELD(open);
    PILLARFIELD(close);
    PILLARFIELD(total_volume);
};

static_assert(sizeof(outright_series_summary_message) == outright_series_summary_message::size, "outright_series_summary_message lies over its bytes exactly");

// Series Rfq Message: The Request for Series RFQ message is published for outright series.
struct series_rfq_message {
    static constexpr std::string_view name = "Series Rfq Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        series_seq_num,
        side,
        type_type,
        capacity,
        total_quantity,
        working_price,
        participant,
        auction_id,
        rfq_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(side);
    PILLARFIELD(type_type);
    PILLARFIELD(capacity);
    PILLARFIELD(total_quantity);
    PILLARFIELD(working_price);
    PILLARFIELD(participant);
    PILLARFIELD(auction_id);
    PILLARFIELD(rfq_status);
};

static_assert(sizeof(series_rfq_message) == series_rfq_message::size, "series_rfq_message lies over its bytes exactly");

// Options Imbalance Message: Options Imbalance messages are published once a second during opening and reopening auctions to update price and volume information
struct options_imbalance_message {
    static constexpr std::string_view name = "Options Imbalance Message";
    static constexpr std::size_t size = 61;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        series_seq_num,
        reserved_4,
        paired_qty,
        total_imbalance_qty,
        market_imbalance_qty,
        reserved_2,
        auction_type,
        imbalance_side,
        continuous_book_clearing_price,
        auction_interest_clearing_price,
        second_reserved_4,
        indicative_match_price,
        upper_collar,
        lower_collar,
        auction_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(reserved_4);
    PILLARFIELD(paired_qty);
    PILLARFIELD(total_imbalance_qty);
    PILLARFIELD(market_imbalance_qty);
    PILLARFIELD(reserved_2);
    PILLARFIELD(auction_type);
    PILLARFIELD(imbalance_side);
    PILLARFIELD(continuous_book_clearing_price);
    PILLARFIELD(auction_interest_clearing_price);
    PILLARFIELD(second_reserved_4);
    PILLARFIELD(indicative_match_price);
    PILLARFIELD(upper_collar);
    PILLARFIELD(lower_collar);
    PILLARFIELD(auction_status);
};

static_assert(sizeof(options_imbalance_message) == options_imbalance_message::size, "options_imbalance_message lies over its bytes exactly");

// Correction Condition
struct correction_condition {
    static constexpr std::string_view name = "Correction Condition";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        transaction,
        reserved_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(transaction);
    PILLARFIELD(reserved_3);
};

static_assert(sizeof(correction_condition) == correction_condition::size, "correction_condition lies over its bytes exactly");

// Options Trade Correction Message: In the event that an earlier trade has been reported with one or multiple fields in error
struct options_trade_correction_message {
    static constexpr std::string_view name = "Options Trade Correction Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        series_seq_num,
        original_trade_id,
        trade_id,
        price,
        volume,
        correction_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(original_trade_id);
    PILLARFIELD(trade_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(correction_condition);
};

static_assert(sizeof(options_trade_correction_message) == options_trade_correction_message::size, "options_trade_correction_message lies over its bytes exactly");

// Options Trade Cancel Message: In the event that an earlier trade has been reported in error, an Options Trade Cancel message is sent
struct options_trade_cancel_message {
    static constexpr std::string_view name = "Options Trade Cancel Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        series_seq_num,
        original_trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(original_trade_id);
};

static_assert(sizeof(options_trade_cancel_message) == options_trade_cancel_message::size, "options_trade_cancel_message lies over its bytes exactly");

// Trade Condition
struct trade_condition {
    static constexpr std::string_view name = "Trade Condition";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        series,
        opening,
        reserved_1,
        offical>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(series);
    PILLARFIELD(opening);
    PILLARFIELD(reserved_1);
    PILLARFIELD(offical);
};

static_assert(sizeof(trade_condition) == trade_condition::size, "trade_condition lies over its bytes exactly");

// Options Trade Message: An Options Trade message is sent when there is an execution on the order book.
struct options_trade_message {
    static constexpr std::string_view name = "Options Trade Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        series_seq_num,
        trade_id,
        price,
        volume,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(trade_id);
    PILLARFIELD(price);
    PILLARFIELD(volume);
    PILLARFIELD(trade_condition);
};

static_assert(sizeof(options_trade_message) == options_trade_message::size, "options_trade_message lies over its bytes exactly");

// Options Quote Message: An Options quote message is sent when any event results in a new top of book value on either side of the market
struct options_quote_message {
    static constexpr std::string_view name = "Options Quote Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        series_index,
        series_seq_num,
        ask_price,
        ask_volume,
        bid_price,
        bid_volume,
        quote_condition,
        reserved_1,
        ask_customer_volume,
        bid_customer_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(ask_price);
    PILLARFIELD(ask_volume);
    PILLARFIELD(bid_price);
    PILLARFIELD(bid_volume);
    PILLARFIELD(quote_condition);
    PILLARFIELD(reserved_1);
    PILLARFIELD(ask_customer_volume);
    PILLARFIELD(bid_customer_volume);
};

static_assert(sizeof(options_quote_message) == options_quote_message::size, "options_quote_message lies over its bytes exactly");

// Options Status Message: This message informs clients of changes in the status of a specific option outright series and complex series
struct options_status_message {
    static constexpr std::string_view name = "Options Status Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time,
        source_time_ns,
        series_index,
        series_seq_num,
        series_status,
        market_state,
        halt_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(series_index);
    PILLARFIELD(series_seq_num);
    PILLARFIELD(series_status);
    PILLARFIELD(market_state);
    PILLARFIELD(halt_condition);
};

static_assert(sizeof(options_status_message) == options_status_message::size, "options_status_message lies over its bytes exactly");

// Outright Series Index Mapping Message: This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or PILLAR Publisher failover.
struct outright_series_index_mapping_message {
    static constexpr std::string_view name = "Outright Series Index Mapping Message";
    static constexpr std::size_t size = 51;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        series_index,
        series_type,
        market_id,
        system_id,
        option_symbol_root,
        underlying_symbol,
        underlying_index,
        price_scale_code,
        contract_multiplier,
        maturity_date,
        put_or_call,
        strike_price,
        closing_only_indicator,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(series_index);
    PILLARFIELD(series_type);
    PILLARFIELD(market_id);
    PILLARFIELD(system_id);
    PILLARFIELD(option_symbol_root);
    PILLARFIELD(underlying_symbol);
    PILLARFIELD(underlying_index);
    PILLARFIELD(price_scale_code);
    PILLARFIELD(contract_multiplier);
    PILLARFIELD(maturity_date);
    PILLARFIELD(put_or_call);
    PILLARFIELD(strike_price);
    PILLARFIELD(closing_only_indicator);
    PILLARFIELD(reserved_1);
};

static_assert(sizeof(outright_series_index_mapping_message) == outright_series_index_mapping_message::size, "outright_series_index_mapping_message lies over its bytes exactly");

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
    PILLARFIELD(last_seq_num);
    PILLARFIELD(last_symbol_seq_num);
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
    PILLARFIELD(current_refresh_pkt);
    PILLARFIELD(total_refresh_pkts);
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
    PILLARFIELD(source_time);
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(next_source_seq_num);
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
    PILLARFIELD(begin_seq_num);
    PILLARFIELD(end_seq_num);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
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
    PILLARFIELD(symbol_index);
    PILLARFIELD(source_id);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
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
    PILLARFIELD(symbol_index);
    PILLARFIELD(source_id);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
    PILLARFIELD(retransmit_method);
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
    PILLARFIELD(source_id);
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
    PILLARFIELD(request_seq_num);
    PILLARFIELD(begin_seq_num);
    PILLARFIELD(end_seq_num);
    PILLARFIELD(source_id);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
    PILLARFIELD(status);
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
    PILLARFIELD(begin_seq_num);
    PILLARFIELD(end_seq_num);
    PILLARFIELD(source_id);
    PILLARFIELD(product_id);
    PILLARFIELD(channel_id);
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
        reserved_6>;

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
    PILLARFIELD(reserved_6);
};

static_assert(sizeof(symbol_index_mapping_message) == symbol_index_mapping_message::size, "symbol_index_mapping_message lies over its bytes exactly");

// Time Reference Message: This message is sent at the start of every second during periods of active data publication
struct time_reference_message {
    static constexpr std::string_view name = "Time Reference Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        id,
        reserved_4,
        source_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(id);
    PILLARFIELD(reserved_4);
    PILLARFIELD(source_time);
};

static_assert(sizeof(time_reference_message) == time_reference_message::size, "time_reference_message lies over its bytes exactly");

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

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
