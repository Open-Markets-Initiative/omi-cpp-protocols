// Siac Cts Output Cta 2.11.b Template Meta Programming

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

namespace siac::cts::output::cta::v2_11_b {

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

// Administrative Message Type: Identifies the type of Administrative message
struct administrative_message_type {
    enum class type : char {
        start_of_end_of_day_summary = 'A',
        end_of_end_of_day_summary = 'B',
        start_of_start_of_day_summary = 'C',
        end_of_start_of_day_summary = 'D',
        symbol_reference_data = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Collar Lower Threshold Price: Represents the latest lower threshold price of the Auction Collar. Has implied 6 decimal places
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

// Auction Collar Reference Price: Represents the price used by the exchange to establish the Auction Collar. Has implied 6 decimal places
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

// Auction Collar Upper Threshold Price: Represents the latest upper threshold price of the Auction Collar. Has implied 6 decimal places
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

// Bid Index Value: Represents the value of the index's calculation formula using the current Bid values of the component securities. Has implied 6 decimal places
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

// Block Checksum: Lower 16 Bits Of The 32 Bit Sum Of All Bytes In The Block Excluding The Block Checksum Field
struct block_checksum {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Pad Byte
struct block_pad_byte {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Sequence Number: Packet Sequence Number
struct block_sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Size: Size In Bytes Of Entire Transmission Block
struct block_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Volume: Represents the reported imbalance of buy orders without matching sell orders for the security for a Participant
struct buy_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cancel Error Action: Denotes whether the referenced transaction is to be cancelled or errored
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

// Category 1: Settlement Type
struct category_1 {
    enum class type : char {
        regular_settlement = ' ',
        cash_trade_same_day_clearing = 'C',
        reserved = 'N',
        seller = 'R',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Category 2: Reason for Trade-Through Exemption / Other Reason
struct category_2 {
    enum class type : char {
        no_trade_through_exempt_reason = ' ',
        inter_market_sweep_order = 'F',
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

// Category 3: Extended Hours / Sequence Type
struct category_3 {
    enum class type : char {
        not_extended_hours_or_sold_out_of_sequence = ' ',
        sold_last_late_reporting = 'L',
        market_center_opening_trade = 'O',
        extended_hours_trade = 'T',
        extended_hours_sold_out_of_sequence = 'U',
        sold_out_of_sequence = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Category 4: SRO Trade Detail
struct category_4 {
    enum class type : char {
        no_sro_required_trade_detail = ' ',
        average_price_trade = 'B',
        automatic_execution = 'E',
        price_variation_trade = 'H',
        odd_lot_trade = 'I',
        rule_127_nyse_only_or_rule_155_nyse_american_only = 'K',
        market_center_official_close = 'M',
        prior_reference_price = 'P',
        market_center_official_open = 'Q',
        contingent_trade = 'V',
        cross_periodic_auction_trade = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Consolidated Closing Price: Represents the consolidated closing price. Has implied 6 decimal places
struct consolidated_closing_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Fractional Total Volume: Consolidated total volume of shares traded. Has implied 6 decimal places
struct consolidated_fractional_total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated High Low Last Indicator: Identifies the Consolidated High/Low/Last Price applicable to the trade
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

// Consolidated High Price: Consolidated highest price paid during the trading day. Has implied 6 decimal places
struct consolidated_high_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Last Participant Id
struct consolidated_last_participant_id {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Consolidated Last Price: Consolidated last price. Has implied 6 decimal places
struct consolidated_last_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Low Price: Consolidated lowest price paid during the trading day. Has implied 6 decimal places
struct consolidated_low_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Previous Close Price Date: Consolidated date the security last traded. Represented in seconds since Epoch
struct consolidated_previous_close_price_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Consolidated Tick: Consolidated tick direction
struct consolidated_tick {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Consolidated Total Volume: Contains the Consolidated Total Volume of shares traded for a security at the time of the trade correction or cancel/error
struct consolidated_total_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Control Message Type: Identifies the type of Control message
struct control_message_type {
    enum class type : char {
        start_of_day = 'A',
        reset_block_sequence_number = 'L',
        disaster_recovery_data_center_activation = 'P',
        line_integrity = 'T',
        end_of_day = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Corrected Fractional Trade Volume: Corrected total number of shares which traded in a single transaction. Has implied 6 decimal places
struct corrected_fractional_trade_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Sale Condition: Corrected sale condition associated with a trade
struct corrected_sale_condition {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Corrected Sellers Sale Days: Corrected number of days that may elapse before delivery of the security
struct corrected_sellers_sale_days {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Short Sale Restriction Indicator
struct corrected_short_sale_restriction_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Corrected Stop Stock Indicator
struct corrected_stop_stock_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Corrected Trade Price: Corrected monetary value of an individual share of security. Has implied 6 decimal places
struct corrected_trade_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corrected Trade Through Exempt Indicator
struct corrected_trade_through_exempt_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Corrected Trade Volume: Corrected total number of shares which traded in a single transaction for an individual security
struct corrected_trade_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Crossing Session I Total Trades Volume: Contains the number of shares traded at the Participant's close price and taking place after the close of a Participant's regular session
struct crossing_session_i_total_trades_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Crossing Session Ii Dollar Value: Contains the Dollar Value traded after the close of a Participant's regular session. Has implied 6 decimal places
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

// Crossing Session Ii Total Trades Volume: Contains the number of shares traded after the close of a Participant's regular session
struct crossing_session_ii_total_trades_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Data Feed Indicator
struct data_feed_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Dollar Value: Represents the total dollar worth of the daily trade transactions. Has implied 6 decimal places
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

// Financial Status Indicator: Identifies the financial status of the security
struct financial_status_indicator {
    enum class type : char {
        financial_status_not_applicable = '0',
        bankrupt = '1',
        below_continuing_listing_standards = '2',
        bankrupt_below_continuing_listing_standards = '3',
        late_filing = '4',
        bankrupt_late_filing = '5',
        below_continuing_listing_standards_late_filing = '6',
        bankrupt_below_continuing_listing_standards_late_filing = '7',
        creations_suspended_for_exchange_traded_products = '8',
        redemptions_suspended_for_exchange_traded_products = '9',
        liquidation_for_exchange_traded_products = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Fractional Total Volume: Contains Total Volume of shares traded in a security either on a Consolidated or an individual Participant basis. Has implied 6 decimal places
struct fractional_total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Fractional Trade Total Volume: Contains the total number of shares traded for each Participant. Has implied 6 decimal places
struct fractional_trade_total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Fractional Trade Volume: Contains the total number of shares which traded in a single transaction for an individual security. Has implied 6 decimal places
struct fractional_trade_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Fractional Trade Volume 4: Contains the total number of shares which traded in a single transaction for an individual security. Has implied 6 decimal places
struct fractional_trade_volume_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Halt Reason: Denotes the reason for the Trading Halt
struct halt_reason {
    enum class type : char {
        halt_reason_not_applicable = ' ',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        news_released = 'D',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        order_imbalance = 'I',
        limit_up_limit_down_luld_trading_pause = 'M',
        corporate_action = 'N',
        new_security_offering = 'O',
        news_pending = 'P',
        intraday_indicative_value_not_available = 'V',
        operational = 'X',
        sub_penny_trading = 'Y',
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

// Held Trade Indicator: Reflects whether a held trade qualifies for the Participant or Consolidated Last Price at the time it is disseminated
struct held_trade_indicator {
    enum class type : char {
        held_trade_indicator_not_applicable = ' ',
        held_trade_not_a_last_sale_for_participant_or_consolidated = 'A',
        held_trade_last_sale_for_participant_but_not_consolidated = 'B',
        held_trade_last_sale_for_participant_and_consolidated = 'C',
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

// High Price: Represents the highest price paid for a security during the trading day. Has implied 6 decimal places
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

// Index Symbol: Contains the Index symbol. Left justified, space-filled
struct index_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Index Value: Represents a statistical composite that measures changes in the economy or in financial markets. Has implied 6 decimal places
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

// Indices Message Type: Identifies the type of Index message
struct indices_message_type {
    enum class type : char {
        indices = 'I',
        bid_and_offer_index = 'Q',
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

// Ipo: Identifies whether the security symbol is an IPO
struct ipo {
    enum class type : char {
        not_an_ipo_symbol = '0',
        ipo_symbol = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Participant Id: Refer to Participant ID field description for Participant codes. Space-filled
struct last_participant_id {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Last Price: Represents the last price for that security either on a Consolidated or an individual Participant basis at the time it is disseminated. Has implied 6 decimal places
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

// Limit Up Limit Down Luld Indicator: Identifies the Limit Up-Limit Down action related to a security
struct limit_up_limit_down_luld_indicator {
    enum class type : char {
        limit_up_limit_down_not_applicable = ' ',
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

// Low Indication Price Lower Limit Price Band: Represents an approximation of what the low end Bid price of a security's trading range may be, or the lower price band value for a security. Has implied 6 decimal places
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

// Low Price: Represents the lowest price paid for a security during the trading day. Has implied 6 decimal places
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

// Luld Leverage Ratio: Represents the Leverage ratio associated with the LULD Tier of the security symbol. Has implied 6 decimal places
struct luld_leverage_ratio {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Luld Tier: Identifies the Limit Up Limit Down tier of the security symbol
struct luld_tier {
    enum class type : char {
        luld_not_applicable = '0',
        luld_tier_1_security = '1',
        luld_tier_2_security = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Status Message Type: Identifies the type of Market Status message
struct market_status_message_type {
    enum class type : char {
        market_wide_circuit_breaker_decline_level_status = 'K',
        market_wide_circuit_breaker_status = 'L',
        approximate_adjusted_volume_market_center = 'N',
        fractional_approximate_adjusted_volume_market_center = 'V',
        approximate_trades_and_total_dollar_value = 'O',
        crossing_session_summary = 'P',
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
        mwcb_not_applicable = ' ',
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

// Message Length: The total length of the message in bytes
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Messages In Block: The Number Of Messages Contained In The Block Data Of The Transmission Block
struct messages_in_block {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Minimum Price Increment Indicator: Identifies the applicable tick size for a symbol
struct minimum_price_increment_indicator {
    enum class type : char {
        penny_mpi_001 = '1',
        half_penny_mpi_0005 = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mwcb Level 1: Identifies the daily established drop level value. Level 1 = 7% of Previous Close S&P 500 Value. Has implied 6 decimal places
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

// Mwcb Level 2: Identifies the daily established drop level value. Level 2 = 13% of Previous Close S&P 500 Value. Has implied 6 decimal places
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

// Mwcb Level 3: Identifies the daily established drop level value. Level 3 = 20% of Previous Close S&P 500 Value. Has implied 6 decimal places
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

// Nanoseconds: The Nanosecond Portion Of The Time Currently Rounded To The Nearest Microsecond
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

// Number Of Participants: Represents the actual number of Participants for which an issue will be reported
struct number_of_participants {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Index Value: Represents the value of the index calculation formula using the current offer values of the component securities. Has implied 6 decimal places
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

// Open Price: Represents the first qualifying price paid for a security during the trading day. Has implied 6 decimal places
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

// Original Fractional Trade Volume: Original total number of shares which traded in a single transaction. Has implied 6 decimal places
struct original_fractional_trade_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Participant Reference Number: Contains the Participant Reference Number of transaction to be corrected, cancelled or errored
struct original_participant_reference_number {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Sale Condition: Original sale condition associated with a trade
struct original_sale_condition {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Original Sellers Sale Days: Original number of days that may elapse before delivery of the security
struct original_sellers_sale_days {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Short Sale Restriction Indicator
struct original_short_sale_restriction_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Original Stop Stock Indicator
struct original_stop_stock_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Original Trade Price: Original monetary value of an individual share of security. Has implied 6 decimal places
struct original_trade_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Trade Through Exempt Indicator
struct original_trade_through_exempt_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Original Trade Volume: Original total number of shares which traded in a single transaction for an individual security
struct original_trade_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Fractional Total Volume: Participant total volume of shares traded. Has implied 6 decimal places
struct participant_fractional_total_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant High Price: Participant highest price paid during the trading day. Has implied 6 decimal places
struct participant_high_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id: Identifies the Participant or Processor that initiated the message
struct participant_id {
    enum class type : char {
        nyse_american_llc_nyse_american = 'A',
        nasdaq_omx_bx_inc_nasdaq_omx_bx = 'B',
        nyse_national_inc_nyse_national = 'C',
        finra_alternative_display_facility_adf = 'D',
        texas_stock_exchange_llc_txse = 'F',
        n24x_national_exchange_llc_24x = 'G',
        miax_pearl_exchange_llc_miax = 'H',
        international_securities_exchange_llc_ise = 'I',
        cboe_edga_exchange_inc_cboe_edga = 'J',
        cboe_edgx_exchange_inc_cboe_edgx = 'K',
        long_term_stock_exchange_inc_ltse = 'L',
        nyse_texas_inc_nyse_texas = 'M',
        new_york_stock_exchange_llc_nyse = 'N',
        nyse_arca_inc_nyse_arca = 'P',
        consolidated_tape_system_cts = 'S',
        nasdaq_stock_market_llc_nasdaq = 'T',
        members_exchange_llc_memx = 'U',
        investors_exchange_llc_iex = 'V',
        cboe_stock_exchange_inc_cbsx = 'W',
        nasdaq_omx_psx_inc_nasdaq_omx_psx = 'X',
        cboe_byx_exchange_inc_cboe_byx = 'Y',
        cboe_bzx_exchange_inc_cboe_bzx = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Participant Last Price: Participant last price. Has implied 6 decimal places
struct participant_last_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Low Price: Participant lowest price paid during the trading day. Has implied 6 decimal places
struct participant_low_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Participant Open Price: Participant first qualifying price paid during the trading day. Has implied 6 decimal places
struct participant_open_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Previous Close Price Date: Participant date the security last traded. Represented in seconds since Epoch
struct participant_previous_close_price_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Reference Number: Contains the Participant Reference Number
struct participant_reference_number {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Tick: Participant tick direction
struct participant_tick {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Participant Total Volume: Contains the Participant Total Volume of shares traded for a security at the time of the trade correction or cancel/error
struct participant_total_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Previous Close Price: Represents the last qualifying price paid for a security during the trading day. Has implied 6 decimal places
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

// Previous Close Price Date: Represents the date the security last traded. Represented in seconds since Epoch
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
        primary_listing_market_participant_id_not_applicable = ' ',
        nyse_american = 'A',
        nasdaq_bx = 'B',
        nyse_national = 'C',
        finra_adf = 'D',
        texas_stock_exchange = 'F',
        n24x = 'G',
        miax_pearl = 'H',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_texas = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'T',
        members_exchange = 'U',
        iex = 'V',
        cbsx = 'W',
        nasdaq_omx_psx = 'X',
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

// Primary Listing Market Previous Closing Price: Represents the previous closing price for the primary listing market. Has implied 6 decimal places
struct primary_listing_market_previous_closing_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prior Day Message Type: Identifies the type of Prior Day message
struct prior_day_message_type {
    enum class type : char {
        prior_day_trade_correction = 'C',
        fractional_prior_day_trade_correction = 'O',
        prior_day_trade = 'T',
        fractional_prior_day_trade = 'R',
        prior_day_trade_cancel_error = 'X',
        fractional_prior_day_trade_cancel_error = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Prior Security Symbol: Contains the prior Security Symbol
struct prior_security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Reserved: Space-filled. Field is reserved for future use
struct reserved {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Reserved 128: Space-filled. Field is reserved for future use
struct reserved_128 {
    using type = std::string_view;
    static constexpr std::size_t size = 128;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 128> value_;
};

// Reserved 62: Space-filled. Field is reserved for future use
struct reserved_62 {
    using type = std::string_view;
    static constexpr std::size_t size = 62;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 62> value_;
};

// Retransmission Indicator
struct retransmission_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Round Lot Size: Round-lot size for a symbol can consist of 1, 10, 40 or 100 shares
struct round_lot_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sale Condition 1: Denotes the sale condition associated with a trade
struct sale_condition_1 {
    enum class type : char {
        regular_sale = ' ',
        average_price_trade = 'B',
        cash_trade_same_day_clearing = 'C',
        automatic_execution = 'E',
        inter_market_sweep_order = 'F',
        price_variation_trade = 'H',
        odd_lot_trade = 'I',
        rule_127_nyse_only_or_rule_155_nyse_american_only = 'K',
        sold_last_late_reporting = 'L',
        market_center_official_close = 'M',
        reserved_n = 'N',
        market_center_opening_trade = 'O',
        prior_reference_price = 'P',
        market_center_official_open = 'Q',
        seller = 'R',
        extended_hours_trade = 'T',
        extended_hours_sold_out_of_sequence = 'U',
        contingent_trade = 'V',
        cross_periodic_auction_trade = 'X',
        sold_out_of_sequence = 'Z',
        derivatively_priced = '4',
        market_center_reopening_trade = '5',
        market_center_closing_trade = '6',
        qualified_contingent_trade = '7',
        reserved_8 = '8',
        corrected_consolidated_close_price_as_per_listing_market = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sale Condition Category: In the Short Trade format, identifies the Sale Condition Category level associated with a trade
struct sale_condition_category {
    enum class type : char {
        sale_condition_category_not_applicable = ' ',
        sale_condition_category_1 = '1',
        sale_condition_category_2 = '2',
        sale_condition_category_3 = '3',
        sale_condition_category_4 = '4',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Second Reserved: Space-filled. Field is reserved for future use
struct second_reserved {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Seconds: Contains The Number Seconds From Epoch 111970000000 Utc
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
        security_status_not_applicable = ' ',
        reserved_1 = '1',
        trading_halt = '2',
        resume = '3',
        reserved_4 = '4',
        price_indication = '5',
        trading_range_indication = '6',
        market_imbalance_buy = '7',
        market_imbalance_sell = '8',
        closing_imbalance_buy = '9',
        closing_imbalance_sell = 'A',
        reserved_b = 'B',
        no_market_imbalance = 'C',
        no_closing_imbalance = 'D',
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

// Security Symbol: Identifies the Security Symbol. Left justified, space-filled
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Security Symbol 5: Identifies the Security Symbol. Left justified, space-filled
struct security_symbol_5 {
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

// Sellers Sale Days: Specifies the number of days that may elapse before delivery of the security. Allowed values 2 through 60 days
struct sellers_sale_days {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is in effect for a security
struct short_sale_restriction_indicator {
    enum class type : char {
        short_sale_restriction_not_in_effect = ' ',
        short_sale_restriction_activated = 'A',
        short_sale_restriction_continued = 'C',
        short_sale_restriction_deactivated = 'D',
        short_sale_restriction_in_effect = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stop Stock Indicator: Identifies whether the transaction constituted a stopped order
struct stop_stock_indicator {
    enum class type : char {
        stop_stock_not_applicable = '0',
        stop_stock = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Summary Message Type: Identifies the type of Summary message
struct summary_message_type {
    enum class type : char {
        consolidated_start_of_day_summary = 'A',
        participant_start_of_day_summary = 'B',
        consolidated_end_of_day_summary = 'C',
        fractional_consolidated_end_of_day_summary = 'T',
        participant_end_of_day_summary = 'D',
        fractional_participant_end_of_day_summary = 'P',
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

// Test: Identifies whether the security symbol is a test symbol
struct test {
    enum class type : char {
        not_a_test_symbol = '0',
        test_symbol = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Tick: Represents for a Participant the upward, downward or unchanged price movement in a security's trades
struct tick {
    enum class type : char {
        tick_not_applicable = ' ',
        up_tick = '1',
        down_tick = '2',
        zero_up_tick = '3',
        zero_down_tick = '4',
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

// Trade Message Type: Identifies the type of Trade message
struct trade_message_type {
    enum class type : char {
        auction_status = 'A',
        trade_correction = 'C',
        fractional_trade_correction = 'O',
        long_trade = 'L',
        fractional_long_trade = 'R',
        trading_status = 'S',
        short_trade = 'T',
        fractional_short_trade = 'H',
        trade_cancel_error = 'X',
        fractional_trade_cancel_error = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Price: Represents the monetary value of an individual share of security at the time of the trade. Has implied 6 decimal places
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

// Trade Price 2: Represents the monetary value of an individual share of security at the time of the trade. Has implied 2 decimal places
struct trade_price_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting Facility (TRF) has been formed. Space-filled
struct trade_reporting_facility_id {
    enum class type : char {
        trf_not_applicable = ' ',
        not_currently_active_a = 'A',
        finra_nasdaq_trf_chicago = 'B',
        not_currently_active_c = 'C',
        not_currently_active_d = 'D',
        not_currently_active_i = 'I',
        not_currently_active_j = 'J',
        not_currently_active_k = 'K',
        not_currently_active_m = 'M',
        finra_nyse_trf = 'N',
        not_currently_active_p = 'P',
        finra_nasdaq_trf_carteret = 'T',
        not_currently_active_v = 'V',
        not_currently_active_w = 'W',
        not_currently_active_x = 'X',
        not_currently_active_y = 'Y',
        not_currently_active_z = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Through Exempt Indicator: Denotes whether or not a trade is exempt (Rule 611)
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

// Trade Total Volume: Contains the total number of shares traded for an individual security
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

// Trade Volume 2: Contains the total number of shares traded in a single transaction for an individual security (short form)
struct trade_volume_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transaction Id: Identifies the transaction
struct transaction_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Version: Designates The Cta Binary Version
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

// Sale Condition 4
struct sale_condition_4 {
    static constexpr std::string_view name = "Sale Condition 4";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        category_1,
        category_2,
        category_3,
        category_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(category_1);
    CTSFIELD(category_2);
    CTSFIELD(category_3);
    CTSFIELD(category_4);
};

static_assert(sizeof(sale_condition_4) == sale_condition_4::size, "sale_condition_4 lies over its bytes exactly");

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

// Fractional Trade Cancel Error Message: Used to cancel or error CTA eligible securities, Local Issues or Bond information. Volume is represented as a fractional value
struct fractional_trade_cancel_error_message {
    static constexpr std::string_view name = "Fractional Trade Cancel Error Message";
    static constexpr std::size_t size = 161;
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
        sale_condition_4,
        trade_price,
        fractional_trade_volume,
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
        consolidated_previous_close_price_date,
        consolidated_last_participant_id,
        consolidated_last_price,
        consolidated_high_price,
        consolidated_low_price,
        consolidated_fractional_total_volume,
        consolidated_tick,
        participant_previous_close_price_date,
        participant_last_price,
        participant_high_price,
        participant_low_price,
        participant_open_price,
        participant_fractional_total_volume,
        participant_tick>;

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
    CTSFIELD(sale_condition_4);
    CTSFIELD(trade_price);
    CTSFIELD(fractional_trade_volume);
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
    CTSFIELD(consolidated_previous_close_price_date);
    CTSFIELD(consolidated_last_participant_id);
    CTSFIELD(consolidated_last_price);
    CTSFIELD(consolidated_high_price);
    CTSFIELD(consolidated_low_price);
    CTSFIELD(consolidated_fractional_total_volume);
    CTSFIELD(consolidated_tick);
    CTSFIELD(participant_previous_close_price_date);
    CTSFIELD(participant_last_price);
    CTSFIELD(participant_high_price);
    CTSFIELD(participant_low_price);
    CTSFIELD(participant_open_price);
    CTSFIELD(participant_fractional_total_volume);
    CTSFIELD(participant_tick);
};

static_assert(sizeof(fractional_trade_cancel_error_message) == fractional_trade_cancel_error_message::size, "fractional_trade_cancel_error_message lies over its bytes exactly");

// Fractional Short Trade Message: Used to report trade information for CTA eligible Equity only. Volume is represented as a fractional value. Not published by CTS currently, message type is reserved for future use
struct fractional_short_trade_message {
    static constexpr std::string_view name = "Fractional Short Trade Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol_5,
        sale_condition_1,
        sale_condition_category,
        trade_price_2,
        fractional_trade_volume_4,
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
    CTSFIELD(security_symbol_5);
    CTSFIELD(sale_condition_1);
    CTSFIELD(sale_condition_category);
    CTSFIELD(trade_price_2);
    CTSFIELD(fractional_trade_volume_4);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(consolidated_high_low_last_indicator);
    CTSFIELD(participant_open_high_low_last_indicator);
};

static_assert(sizeof(fractional_short_trade_message) == fractional_short_trade_message::size, "fractional_short_trade_message lies over its bytes exactly");

// Trading Status Message: Transmitted when a Participant in a CTA eligible security, Local Issue or a Bond elects to notify CTS of a Trading Halt, a Trading Resume, a Price Indication or a Market Imbalance
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
        limit_up_limit_down_luld_indicator>;

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
    CTSFIELD(limit_up_limit_down_luld_indicator);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Fractional Long Trade Message: Used to report trade information for CTA eligible Equity, Local Issue or Bonds. Volume is represented as a fractional value
struct fractional_long_trade_message {
    static constexpr std::string_view name = "Fractional Long Trade Message";
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
        sale_condition_4,
        trade_price,
        fractional_trade_volume,
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
    CTSFIELD(sale_condition_4);
    CTSFIELD(trade_price);
    CTSFIELD(fractional_trade_volume);
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

static_assert(sizeof(fractional_long_trade_message) == fractional_long_trade_message::size, "fractional_long_trade_message lies over its bytes exactly");

// Fractional Trade Correction Message: Used to correct CTA eligible Equity, Local Issue or Bond information. Volume is represented as a fractional value
struct fractional_trade_correction_message {
    static constexpr std::string_view name = "Fractional Trade Correction Message";
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
        corrected_sale_condition,
        corrected_trade_price,
        corrected_fractional_trade_volume,
        corrected_sellers_sale_days,
        corrected_stop_stock_indicator,
        corrected_trade_through_exempt_indicator,
        corrected_short_sale_restriction_indicator,
        trade_reporting_facility_id,
        timestamp_2,
        original_participant_reference_number,
        original_sale_condition,
        original_trade_price,
        original_fractional_trade_volume,
        original_sellers_sale_days,
        original_stop_stock_indicator,
        original_trade_through_exempt_indicator,
        original_short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        consolidated_previous_close_price_date,
        consolidated_last_participant_id,
        consolidated_last_price,
        consolidated_high_price,
        consolidated_low_price,
        consolidated_fractional_total_volume,
        consolidated_tick,
        participant_previous_close_price_date,
        participant_last_price,
        participant_high_price,
        participant_low_price,
        participant_open_price,
        participant_fractional_total_volume,
        participant_tick>;

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
    CTSFIELD(corrected_sale_condition);
    CTSFIELD(corrected_trade_price);
    CTSFIELD(corrected_fractional_trade_volume);
    CTSFIELD(corrected_sellers_sale_days);
    CTSFIELD(corrected_stop_stock_indicator);
    CTSFIELD(corrected_trade_through_exempt_indicator);
    CTSFIELD(corrected_short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(timestamp_2);
    CTSFIELD(original_participant_reference_number);
    CTSFIELD(original_sale_condition);
    CTSFIELD(original_trade_price);
    CTSFIELD(original_fractional_trade_volume);
    CTSFIELD(original_sellers_sale_days);
    CTSFIELD(original_stop_stock_indicator);
    CTSFIELD(original_trade_through_exempt_indicator);
    CTSFIELD(original_short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(consolidated_previous_close_price_date);
    CTSFIELD(consolidated_last_participant_id);
    CTSFIELD(consolidated_last_price);
    CTSFIELD(consolidated_high_price);
    CTSFIELD(consolidated_low_price);
    CTSFIELD(consolidated_fractional_total_volume);
    CTSFIELD(consolidated_tick);
    CTSFIELD(participant_previous_close_price_date);
    CTSFIELD(participant_last_price);
    CTSFIELD(participant_high_price);
    CTSFIELD(participant_low_price);
    CTSFIELD(participant_open_price);
    CTSFIELD(participant_fractional_total_volume);
    CTSFIELD(participant_tick);
};

static_assert(sizeof(fractional_trade_correction_message) == fractional_trade_correction_message::size, "fractional_trade_correction_message lies over its bytes exactly");

// Trade Cancel Error Message: Used to cancel or error CTA eligible securities, Local Issues or Bond information. To be descoped when Fractional Trade Volume publication is activated
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
        sale_condition_4,
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
        consolidated_previous_close_price_date,
        consolidated_last_participant_id,
        consolidated_last_price,
        consolidated_high_price,
        consolidated_low_price,
        consolidated_total_volume,
        consolidated_tick,
        participant_previous_close_price_date,
        participant_last_price,
        participant_high_price,
        participant_low_price,
        participant_open_price,
        participant_total_volume,
        participant_tick>;

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
    CTSFIELD(sale_condition_4);
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
    CTSFIELD(consolidated_previous_close_price_date);
    CTSFIELD(consolidated_last_participant_id);
    CTSFIELD(consolidated_last_price);
    CTSFIELD(consolidated_high_price);
    CTSFIELD(consolidated_low_price);
    CTSFIELD(consolidated_total_volume);
    CTSFIELD(consolidated_tick);
    CTSFIELD(participant_previous_close_price_date);
    CTSFIELD(participant_last_price);
    CTSFIELD(participant_high_price);
    CTSFIELD(participant_low_price);
    CTSFIELD(participant_open_price);
    CTSFIELD(participant_total_volume);
    CTSFIELD(participant_tick);
};

static_assert(sizeof(trade_cancel_error_message) == trade_cancel_error_message::size, "trade_cancel_error_message lies over its bytes exactly");

// Short Trade Message: Used to report trade information for CTA eligible Equity only. To be descoped when Fractional Trade Volume publication is activated
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
        security_symbol_5,
        sale_condition_1,
        sale_condition_category,
        trade_price_2,
        trade_volume_2,
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
    CTSFIELD(security_symbol_5);
    CTSFIELD(sale_condition_1);
    CTSFIELD(sale_condition_category);
    CTSFIELD(trade_price_2);
    CTSFIELD(trade_volume_2);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(consolidated_high_low_last_indicator);
    CTSFIELD(participant_open_high_low_last_indicator);
};

static_assert(sizeof(short_trade_message) == short_trade_message::size, "short_trade_message lies over its bytes exactly");

// Long Trade Message: Used to report trade information for CTA eligible Equity, Local Issue or Bonds. To be descoped when Fractional Trade Volume publication is activated
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
        sale_condition_4,
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
    CTSFIELD(sale_condition_4);
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

// Trade Correction Message: Used to correct CTA eligible Equity, Local Issue or Bond information. To be descoped when Fractional Trade Volume publication is activated
struct trade_correction_message {
    static constexpr std::string_view name = "Trade Correction Message";
    static constexpr std::size_t size = 168;
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
        corrected_sale_condition,
        corrected_trade_price,
        corrected_trade_volume,
        corrected_sellers_sale_days,
        corrected_stop_stock_indicator,
        corrected_trade_through_exempt_indicator,
        corrected_short_sale_restriction_indicator,
        trade_reporting_facility_id,
        timestamp_2,
        original_participant_reference_number,
        original_sale_condition,
        original_trade_price,
        original_trade_volume,
        original_sellers_sale_days,
        original_stop_stock_indicator,
        original_trade_through_exempt_indicator,
        original_short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        consolidated_previous_close_price_date,
        consolidated_last_participant_id,
        consolidated_last_price,
        consolidated_high_price,
        consolidated_low_price,
        consolidated_total_volume,
        consolidated_tick,
        participant_previous_close_price_date,
        participant_last_price,
        participant_high_price,
        participant_low_price,
        participant_open_price,
        participant_total_volume,
        participant_tick>;

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
    CTSFIELD(corrected_sale_condition);
    CTSFIELD(corrected_trade_price);
    CTSFIELD(corrected_trade_volume);
    CTSFIELD(corrected_sellers_sale_days);
    CTSFIELD(corrected_stop_stock_indicator);
    CTSFIELD(corrected_trade_through_exempt_indicator);
    CTSFIELD(corrected_short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(timestamp_2);
    CTSFIELD(original_participant_reference_number);
    CTSFIELD(original_sale_condition);
    CTSFIELD(original_trade_price);
    CTSFIELD(original_trade_volume);
    CTSFIELD(original_sellers_sale_days);
    CTSFIELD(original_stop_stock_indicator);
    CTSFIELD(original_trade_through_exempt_indicator);
    CTSFIELD(original_short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(consolidated_previous_close_price_date);
    CTSFIELD(consolidated_last_participant_id);
    CTSFIELD(consolidated_last_price);
    CTSFIELD(consolidated_high_price);
    CTSFIELD(consolidated_low_price);
    CTSFIELD(consolidated_total_volume);
    CTSFIELD(consolidated_tick);
    CTSFIELD(participant_previous_close_price_date);
    CTSFIELD(participant_last_price);
    CTSFIELD(participant_high_price);
    CTSFIELD(participant_low_price);
    CTSFIELD(participant_open_price);
    CTSFIELD(participant_total_volume);
    CTSFIELD(participant_tick);
};

static_assert(sizeof(trade_correction_message) == trade_correction_message::size, "trade_correction_message lies over its bytes exactly");

// Auction Status Message: Used when a Participant in a CTA eligible security, Local Issue or a Bond requires Auction Information
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
        reserved_62>;

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
    CTSFIELD(reserved_62);
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

// Trade Message: Trade Category Trade Messages Are Used To Report Cta Eligible Equity Local Issue Or Bond Information
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr bool is_message = false;
};

// Fractional Participant End Of Day Summary Message: Provides by security, the Participant Open, High, Low, Last, Volume and Tick information for CTA eligible securities, Local Issues and Bonds. Volume is represented as a fractional value
struct fractional_participant_end_of_day_summary_message {
    static constexpr std::string_view name = "Fractional Participant End Of Day Summary Message";
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
        summary_participant_id,
        previous_close_price_date,
        last_price,
        high_price,
        low_price,
        open_price,
        fractional_total_volume,
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
    CTSFIELD(summary_participant_id);
    CTSFIELD(previous_close_price_date);
    CTSFIELD(last_price);
    CTSFIELD(high_price);
    CTSFIELD(low_price);
    CTSFIELD(open_price);
    CTSFIELD(fractional_total_volume);
    CTSFIELD(tick);
};

static_assert(sizeof(fractional_participant_end_of_day_summary_message) == fractional_participant_end_of_day_summary_message::size, "fractional_participant_end_of_day_summary_message lies over its bytes exactly");

// Participant End Of Day Summary Message: Provides by security, the Participant Open, High, Low, Last, Volume and Tick information for CTA eligible securities, Local Issues and Bonds. To be descoped when Fractional Trade Volume publication is activated
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
        summary_participant_id,
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
    CTSFIELD(summary_participant_id);
    CTSFIELD(previous_close_price_date);
    CTSFIELD(last_price);
    CTSFIELD(high_price);
    CTSFIELD(low_price);
    CTSFIELD(open_price);
    CTSFIELD(total_volume);
    CTSFIELD(tick);
};

static_assert(sizeof(participant_end_of_day_summary_message) == participant_end_of_day_summary_message::size, "participant_end_of_day_summary_message lies over its bytes exactly");

// Fractional Consolidated End Of Day Summary Message: Provides by security, the Consolidated High, Low, Last and Volume for CTA eligible Equity, Local Issues and Bonds. Volume is represented as a fractional value
struct fractional_consolidated_end_of_day_summary_message {
    static constexpr std::string_view name = "Fractional Consolidated End Of Day Summary Message";
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
        fractional_total_volume,
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
    CTSFIELD(fractional_total_volume);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(number_of_participants);
};

static_assert(sizeof(fractional_consolidated_end_of_day_summary_message) == fractional_consolidated_end_of_day_summary_message::size, "fractional_consolidated_end_of_day_summary_message lies over its bytes exactly");

// Consolidated End Of Day Summary Message: Provides by security, the Consolidated High, Low, Last and Volume for CTA eligible Equity, Local Issues and Bonds. To be descoped when Fractional Trade Volume publication is activated
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

// Participant Start Of Day Summary Message: Provides, by security, Participant previous close price and previous close price date information for CTA eligible Equity, Local Issues and Bonds
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

// Consolidated Start Of Day Summary Message: Provides, by security, consolidated previous close price and previous close price date information for CTA eligible Equity, Local Issues and Bonds
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

// Summary Message: Summary Category Summary Messages Are Used To Provide Cta Eligible Equity Local Issue And Bond Summary Information By Security
struct summary_message {
    static constexpr std::string_view name = "Summary Message";
    static constexpr bool is_message = false;
};

// Prior Day Trade Date and Time: The date and time the prior day trade was executed
struct prior_day_trade_date_and_time {
    static constexpr std::string_view name = "Prior Day Trade Date and Time";
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

// Fractional Prior Day Trade Cancel Error Message: Used to report the cancellation of a trade or error a trade that never took place but was reported, for transactions originally reported earlier than the current day. Volume is represented as a fractional value
struct fractional_prior_day_trade_cancel_error_message {
    static constexpr std::string_view name = "Fractional Prior Day Trade Cancel Error Message";
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
        sale_condition_4,
        trade_price,
        fractional_trade_volume,
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
    CTSFIELD(sale_condition_4);
    CTSFIELD(trade_price);
    CTSFIELD(fractional_trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(prior_day_trade_date_and_time);
    CTSFIELD(cancel_error_action);
};

static_assert(sizeof(fractional_prior_day_trade_cancel_error_message) == fractional_prior_day_trade_cancel_error_message::size, "fractional_prior_day_trade_cancel_error_message lies over its bytes exactly");

// Fractional Prior Day Trade Message: Used to report a CTA Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. Volume is represented as a fractional value
struct fractional_prior_day_trade_message {
    static constexpr std::string_view name = "Fractional Prior Day Trade Message";
    static constexpr std::size_t size = 67;
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
        sale_condition_4,
        trade_price,
        fractional_trade_volume,
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
    CTSFIELD(sale_condition_4);
    CTSFIELD(trade_price);
    CTSFIELD(fractional_trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(prior_day_trade_date_and_time);
};

static_assert(sizeof(fractional_prior_day_trade_message) == fractional_prior_day_trade_message::size, "fractional_prior_day_trade_message lies over its bytes exactly");

// Fractional Prior Day Trade Correction Message: Used to correct a transaction originally reported on a trading day earlier than the current trading day. Volume is represented as a fractional value
struct fractional_prior_day_trade_correction_message {
    static constexpr std::string_view name = "Fractional Prior Day Trade Correction Message";
    static constexpr std::size_t size = 67;
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
        sale_condition_4,
        trade_price,
        fractional_trade_volume,
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
    CTSFIELD(sale_condition_4);
    CTSFIELD(trade_price);
    CTSFIELD(fractional_trade_volume);
    CTSFIELD(sellers_sale_days);
    CTSFIELD(stop_stock_indicator);
    CTSFIELD(trade_through_exempt_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(prior_day_trade_date_and_time);
};

static_assert(sizeof(fractional_prior_day_trade_correction_message) == fractional_prior_day_trade_correction_message::size, "fractional_prior_day_trade_correction_message lies over its bytes exactly");

// Prior Day Trade Cancel Error Message: Used to report the cancellation of a trade or error a trade that never took place but was reported, for transactions originally reported earlier than the current day. To be descoped when Fractional Trade Volume publication is activated
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
        sale_condition_4,
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
    CTSFIELD(sale_condition_4);
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

// Prior Day Trade Message: Used to report a CTA Equity, Local Issue or Bond transaction which occurred earlier than the current trading day and was not reported. To be descoped when Fractional Trade Volume publication is activated
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
        sale_condition_4,
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
    CTSFIELD(sale_condition_4);
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

// Original Prior Day Trade Date and Time: The original prior day trade date and time
struct original_prior_day_trade_date_and_time {
    static constexpr std::string_view name = "Original Prior Day Trade Date and Time";
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

static_assert(sizeof(original_prior_day_trade_date_and_time) == original_prior_day_trade_date_and_time::size, "original_prior_day_trade_date_and_time lies over its bytes exactly");

// Corrected Prior Day Trade Date and Time: The corrected prior day trade date and time
struct corrected_prior_day_trade_date_and_time {
    static constexpr std::string_view name = "Corrected Prior Day Trade Date and Time";
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

static_assert(sizeof(corrected_prior_day_trade_date_and_time) == corrected_prior_day_trade_date_and_time::size, "corrected_prior_day_trade_date_and_time lies over its bytes exactly");

// Prior Day Trade Correction Message: Used to correct a transaction originally reported on a trading day earlier than the current trading day. To be descoped when Fractional Trade Volume publication is activated
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
        corrected_sale_condition,
        corrected_trade_price,
        corrected_trade_volume,
        corrected_sellers_sale_days,
        corrected_stop_stock_indicator,
        corrected_trade_through_exempt_indicator,
        corrected_short_sale_restriction_indicator,
        corrected_prior_day_trade_date_and_time,
        trade_reporting_facility_id,
        original_sale_condition,
        original_trade_price,
        original_trade_volume,
        original_sellers_sale_days,
        original_stop_stock_indicator,
        original_trade_through_exempt_indicator,
        original_short_sale_restriction_indicator,
        original_prior_day_trade_date_and_time>;

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
    CTSFIELD(corrected_sale_condition);
    CTSFIELD(corrected_trade_price);
    CTSFIELD(corrected_trade_volume);
    CTSFIELD(corrected_sellers_sale_days);
    CTSFIELD(corrected_stop_stock_indicator);
    CTSFIELD(corrected_trade_through_exempt_indicator);
    CTSFIELD(corrected_short_sale_restriction_indicator);
    CTSFIELD(corrected_prior_day_trade_date_and_time);
    CTSFIELD(trade_reporting_facility_id);
    CTSFIELD(original_sale_condition);
    CTSFIELD(original_trade_price);
    CTSFIELD(original_trade_volume);
    CTSFIELD(original_sellers_sale_days);
    CTSFIELD(original_stop_stock_indicator);
    CTSFIELD(original_trade_through_exempt_indicator);
    CTSFIELD(original_short_sale_restriction_indicator);
    CTSFIELD(original_prior_day_trade_date_and_time);
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

// Prior Day Message: Prior Day Category Prior Day Messages Are Used To Report Cta Eligible Equity Local Issue Or Bond Trades Corrections Cancels Or Errors For Transactions That Occurred Earlier Than The Current Trading Day And Had Not Been Reported
struct prior_day_message {
    static constexpr std::string_view name = "Prior Day Message";
    static constexpr bool is_message = false;
};

// Crossing Session Summary Message: Used to report the total volume and dollar value of trades transacted after the close of a Participant's regular session
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

// Approximate Trades And Total Dollar Value Message: Allows a Participant to report the total trades and total dollar value of trades at their respective market centers
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

// Participant: Active Participants
struct participant {
    static constexpr std::string_view name = "Participant";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        fractional_trade_total_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CTSFIELD(participant_id);
    CTSFIELD(fractional_trade_total_volume);
};

static_assert(sizeof(participant) == participant::size, "participant lies over its bytes exactly");

// Fractional Approximate Adjusted Volume Market Center Message Section 1
struct fractional_approximate_adjusted_volume_market_center_message_section_1 {
    static constexpr std::string_view name = "Fractional Approximate Adjusted Volume Market Center Message Section 1";
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

static_assert(sizeof(fractional_approximate_adjusted_volume_market_center_message_section_1) == fractional_approximate_adjusted_volume_market_center_message_section_1::size, "fractional_approximate_adjusted_volume_market_center_message_section_1 lies over its bytes exactly");

// Fractional Approximate Adjusted Volume Market Center Message: Used to report the volume of adjusted trading activity for each Participant. Volume is represented as a fractional value
struct fractional_approximate_adjusted_volume_market_center_message {
    static constexpr std::string_view name = "Fractional Approximate Adjusted Volume Market Center Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CTSSEQUENCE(participant);
};

// Approximate Volume Participant: Active Participants for Approximate Adjusted Volume Market Center
struct approximate_volume_participant {
    static constexpr std::string_view name = "Approximate Volume Participant";
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

static_assert(sizeof(approximate_volume_participant) == approximate_volume_participant::size, "approximate_volume_participant lies over its bytes exactly");

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

// Approximate Adjusted Volume Market Center Message: Used to report the volume of adjusted trading activity for each Participant. To be descoped when Fractional Trade Volume publication is activated
struct approximate_adjusted_volume_market_center_message {
    static constexpr std::string_view name = "Approximate Adjusted Volume Market Center Message";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    CTSSEQUENCE(approximate_volume_participant);
};

// Market Wide Circuit Breaker Status Message: Reports the Market-Wide Circuit Breaker threshold Level that has been breached
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

// Market Wide Circuit Breaker Decline Level Status Message: Reports the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker
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

// Market Status Message: Market Status Category Market Status Messages Are Used To Provide Market Data Information
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

// Indices Message: Index Category Index Messages Are Used To Provide Index Value Information Of A Security
struct indices_message {
    static constexpr std::string_view name = "Indices Message";
    static constexpr bool is_message = false;
};

// End Of Day Message: Transmitted over the multicast lines to advise all Data Recipients that there are no further messages to be transmitted for the day
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

// Line Integrity Message: Transmitted over the multicast lines at frequent intervals to verify continued integrity of multicast transmission
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

// Disaster Recovery Data Center Activation Message: Signifies that the Consolidated Tape System has switched processing from the Primary Data Center to the Disaster Recovery Data Center
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

// Reset Block Sequence Number Message: Transmitted when the Block Sequence Number on an output multicast line requires resetting
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

// Start Of Day Message: Signals the start of normal data dissemination over the multicast lines
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

// Control Message: Control Category
struct control_message {
    static constexpr std::string_view name = "Control Message";
    static constexpr bool is_message = false;
};

// Symbol Reference Data Message
struct symbol_reference_data_message {
    static constexpr std::string_view name = "Symbol Reference Data Message";
    static constexpr std::size_t size = 205;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        timestamp_1,
        message_id,
        transaction_id,
        participant_reference_number,
        security_symbol,
        prior_security_symbol,
        primary_listing_market_participant_id,
        primary_listing_market_previous_closing_price,
        consolidated_closing_price,
        round_lot_size,
        minimum_price_increment_indicator,
        luld_tier,
        luld_leverage_ratio,
        test,
        ipo,
        financial_status_indicator,
        short_sale_restriction_indicator,
        halt_reason,
        instrument_type,
        reserved,
        second_reserved,
        reserved_128>;

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
    CTSFIELD(prior_security_symbol);
    CTSFIELD(primary_listing_market_participant_id);
    CTSFIELD(primary_listing_market_previous_closing_price);
    CTSFIELD(consolidated_closing_price);
    CTSFIELD(round_lot_size);
    CTSFIELD(minimum_price_increment_indicator);
    CTSFIELD(luld_tier);
    CTSFIELD(luld_leverage_ratio);
    CTSFIELD(test);
    CTSFIELD(ipo);
    CTSFIELD(financial_status_indicator);
    CTSFIELD(short_sale_restriction_indicator);
    CTSFIELD(halt_reason);
    CTSFIELD(instrument_type);
    CTSFIELD(reserved);
    CTSFIELD(second_reserved);
    CTSFIELD(reserved_128);
};

static_assert(sizeof(symbol_reference_data_message) == symbol_reference_data_message::size, "symbol_reference_data_message lies over its bytes exactly");

// End Of Start Of Day Summary Message: Used to signal the end of Start of Day Summary message iterations
struct end_of_start_of_day_summary_message {
    static constexpr std::string_view name = "End Of Start Of Day Summary Message";
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

static_assert(sizeof(end_of_start_of_day_summary_message) == end_of_start_of_day_summary_message::size, "end_of_start_of_day_summary_message lies over its bytes exactly");

// Start Of Start Of Day Summary Message: Used to signal the start of Start of Day Summary message iterations
struct start_of_start_of_day_summary_message {
    static constexpr std::string_view name = "Start Of Start Of Day Summary Message";
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

static_assert(sizeof(start_of_start_of_day_summary_message) == start_of_start_of_day_summary_message::size, "start_of_start_of_day_summary_message lies over its bytes exactly");

// End Of End Of Day Summary Message: Used to signal the end of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct end_of_end_of_day_summary_message {
    static constexpr std::string_view name = "End Of End Of Day Summary Message";
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

static_assert(sizeof(end_of_end_of_day_summary_message) == end_of_end_of_day_summary_message::size, "end_of_end_of_day_summary_message lies over its bytes exactly");

// Start Of End Of Day Summary Message: Used to signal the start of Consolidated End of Day Summary and Participant End of Day Summary message iterations
struct start_of_end_of_day_summary_message {
    static constexpr std::string_view name = "Start Of End Of Day Summary Message";
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

static_assert(sizeof(start_of_end_of_day_summary_message) == start_of_end_of_day_summary_message::size, "start_of_end_of_day_summary_message lies over its bytes exactly");

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

// Administrative Message: Administrative Category
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

// SIP Block Timestamp: Cta packet timestamp
struct sip_block_timestamp {
    static constexpr std::string_view name = "SIP Block Timestamp";
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

} // namespace siac::cts::output::cta::v2_11_b
