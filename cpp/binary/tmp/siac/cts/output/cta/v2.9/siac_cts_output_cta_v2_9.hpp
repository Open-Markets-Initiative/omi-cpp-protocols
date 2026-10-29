// Siac Cts Output Cta 2.9 Template Meta Programming

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
#ifndef CTSFIELD
#define CTSFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef CTSSEQUENCE
#define CTSSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace siac::cts::output::cta::v2_9 {

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

// Administrative Message Type
struct administrative_message_type {
    enum class type : char {
        start_of_end_of_day_message = 'A',
        end_of_end_of_day_message = 'B',
        start_of_start_of_day_message = 'C',
        end_of_start_of_day_message = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Collar Lower Threshold Price: Represents the latest lower threshold price of the Auction Collar. The lower threshold price of the Auction Collar is the lowest price of the auction collar, if any
struct auction_collar_lower_threshold_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Collar Reference Price: The Auction Collar Reference Price represents the price used by the exchange to establish the Auction Collar
struct auction_collar_reference_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Collar Upper Threshold Price: Represents the latest upper threshold price of the Auction Collar
struct auction_collar_upper_threshold_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Index Value: The Bid Index Value represents the value of the index’s calculation formula using the current Bid values of the component securities.
struct bid_index_value {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Checksum: Lower 2 bytes of the 4 byte sum of all the bytes in the block, excluding this Block Checksum field
struct block_checksum {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Pad Byte: Cta Block Pad Byte
struct block_pad_byte {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Sequence Number: All transmission blocks are assigned a sequential Block Sequence Number
struct block_sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Size: Indicate size in bytes of the entire transmission bloc
struct block_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Volume: The Buy Volume represents the reported imbalance of buy orders without matching sell orders for the security for a Participant.
struct buy_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cancel Error Action: Denotes whether the referenced transaction is to be cancelled or error
struct cancel_error_action {
    enum class type : char {
        cancel = '1',
        error = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Consolidated High Low Last Indicator: Identifies the Consolidated High/Low/Last Price applicable to the trade.
struct consolidated_high_low_last_indicator {
    enum class type : char {
        none = 'A',
        high = 'B',
        low = 'C',
        last = 'D',
        high_last = 'E',
        low_last = 'F',
        high_low_last = 'G',
        high_low = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Control Message Type
struct control_message_type {
    enum class type : char {
        start_of_day_message = 'A',
        reset_block_sequence_number_message = 'L',
        disaster_recovery_data_center_activation_message = 'P',
        line_integrity_message = 'T',
        end_of_day_message = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Crossing Session I Total Trades Volume: Contains the number of shares traded at the Participant’s close price and taking place after the close of a Participant’s regular session.
struct crossing_session_i_total_trades_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Crossing Session Ii Dollar Value: Contains the Dollar Value traded after the close of a Participant’s regular session.
struct crossing_session_ii_dollar_value {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Crossing Session Ii Total Trades Volume: Contains the number of shares traded after the close of a Participant’s regular session.
struct crossing_session_ii_total_trades_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Data Feed Indicator: Q for Consolidated Quotation System
struct data_feed_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Dollar Value: The Dollar Value represents the total dollar worth of the daily trade transactions.
struct dollar_value {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Extended Hours Or Sequence Type: Category 3: Extended Hours Or Sequence Type
struct extended_hours_or_sequence_type {
    enum class type : char {
        not_extended_hours_or_sold_out_of_sequence = ' ',
        sold_last = 'L',
        extended_hours_trade = 'T',
        extended_hours_sold = 'U',
        sold_out_of_sequence = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Financial Status Indicator: Identifies the financial status of the security.
struct financial_status_indicator {
    enum class type : char {
        not_applicable = '0',
        bankrupt = '1',
        below_continuing_listing_standards = '2',
        bankrupt_and_below_continuing_listing_standards = '3',
        late_filing = '4',
        bankrupt_and_late_filing = '5',
        below_continuing_listing_standards_and_late_filing = '6',
        bankrupt_below_continuing_listing_standards_and_late_filing = '7',
        creations_suspended = '8',
        redemptions_suspended = '9',
        liquidation = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Future Use: Field is reserved for future use.
struct future_use {
    using type = std::string_view;
    static constexpr std::size_t size = 62;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 62> value_;
};

// Halt Reason: Denotes the reason for the Opening Delay or Trading Halt
struct halt_reason {
    enum class type : char {
        not_applicable = ' ',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        news_released = 'D',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        order_imbalance = 'I',
        limit_up_limit_down_trading_pause = 'M',
        corporate_action = 'N',
        new_security_offering = 'O',
        news_pending = 'P',
        intraday_indicative_value_not_available = 'V',
        operational = 'X',
        subpenny_trading = 'Y',
        market_wide_circuit_breaker_level_1_breached = '1',
        market_wide_circuit_breaker_level_2_breached = '2',
        market_wide_circuit_breaker_level_3_breached = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Held Trade Indicator: The Held Trade Indicator reflects whether this trade qualifies for the Participant or Consolidated Last Price at the time it is disseminated
struct held_trade_indicator {
    enum class type : char {
        not_applicable = ' ',
        cannot_be_used_as_a_last_sale_for_both_participant_and_consolidated_basis = 'A',
        can_be_used_as_a_last_sale_for_participant_but_not_consolidated_basis = 'B',
        can_be_used_as_a_last_sale_for_participant_and_consolidated_basis = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// High Indication Price Upper Limit Price Band: Represents an approximation of what the high end Offer price of a security's trading range may be, or the upper price band value for a security. Has implied 6 decimal places
struct high_indication_price_upper_limit_price_band {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// High Price: The High Price represents the highest price paid for a security during the trading day
struct high_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Index Symbol: Contains the Index symbol
struct index_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Index Value: The Index Value represents a statistical composite that measures changes in the economy or in financial markets
struct index_value {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Indices Message Type
struct indices_message_type {
    enum class type : char {
        index_message = 'I',
        bid_and_offer_index_message = 'Q',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Initiating Participant Id: Participant or Processor that generated the message
struct initiating_participant_id {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_bx = 'B',
        nyse_national = 'C',
        adf = 'D',
        miax = 'H',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_chicago = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        cts = 'S',
        nasdaq = 'T',
        members_exchange = 'U',
        iex = 'V',
        cbsx = 'W',
        nasdaq_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Instrument Type: Identifies the instrument type relevant to the trade
struct instrument_type {
    enum class type : char {
        cta_eligible_equity = '0',
        local_issue = '1',
        corporate_bond = '2',
        government_bond = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Participant Id: Refer to Participant ID field description for Participant codes
struct last_participant_id {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_bx = 'B',
        nyse_national = 'C',
        finra_adf = 'D',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_chicago = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        cts = 'S',
        nasdaq = 'T',
        iex = 'V',
        cbsx = 'W',
        nasdaq_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Price: The Last Price represents the last price for that security either on a Consolidated or an individual Participant basis at the time it is disseminated
struct last_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Limit Up Limit Down Indicator: Identifies the Limit Up-Limit Down action related to a security
struct limit_up_limit_down_indicator {
    enum class type : char {
        not_applicable = ' ',
        limit_up_limit_down_price_band = 'A',
        republished_limit_up_limit_down_price_band = 'B',
        national_best_bid_limit_state_entered = 'C',
        national_best_bid_limit_state_exited = 'D',
        national_best_offer_limit_state_entered = 'E',
        national_best_offer_limit_state_exited = 'F',
        national_best_bid_and_national_best_offer_limit_state_entered = 'G',
        national_best_bid_and_national_best_offer_limit_state_exited = 'H',
        national_best_bid_limit_state_entered_and_national_best_offer_limit_state_exited = 'I',
        national_best_bid_limit_state_exited_and_national_best_offer_limit_state_entered = 'J',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Low Indication Price Lower Limit Price Band: The Low Indication Price represents an approximation of what the low end "Bid" price of a security's trading range may be
struct low_indication_price_lower_limit_price_band {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Price: The Low Price represents the lowest price paid for a security during the trading day
struct low_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Status Message Type
struct market_status_message_type {
    enum class type : char {
        market_wide_circuit_breaker_decline_level_status_message = 'K',
        market_wide_circuit_breaker_status_message = 'L',
        approximate_adjusted_volume_market_center_message = 'N',
        approximate_trades_and_total_dollar_value_message = 'O',
        crossing_session_summary_message = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Wide Circuit Breaker Level Indicator: Identifies the threshold level that was breached
struct market_wide_circuit_breaker_level_indicator {
    enum class type : char {
        not_applicable = ' ',
        level_1_breached = '1',
        level_2_breached = '2',
        level_3_breached = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Category: The Message Category represents the message classification
struct message_category {
    enum class type : char {
        administrative = 'A',
        control = 'C',
        indices = 'I',
        market_status = 'M',
        prior_day = 'P',
        summary = 'S',
        trade = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Id: The Message ID identifies the individual message within the block beginning with number one
struct message_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: The Message Length identifies the total message length inclusive of the Message Header and Message Body
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Messages In Block: The number of messages contained in the transmission block
struct messages_in_block {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mwcb Level 1: Identifies the daily established drop level value (trigger value) associated with each Decline Level 7%
struct mwcb_level_1 {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mwcb Level 2: Decline Level 13% of Previous Close
struct mwcb_level_2 {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mwcb Level 3: Decline Level 20% of Previous Close
struct mwcb_level_3 {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nanoseconds: Nanosecond portion of the time
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Extensions: Identifies the number of manual or automatic extensions the applicable auction has received
struct number_of_extensions {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Participants: Represents the actual number of Participants for which an issue will be reported.
struct number_of_participants {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Index Value: Represents the value of the index calculation formula using the current offer values of the component securities
struct offer_index_value {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Price: The Open Price represents the first qualifying price paid for a security during the trading day.
struct open_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Participant Reference Number: Contains the Participant Reference Number of transaction to be corrected, cancelled or error
struct original_participant_reference_number {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id: Participant or Processor that generated the message
struct participant_id {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_bx = 'B',
        nyse_national = 'C',
        adf = 'D',
        miax = 'H',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_chicago = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        cts = 'S',
        nasdaq = 'T',
        members_exchange = 'U',
        iex = 'V',
        cbsx = 'W',
        nasdaq_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Participant Open High Low Last Indicator: Identifies the Participant Open/High/Low/Last applicable to the transaction
struct participant_open_high_low_last_indicator {
    enum class type : char {
        none = 'A',
        high = 'B',
        low = 'C',
        last = 'D',
        high_last = 'E',
        low_last = 'F',
        unused = 'G',
        open = 'H',
        open_high = 'I',
        open_low = 'J',
        open_high_low_last = 'K',
        open_last = 'L',
        open_high_low = 'M',
        open_high_last = 'N',
        open_low_last = 'O',
        high_low = 'P',
        high_low_last = 'Q',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Participant Reference Number: Participant Reference Number is a pass-thru of the inbound Participant Reference number assigned to a transaction
struct participant_reference_number {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Previous Close Price: The Previous Close Price represents the last qualifying price paid for a security during the trading day
struct previous_close_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Previous Close Price Date: Represents the date the security last traded
struct previous_close_price_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Primary Listing Market Participant Id: Identifies the Primary Listing Market of the security symbol
struct primary_listing_market_participant_id {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_bx = 'B',
        nyse_national = 'C',
        finra_adf = 'D',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        nyse_chicago = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'T',
        iex = 'V',
        cbsx = 'W',
        nasdaq_psx = 'X',
        cboe_byx = 'Y',
        cboe_bzx = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Prior Day Message Type
struct prior_day_message_type {
    enum class type : char {
        prior_day_trade_correction_message = 'C',
        prior_day_trade_message = 'T',
        prior_day_trade_cancel_error_message = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reserved: Field is reserved for future use.
struct reserved {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Retransmission Indicator: Indicates an original message or a retransmitted block
struct retransmission_indicator {
    enum class type : char {
        original = 'O',
        retransmitted = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sale Condition: Denotes the sale condition associated with a trade
struct sale_condition {
    enum class type : char {
        regular_sale = ' ',
        average_price_trade = 'B',
        cash_trade = 'C',
        automatic_execution = 'E',
        intermarket_sweep_order = 'F',
        price_variation_trade = 'H',
        odd_lot_trade = 'I',
        rule_127_or_155 = 'K',
        sold_last = 'L',
        market_center_official_close = 'M',
        next_day_trade = 'N',
        market_center_opening_trade = 'O',
        prior_reference_price = 'P',
        market_center_official_open = 'Q',
        seller = 'R',
        extended_hours_trade = 'T',
        extended_hours_sold = 'U',
        contingent_trade = 'V',
        cross_trade = 'X',
        sold = 'Z',
        derivatively_priced = '4',
        market_center_reopening_trade = '5',
        market_center_closing_trade = '6',
        qualified_contingent_trade = '7',
        reserved = '8',
        corrected_consolidated_close_price_as_per_listing_market = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sale Condition Category: Identifies the Sale Condition Category level associated with a trade
struct sale_condition_category {
    enum class type : char {
        not_applicable = ' ',
        category_1 = '1',
        category_2 = '2',
        category_3 = '3',
        category_4 = '4',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seconds: contains the number of seconds from Epoch 1/1/1970, 00:00:00 UTC
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Status: Identifies the trading status applicable to the transaction
struct security_status {
    enum class type : char {
        not_applicable = ' ',
        trading_halt = '2',
        resume = '3',
        price_indication = '5',
        trading_range_indication = '6',
        market_imbalance_buy = '7',
        market_imbalance_sell = '8',
        market_on_close_imbalance_buy = '9',
        market_on_close_imbalance_sell = 'A',
        no_market_imbalance = 'C',
        no_market_on_close_imbalance = 'D',
        short_sale_restriction = 'E',
        limit_up_limit_down = 'F',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Symbol: Contains the security symbol
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Security Symbol Short: Contains the security symbol
struct security_symbol_short {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Sell Volume: Represents the reported imbalance of sell orders without matching buy orders for the security for a Participant
struct sell_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sellers Sale Days: Specifies the number of days that may elapse before delivery of the security
struct sellers_sale_days {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settlement Type: Category 1: Settlement Type
struct settlement_type {
    enum class type : char {
        regular_settlement = ' ',
        cash_trade = 'C',
        next_day_trade = 'N',
        seller = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is in effect for a security
struct short_sale_restriction_indicator {
    enum class type : char {
        not_in_effect = ' ',
        activated = 'A',
        continued = 'C',
        deactivated = 'D',
        restriction_in_effect = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sro Trade Detail: Category 4: SRO Trade Detail
struct sro_trade_detail {
    enum class type : char {
        no_sro_required_trade_detail = ' ',
        average_price_trade = 'B',
        automatic_execution = 'E',
        price_variation_trade = 'H',
        odd_lot_trade = 'I',
        rule_127_or_155 = 'K',
        market_center_official_close = 'M',
        prior_reference_price = 'P',
        market_center_official_open = 'Q',
        contingent_trade = 'V',
        cross_trade = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stop Stock Indicator: The transaction that constituted the trade-through was the execution by a trading center of an order for which, at the time of receipt of the order, the trading center had guaranteed an execution at no worse than a specified price
struct stop_stock_indicator {
    enum class type : char {
        not_applicable = '0',
        stop_stock = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Summary Message Type
struct summary_message_type {
    enum class type : char {
        consolidated_start_of_day_summary_message = 'A',
        participant_start_of_day_summary_message = 'B',
        consolidated_end_of_day_summary_message = 'C',
        participant_end_of_day_summary_message = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Summary Participant Id: Identifies the Participant whose summary information is provided
struct summary_participant_id {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Tick: Represents for a Participant the upward, downward or unchanged price movement in a security's trades
struct tick {
    enum class type : char {
        not_applicable = ' ',
        upward = '1',
        downward = '2',
        unchanged_upward = '3',
        unchanged_downward = '4',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Total Trades: Contains the total number of trade transactions executed from a Market Center
struct total_trades {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Volume: Contains Total Volume of shares traded in a security either on a Consolidated or an individual Participant basis at the time it is disseminated
struct total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Volume Short: Contains Total Volume of shares traded in a security either on a Consolidated or an individual Participant basis at the time it is disseminated
struct total_volume_short {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Message Type
struct trade_message_type {
    enum class type : char {
        auction_status_message = 'A',
        trade_correction_message = 'C',
        long_trade_message = 'L',
        trading_status_message = 'S',
        short_trade_message = 'T',
        trade_cancel_error_message = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Price: The Trade Price is the monetary value of an individual share of security at the time of the trade
struct trade_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price Short: The Trade Price is the monetary value of an individual share of security at the time of the trade
struct trade_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting Facility has been formed
struct trade_reporting_facility_id {
    enum class type : char {
        not_applicable = ' ',
        finra_nasdaq_chicago = 'B',
        finra_nyse = 'N',
        finra_nasdaq_carteret = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Through Exempt Indicator: Denotes whether or not a trade is exempt (Rule 611) and when used jointly with certain Sale Conditions, will more fully describe the characteristics of a particular trade
struct trade_through_exempt_indicator {
    enum class type : char {
        not_a_trade_through_exemption = '0',
        trade_through_exemption = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Through Exempt Reason: Category 2: Reason for Trade-Through Exemption / Other Reason
struct trade_through_exempt_reason {
    enum class type : char {
        no_reason = ' ',
        intermarket_sweep_order = 'F',
        market_center_opening_trade = 'O',
        derivatively_priced = '4',
        market_center_reopening_trade = '5',
        market_center_closing_trade = '6',
        qualified_contingent_trade = '7',
        reserved = '8',
        corrected_consolidated_close_price_as_per_listing_market = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Total Volume: Contains the total number of shares traded in a single transaction for an individual security
struct trade_total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Volume: Contains the total number of shares traded in a single transaction for an individual security
struct trade_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Volume Short: Contains the total number of shares traded in a single transaction for an individual security
struct trade_volume_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transaction Id: The Transaction Id will be populated by CQS and is Reserved for Internal Use only
struct transaction_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Version: CQS binary protocol version
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

// Participant Data
struct participant_data {
    static constexpr std::string_view name = "Participant Data";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        previous_close_price_date,
        last_price,
        high_price,
        low_price,
        open_price,
        total_volume_short,
        tick>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(previous_close_price_date);
    CTSFIELD(last_price);
    CTSFIELD(high_price);
    CTSFIELD(low_price);
    CTSFIELD(open_price);
    CTSFIELD(total_volume_short);
    CTSFIELD(tick);
};

static_assert(sizeof(participant_data) == participant_data::size, "participant_data lies over its bytes exactly");

// Consolidated Data
struct consolidated_data {
    static constexpr std::string_view name = "Consolidated Data";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        previous_close_price_date,
        last_participant_id,
        last_price,
        high_price,
        low_price,
        total_volume_short,
        tick>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(previous_close_price_date);
    CTSFIELD(last_participant_id);
    CTSFIELD(last_price);
    CTSFIELD(high_price);
    CTSFIELD(low_price);
    CTSFIELD(total_volume_short);
    CTSFIELD(tick);
};

static_assert(sizeof(consolidated_data) == consolidated_data::size, "consolidated_data lies over its bytes exactly");

// Timestamp 2
struct timestamp_2 {
    static constexpr std::string_view name = "Timestamp 2";
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
    CTSFIELD(seconds);
    CTSFIELD(nanoseconds);
};

static_assert(sizeof(timestamp_2) == timestamp_2::size, "timestamp_2 lies over its bytes exactly");

// Sale Conditions
struct sale_conditions {
    static constexpr std::string_view name = "Sale Conditions";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        settlement_type,
        trade_through_exempt_reason,
        extended_hours_or_sequence_type,
        sro_trade_detail>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(settlement_type);
    CTSFIELD(trade_through_exempt_reason);
    CTSFIELD(extended_hours_or_sequence_type);
    CTSFIELD(sro_trade_detail);
};

static_assert(sizeof(sale_conditions) == sale_conditions::size, "sale_conditions lies over its bytes exactly");

// Timestamp 1
struct timestamp_1 {
    static constexpr std::string_view name = "Timestamp 1";
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
    CTSFIELD(seconds);
    CTSFIELD(nanoseconds);
};

static_assert(sizeof(timestamp_1) == timestamp_1::size, "timestamp_1 lies over its bytes exactly");

// Trade Cancel Error Message: The Trade Cancel/Error message is used cancel or error Cta eligible securities, Local Issues or Bond information.
struct trade_cancel_error_message {
    static constexpr std::string_view name = "Trade Cancel Error Message";
    static constexpr std::size_t size = 149;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        sale_conditions,
        trade_price,
        trade_volume,
        sellers_sale_days,
        stop_stock_indicator,
        trade_through_exempt_indicator,
        trade_reporting_facility_id,
        original_participant_reference_number,
        timestamp_2,
        cancel_error_action,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        consolidated_data,
        participant_data>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(sale_conditions);
    CTSFIELD(trade_price);
    CTSFIELD(trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(original_participant_reference_number);
    CTSFIELD(timestamp_2);
    CTSFIELD(cancel_error_action);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(consolidated_data);
    CTSFIELD(participant_data);
};

static_assert(sizeof(trade_cancel_error_message) == trade_cancel_error_message::size, "trade_cancel_error_message lies over its bytes exactly");

// Short Trade Message: The Short Trade message is used to report trade information for Cta eligible Equity only (not used for Local Issues or Bonds) if the trade meets message format requirements otherwise Long Trade message is used.
struct short_trade_message {
    static constexpr std::string_view name = "Short Trade Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol_short,
        sale_condition,
        sale_condition_category,
        trade_price_short,
        trade_volume_short,
        primary_listing_market_participant_id,
        consolidated_high_low_last_indicator,
        participant_open_high_low_last_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol_short);
    CTSFIELD(sale_condition);
    CTSFIELD(sale_condition_category);
    CTSFIELD(trade_price_short);
    CTSFIELD(trade_volume_short);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(consolidated_high_low_last_indicator);
    CTSFIELD(participant_open_high_low_last_indicator);
};

static_assert(sizeof(short_trade_message) == short_trade_message::size, "short_trade_message lies over its bytes exactly");

// Trading Status Message: The Trading Status message is transmitted when a Participant in a Cta eligible security, Local Issue or a Bond elects to notify CTS of an Opening Delay, a Trading Halt, a Trading Resume, a Price Indication or a Market Imbalance.
struct trading_status_message {
    static constexpr std::string_view name = "Trading Status Message";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        last_price,
        high_indication_price_upper_limit_price_band,
        low_indication_price_lower_limit_price_band,
        buy_volume,
        sell_volume,
        security_status,
        halt_reason,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        limit_up_limit_down_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(last_price);
    CTSFIELD(high_indication_price_upper_limit_price_band);
    CTSFIELD(low_indication_price_lower_limit_price_band);
    CTSFIELD(buy_volume);
    CTSFIELD(sell_volume);
    CTSFIELD(security_status);
    CTSFIELD(halt_reason);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(limit_up_limit_down_indicator);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Long Trade Message: The Long Trade message is used to report trade information for Cta eligible Equity, Local Issue or Bonds.
struct long_trade_message {
    static constexpr std::string_view name = "Long Trade Message";
    static constexpr std::size_t size = 68;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        sale_conditions,
        trade_price,
        trade_volume,
        sellers_sale_days,
        stop_stock_indicator,
        trade_through_exempt_indicator,
        trade_reporting_facility_id,
        timestamp_2,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        held_trade_indicator,
        consolidated_high_low_last_indicator,
        participant_open_high_low_last_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(sale_conditions);
    CTSFIELD(trade_price);
    CTSFIELD(trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(timestamp_2);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(held_trade_indicator);
    CTSFIELD(consolidated_high_low_last_indicator);
    CTSFIELD(participant_open_high_low_last_indicator);
};

static_assert(sizeof(long_trade_message) == long_trade_message::size, "long_trade_message lies over its bytes exactly");

// Prior Day Trade Date And Time
struct prior_day_trade_date_and_time {
    static constexpr std::string_view name = "Prior Day Trade Date And Time";
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
    CTSFIELD(seconds);
    CTSFIELD(nanoseconds);
};

static_assert(sizeof(prior_day_trade_date_and_time) == prior_day_trade_date_and_time::size, "prior_day_trade_date_and_time lies over its bytes exactly");

// Original Trade
struct original_trade {
    static constexpr std::string_view name = "Original Trade";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_conditions,
        trade_price,
        trade_volume,
        sellers_sale_days,
        stop_stock_indicator,
        trade_through_exempt_indicator,
        short_sale_restriction_indicator,
        prior_day_trade_date_and_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(sale_conditions);
    CTSFIELD(trade_price);
    CTSFIELD(trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(prior_day_trade_date_and_time);
};

static_assert(sizeof(original_trade) == original_trade::size, "original_trade lies over its bytes exactly");

// Corrected Trade
struct corrected_trade {
    static constexpr std::string_view name = "Corrected Trade";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_conditions,
        trade_price,
        trade_volume,
        sellers_sale_days,
        stop_stock_indicator,
        trade_through_exempt_indicator,
        short_sale_restriction_indicator,
        prior_day_trade_date_and_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(sale_conditions);
    CTSFIELD(trade_price);
    CTSFIELD(trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(prior_day_trade_date_and_time);
};

static_assert(sizeof(corrected_trade) == corrected_trade::size, "corrected_trade lies over its bytes exactly");

// Trade Correction Message: The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond information.
struct trade_correction_message {
    static constexpr std::string_view name = "Trade Correction Message";
    static constexpr std::size_t size = 184;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        corrected_trade,
        trade_reporting_facility_id,
        timestamp_2,
        original_participant_reference_number,
        original_trade,
        primary_listing_market_participant_id,
        financial_status_indicator,
        consolidated_data,
        participant_data>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(corrected_trade);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(timestamp_2);
    CTSFIELD(original_participant_reference_number);
    CTSFIELD(original_trade);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(consolidated_data);
    CTSFIELD(participant_data);
};

static_assert(sizeof(trade_correction_message) == trade_correction_message::size, "trade_correction_message lies over its bytes exactly");

// Auction Status Message: The Auction Status message is used when a Participant in a Cta eligible security, Local Issue or a Bond requires Auction Information
struct auction_status_message {
    static constexpr std::string_view name = "Auction Status Message";
    static constexpr std::size_t size = 124;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        auction_collar_reference_price,
        auction_collar_upper_threshold_price,
        auction_collar_lower_threshold_price,
        number_of_extensions,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        future_use>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(auction_collar_reference_price);
    CTSFIELD(auction_collar_upper_threshold_price);
    CTSFIELD(auction_collar_lower_threshold_price);
    CTSFIELD(number_of_extensions);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(future_use);
};

static_assert(sizeof(auction_status_message) == auction_status_message::size, "auction_status_message lies over its bytes exactly");

// Trade Message Payload: Branch
struct trade_message_payload {
    static constexpr std::string_view name = "Trade Message Payload";
    static constexpr bool is_message = false;
};

// Trade Message Section 1
struct trade_message_section_1 {
    static constexpr std::string_view name = "Trade Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trade_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(trade_message_type);
};

static_assert(sizeof(trade_message_section_1) == trade_message_section_1::size, "trade_message_section_1 lies over its bytes exactly");

// Trade Message: Trade Messages
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr bool is_message = false;
};

// Participant End Of Day Summary Message: The Participant End of Day Summary messages are transmitted shortly before the ‘Goodnight’ messages.
struct participant_end_of_day_summary_message {
    static constexpr std::string_view name = "Participant End Of Day Summary Message";
    static constexpr std::size_t size = 80;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        initiating_participant_id,
        previous_close_price_date,
        last_price,
        high_price,
        low_price,
        open_price,
        total_volume,
        tick>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(initiating_participant_id);
    CTSFIELD(previous_close_price_date);
    CTSFIELD(last_price);
    CTSFIELD(high_price);
    CTSFIELD(low_price);
    CTSFIELD(open_price);
    CTSFIELD(total_volume);
    CTSFIELD(tick);
};

static_assert(sizeof(participant_end_of_day_summary_message) == participant_end_of_day_summary_message::size, "participant_end_of_day_summary_message lies over its bytes exactly");

// Consolidated End Of Day Summary Message: The Consolidated End of Day Summary messages are transmitted shortly before the "Goodnight" messages
struct consolidated_end_of_day_summary_message {
    static constexpr std::string_view name = "Consolidated End Of Day Summary Message";
    static constexpr std::size_t size = 75;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        last_participant_id,
        previous_close_price_date,
        last_price,
        high_price,
        low_price,
        total_volume,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        number_of_participants>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(last_participant_id);
    CTSFIELD(previous_close_price_date);
    CTSFIELD(last_price);
    CTSFIELD(high_price);
    CTSFIELD(low_price);
    CTSFIELD(total_volume);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(number_of_participants);
};

static_assert(sizeof(consolidated_end_of_day_summary_message) == consolidated_end_of_day_summary_message::size, "consolidated_end_of_day_summary_message lies over its bytes exactly");

// Participant Start Of Day Summary Message: The Participant Start of Day Summary messages are transmitted shortly after the Multicast Line ‘Start of Day’ message
struct participant_start_of_day_summary_message {
    static constexpr std::string_view name = "Participant Start Of Day Summary Message";
    static constexpr std::size_t size = 47;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        summary_participant_id,
        previous_close_price_date,
        previous_close_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(summary_participant_id);
    CTSFIELD(previous_close_price_date);
    CTSFIELD(previous_close_price);
};

static_assert(sizeof(participant_start_of_day_summary_message) == participant_start_of_day_summary_message::size, "participant_start_of_day_summary_message lies over its bytes exactly");

// Consolidated Start Of Day Summary Message: The Consolidated Start of Day Summary messages are transmitted shortly after the Multicast Line ‘Start of Day’ message
struct consolidated_start_of_day_summary_message {
    static constexpr std::string_view name = "Consolidated Start Of Day Summary Message";
    static constexpr std::size_t size = 51;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        summary_participant_id,
        previous_close_price_date,
        previous_close_price,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        number_of_participants>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(summary_participant_id);
    CTSFIELD(previous_close_price_date);
    CTSFIELD(previous_close_price);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(number_of_participants);
};

static_assert(sizeof(consolidated_start_of_day_summary_message) == consolidated_start_of_day_summary_message::size, "consolidated_start_of_day_summary_message lies over its bytes exactly");

// Summary Message Payload: Branch
struct summary_message_payload {
    static constexpr std::string_view name = "Summary Message Payload";
    static constexpr bool is_message = false;
};

// Summary Message Section 1
struct summary_message_section_1 {
    static constexpr std::string_view name = "Summary Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        summary_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(summary_message_type);
};

static_assert(sizeof(summary_message_section_1) == summary_message_section_1::size, "summary_message_section_1 lies over its bytes exactly");

// Summary Message: Summary Messages
struct summary_message {
    static constexpr std::string_view name = "Summary Message";
    static constexpr bool is_message = false;
};

// Prior Day Trade Cancel Error Message: The Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported.
struct prior_day_trade_cancel_error_message {
    static constexpr std::string_view name = "Prior Day Trade Cancel Error Message";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        sale_conditions,
        trade_price,
        trade_volume,
        sellers_sale_days,
        stop_stock_indicator,
        trade_through_exempt_indicator,
        short_sale_restriction_indicator,
        trade_reporting_facility_id,
        prior_day_trade_date_and_time,
        cancel_error_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(sale_conditions);
    CTSFIELD(trade_price);
    CTSFIELD(trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(prior_day_trade_date_and_time);
    CTSFIELD(cancel_error_action);
};

static_assert(sizeof(prior_day_trade_cancel_error_message) == prior_day_trade_cancel_error_message::size, "prior_day_trade_cancel_error_message lies over its bytes exactly");

// Prior Day Trade Message: The Prior Day Trade message is used to report a Cta Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported.
struct prior_day_trade_message {
    static constexpr std::string_view name = "Prior Day Trade Message";
    static constexpr std::size_t size = 63;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        sale_conditions,
        trade_price,
        trade_volume,
        sellers_sale_days,
        stop_stock_indicator,
        trade_through_exempt_indicator,
        short_sale_restriction_indicator,
        trade_reporting_facility_id,
        prior_day_trade_date_and_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(sale_conditions);
    CTSFIELD(trade_price);
    CTSFIELD(trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(prior_day_trade_date_and_time);
};

static_assert(sizeof(prior_day_trade_message) == prior_day_trade_message::size, "prior_day_trade_message lies over its bytes exactly");

// Prior Day Trade Correction Message: Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades, corrections, cancels or errors for transactions that occurred earlier than the current trading day and had not been reported
struct prior_day_trade_correction_message {
    static constexpr std::string_view name = "Prior Day Trade Correction Message";
    static constexpr std::size_t size = 91;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        instrument_type,
        corrected_trade,
        trade_reporting_facility_id,
        original_trade>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(security_symbol);
    CTSFIELD(instrument_type);
    CTSFIELD(corrected_trade);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(original_trade);
};

static_assert(sizeof(prior_day_trade_correction_message) == prior_day_trade_correction_message::size, "prior_day_trade_correction_message lies over its bytes exactly");

// Prior Day Message Payload: Branch
struct prior_day_message_payload {
    static constexpr std::string_view name = "Prior Day Message Payload";
    static constexpr bool is_message = false;
};

// Prior Day Message Section 1
struct prior_day_message_section_1 {
    static constexpr std::string_view name = "Prior Day Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        prior_day_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(prior_day_message_type);
};

static_assert(sizeof(prior_day_message_section_1) == prior_day_message_section_1::size, "prior_day_message_section_1 lies over its bytes exactly");

// Prior Day Message: Prior Day Messages
struct prior_day_message {
    static constexpr std::string_view name = "Prior Day Message";
    static constexpr bool is_message = false;
};

// Crossing Session Summary Message: The Crossing Session message is used to report the total volume and dollar value of trades transacted after the close of a Participant’s regular session.
struct crossing_session_summary_message {
    static constexpr std::string_view name = "Crossing Session Summary Message";
    static constexpr std::size_t size = 46;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        crossing_session_i_total_trades_volume,
        crossing_session_ii_dollar_value,
        crossing_session_ii_total_trades_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(crossing_session_i_total_trades_volume);
    CTSFIELD(crossing_session_ii_dollar_value);
    CTSFIELD(crossing_session_ii_total_trades_volume);
};

static_assert(sizeof(crossing_session_summary_message) == crossing_session_summary_message::size, "crossing_session_summary_message lies over its bytes exactly");

// Approximate Trades And Total Dollar Value Message: The Approximate Trades and Total Dollar Value message allows a Participant to report the total trades and total dollar value of trades at their respective market centers.
struct approximate_trades_and_total_dollar_value_message {
    static constexpr std::string_view name = "Approximate Trades And Total Dollar Value Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        total_trades,
        dollar_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(total_trades);
    CTSFIELD(dollar_value);
};

static_assert(sizeof(approximate_trades_and_total_dollar_value_message) == approximate_trades_and_total_dollar_value_message::size, "approximate_trades_and_total_dollar_value_message lies over its bytes exactly");

// Participants: Active Participants
struct participants {
    static constexpr std::string_view name = "Participants";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        trade_total_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(trade_total_volume);
};

static_assert(sizeof(participants) == participants::size, "participants lies over its bytes exactly");

// Approximate Adjusted Volume Market Center Message Section 1
struct approximate_adjusted_volume_market_center_message_section_1 {
    static constexpr std::string_view name = "Approximate Adjusted Volume Market Center Message Section 1";
    static constexpr std::size_t size = 23;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        number_of_participants>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(number_of_participants);
};

static_assert(sizeof(approximate_adjusted_volume_market_center_message_section_1) == approximate_adjusted_volume_market_center_message_section_1::size, "approximate_adjusted_volume_market_center_message_section_1 lies over its bytes exactly");

// Approximate Adjusted Volume Market Center Message: Approximate Adjusted Volume Market Center message is used to report the volume of adjusted trading activity for each Participant.
struct approximate_adjusted_volume_market_center_message {
    static constexpr std::string_view name = "Approximate Adjusted Volume Market Center Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CTSSEQUENCE(participants);
};

// Market Wide Circuit Breaker Status Message: The Market-Wide Circuit Breaker Status message is used to report the Market-Wide Circuit Breaker threshold Level that has been breached.
struct market_wide_circuit_breaker_status_message {
    static constexpr std::string_view name = "Market Wide Circuit Breaker Status Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        market_wide_circuit_breaker_level_indicator,
        reserved>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(market_wide_circuit_breaker_level_indicator);
    CTSFIELD(reserved);
};

static_assert(sizeof(market_wide_circuit_breaker_status_message) == market_wide_circuit_breaker_status_message::size, "market_wide_circuit_breaker_status_message lies over its bytes exactly");

// Market Wide Circuit Breaker Decline Level Status Message: The Market-Wide Circuit Breaker Decline Level Status message is used to report the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker
struct market_wide_circuit_breaker_decline_level_status_message {
    static constexpr std::string_view name = "Market Wide Circuit Breaker Decline Level Status Message";
    static constexpr std::size_t size = 47;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        mwcb_level_1,
        mwcb_level_2,
        mwcb_level_3,
        reserved>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(mwcb_level_1);
    CTSFIELD(mwcb_level_2);
    CTSFIELD(mwcb_level_3);
    CTSFIELD(reserved);
};

static_assert(sizeof(market_wide_circuit_breaker_decline_level_status_message) == market_wide_circuit_breaker_decline_level_status_message::size, "market_wide_circuit_breaker_decline_level_status_message lies over its bytes exactly");

// Market Status Message Payload: Branch
struct market_status_message_payload {
    static constexpr std::string_view name = "Market Status Message Payload";
    static constexpr bool is_message = false;
};

// Market Status Message Section 1
struct market_status_message_section_1 {
    static constexpr std::string_view name = "Market Status Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        market_status_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(market_status_message_type);
};

static_assert(sizeof(market_status_message_section_1) == market_status_message_section_1::size, "market_status_message_section_1 lies over its bytes exactly");

// Market Status Message: Market Status Message Header
struct market_status_message {
    static constexpr std::string_view name = "Market Status Message";
    static constexpr bool is_message = false;
};

// Bid And Offer Index Message: The Bid and Offer Index message contains the index Bid and Offer index values
struct bid_and_offer_index_message {
    static constexpr std::string_view name = "Bid And Offer Index Message";
    static constexpr std::size_t size = 49;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        index_symbol,
        bid_index_value,
        offer_index_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(index_symbol);
    CTSFIELD(bid_index_value);
    CTSFIELD(offer_index_value);
};

static_assert(sizeof(bid_and_offer_index_message) == bid_and_offer_index_message::size, "bid_and_offer_index_message lies over its bytes exactly");

// Index Message: The Index message contains the index and the index value
struct index_message {
    static constexpr std::string_view name = "Index Message";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        index_symbol,
        index_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
    CTSFIELD(index_symbol);
    CTSFIELD(index_value);
};

static_assert(sizeof(index_message) == index_message::size, "index_message lies over its bytes exactly");

// Indices Message Payload: Branch
struct indices_message_payload {
    static constexpr std::string_view name = "Indices Message Payload";
    static constexpr bool is_message = false;
};

// Indices Message Section 1
struct indices_message_section_1 {
    static constexpr std::string_view name = "Indices Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        indices_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(indices_message_type);
};

static_assert(sizeof(indices_message_section_1) == indices_message_section_1::size, "indices_message_section_1 lies over its bytes exactly");

// Indices Message: Index Messages Header
struct indices_message {
    static constexpr std::string_view name = "Indices Message";
    static constexpr bool is_message = false;
};

// End Of Day Message: The End of Day message is transmitted over the multicast lines to advise all Data Recipients that there are no further messages of any type transmitted for the day
struct end_of_day_message {
    static constexpr std::string_view name = "End Of Day Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(end_of_day_message) == end_of_day_message::size, "end_of_day_message lies over its bytes exactly");

// Line Integrity Message: The Line Integrity message is transmitted over the multicast lines at intervals of sixty (60) seconds to verify continued integrity of multicast transmission
struct line_integrity_message {
    static constexpr std::string_view name = "Line Integrity Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(line_integrity_message) == line_integrity_message::size, "line_integrity_message lies over its bytes exactly");

// Disaster Recovery Data Center Activation Message: The Disaster Recovery Data Center Activation message is transmitted to signify that the Consolidated Quotation System (CQS) has switched processing from the Primary Data Center to the Disaster Recovery Data Center
struct disaster_recovery_data_center_activation_message {
    static constexpr std::string_view name = "Disaster Recovery Data Center Activation Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(disaster_recovery_data_center_activation_message) == disaster_recovery_data_center_activation_message::size, "disaster_recovery_data_center_activation_message lies over its bytes exactly");

// Reset Block Sequence Number Message: The Reset Block Sequence Number message is transmitted when the block sequence number on an output multicast line requires resetting.
struct reset_block_sequence_number_message {
    static constexpr std::string_view name = "Reset Block Sequence Number Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(reset_block_sequence_number_message) == reset_block_sequence_number_message::size, "reset_block_sequence_number_message lies over its bytes exactly");

// Start Of Day Message: The Start of Day message signals the start of normal data dissemination over the multicast lines
struct start_of_day_message {
    static constexpr std::string_view name = "Start Of Day Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(start_of_day_message) == start_of_day_message::size, "start_of_day_message lies over its bytes exactly");

// Control Message Payload: Branch
struct control_message_payload {
    static constexpr std::string_view name = "Control Message Payload";
    static constexpr bool is_message = false;
};

// Control Message Section 1
struct control_message_section_1 {
    static constexpr std::string_view name = "Control Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        control_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(control_message_type);
};

static_assert(sizeof(control_message_section_1) == control_message_section_1::size, "control_message_section_1 lies over its bytes exactly");

// Control Message: Control Message Header
struct control_message {
    static constexpr std::string_view name = "Control Message";
    static constexpr bool is_message = false;
};

// End Of Start Of Day Message: The End of Start of Day message signals the start of Start of Day Summary message iterations
struct end_of_start_of_day_message {
    static constexpr std::string_view name = "End Of Start Of Day Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(end_of_start_of_day_message) == end_of_start_of_day_message::size, "end_of_start_of_day_message lies over its bytes exactly");

// Start Of Start Of Day Message: The Start of Start of Day message signals the end of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct start_of_start_of_day_message {
    static constexpr std::string_view name = "Start Of Start Of Day Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(start_of_start_of_day_message) == start_of_start_of_day_message::size, "start_of_start_of_day_message lies over its bytes exactly");

// End Of End Of Day Message: The End of End of Day message signals the end of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct end_of_end_of_day_message {
    static constexpr std::string_view name = "End Of End Of Day Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(end_of_end_of_day_message) == end_of_end_of_day_message::size, "end_of_end_of_day_message lies over its bytes exactly");

// Start Of End Of Day Message: The Start of End of Day message signals the start of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct start_of_end_of_day_message {
    static constexpr std::string_view name = "Start Of End Of Day Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(timestamp_1);
    CTSFIELD(message_id);
    CTSFIELD(transaction_id);
    CTSFIELD(participant_reference_number);
};

static_assert(sizeof(start_of_end_of_day_message) == start_of_end_of_day_message::size, "start_of_end_of_day_message lies over its bytes exactly");

// Administrative Message Payload: Branch
struct administrative_message_payload {
    static constexpr std::string_view name = "Administrative Message Payload";
    static constexpr bool is_message = false;
};

// Administrative Message Section 1
struct administrative_message_section_1 {
    static constexpr std::string_view name = "Administrative Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        administrative_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(administrative_message_type);
};

static_assert(sizeof(administrative_message_section_1) == administrative_message_section_1::size, "administrative_message_section_1 lies over its bytes exactly");

// Administrative Message: Administrative Message Header
struct administrative_message {
    static constexpr std::string_view name = "Administrative Message";
    static constexpr bool is_message = false;
};

// Category Payload: Branch
struct category_payload {
    static constexpr std::string_view name = "Category Payload";
    static constexpr bool is_message = false;
};

// Message Section 1
struct message_section_1 {
    static constexpr std::string_view name = "Message Section 1";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        message_category>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(message_length);
    CTSFIELD(message_category);
};

static_assert(sizeof(message_section_1) == message_section_1::size, "message_section_1 lies over its bytes exactly");

// Message: Repeating message block
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Sip Block Timestamp
struct sip_block_timestamp {
    static constexpr std::string_view name = "Sip Block Timestamp";
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
    CTSFIELD(seconds);
    CTSFIELD(nanoseconds);
};

static_assert(sizeof(sip_block_timestamp) == sip_block_timestamp::size, "sip_block_timestamp lies over its bytes exactly");

// Block Header: Cta Output packet header
struct block_header {
    static constexpr std::string_view name = "Block Header";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        version,
        block_size,
        data_feed_indicator,
        retransmission_indicator,
        block_sequence_number,
        messages_in_block,
        sip_block_timestamp,
        block_checksum>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(version);
    CTSFIELD(block_size);
    CTSFIELD(data_feed_indicator);
    CTSFIELD(retransmission_indicator);
    CTSFIELD(block_sequence_number);
    CTSFIELD(messages_in_block);
    CTSFIELD(sip_block_timestamp);
    CTSFIELD(block_checksum);
};

static_assert(sizeof(block_header) == block_header::size, "block_header lies over its bytes exactly");

// Packet: Cta Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    CTSSEQUENCE(message);
};

#pragma pack(pop)

} // namespace siac::cts::output::cta::v2_9
