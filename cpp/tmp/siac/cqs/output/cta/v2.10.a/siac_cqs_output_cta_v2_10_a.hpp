// Siac Cqs Output Cta 2.10.a Template Meta Programming

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
#ifndef CQSFIELD
#define CQSFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef CQSSEQUENCE
#define CQSSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace siac::cqs::output::cta::v2_10_a {

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
        symbol_reference_data = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Collar Lower Threshold Price: Represents the latest lower threshold price of the Auction Collar
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

// Auction Collar Reference Price: Represents the price used by the exchange to establish the Auction Collar
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

// Best Bid Participant Id: Identifies the Participant that submitted the Best Bid on a consolidated basis
struct best_bid_participant_id {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Best Bid Price Long: Represents the Best Bid Price on a consolidated basis
struct best_bid_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Bid Price Short: Represents the Best Bid Price on a consolidated basis. Has implied 2 decimal places
struct best_bid_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Bid Quote Condition: Identifies the Quote Condition associated with the Best Bid Price on a consolidated basis
struct best_bid_quote_condition {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Best Bid Size Long: Represents the Best Bid Size associated with the Best Bid Price on a consolidated basis
struct best_bid_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Bid Size Short: Represents the Best Bid Size associated with the Best Bid Price on a consolidated basis
struct best_bid_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Participant Id: Identifies the Participant that submitted the Best Offer on a consolidated basis
struct best_offer_participant_id {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Best Offer Price Long: Represents the Best Offer Price on a consolidated basis
struct best_offer_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Price Short: Represents the Best Offer Price on a consolidated basis. Has implied 2 decimal places
struct best_offer_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Quote Condition: Identifies the Quote Condition associated with the Best Offer Price on a consolidated basis
struct best_offer_quote_condition {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Best Offer Size Long: Represents the Best Offer Size associated with the Best Offer Price on a consolidated basis
struct best_offer_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Size Short: Represents the Best Offer Size associated with the Best Offer Price on a consolidated basis
struct best_offer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Long: Represents the highest price a prospective buyer is prepared to pay at a particular time for a security. Has implied 6 decimal places
struct bid_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Lower Limit Price Band: Bid Price represents the highest price a prospective buyer is prepared to pay; Lower Limit Price Band represents the lower price band value when Security Status Indicator is Limit Up-Limit Down Price Band
struct bid_price_lower_limit_price_band {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Short: Represents the highest price a prospective buyer is prepared to pay at a particular time for a security. Has implied 2 decimal places
struct bid_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Long: Identifies the number of shares for a symbol rounded down to the nearest multiple of its Round Lot Size
struct bid_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Short: Identifies the number of shares for a symbol rounded down to the nearest multiple of its Round Lot Size
struct bid_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

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

// Consolidated Closing Price: Consolidated Closing Price. Has implied 6 decimal places
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

// Control Message Type: Identifies the type of Control message
struct control_message_type {
    enum class type : char {
        start_of_day = 'A',
        finra_close = 'C',
        reset_block_sequence_number = 'L',
        finra_open = 'O',
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

// Data Feed Indicator
struct data_feed_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Financial Status Indicator: Identifies the financial status of the security
struct financial_status_indicator {
    enum class type : char {
        financial_status_not_applicable = '0',
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

// Finra Bbo Indicator: For FINRA ADF, represents the FINRA BBO state of the FINRA ADF quote
struct finra_bbo_indicator {
    enum class type : char {
        finra_bbo_indicator_not_applicable = ' ',
        no_finra_bbo_change = 'A',
        no_finra_bbo_exists = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Finra Bbo Luld Indicator: Indicates the effect that the Limit Up-Limit Down Price Bands have on the FINRA Best Bid and FINRA Best Offer
struct finra_bbo_luld_indicator {
    enum class type : char {
        limit_up_limit_down_not_applicable = ' ',
        finra_best_bid_and_finra_best_offer_are_executable = 'A',
        finra_best_bid_outside_price_band = 'B',
        finra_best_offer_outside_price_band = 'C',
        finra_best_bid_and_finra_best_offer_outside_price_band = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Finra Best Bid Market Maker Id: Contains the FINRA ADF provided FINRA Best Bid Market Maker identifier of the Market Maker that had the FINRA Best Bid
struct finra_best_bid_market_maker_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Finra Best Bid Price: Contains the FINRA ADF provided FINRA Best Bid Price that is the FINRA Best Bid
struct finra_best_bid_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Finra Best Bid Quote Condition: Contains the FINRA ADF provided FINRA Best Bid Quote Condition associated with the FINRA Best Bid Price that had the FINRA Best Bid
struct finra_best_bid_quote_condition {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Finra Best Bid Size: Contains the FINRA ADF provided FINRA Best Bid Size associated with the FINRA Best Bid Price that had the FINRA Best Bid
struct finra_best_bid_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Finra Best Offer Market Maker Id: Contains the FINRA ADF provided FINRA Best Offer Market Maker identifier of the Market Maker that had the FINRA Best Offer
struct finra_best_offer_market_maker_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Finra Best Offer Price: Contains the FINRA ADF provided FINRA Best Offer Price that is the FINRA Best Offer
struct finra_best_offer_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Finra Best Offer Quote Condition: Contains the FINRA ADF provided FINRA Best Offer Quote Condition associated with the FINRA Best Offer Price that had the FINRA Best Offer
struct finra_best_offer_quote_condition {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Finra Best Offer Size: Contains the FINRA ADF provided FINRA Best Offer Size associated with the FINRA Best Offer Price that had the FINRA Best Offer
struct finra_best_offer_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Finra Market Maker Id: Contains the FINRA Market Maker ID of the quoting participant on FINRA's Alternative Display Facility or the FINRA ADF Identifier 'FNRA'
struct finra_market_maker_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Halt Reason: Denotes the reason for the Trading Halt
struct halt_reason {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Instrument Type: Identifies the instrument type relevant to the quote
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

// Limit Up Limit Down Luld Indicator: Indicates the effect the Quote has on the Limit Up-Limit Down Price Band range
struct limit_up_limit_down_luld_indicator {
    enum class type : char {
        limit_up_limit_down_not_applicable = ' ',
        bid_price_above_upper_limit_price_band = 'A',
        offer_price_below_lower_limit_price_band = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Luld Leverage Ratio: Represents the Leverage ratio associated with the LULD Tier of the security symbol. Has implied 6 decimal places
struct luld_leverage_ratio {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

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

// Market Condition: Identifies the market condition of a quote for a security
struct market_condition {
    enum class type : char {
        normal_auction_market = ' ',
        crossed_market = 'A',
        locked_market = 'B',
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
        market_status = 'M',
        quote = 'Q',
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

// Mwcb Level 1: Identifies the daily established drop level value associated with Level 1 = 7% of Previous Close S&P 500 Value. Has implied 6 decimal places
struct mwcb_level_1 {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mwcb Level 2: Identifies the daily established drop level value associated with Level 2 = 13% of Previous Close S&P 500 Value. Has implied 6 decimal places
struct mwcb_level_2 {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mwcb Level 3: Identifies the daily established drop level value associated with Level 3 = 20% of Previous Close S&P 500 Value. Has implied 6 decimal places
struct mwcb_level_3 {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

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

// National Bbo Indicator: Indicates the effect the new quote has on the National BBO
struct national_bbo_indicator {
    enum class type : char {
        quote_not_included_in_bbo = ' ',
        no_best_bid_change_no_best_offer_change = 'A',
        no_best_bid_change_quote_contains_best_offer = 'B',
        no_best_bid_change_best_offer_short_appendage = 'C',
        no_best_bid_change_best_offer_long_appendage = 'D',
        no_best_bid_change_no_best_offer = 'E',
        quote_contains_best_bid_no_best_offer_change = 'F',
        quote_contains_best_bid_quote_contains_best_offer = 'G',
        quote_contains_best_bid_best_offer_short_appendage = 'H',
        quote_contains_best_bid_best_offer_long_appendage = 'I',
        quote_contains_best_bid_no_best_offer = 'J',
        no_best_bid_no_best_offer_change = 'K',
        no_best_bid_quote_contains_best_offer = 'L',
        no_best_bid_best_offer_short_appendage = 'M',
        no_best_bid_best_offer_long_appendage = 'N',
        no_best_bid_no_best_offer = 'O',
        best_bid_short_appendage_no_best_offer_change = 'P',
        best_bid_long_appendage_no_best_offer_change = 'Q',
        best_bid_short_appendage_quote_contains_best_offer = 'R',
        best_bid_long_appendage_quote_contains_best_offer = 'S',
        best_bid_short_appendage_best_offer_short_appendage = 'T',
        best_bid_long_appendage_best_offer_long_appendage = 'U',
        best_bid_short_appendage_no_best_offer = 'V',
        best_bid_long_appendage_no_best_offer = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// National Bbo Luld Indicator: Indicates the effect that the Limit Up-Limit Down Price Band changes have on the National Best Bid and National Best Offer
struct national_bbo_luld_indicator {
    enum class type : char {
        limit_up_limit_down_not_applicable = ' ',
        national_best_bid_andor_national_best_offer_are_executable = 'A',
        national_best_bid_below_lower_limit_price_band = 'B',
        national_best_offer_above_upper_limit_price_band = 'C',
        national_best_bid_below_lower_and_national_best_offer_above_upper_limit_price_band = 'D',
        national_best_bid_equals_upper_limit_price_band = 'E',
        national_best_offer_equals_lower_limit_price_band = 'F',
        national_best_bid_in_limit_state_and_national_best_offer_non_executable = 'G',
        national_best_bid_non_executable_and_national_best_offer_in_limit_state = 'H',
        national_best_bid_equals_upper_and_national_best_offer_equals_lower_limit_price_band = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Offer Price Long: Represents the lowest price acceptable to a prospective seller at a particular time for a security. Has implied 6 decimal places
struct offer_price_long {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Price Short: Represents the lowest price acceptable to a prospective seller at a particular time for a security. Has implied 2 decimal places
struct offer_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Price Upper Limit Price Band: Offer Price represents the lowest price acceptable to a prospective seller at a particular time for a security; Upper Limit Price Band represents the upper price band value when Security Status Indicator is Limit Up-Limit Down Price Band
struct offer_price_upper_limit_price_band {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Size Long: Identifies the number of shares for a symbol rounded down to the nearest multiple of its Round Lot Size
struct offer_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Size Short: Identifies the number of shares for a symbol rounded down to the nearest multiple of its Round Lot Size
struct offer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id: Identifies the Participant or Processor that generated the message
struct participant_id {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_omx_bx = 'B',
        nyse_national = 'C',
        finra_adf = 'D',
        n24x = 'G',
        miax = 'H',
        ise = 'I',
        cboe_edga = 'J',
        cboe_edgx = 'K',
        ltse = 'L',
        nyse_texas = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        cqs = 'S',
        nasdaq = 'T',
        memx = 'U',
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

// Primary Listing Market Participant Id: Identifies the Primary Listing Market for a security
struct primary_listing_market_participant_id {
    enum class type : char {
        primary_listing_market_participant_id_not_applicable = ' ',
        nyse_american = 'A',
        nasdaq_omx_bx = 'B',
        nyse_national = 'C',
        finra_adf = 'D',
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

// Primary Listing Market Previous Closing Price: Primary Listing Market Previous Closing Price. Has implied 6 decimal places
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

// Prior Security Symbol: Contains the prior security symbol, left justified, space filled
struct prior_security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Quote Condition: Denotes a particular condition applicable to the quote used to determine whether a quote qualifies for the Best Bid and Best Offer calculation
struct quote_condition {
    enum class type : char {
        quote_condition_not_applicable = ' ',
        slow_quote_on_offer_side = 'A',
        slow_quote_on_bid_side = 'B',
        closing = 'C',
        slow_quote_due_to_lrp_or_gap_quote_on_the_bid_side = 'E',
        slow_quote_due_to_lrp_or_gap_quote_on_the_offer_side = 'F',
        slow_quote_on_the_bid_and_offer_sides = 'H',
        closed_market_maker = 'L',
        non_firm_quote = 'N',
        opening_quote = 'O',
        regular = 'R',
        slow_quote_due_to_lrp_or_gap_quote_on_both_sides = 'U',
        slow_quote_due_to_set_slow_list_on_both_sides = 'W',
        on_demand_intra_day_auction = '4',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quote Message Type: Identifies the type of Quote message
struct quote_message_type {
    enum class type : char {
        auction_status = 'A',
        long_quote = 'L',
        short_quote = 'Q',
        special_long_quote = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Retail Interest Indicator: Identifies Retail Price Improvement interest priced better than the Protected Best Bid or Offer by a minimum of $0.001
struct retail_interest_indicator {
    enum class type : char {
        retail_interest_indicator_not_applicable = ' ',
        retail_interest_on_bid_quote = 'A',
        retail_interest_on_offer_quote = 'B',
        retail_interest_on_both_the_bid_and_offer_quotes = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Security Status Indicator: Reports trading suspensions, price indications, trading range indications, LULD Price Bands and Market Wide Circuit Breaker activity
struct security_status_indicator {
    enum class type : char {
        security_status_indicator_not_applicable = ' ',
        additional_information_requested = 'A',
        regulatory_concern = 'C',
        news_released = 'D',
        merger_effective = 'E',
        etf_component_prices_not_available = 'F',
        trading_range_indication = 'G',
        order_imbalance = 'I',
        limit_up_limit_down_trading_pause = 'M',
        corporate_action = 'N',
        new_security_offering = 'O',
        news_pending = 'P',
        intraday_indicative_value_not_available = 'V',
        resume = 'T',
        operational = 'X',
        sup_penny_trading = 'Y',
        reserved = 'Z',
        limit_up_limit_down_price_band = '0',
        market_wide_circuit_breaker_level_1_breached = '1',
        market_wide_circuit_breaker_level_2_breached = '2',
        market_wide_circuit_breaker_level_3_breached = '3',
        republished_limit_up_limit_down_price_band = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Symbol: Contains the security symbol. Left justified, space-filled
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Settlement Condition: Identifies the settlement condition for a security
struct settlement_condition {
    enum class type : char {
        regular_way_settlement = ' ',
        cash_settlement = 'A',
        next_day_settlement = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is in effect
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

// Sip Generated Message Identifier: Identifies CQS as the originator of a message
struct sip_generated_message_identifier {
    enum class type : char {
        sip_generated_message_not_applicable = ' ',
        consolidated_quotation_system = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Third Reserved: Space-filled. Field is reserved for future use
struct third_reserved {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Transaction Id: The Transaction ID will be populated by CQS and is Reserved for Internal Use only
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

// National Best Bid And Offer Short Appendage
struct national_best_bid_and_offer_short_appendage {
    static constexpr std::string_view name = "National Best Bid And Offer Short Appendage";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_bid_participant_id,
        best_bid_price_short,
        best_bid_size_short,
        best_offer_participant_id,
        best_offer_price_short,
        best_offer_size_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(best_bid_participant_id);
    CQSFIELD(best_bid_price_short);
    CQSFIELD(best_bid_size_short);
    CQSFIELD(best_offer_participant_id);
    CQSFIELD(best_offer_price_short);
    CQSFIELD(best_offer_size_short);
};

static_assert(sizeof(national_best_bid_and_offer_short_appendage) == national_best_bid_and_offer_short_appendage::size, "national_best_bid_and_offer_short_appendage lies over its bytes exactly");

// National Best Offer Short Appendage
struct national_best_offer_short_appendage {
    static constexpr std::string_view name = "National Best Offer Short Appendage";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_offer_participant_id,
        best_offer_price_short,
        best_offer_size_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(best_offer_participant_id);
    CQSFIELD(best_offer_price_short);
    CQSFIELD(best_offer_size_short);
};

static_assert(sizeof(national_best_offer_short_appendage) == national_best_offer_short_appendage::size, "national_best_offer_short_appendage lies over its bytes exactly");

// National Best Bid Short Appendage
struct national_best_bid_short_appendage {
    static constexpr std::string_view name = "National Best Bid Short Appendage";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_bid_participant_id,
        best_bid_price_short,
        best_bid_size_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(best_bid_participant_id);
    CQSFIELD(best_bid_price_short);
    CQSFIELD(best_bid_size_short);
};

static_assert(sizeof(national_best_bid_short_appendage) == national_best_bid_short_appendage::size, "national_best_bid_short_appendage lies over its bytes exactly");

// National Best Bid And Offer Long Appendage
struct national_best_bid_and_offer_long_appendage {
    static constexpr std::string_view name = "National Best Bid And Offer Long Appendage";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_bid_participant_id,
        best_bid_quote_condition,
        best_bid_price_long,
        best_bid_size_long,
        finra_best_bid_market_maker_id,
        best_offer_participant_id,
        best_offer_quote_condition,
        best_offer_price_long,
        best_offer_size_long,
        finra_best_offer_market_maker_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(best_bid_participant_id);
    CQSFIELD(best_bid_quote_condition);
    CQSFIELD(best_bid_price_long);
    CQSFIELD(best_bid_size_long);
    CQSFIELD(finra_best_bid_market_maker_id);
    CQSFIELD(best_offer_participant_id);
    CQSFIELD(best_offer_quote_condition);
    CQSFIELD(best_offer_price_long);
    CQSFIELD(best_offer_size_long);
    CQSFIELD(finra_best_offer_market_maker_id);
};

static_assert(sizeof(national_best_bid_and_offer_long_appendage) == national_best_bid_and_offer_long_appendage::size, "national_best_bid_and_offer_long_appendage lies over its bytes exactly");

// National Best Offer Long Appendage
struct national_best_offer_long_appendage {
    static constexpr std::string_view name = "National Best Offer Long Appendage";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_offer_participant_id,
        best_offer_quote_condition,
        best_offer_price_long,
        best_offer_size_long,
        finra_best_offer_market_maker_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(best_offer_participant_id);
    CQSFIELD(best_offer_quote_condition);
    CQSFIELD(best_offer_price_long);
    CQSFIELD(best_offer_size_long);
    CQSFIELD(finra_best_offer_market_maker_id);
};

static_assert(sizeof(national_best_offer_long_appendage) == national_best_offer_long_appendage::size, "national_best_offer_long_appendage lies over its bytes exactly");

// National Best Bid Long Appendage
struct national_best_bid_long_appendage {
    static constexpr std::string_view name = "National Best Bid Long Appendage";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_bid_participant_id,
        best_bid_quote_condition,
        best_bid_price_long,
        best_bid_size_long,
        finra_best_bid_market_maker_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(best_bid_participant_id);
    CQSFIELD(best_bid_quote_condition);
    CQSFIELD(best_bid_price_long);
    CQSFIELD(best_bid_size_long);
    CQSFIELD(finra_best_bid_market_maker_id);
};

static_assert(sizeof(national_best_bid_long_appendage) == national_best_bid_long_appendage::size, "national_best_bid_long_appendage lies over its bytes exactly");

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
    CQSFIELD(seconds);
    CQSFIELD(nanoseconds);
};

static_assert(sizeof(timestamp_2) == timestamp_2::size, "timestamp_2 lies over its bytes exactly");

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
    CQSFIELD(seconds);
    CQSFIELD(nanoseconds);
};

static_assert(sizeof(timestamp_1) == timestamp_1::size, "timestamp_1 lies over its bytes exactly");

// Special Long Quote Message Section 1
struct special_long_quote_message_section_1 {
    static constexpr std::string_view name = "Special Long Quote Message Section 1";
    static constexpr std::size_t size = 116;
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
        security_symbol,
        instrument_type,
        quote_condition,
        security_status_indicator,
        bid_price_long,
        bid_size_long,
        offer_price_long,
        offer_size_long,
        retail_interest_indicator,
        settlement_condition,
        market_condition,
        finra_market_maker_id,
        finra_best_bid_quote_condition,
        finra_best_bid_price,
        finra_best_bid_size,
        finra_best_bid_market_maker_id,
        finra_best_offer_quote_condition,
        finra_best_offer_price,
        finra_best_offer_size,
        finra_best_offer_market_maker_id,
        timestamp_2,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        sip_generated_message_identifier,
        finra_bbo_luld_indicator,
        national_bbo_luld_indicator,
        national_bbo_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(security_symbol);
    CQSFIELD(instrument_type);
    CQSFIELD(quote_condition);
    CQSFIELD(security_status_indicator);
    CQSFIELD(bid_price_long);
    CQSFIELD(bid_size_long);
    CQSFIELD(offer_price_long);
    CQSFIELD(offer_size_long);
    CQSFIELD(retail_interest_indicator);
    CQSFIELD(settlement_condition);
    CQSFIELD(market_condition);
    CQSFIELD(finra_market_maker_id);
    CQSFIELD(finra_best_bid_quote_condition);
    CQSFIELD(finra_best_bid_price);
    CQSFIELD(finra_best_bid_size);
    CQSFIELD(finra_best_bid_market_maker_id);
    CQSFIELD(finra_best_offer_quote_condition);
    CQSFIELD(finra_best_offer_price);
    CQSFIELD(finra_best_offer_size);
    CQSFIELD(finra_best_offer_market_maker_id);
    CQSFIELD(timestamp_2);
    CQSFIELD(short_sale_restriction_indicator);
    CQSFIELD(primary_listing_market_participant_id);
    CQSFIELD(financial_status_indicator);
    CQSFIELD(sip_generated_message_identifier);
    CQSFIELD(finra_bbo_luld_indicator);
    CQSFIELD(national_bbo_luld_indicator);
    CQSFIELD(national_bbo_indicator);
};

static_assert(sizeof(special_long_quote_message_section_1) == special_long_quote_message_section_1::size, "special_long_quote_message_section_1 lies over its bytes exactly");

// Special Long Quote Message: Used only by FINRA to report the FINRA Best Bid and FINRA Best Offer for their Market Makers for CTA eligible Equity, Local Issue or Bond information inclusive of changes to any existing FINRA BBO
struct special_long_quote_message {
    static constexpr std::string_view name = "Special Long Quote Message";
    static constexpr bool is_message = true;
};

// Short Quote Message Section 1
struct short_quote_message_section_1 {
    static constexpr std::string_view name = "Short Quote Message Section 1";
    static constexpr std::size_t size = 43;
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
        security_symbol,
        bid_price_short,
        bid_size_short,
        offer_price_short,
        offer_size_short,
        primary_listing_market_participant_id,
        national_bbo_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(security_symbol);
    CQSFIELD(bid_price_short);
    CQSFIELD(bid_size_short);
    CQSFIELD(offer_price_short);
    CQSFIELD(offer_size_short);
    CQSFIELD(primary_listing_market_participant_id);
    CQSFIELD(national_bbo_indicator);
};

static_assert(sizeof(short_quote_message_section_1) == short_quote_message_section_1::size, "short_quote_message_section_1 lies over its bytes exactly");

// Short Quote Message: Reports Bid and Offer quote information for CTA eligible Equity only if the quote meets all criteria and message format requirements
struct short_quote_message {
    static constexpr std::string_view name = "Short Quote Message";
    static constexpr bool is_message = true;
};

// Long Quote Message Section 1
struct long_quote_message_section_1 {
    static constexpr std::string_view name = "Long Quote Message Section 1";
    static constexpr std::size_t size = 83;
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
        security_symbol,
        instrument_type,
        quote_condition,
        security_status_indicator,
        bid_price_lower_limit_price_band,
        bid_size_long,
        offer_price_upper_limit_price_band,
        offer_size_long,
        retail_interest_indicator,
        settlement_condition,
        market_condition,
        finra_market_maker_id,
        finra_bbo_indicator,
        timestamp_2,
        short_sale_restriction_indicator,
        primary_listing_market_participant_id,
        financial_status_indicator,
        sip_generated_message_identifier,
        limit_up_limit_down_luld_indicator,
        national_bbo_luld_indicator,
        national_bbo_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(security_symbol);
    CQSFIELD(instrument_type);
    CQSFIELD(quote_condition);
    CQSFIELD(security_status_indicator);
    CQSFIELD(bid_price_lower_limit_price_band);
    CQSFIELD(bid_size_long);
    CQSFIELD(offer_price_upper_limit_price_band);
    CQSFIELD(offer_size_long);
    CQSFIELD(retail_interest_indicator);
    CQSFIELD(settlement_condition);
    CQSFIELD(market_condition);
    CQSFIELD(finra_market_maker_id);
    CQSFIELD(finra_bbo_indicator);
    CQSFIELD(timestamp_2);
    CQSFIELD(short_sale_restriction_indicator);
    CQSFIELD(primary_listing_market_participant_id);
    CQSFIELD(financial_status_indicator);
    CQSFIELD(sip_generated_message_identifier);
    CQSFIELD(limit_up_limit_down_luld_indicator);
    CQSFIELD(national_bbo_luld_indicator);
    CQSFIELD(national_bbo_indicator);
};

static_assert(sizeof(long_quote_message_section_1) == long_quote_message_section_1::size, "long_quote_message_section_1 lies over its bytes exactly");

// Long Quote Message: Reports quote data for a CTA eligible Equity, Local Issue or Bonds, including trading suspensions, price indications and trading range indications
struct long_quote_message {
    static constexpr std::string_view name = "Long Quote Message";
    static constexpr bool is_message = true;
};

// Auction Status Message: Used when a Participant in a CTA eligible security, Local Issue or Bonds reports requires Auction Information
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(security_symbol);
    CQSFIELD(instrument_type);
    CQSFIELD(auction_collar_reference_price);
    CQSFIELD(auction_collar_upper_threshold_price);
    CQSFIELD(auction_collar_lower_threshold_price);
    CQSFIELD(number_of_extensions);
    CQSFIELD(short_sale_restriction_indicator);
    CQSFIELD(primary_listing_market_participant_id);
    CQSFIELD(financial_status_indicator);
    CQSFIELD(reserved_62);
};

static_assert(sizeof(auction_status_message) == auction_status_message::size, "auction_status_message lies over its bytes exactly");

// Quote Message Payload: Branch
struct quote_message_payload {
    static constexpr std::string_view name = "Quote Message Payload";
    static constexpr bool is_message = false;
};

// Quote Message Section 1
struct quote_message_section_1 {
    static constexpr std::string_view name = "Quote Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        quote_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(quote_message_type);
};

static_assert(sizeof(quote_message_section_1) == quote_message_section_1::size, "quote_message_section_1 lies over its bytes exactly");

// Quote Message: Quote Category
struct quote_message {
    static constexpr std::string_view name = "Quote Message";
    static constexpr bool is_message = false;
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(market_wide_circuit_breaker_level_indicator);
    CQSFIELD(reserved);
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(mwcb_level_1);
    CQSFIELD(mwcb_level_2);
    CQSFIELD(mwcb_level_3);
    CQSFIELD(reserved);
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
    CQSFIELD(market_status_message_type);
};

static_assert(sizeof(market_status_message_section_1) == market_status_message_section_1::size, "market_status_message_section_1 lies over its bytes exactly");

// Market Status Message: Market Status Category
struct market_status_message {
    static constexpr std::string_view name = "Market Status Message";
    static constexpr bool is_message = false;
};

// End Of Day Message
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
};

static_assert(sizeof(end_of_day_message) == end_of_day_message::size, "end_of_day_message lies over its bytes exactly");

// Line Integrity Message
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
};

static_assert(sizeof(line_integrity_message) == line_integrity_message::size, "line_integrity_message lies over its bytes exactly");

// Disaster Recovery Data Center Activation Message
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
};

static_assert(sizeof(disaster_recovery_data_center_activation_message) == disaster_recovery_data_center_activation_message::size, "disaster_recovery_data_center_activation_message lies over its bytes exactly");

// Finra Open Message
struct finra_open_message {
    static constexpr std::string_view name = "Finra Open Message";
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
};

static_assert(sizeof(finra_open_message) == finra_open_message::size, "finra_open_message lies over its bytes exactly");

// Reset Block Sequence Number Message
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
};

static_assert(sizeof(reset_block_sequence_number_message) == reset_block_sequence_number_message::size, "reset_block_sequence_number_message lies over its bytes exactly");

// Finra Close Message
struct finra_close_message {
    static constexpr std::string_view name = "Finra Close Message";
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
};

static_assert(sizeof(finra_close_message) == finra_close_message::size, "finra_close_message lies over its bytes exactly");

// Start Of Day Message
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
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
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
    CQSFIELD(control_message_type);
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
        reserved,
        luld_tier,
        luld_leverage_ratio,
        test,
        ipo,
        financial_status_indicator,
        short_sale_restriction_indicator,
        halt_reason,
        instrument_type,
        second_reserved,
        third_reserved,
        reserved_128>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    CQSFIELD(participant_id);
    CQSFIELD(timestamp_1);
    CQSFIELD(message_id);
    CQSFIELD(transaction_id);
    CQSFIELD(participant_reference_number);
    CQSFIELD(security_symbol);
    CQSFIELD(prior_security_symbol);
    CQSFIELD(primary_listing_market_participant_id);
    CQSFIELD(primary_listing_market_previous_closing_price);
    CQSFIELD(consolidated_closing_price);
    CQSFIELD(round_lot_size);
    CQSFIELD(reserved);
    CQSFIELD(luld_tier);
    CQSFIELD(luld_leverage_ratio);
    CQSFIELD(test);
    CQSFIELD(ipo);
    CQSFIELD(financial_status_indicator);
    CQSFIELD(short_sale_restriction_indicator);
    CQSFIELD(halt_reason);
    CQSFIELD(instrument_type);
    CQSFIELD(second_reserved);
    CQSFIELD(third_reserved);
    CQSFIELD(reserved_128);
};

static_assert(sizeof(symbol_reference_data_message) == symbol_reference_data_message::size, "symbol_reference_data_message lies over its bytes exactly");

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
    CQSFIELD(administrative_message_type);
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
    CQSFIELD(message_length);
    CQSFIELD(message_category);
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
    CQSFIELD(seconds);
    CQSFIELD(nanoseconds);
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
    CQSFIELD(version);
    CQSFIELD(block_size);
    CQSFIELD(data_feed_indicator);
    CQSFIELD(retransmission_indicator);
    CQSFIELD(block_sequence_number);
    CQSFIELD(messages_in_block);
    CQSFIELD(sip_block_timestamp);
    CQSFIELD(block_checksum);
};

static_assert(sizeof(block_header) == block_header::size, "block_header lies over its bytes exactly");

// Packet: Cta Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    CQSSEQUENCE(message);
};

#pragma pack(pop)

} // namespace siac::cqs::output::cta::v2_10_a
