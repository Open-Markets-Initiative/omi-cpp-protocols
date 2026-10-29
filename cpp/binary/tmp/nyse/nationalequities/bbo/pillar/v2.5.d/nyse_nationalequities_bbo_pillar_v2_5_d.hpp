// Nyse NationalEquities Bbo Pillar 2.5.d Template Meta Programming

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

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

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

// Ask Price: The Ask price. Use the Price scale from the Symbol Index message.
struct ask_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Volume: The aggregate round lot size at the ask price, in shares.
struct ask_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Bid Price: The Bid price. Use the Price scale from the Symbol Index message.
struct bid_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Volume: The aggregate round lot size at the bid price, in shares.
struct bid_volume {
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

// Current Refresh Pkt: The current refresh packet in the update.
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

// Exchange Code: For listed equity markets, the market where this symbol is listed.
struct exchange_code {
    enum class type : char {
        nyse_american = 'A',
        ltse = 'L',
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
        retransmission_request_message = 10,
        symbol_index_mapping_request_message = 13,
        refresh_request_message = 15,
        message_unavailable_message = 31,
        refresh_header_message = 35,
        request_response_message = 11,
        heartbeat_response_message = 12,
        quote_message = 140,
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

// Number Msgs: The number of messages in this packet
struct number_msgs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Product Id: The unique ID for this NYSE feed listed in the feed's client specification.
struct product_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Condition
struct quote_condition {
    enum class type : char {
        regular_quote = 'R',
        opening_quote = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Request Seq Num: The sequence number of the request message sent by the client. This can be used by the client to couple this response with the original request message.
struct request_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: This field is reserved for future use.
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

// Retransmit Method: The delivery method for the requested symbol index mapping information. Valid values: 0 - deliver via UDP.
struct retransmit_method {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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

// Rpi Indicator: The side(s) where Retail Price Indication orders (RPI orders) exist. Values correspond to CQS values.
struct rpi_indicator {
    enum class type : char {
        no_retail_interest_default = ' ',
        retail_interest_on_bid_side = 'A',
        retail_interest_on_offer_side = 'B',
        retail_interest_on_the_bid_and_offer_side = 'C',
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

// Source Id: The ID of the client requesting this retransmission. All trailing characters should be NULL.
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

// Source Time Ns: The nanosecond offset (UTC Time) from the Time Reference message.
struct source_time_ns {
    using type = std::uint32_t;
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

// Status: The reason why the request was rejected.
struct status {
    enum class type : char {
        message_was_accepted = '0',
        rejected_due_to_an_invalid_source_id = '1',
        rejected_due_to_maximum_sequence_range_see_threshold_limits = '3',
        rejected_due_to_maximum_request_in_a_day = '4',
        rejected_due_to_maximum_number_of_refresh_requests_in_a_day = '5',
        rejected_request_message_seq_num_ttl_time_to_live_is_too_old_use_refresh_to_recover_current_state_if_necessary = '6',
        rejected_due_to_an_invalid_channel_id = '7',
        rejected_due_to_an_invalid_product_id = '8',
        rejected_due_to_1_invalid_msg_type_or_2_mismatch_between_msg_type_and_msg_size = '9',
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

// Symbol Index: The ID of the symbol in the Symbol Index message.
struct symbol_index {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Seq Num: The symbol sequence number.
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

// Total Refresh Pkts: The total number of refresh packets you should expect in the update.
struct total_refresh_pkts {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
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


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Quote Message: A quote message is sent when any event results in a new top of book value on either side of the market.
struct quote_message {
    static constexpr std::string_view name = "Quote Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_time_ns,
        symbol_index,
        symbol_seq_num,
        ask_price,
        ask_volume,
        bid_price,
        bid_volume,
        quote_condition,
        rpi_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    PILLARFIELD(source_time_ns);
    PILLARFIELD(symbol_index);
    PILLARFIELD(symbol_seq_num);
    PILLARFIELD(ask_price);
    PILLARFIELD(ask_volume);
    PILLARFIELD(bid_price);
    PILLARFIELD(bid_volume);
    PILLARFIELD(quote_condition);
    PILLARFIELD(rpi_indicator);
};

static_assert(sizeof(quote_message) == quote_message::size, "quote_message lies over its bytes exactly");

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

// Request Response Message: This message will be sent immediately via TCP/IP in response to the client's request for retransmission, refresh or Symbol Mapping messages.
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

// Refresh Request Message: Clients who have experienced a failure and need a refresh of the state of one or all symbols in a specific channel should send a Refresh Request message via TCP to the Request Controller.
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

// Retransmission Request Message: Clients who have experienced a sequence number gap and need a retransmission of the missed messages should send a Retransmission Request message via TCP to the Request Controller.
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

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
