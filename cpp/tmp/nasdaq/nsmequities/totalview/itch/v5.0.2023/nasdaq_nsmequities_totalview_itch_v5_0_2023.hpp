// Nasdaq NsmEquities TotalView Itch 5.0.2023 Template Meta Programming

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

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

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

// Accepted Sequence Number: The sequence number in ASCII of the next Sequenced Message to be sent. Left padded with spaces.
struct accepted_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::number<type>(raw(), fill); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::string_view raw() const noexcept { return tmp::trimmed_front(value_, fill); }

  protected:
    std::array<char, 20> value_;
};

// Accepted Session: The session ID of the session that is now logged into. Left padded with spaces.
struct accepted_session {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed_front(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Attribution: Nasdaq market participant identifier associated with the entered order
struct attribution {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Auction Collar Extension: Indicates the number of extensions to the Reopening Auction
struct auction_collar_extension {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Collar Reference Price: Reference price used to set the auction collars
struct auction_collar_reference_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Authenticity: Denotes if an issue or quoting participant record is set-up in NASDAQ systems in a live/production, test, or demo state
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

// Breached Level: Denotes the MWCB Level that was breached
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

// Buy Sell Indicator: The type of order being added
struct buy_sell_indicator {
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

// Canceled Shares: The number of shares being removed from the display size of the order as the result of a cancellation
struct canceled_shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Client Packet Type: Code identifying this packet type sent by the client
struct client_packet_type {
    enum class type : char {
        debug_packet = '+',
        login_request_packet = 'L',
        unsequenced_data_packet = 'U',
        client_heartbeat_packet = 'R',
        logout_request_packet = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Cross Price: The price at which the cross occurred
struct cross_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Shares: The number of shares matched in the Nasdaq Cross
struct cross_shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Type: The Nasdaq cross session for which the message is being generated
struct cross_type {
    enum class type : char {
        opening = 'O',
        closing = 'C',
        halted_or_paused = 'H',
        extended_close = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Current Reference Price: The price at which the NOII shares are being calculated
struct current_reference_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Debug Text: Free form human readable text
struct debug_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr debug_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Etp Flag: Indicates whether the security is an exchange traded product
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

// Etp Leverage Factor: Tracks the integral relationship of the ETP to the underlying index
struct etp_leverage_factor {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code: System Event Codes
struct event_code {
    enum class type : char {
        start_of_messages = 'O',
        start_of_system_hours = 'S',
        start_of_market_hours = 'Q',
        end_of_market_hours = 'M',
        end_of_system_hours = 'E',
        end_of_messages = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Shares: The number of shares executed
struct executed_shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Execution Price: The price at which the order execution occurred
struct execution_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Far Price: A hypothetical auction-clearing price for cross orders only
struct far_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Financial Status Indicator: Indicates when a firm is not in compliance with NASDAQ continued listing requirements
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
        creations_and_redemptions_suspended = 'C',
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

// Imbalance Direction: The market side of the order imbalance
struct imbalance_direction {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        none = 'N',
        insufficient_orders = 'O',
        paused = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Shares: The number of shares not paired at the Current Reference Price
struct imbalance_shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Interest Flag
struct interest_flag {
    enum class type : char {
        buy_side = 'B',
        sell_side = 'S',
        both_sides = 'A',
        no_rpi_orders_available = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Inverse Indicator: Indicates the directional relationship between the ETP and underlying index. Example: An ETP Leverage Factor of 3 and an Inverse value of 'Y' indicates the ETP will decrease by a value of 3.
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

// Ipo Flag: Indicates if the NASDAQ security is set up for IPO release
struct ipo_flag {
    enum class type : char {
        set_up_for_ipo_release = 'Y',
        not_set_up_for_ipo_release = 'N',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Price: Denotes the IPO price to be used for intraday net change calculations
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

// Ipo Quotation Release Qualifier
struct ipo_quotation_release_qualifier {
    enum class type : char {
        anticipated_quotation_release_time = 'A',
        ipo_release_canceled_or_postponed = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ipo Quotation Release Time: Denotes the IPO release time, in seconds since midnight, for quotation to the nearest second
struct ipo_quotation_release_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Issue Classification: Identifies the security class for the issue as assigned by NASDAQ
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
        units_of_beneficial_interest = 'V',
        warrant = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Issue Sub Type: Identifies the security sub-type for the issue as assigned by NASDAQ
struct issue_sub_type {
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

// Locate Code: Locate code identifying the security
struct locate_code {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lower Auction Collar Price: Indicates the price of the lower auction collar threshold
struct lower_auction_collar_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lower Price Range Collar: Indicates the price of the Lower Auction Collar Threshold
struct lower_price_range_collar {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Luld Reference Price Tier: Indicates which Limit Up / Limit Down price band calculation parameter is to be used for the instrument
struct luld_reference_price_tier {
    enum class type : char {
        tier_1 = '1',
        tier_2 = '2',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Category: Indicates listing market or listing market tier for the issue
struct market_category {
    enum class type : char {
        nasdaq_global_select_market = 'Q',
        nasdaq_global_market = 'G',
        nasdaq_capital_market = 'S',
        nyse = 'N',
        nyse_american = 'A',
        nyse_arca = 'P',
        bats_z = 'Z',
        investors_exchange = 'V',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Code
struct market_code {
    enum class type : char {
        nasdaq = 'Q',
        bx = 'B',
        psx = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Maker Mode: Indicates the quoting participant's registration status in relation to SEC Rules 101 and 104 of Regulation M
struct market_maker_mode {
    enum class type : char {
        normal = 'N',
        passive = 'P',
        syndicate = 'S',
        pre_syndicate = 'R',
        penalty = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Participant State: Indicates the market participant's current registration status in the issue
struct market_participant_state {
    enum class type : char {
        active = 'A',
        excused = 'E',
        withdrawn = 'W',
        suspended = 'S',
        deleted = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Number: The Nasdaq generated day-unique Match Number of this execution
struct match_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maximum Allowable Price: 80% above Registration Statement Highest Price
struct maximum_allowable_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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
        reg_sho_short_sale_price_test_restricted_indicator_message = 'Y',
        market_participant_position_message = 'L',
        mwcb_decline_level_message = 'V',
        mwcb_status_level_message = 'W',
        ipo_quoting_period_update = 'K',
        luld_auction_collar_message = 'J',
        operational_halt_message = 'h',
        add_order_no_mpid_attribution_message = 'A',
        add_order_with_mpid_attribution_message = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        order_delete_message = 'D',
        order_replace_message = 'U',
        non_cross_trade_message = 'P',
        cross_trade_message = 'Q',
        broken_trade_message = 'B',
        net_order_imbalance_indicator_message = 'I',
        retail_price_improvement_indicator_message = 'N',
        direct_listing_with_capital_raise_price_discovery_message = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Minimum Allowable Price: 20% below Registration Statement Lower Price
struct minimum_allowable_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mpid: Denotes the market participant identifier for which the position message is being generated
struct mpid {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Near Execution Price: The current reference price when the DLCR volatility test has successfully passed
struct near_execution_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Near Execution Time: The time at which the Near Execution Price was determined
struct near_execution_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Near Price: A hypothetical auction-clearing price for cross orders as well as continuous orders
struct near_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New Order Reference Number: The new reference number for this order at time of replacement
struct new_order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Eligibility Status: Indicates if the security is eligible to be released for trading
struct open_eligibility_status {
    enum class type : char {
        not_eligible = 'N',
        eligible = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Operational Halt Action: Indicates the operational halt action for the security
struct operational_halt_action {
    enum class type : char {
        halted = 'H',
        trading_resumed = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Reference Number: The unique reference number assigned to the new order at the time of receipt
struct order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Order Reference Number: The original reference number of the order being replaced
struct original_order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Length: Length of data message not including this field
struct packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Shares: The total number of shares that are eligible to be matched at the Current Reference Price
struct paired_shares {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Password: Login password
struct password {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Price: The display price of the new order
struct price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Variation Indicator: Indicates the absolute value of the percentage of deviation of the Near Indicative Clearing Price to the nearest Current Reference Price
struct price_variation_indicator {
    enum class type : char {
        less_than_1_percent = 'L',
        less_than_2_percent = '1',
        less_than_3_percent = '2',
        less_than_4_percent = '3',
        less_than_5_percent = '4',
        less_than_6_percent = '5',
        less_than_7_percent = '6',
        less_than_8_percent = '7',
        less_than_9_percent = '8',
        less_than_10_percent = '9',
        less_than_20_percent = 'A',
        less_than_30_percent = 'B',
        more_than_30_percent = 'C',
        not_available = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Primary Market Maker: Indicates if the market participant firm qualifies as a Primary Market Maker in accordance with NASDAQ marketplace rules
struct primary_market_maker {
    enum class type : char {
        primary = 'Y',
        non_primary = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Printable: Indicates if the execution should be reflected on time and sale displays and volume calculations
struct printable {
    enum class type : char {
        no = 'N',
        yes = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reason Code: Trading Action reason
struct reason_code {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reg Sho Action: Denotes the Reg SHO Short Sale Price Test Restriction status for the issue at the time of the message dissemination
struct reg_sho_action {
    enum class type : char {
        no_price_test = '0',
        reg_sho_short_sale_price_test_restriction = '1',
        test_restriction_remains = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reject Reason Code: Login Reject Codes
struct reject_reason_code {
    enum class type : char {
        not_authorized = 'A',
        session_not_available = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Requested Sequence Number: Specifies the next sequence number in ASCII the client wants to receive upon connection, or 0 to start receiving the most recently generated message.
struct requested_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::number<type>(raw(), fill); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::string_view raw() const noexcept { return tmp::trimmed_front(value_, fill); }

  protected:
    std::array<char, 20> value_;
};

// Requested Session: Specifies the session the client would like to log into, or all blanks to log into the currently active session.
struct requested_session {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed_front(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Reserved
struct reserved {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Round Lot Size: Denotes the number of shares that represent a round lot for the issue
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

// Sequenced Message Type: Value identifying sequenced message type
struct sequenced_message_type {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Server Packet Type: Code identifying this packet type sent by the server
struct server_packet_type {
    enum class type : char {
        debug_packet = '+',
        login_accepted_packet = 'A',
        login_rejected_packet = 'J',
        sequenced_data_packet = 'S',
        server_heartbeat_packet = 'H',
        end_of_session_packet = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Shares: The total number of shares associated with the order being added to the book
struct shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
struct stock {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Stock Locate: Locate Code uniquely assigned to the security symbol for the day
struct stock_locate {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Timestamp: Nanoseconds since midnight
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
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

// Trading State: Indicates the current trading state for the stock
struct trading_state {
    enum class type : char {
        halted = 'H',
        paused = 'P',
        quotation_only_period = 'Q',
        trading = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Unsequenced Message: The unsequenced (client to server) message carried by the packet, opaque bytes unless an application source dispatches it
struct unsequenced_message {
    using type = std::span<const std::byte>;
    static constexpr bool dynamic = true;

    constexpr unsequenced_message(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { data_, length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Unsequenced Message Type: Value identifying unsequenced message type
struct unsequenced_message_type {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Upper Auction Collar Price: Indicates the price of the upper auction collar threshold
struct upper_auction_collar_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Upper Price Range Collar: Indicates the price of the Upper Auction Collar Threshold
struct upper_price_range_collar {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Username: Session username
struct username {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Direct Listing With Capital Raise Price Discovery Message: This message is disseminated only for Direct Listing with Capital Raise (DLCR) securities
struct direct_listing_with_capital_raise_price_discovery_message {
    static constexpr std::string_view name = "Direct Listing With Capital Raise Price Discovery Message";
    static constexpr std::size_t size = 47;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        open_eligibility_status,
        minimum_allowable_price,
        maximum_allowable_price,
        near_execution_price,
        near_execution_time,
        lower_price_range_collar,
        upper_price_range_collar>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(open_eligibility_status);
    ITCHFIELD(minimum_allowable_price);
    ITCHFIELD(maximum_allowable_price);
    ITCHFIELD(near_execution_price);
    ITCHFIELD(near_execution_time);
    ITCHFIELD(lower_price_range_collar);
    ITCHFIELD(upper_price_range_collar);
};

static_assert(sizeof(direct_listing_with_capital_raise_price_discovery_message) == direct_listing_with_capital_raise_price_discovery_message::size, "direct_listing_with_capital_raise_price_discovery_message lies over its bytes exactly");

// Retail Price Improvement Indicator Message: Identifies a retail interest indication of the Bid, Ask or both the Bid and Ask for NASDAQ-listed securities.
struct retail_price_improvement_indicator_message {
    static constexpr std::string_view name = "Retail Price Improvement Indicator Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        interest_flag>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(interest_flag);
};

static_assert(sizeof(retail_price_improvement_indicator_message) == retail_price_improvement_indicator_message::size, "retail_price_improvement_indicator_message lies over its bytes exactly");

// Net Order Imbalance Indicator Message: NASDAQ disseminates NOII data
struct net_order_imbalance_indicator_message {
    static constexpr std::string_view name = "Net Order Imbalance Indicator Message";
    static constexpr std::size_t size = 49;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        paired_shares,
        imbalance_shares,
        imbalance_direction,
        stock,
        far_price,
        near_price,
        current_reference_price,
        cross_type,
        price_variation_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(paired_shares);
    ITCHFIELD(imbalance_shares);
    ITCHFIELD(imbalance_direction);
    ITCHFIELD(stock);
    ITCHFIELD(far_price);
    ITCHFIELD(near_price);
    ITCHFIELD(current_reference_price);
    ITCHFIELD(cross_type);
    ITCHFIELD(price_variation_indicator);
};

static_assert(sizeof(net_order_imbalance_indicator_message) == net_order_imbalance_indicator_message::size, "net_order_imbalance_indicator_message lies over its bytes exactly");

// Broken Trade Message: The Broken Trade Message is sent whenever an execution on Nasdaq is broken
struct broken_trade_message {
    static constexpr std::string_view name = "Broken Trade Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(match_number);
};

static_assert(sizeof(broken_trade_message) == broken_trade_message::size, "broken_trade_message lies over its bytes exactly");

// Cross Trade Message: Cross Trade message indicates that Nasdaq has completed its cross process for a specific security
struct cross_trade_message {
    static constexpr std::string_view name = "Cross Trade Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        cross_shares,
        stock,
        cross_price,
        match_number,
        cross_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(cross_shares);
    ITCHFIELD(stock);
    ITCHFIELD(cross_price);
    ITCHFIELD(match_number);
    ITCHFIELD(cross_type);
};

static_assert(sizeof(cross_trade_message) == cross_trade_message::size, "cross_trade_message lies over its bytes exactly");

// Non Cross Trade Message: Trade Messages should be included in NASDAQ time-and-sales displays as well as volume and other market statistics
struct non_cross_trade_message {
    static constexpr std::string_view name = "Non Cross Trade Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number,
        buy_sell_indicator,
        shares,
        stock,
        price,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(buy_sell_indicator);
    ITCHFIELD(shares);
    ITCHFIELD(stock);
    ITCHFIELD(price);
    ITCHFIELD(match_number);
};

static_assert(sizeof(non_cross_trade_message) == non_cross_trade_message::size, "non_cross_trade_message lies over its bytes exactly");

// Order Replace Message: This message is sent whenever an order on the book has been cancel-replaced
struct order_replace_message {
    static constexpr std::string_view name = "Order Replace Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        original_order_reference_number,
        new_order_reference_number,
        shares,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(original_order_reference_number);
    ITCHFIELD(new_order_reference_number);
    ITCHFIELD(shares);
    ITCHFIELD(price);
};

static_assert(sizeof(order_replace_message) == order_replace_message::size, "order_replace_message lies over its bytes exactly");

// Order Delete Message: This message is sent whenever an order on the book is being cancelled
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Order Cancel Message: This message is sent whenever an order on the book is modified as a result of a partial cancellation
struct order_cancel_message {
    static constexpr std::string_view name = "Order Cancel Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number,
        canceled_shares>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(canceled_shares);
};

static_assert(sizeof(order_cancel_message) == order_cancel_message::size, "order_cancel_message lies over its bytes exactly");

// Order Executed With Price Message: This message is sent whenever an order on the book is executed in whole or in part at a price different from the initial display price
struct order_executed_with_price_message {
    static constexpr std::string_view name = "Order Executed With Price Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number,
        executed_shares,
        match_number,
        printable,
        execution_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(executed_shares);
    ITCHFIELD(match_number);
    ITCHFIELD(printable);
    ITCHFIELD(execution_price);
};

static_assert(sizeof(order_executed_with_price_message) == order_executed_with_price_message::size, "order_executed_with_price_message lies over its bytes exactly");

// Order Executed Message: This message is sent whenever an order on the book is executed in whole or in part
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number,
        executed_shares,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(executed_shares);
    ITCHFIELD(match_number);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Add Order With Mpid Attribution Message: This message will be generated for attributed orders and quotations accepted by the Nasdaq system
struct add_order_with_mpid_attribution_message {
    static constexpr std::string_view name = "Add Order With Mpid Attribution Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number,
        buy_sell_indicator,
        shares,
        stock,
        price,
        attribution>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(buy_sell_indicator);
    ITCHFIELD(shares);
    ITCHFIELD(stock);
    ITCHFIELD(price);
    ITCHFIELD(attribution);
};

static_assert(sizeof(add_order_with_mpid_attribution_message) == add_order_with_mpid_attribution_message::size, "add_order_with_mpid_attribution_message lies over its bytes exactly");

// Add Order No Mpid Attribution Message: This message will be generated for unattributed orders accepted by the Nasdaq system
struct add_order_no_mpid_attribution_message {
    static constexpr std::string_view name = "Add Order No Mpid Attribution Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        order_reference_number,
        buy_sell_indicator,
        shares,
        stock,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(buy_sell_indicator);
    ITCHFIELD(shares);
    ITCHFIELD(stock);
    ITCHFIELD(price);
};

static_assert(sizeof(add_order_no_mpid_attribution_message) == add_order_no_mpid_attribution_message::size, "add_order_no_mpid_attribution_message lies over its bytes exactly");

// Operational Halt Message: An Operational Halt means that there has been an interruption of service on the identified security impacting only the designated Market Center
struct operational_halt_message {
    static constexpr std::string_view name = "Operational Halt Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        market_code,
        operational_halt_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(market_code);
    ITCHFIELD(operational_halt_action);
};

static_assert(sizeof(operational_halt_message) == operational_halt_message::size, "operational_halt_message lies over its bytes exactly");

// Luld Auction Collar Message: Indicates the auction collar thresholds within which a paused security can reopen following a LULD trading pause
struct luld_auction_collar_message {
    static constexpr std::string_view name = "Luld Auction Collar Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        auction_collar_reference_price,
        upper_auction_collar_price,
        lower_auction_collar_price,
        auction_collar_extension>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(auction_collar_reference_price);
    ITCHFIELD(upper_auction_collar_price);
    ITCHFIELD(lower_auction_collar_price);
    ITCHFIELD(auction_collar_extension);
};

static_assert(sizeof(luld_auction_collar_message) == luld_auction_collar_message::size, "luld_auction_collar_message lies over its bytes exactly");

// Ipo Quoting Period Update: Indicates the anticipated IPO quotation release time of a security.
struct ipo_quoting_period_update {
    static constexpr std::string_view name = "Ipo Quoting Period Update";
    static constexpr std::size_t size = 27;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        ipo_quotation_release_time,
        ipo_quotation_release_qualifier,
        ipo_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(ipo_quotation_release_time);
    ITCHFIELD(ipo_quotation_release_qualifier);
    ITCHFIELD(ipo_price);
};

static_assert(sizeof(ipo_quoting_period_update) == ipo_quoting_period_update::size, "ipo_quoting_period_update lies over its bytes exactly");

// Mwcb Status Level Message: Informs data recipients when a MWCB has breached one of the established levels
struct mwcb_status_level_message {
    static constexpr std::string_view name = "Mwcb Status Level Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        breached_level>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(breached_level);
};

static_assert(sizeof(mwcb_status_level_message) == mwcb_status_level_message::size, "mwcb_status_level_message lies over its bytes exactly");

// Mwcb Decline Level Message: Informs data recipients what the daily MWCB breach points are set to for the current trading day.
struct mwcb_decline_level_message {
    static constexpr std::string_view name = "Mwcb Decline Level Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        level_1,
        level_2,
        level_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(level_1);
    ITCHFIELD(level_2);
    ITCHFIELD(level_3);
};

static_assert(sizeof(mwcb_decline_level_message) == mwcb_decline_level_message::size, "mwcb_decline_level_message lies over its bytes exactly");

// Market Participant Position Message: Nasdaq will send out this message only if Nasdaq Operations changes the status of a market participant firm in an issue
struct market_participant_position_message {
    static constexpr std::string_view name = "Market Participant Position Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        mpid,
        stock,
        primary_market_maker,
        market_maker_mode,
        market_participant_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(mpid);
    ITCHFIELD(stock);
    ITCHFIELD(primary_market_maker);
    ITCHFIELD(market_maker_mode);
    ITCHFIELD(market_participant_state);
};

static_assert(sizeof(market_participant_position_message) == market_participant_position_message::size, "market_participant_position_message lies over its bytes exactly");

// Reg Sho Short Sale Price Test Restricted Indicator Message: Nasaq processes orders based on the most Reg SHO Restriction status value
struct reg_sho_short_sale_price_test_restricted_indicator_message {
    static constexpr std::string_view name = "Reg Sho Short Sale Price Test Restricted Indicator Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        locate_code,
        tracking_number,
        timestamp,
        stock,
        reg_sho_action>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(locate_code);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(reg_sho_action);
};

static_assert(sizeof(reg_sho_short_sale_price_test_restricted_indicator_message) == reg_sho_short_sale_price_test_restricted_indicator_message::size, "reg_sho_short_sale_price_test_restricted_indicator_message lies over its bytes exactly");

// Stock Trading Action Message: Nasdaq uses this administrative message to indicate the current trading status of a security to the trading community
struct stock_trading_action_message {
    static constexpr std::string_view name = "Stock Trading Action Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        trading_state,
        reserved,
        reason_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(trading_state);
    ITCHFIELD(reserved);
    ITCHFIELD(reason_code);
};

static_assert(sizeof(stock_trading_action_message) == stock_trading_action_message::size, "stock_trading_action_message lies over its bytes exactly");

// Stock Directory Message: Market data redistributors should process this message to populate the Financial Status Indicator (required display field) and the Market Category (recommended display field) for NASDAQ-listed issues.
struct stock_directory_message {
    static constexpr std::string_view name = "Stock Directory Message";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        stock,
        market_category,
        financial_status_indicator,
        round_lot_size,
        round_lots_only,
        issue_classification,
        issue_sub_type,
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
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
    ITCHFIELD(stock);
    ITCHFIELD(market_category);
    ITCHFIELD(financial_status_indicator);
    ITCHFIELD(round_lot_size);
    ITCHFIELD(round_lots_only);
    ITCHFIELD(issue_classification);
    ITCHFIELD(issue_sub_type);
    ITCHFIELD(authenticity);
    ITCHFIELD(short_sale_threshold_indicator);
    ITCHFIELD(ipo_flag);
    ITCHFIELD(luld_reference_price_tier);
    ITCHFIELD(etp_flag);
    ITCHFIELD(etp_leverage_factor);
    ITCHFIELD(inverse_indicator);
};

static_assert(sizeof(stock_directory_message) == stock_directory_message::size, "stock_directory_message lies over its bytes exactly");

// System Event Message: The system event message type is used to signal a market or data feed handler event
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stock_locate,
        tracking_number,
        timestamp,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(stock_locate);
    ITCHFIELD(tracking_number);
    ITCHFIELD(timestamp);
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

// Server Heartbeat
struct server_heartbeat {
    static constexpr std::string_view name = "Server Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Sequenced Message: The sequenced (server to client) message carried by the packet, opaque bytes unless an application source dispatches it
struct sequenced_message {
    static constexpr std::string_view name = "Sequenced Message";
    static constexpr bool is_message = false;
};

// Sequenced Data Packet Section 1
struct sequenced_data_packet_section_1 {
    static constexpr std::string_view name = "Sequenced Data Packet Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequenced_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(sequenced_message_type);
};

static_assert(sizeof(sequenced_data_packet_section_1) == sequenced_data_packet_section_1::size, "sequenced_data_packet_section_1 lies over its bytes exactly");

// Sequenced Data Packet: The Sequenced Data Packets act as an envelope to carry the actual sequenced data messages that are transferred from the server to the client. Each Sequenced Data Packet carries one message from the higher-lever protocol
struct sequenced_data_packet {
    static constexpr std::string_view name = "Sequenced Data Packet";
    static constexpr bool is_message = false;
};

// Login Rejected Packet: The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from the client
struct login_rejected_packet {
    static constexpr std::string_view name = "Login Rejected Packet";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reject_reason_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(reject_reason_code);
};

static_assert(sizeof(login_rejected_packet) == login_rejected_packet::size, "login_rejected_packet lies over its bytes exactly");

// Login Accepted Packet: The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login Request from the client
struct login_accepted_packet {
    static constexpr std::string_view name = "Login Accepted Packet";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        accepted_session,
        accepted_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(accepted_session);
    ITCHFIELD(accepted_sequence_number);
};

static_assert(sizeof(login_accepted_packet) == login_accepted_packet::size, "login_accepted_packet lies over its bytes exactly");

// Debug Packet: Debug packets are intended to provide human readable text that may aid in debugging problems
struct debug_packet {
    static constexpr std::string_view name = "Debug Packet";
    static constexpr bool is_message = true;
};

// Server Payload: Branch
struct server_payload {
    static constexpr std::string_view name = "Server Payload";
    static constexpr bool is_message = false;
};

// Server Packet Header: Packet header of a packet sent by the server
struct server_packet_header {
    static constexpr std::string_view name = "Server Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_length,
        server_packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(packet_length);
    ITCHFIELD(server_packet_type);
};

static_assert(sizeof(server_packet_header) == server_packet_header::size, "server_packet_header lies over its bytes exactly");

// Server Soup Bin Tcp Packet: Soup Bin Tcp Packet sent by the server
struct server_soup_bin_tcp_packet {
    static constexpr std::string_view name = "Server Soup Bin Tcp Packet";
    static constexpr bool is_message = false;
};

// Server Packet: SoupBinTCP Packet sent by the server
struct server_packet {
    static constexpr std::string_view name = "Server Packet";
    static constexpr bool is_message = false;
};

// Logout Request
struct logout_request {
    static constexpr std::string_view name = "Logout Request";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Client Heartbeat
struct client_heartbeat {
    static constexpr std::string_view name = "Client Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Unsequenced Data Packet Section 1
struct unsequenced_data_packet_section_1 {
    static constexpr std::string_view name = "Unsequenced Data Packet Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        unsequenced_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(unsequenced_message_type);
};

static_assert(sizeof(unsequenced_data_packet_section_1) == unsequenced_data_packet_section_1::size, "unsequenced_data_packet_section_1 lies over its bytes exactly");

// Unsequenced Data Packet: The Unsequenced Data Packets act as an envelope to carry the actual data messages that are transferred from the client to the server
struct unsequenced_data_packet {
    static constexpr std::string_view name = "Unsequenced Data Packet";
    static constexpr bool is_message = true;
};

// Login Request Packet: The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server
struct login_request_packet {
    static constexpr std::string_view name = "Login Request Packet";
    static constexpr std::size_t size = 46;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        username,
        password,
        requested_session,
        requested_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(username);
    ITCHFIELD(password);
    ITCHFIELD(requested_session);
    ITCHFIELD(requested_sequence_number);
};

static_assert(sizeof(login_request_packet) == login_request_packet::size, "login_request_packet lies over its bytes exactly");

// Client Payload: Branch
struct client_payload {
    static constexpr std::string_view name = "Client Payload";
    static constexpr bool is_message = false;
};

// Client Packet Header: Packet header of a packet sent by the client
struct client_packet_header {
    static constexpr std::string_view name = "Client Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_length,
        client_packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(packet_length);
    ITCHFIELD(client_packet_type);
};

static_assert(sizeof(client_packet_header) == client_packet_header::size, "client_packet_header lies over its bytes exactly");

// Client Soup Bin Tcp Packet: Soup Bin Tcp Packet sent by the client
struct client_soup_bin_tcp_packet {
    static constexpr std::string_view name = "Client Soup Bin Tcp Packet";
    static constexpr bool is_message = false;
};

// Client Packet: SoupBinTCP Packet sent by the client
struct client_packet {
    static constexpr std::string_view name = "Client Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
