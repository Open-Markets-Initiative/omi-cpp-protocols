// Nasdaq NsmEquities Qbbo Itch 2.1 Template Meta Programming

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
#ifndef ITCHFIELD
#define ITCHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef ITCHSEQUENCE
#define ITCHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

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

// Authenticity: Denotes if an issue or quoting participant record is set-up in Nasdaq systems in a live/production, test, or demo state.
struct authenticity {
    enum class type : char {
        live_production = 'P',
        test = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Bid Price: Denotes the best bid price, or the highest price for market buy order(s) in the execution system.
struct best_bid_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Bid Size: Denotes the aggregated number of shares available for display within the execution system at the best bid price.
struct best_bid_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Price: Denotes the Nasdaq exchange's best offer price, or the lowest price for market sell order(s) in the execution system.
struct best_offer_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Size: Denotes the aggregated number of shares available for display within the execution system at the best offer price.
struct best_offer_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Breached Level: Denotes the MWCB Level that was breached.
struct breached_level {
    enum class type : char {
        level_1 = '1',
        level_2 = '2',
        level_3 = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Current Trading State: Reflects the current trading state for the issue.
struct current_trading_state {
    enum class type : char {
        halted_paused = 'H',
        quotation_only = 'Q',
        paused = 'P',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Etp Flag: Indicates whether the security is an exchange traded product (ETP).
struct etp_flag {
    enum class type : char {
        etp = 'Y',
        not_etp = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Etp Leverage Factor: Tracks the integral relationship of the ETP to the underlying index.
struct etp_leverage_factor {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code: Denotes the type of event for which the message is being generated.
struct event_code {
    enum class type : char {
        start_of_transmissions = 'O',
        start_of_system_hours = 'S',
        start_of_market_hours = 'Q',
        end_of_market_hours = 'M',
        end_of_system_hours = 'E',
        end_of_transmissions = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Financial Status Indicator: For Nasdaq-listed issues, this field indicates when a firm is not in compliance with Nasdaq continued listing requirements.
struct financial_status_indicator {
    enum class type : char {
        deficient = 'D',
        delinquent = 'E',
        bankrupt = 'Q',
        suspended = 'S',
        deficient_and_bankrupt = 'G',
        deficient_and_delinquent = 'H',
        delinquent_and_bankrupt = 'J',
        deficient_delinquent_and_bankrupt = 'K',
        creations_andor_redemptions_suspended = 'C',
        normal = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Interest Flag: Indicates the type of price improvement available
struct interest_flag {
    enum class type : char {
        buy_side = 'B',
        sell_side = 'S',
        both_sides = 'A',
        no_pi_available = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Inverse Indicator: Indicates the directional relationship between the ETP and underlying index.
struct inverse_indicator {
    enum class type : char {
        inverse_etp = 'Y',
        not_inverse_etp = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Flag: Indicates if the Nasdaq security is set up for IPO release.
struct ipo_flag {
    enum class type : char {
        ipo_security = 'Y',
        not_ipo_security = 'N',
        non_ipo_new_listed_security = 'Z',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Price: Denotes the IPO price to be used for intraday net change calculations.
struct ipo_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ipo Quotation Release Qualifier: Denotes the IPO release qualifier
struct ipo_quotation_release_qualifier {
    enum class type : char {
        anticipated_quotation_release_time = 'A',
        ipo_release_canceled_postponed = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Quotation Release Time: Denotes the IPO release time, in seconds since midnight, for quotation to the nearest second.
struct ipo_quotation_release_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Issue Classification: Identifies the security class for the issue as assigned by Nasdaq. See Appendix for allowable values.
struct issue_classification {
    enum class type : char {
        american_depositary_share = 'A',
        bond = 'B',
        common_stock = 'C',
        depository_receipt = 'F',
        sec_144_a = 'I',
        limited_partnership = 'L',
        notes = 'N',
        ordinary_share = 'O',
        preferred_stock = 'P',
        other_securities = 'Q',
        right = 'R',
        shares_of_beneficial_interest = 'S',
        convertible_debenture = 'T',
        unit = 'U',
        units_benif_int = 'V',
        warrant = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Issue Subtype: Identifies the security sub-type for the issue as assigned by Nasdaq. See Appendix for allowable values.
struct issue_subtype {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Level 1: Denotes the MWCB Level 1 Value.
struct level_1 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Level 2: Denotes the MWCB Level 2 Value.
struct level_2 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Level 3: Denotes the MWCB Level 3 Value.
struct level_3 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Luld Reference Price Tier: Indicates which Limit Up / Limit Down price band calculation parameter is to be used for the instrument.
struct luld_reference_price_tier {
    enum class type : char {
        tier_1_nms_stocks_and_select_et_ps = '1',
        tier_2_nms_stocks = '2',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Category: Indicates Listing market or listing market tier for the issue
struct market_category {
    enum class type : char {
        nasdaq_global_select_market = 'Q',
        nasdaq_global_market = 'G',
        nasdaq_capital_market = 'S',
        new_york_stock_exchange = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        nyse_texas = 'M',
        bats_bzx_exchange = 'Z',
        investors_exchange_llc = 'V',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Code: Identifies the applicable Nasdaq market center
struct market_code {
    enum class type : char {
        nasdaq = 'Q',
        nasdaq_texas = 'B',
        psx = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Count: Number of messages to follow this header
struct message_count {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Length of data message not including this field
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
    enum class type : char {
        system_event_message = 'S',
        stock_directory_message = 'R',
        stock_trading_action_message = 'H',
        reg_sho_restriction_message = 'Y',
        mwcb_decline_level_message = 'V',
        mwcb_breach_message = 'W',
        operational_halt_message = 'h',
        bbo_quotation_message = 'Q',
        price_improvement_message = 'N',
        ipo_quoting_period_update_message = 'K',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Operational Halt Action: Denotes the operational halt action
struct operational_halt_action {
    enum class type : char {
        halted = 'H',
        resumed = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reason: Reflects the Market Ops or MarketWatch code for the trading state change.
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reg Sho Action: Denotes the Reg SHO Short Sale Price Test Restriction status for the issue at the time of the message dissemination.
struct reg_sho_action {
    enum class type : char {
        no_price_test = '0',
        restriction_in_effect = '1',
        restriction_remains = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Round Lot Size: Indicates the number of shares that represent a round lot for the issue
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Round Lots Only: Indicates if Nasdaq system limits order entry for issue
struct round_lots_only {
    enum class type : char {
        round_lots_only = 'Y',
        no_restrictions = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Class: Indicates the primary listing market for the issue.
struct security_class {
    enum class type : char {
        nasdaq_listed_issue = 'Q',
        nyse = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        nyse_texas = 'M',
        bats = 'Z',
        iexg = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sequence Number: Sequence number of the first message to follow this header
struct sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session: Identity of the multicast session
struct session {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Short Sale Threshold Indicator: Indicates if a security is subject to mandatory close-out of short sales under SEC Rule 203(b)(3).
struct short_sale_threshold_indicator {
    enum class type : char {
        restricted = 'Y',
        not_restricted = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stock: Denotes the security symbol for the issue in the execution system.
struct stock {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Time Stamp: Timestamp
struct time_stamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Tracking: Nasdaq internal tracking number
struct tracking {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tracking Number: Nasdaq internal tracking number
struct tracking_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Ipo Quoting Period Update Message: Indicates the anticipated IPO quotation release time of a security.
struct ipo_quoting_period_update_message {
    static constexpr std::string_view name = "Ipo Quoting Period Update Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking,
        time_stamp,
        stock,
        ipo_quotation_release_time,
        ipo_quotation_release_qualifier,
        ipo_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(ipo_quotation_release_time);
    ITCHFIELD(ipo_quotation_release_qualifier);
    ITCHFIELD(ipo_price);
};

static_assert(sizeof(ipo_quoting_period_update_message) == ipo_quoting_period_update_message::size, "ipo_quoting_period_update_message lies over its bytes exactly");

// Price Improvement Message: Indicates a retail interest indication of the Bid, Ask or both the Bid and Ask for Nasdaq-listed securities.
struct price_improvement_message {
    static constexpr std::string_view name = "Price Improvement Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking,
        time_stamp,
        stock,
        interest_flag>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(interest_flag);
};

static_assert(sizeof(price_improvement_message) == price_improvement_message::size, "price_improvement_message lies over its bytes exactly");

// Bbo Quotation Message: BBO products will broadcast a real-time update every time that the exchange's best bid and offer quote is updated during the trading day.
struct bbo_quotation_message {
    static constexpr std::string_view name = "Bbo Quotation Message";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        stock,
        security_class,
        best_bid_price,
        best_bid_size,
        best_offer_price,
        best_offer_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(security_class);
    ITCHFIELD(best_bid_price);
    ITCHFIELD(best_bid_size);
    ITCHFIELD(best_offer_price);
    ITCHFIELD(best_offer_size);
};

static_assert(sizeof(bbo_quotation_message) == bbo_quotation_message::size, "bbo_quotation_message lies over its bytes exactly");

// Operational Halt Message: The Exchange uses this message to indicate the current Operational Status of a security to the trading community.
struct operational_halt_message {
    static constexpr std::string_view name = "Operational Halt Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        stock,
        market_code,
        operational_halt_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(market_code);
    ITCHFIELD(operational_halt_action);
};

static_assert(sizeof(operational_halt_message) == operational_halt_message::size, "operational_halt_message lies over its bytes exactly");

// Mwcb Breach Message: Informs data recipients when a MWCB has breached one of the established levels
struct mwcb_breach_message {
    static constexpr std::string_view name = "Mwcb Breach Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        breached_level>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(breached_level);
};

static_assert(sizeof(mwcb_breach_message) == mwcb_breach_message::size, "mwcb_breach_message lies over its bytes exactly");

// Mwcb Decline Level Message: Informs data recipients what the daily MWCB breach points are set to for the current trading day.
struct mwcb_decline_level_message {
    static constexpr std::string_view name = "Mwcb Decline Level Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        level_1,
        level_2,
        level_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(level_1);
    ITCHFIELD(level_2);
    ITCHFIELD(level_3);
};

static_assert(sizeof(mwcb_decline_level_message) == mwcb_decline_level_message::size, "mwcb_decline_level_message lies over its bytes exactly");

// Reg Sho Restriction Message: Nasdaq introduced the Reg SHO Short Sale Price Test Restricted Indicator message format.
struct reg_sho_restriction_message {
    static constexpr std::string_view name = "Reg Sho Restriction Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        stock,
        reg_sho_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(reg_sho_action);
};

static_assert(sizeof(reg_sho_restriction_message) == reg_sho_restriction_message::size, "reg_sho_restriction_message lies over its bytes exactly");

// Stock Trading Action Message: Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community.
struct stock_trading_action_message {
    static constexpr std::string_view name = "Stock Trading Action Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        stock,
        security_class,
        current_trading_state,
        reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(security_class);
    ITCHFIELD(current_trading_state);
    ITCHFIELD(reason);
};

static_assert(sizeof(stock_trading_action_message) == stock_trading_action_message::size, "stock_trading_action_message lies over its bytes exactly");

// Stock Directory Message: At the start of each trading day, Nasdaq disseminates stock directory messages for all active symbols in its market center system.
struct stock_directory_message {
    static constexpr std::string_view name = "Stock Directory Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        stock,
        market_category,
        financial_status_indicator,
        round_lot_size,
        round_lots_only,
        issue_classification,
        issue_subtype,
        authenticity,
        short_sale_threshold_indicator,
        ipo_flag,
        luld_reference_price_tier,
        etp_flag,
        etp_leverage_factor,
        inverse_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(stock);
    ITCHFIELD(market_category);
    ITCHFIELD(financial_status_indicator);
    ITCHFIELD(round_lot_size);
    ITCHFIELD(round_lots_only);
    ITCHFIELD(issue_classification);
    ITCHFIELD(issue_subtype);
    ITCHFIELD(authenticity);
    ITCHFIELD(short_sale_threshold_indicator);
    ITCHFIELD(ipo_flag);
    ITCHFIELD(luld_reference_price_tier);
    ITCHFIELD(etp_flag);
    ITCHFIELD(etp_leverage_factor);
    ITCHFIELD(inverse_indicator);
};

static_assert(sizeof(stock_directory_message) == stock_directory_message::size, "stock_directory_message lies over its bytes exactly");

// System Event Message: The System Event message is used to signal key market or data feed control events.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        tracking_number,
        time_stamp,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tracking_number);
    ITCHFIELD(time_stamp);
    ITCHFIELD(event_code);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Mold Udp 64 Message Header
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(message_length);
    ITCHFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Mold Udp64 Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// End Of Session
struct end_of_session {
    static constexpr std::string_view name = "End Of Session";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
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
    ITCHSEQUENCE(message);
};

// Packet Header: Itch Mold Udp 64 Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        session,
        sequence_number,
        message_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(session);
    ITCHFIELD(sequence_number);
    ITCHFIELD(message_count);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Itch Mold Udp 64 Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
