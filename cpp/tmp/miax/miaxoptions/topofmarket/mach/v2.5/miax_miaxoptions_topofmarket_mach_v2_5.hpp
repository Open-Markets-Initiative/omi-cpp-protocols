// Miax MiaxOptions TopOfMarket Mach 2.5 Template Meta Programming

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
#ifndef MACHFIELD
#define MACHFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef MACHSEQUENCE
#define MACHSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

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

// Active On Miax: Indicates if this symbol is tradable on MIAX in the current session
struct active_on_miax {
    enum class type : char {
        active = 'A',
        inactive = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Application Protocol: Miax Application Protocol
struct application_protocol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Bid Condition: Bid Condition Values
struct bid_condition {
    enum class type : char {
        regular = 'A',
        public_customer_interest = 'B',
        not_firm = 'C',
        reserved = 'R',
        trading_halt = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bid Price Long: MIAX best bid price at the time stated in Timestamp and side specified in Message Type
struct bid_price_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Short: MIAX best bid price at the time stated in Timestamp and side specified in Message Type
struct bid_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Priority Customer Size Long: Aggregate size of Priority Customer contracts at the MIAX Best Bid Price
struct bid_priority_customer_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Priority Customer Size Short: Aggregate size of Priority Customer contracts at the MIAX Best Bid Price
struct bid_priority_customer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Long: Aggregate size at MIAX best bid Price at the time stated in Timestamp and side specified in Message Type
struct bid_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Short: Aggregate size at MIAX best bid Price at the time stated in Timestamp and side specified in Message Type
struct bid_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Call Or Put: Option Type
struct call_or_put {
    enum class type : char {
        call = 'C',
        put = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Closing Time: Expressed in HH:MM:SS format. Eg: 16:15:00
struct closing_time {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Computer Id: issued by MIAX Futures Exchange during initial setup
struct computer_id {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Correction Number: Trade correction number. 0 for New trades. Greater than or equal to 0 for trades resulting from corrections/adjustments.
struct correction_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// End Sequence Number: Sequence number of the last packet to be retransmitted
struct end_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Reason: Event Reason value
struct event_reason {
    enum class type : char {
        automatic = 'A',
        manual = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Expected Event Time Nano Seconds Part: Nano-seconds portion of the expected time of the event. Specifies number of nano-seconds since the seconds specified in "Expected Event Time Seconds" field.
struct expected_event_time_nano_seconds_part {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expected Event Time Seconds Part: Seconds portion of the expected time of the event. Always use in conjunction with the Nano-seconds part field.
struct expected_event_time_seconds_part {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Date: Expiration date of the option in YYYYMMDD format
struct expiration_date {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Highest Sequence Number: the highest sequence number that the server currently has for the client
struct highest_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Liquidity Acceptance Increment Indicator: This is the Minimum Price Variation for Quote/Order acceptance as per MIAX rules
struct liquidity_acceptance_increment_indicator {
    enum class type : char {
        penny = 'P',
        penny_or_nickel = 'N',
        nickel_or_dime = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Login Status
struct login_status {
    enum class type : char {
        successful = ' ',
        invalid_trading_session_requested = 'S',
        no_active_trading_session_exists = 'U',
        rejected = 'X',
        invalid_start_sequence_number_requested = 'N',
        incompatible_session_protocol_version = 'I',
        incompatible_application_protocol_version = 'A',
        request_rejected_because_client_already_logged_in = 'L',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Logout Reason: Logout Request Reason
struct logout_reason {
    enum class type : char {
        graceful_logout = ' ',
        bad_packet = 'B',
        timed_out = 'L',
        application_terminating_connection = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Logout Text: Free form human readable text
struct logout_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr logout_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Long Term Option: "Y" = Far month expiration (as defined by MIAX rules), "N" = Near month expiration (as defined by MIAX rules)
struct long_term_option {
    enum class type : char {
        far_month_expiration = 'Y',
        near_month_expiration = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Matching Engine Id: Matching Engine that originated the packet
struct matching_engine_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mbbo Condition: MBBO Condition Values
struct mbbo_condition {
    enum class type : char {
        regular = 'A',
        public_customer_interest = 'B',
        not_firm = 'C',
        reserved = 'R',
        trading_halt = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// MBBO Price Long: MIAX Best price at the time stated in Timestamp and side specified in Message Type
struct mbbo_price_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// MBBO Price Short: MIAX Best price at the time stated in Timestamp and side specified in Message Type
struct mbbo_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// MBBO Priority Customer Size Long: Aggregate size of Priority Customer contracts at the MIAX Best Price
struct mbbo_priority_customer_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// MBBO Priority Customer Size Short: Aggregate size of Priority Customer contracts at the MIAX Best Price
struct mbbo_priority_customer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// MBBO Size Long: Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct mbbo_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// MBBO Size Short: Aggregate size at MIAX Best Price at the time stated in Timestamp and side specified in Message Type
struct mbbo_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Type: Code identifying this message type
struct message_type {
    enum class type : char {
        system_time_message = '1',
        simple_series_update_message = 'P',
        system_state_message = 'S',
        simple_top_of_market_best_bid_or_offer_compact_bid_message = 'B',
        simple_top_of_market_best_bid_or_offer_compact_offer_message = 'O',
        simple_top_of_market_best_bid_or_offer_wide_bid_message = 'b',
        simple_top_of_market_best_bid_or_offer_wide_offer_message = 'o',
        simple_double_sided_top_of_market_best_bid_or_offer_compact_message = 'd',
        simple_double_sided_top_of_market_best_bid_or_offer_wide_message = 'D',
        last_sale_message = 'T',
        trade_cancel_message = 'X',
        underlying_trading_status_notification_message = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Miax Bbo Posting Increment Indicator: This is the Minimum Price Variation as agreed to by the Options industry (penny pilot program) and as published by MIAX
struct miax_bbo_posting_increment_indicator {
    enum class type : char {
        penny = 'P',
        penny_or_nickel = 'N',
        nickel_or_dime = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Nanoseconds: Time at which this product is added/updated on MIAX system today.
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Matching Engines: Count of all Matching Engines for the exchange
struct number_of_matching_engines {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Condition: Offer Condition Values
struct offer_condition {
    enum class type : char {
        regular = 'A',
        public_customer_interest = 'B',
        not_firm = 'C',
        reserved = 'R',
        trading_halt = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Offer Price Long: MIAX best offer price at the time stated in Timestamp and side specified in Message Type
struct offer_price_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Price Short: MIAX best offer price at the time stated in Timestamp and side specified in Message Type
struct offer_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Priority Customer Size Long: Aggregate size of Priority Customer contracts at the MIAX Best Offer Price
struct offer_priority_customer_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Priority Customer Size Short: Aggregate size of Priority Customer contracts at the MIAX Best Offer Price
struct offer_priority_customer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Size Long: Aggregate size at MIAX best offer Price at the time stated in Timestamp and side specified in Message Type
struct offer_size_long {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Size Short: Aggregate size at MIAX best offer Price at the time stated in Timestamp and side specified in Message Type
struct offer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opening Time: Expressed in HH:MM:SS format. Eg: 09:30:00
struct opening_time {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Opening Underlying Market Code: Options opening will be triggered on receipt of Opening quote/trade from this Underlying market
struct opening_underlying_market_code {
    enum class type : char {
        nyse_amex = 'A',
        nasdaq_omx_bx = 'B',
        national_stock_exchange = 'C',
        finra_adf = 'D',
        market_independent = 'E',
        miax_pearl_equities = 'H',
        international_securities_exchange = 'I',
        edga_exchange_inc = 'J',
        edgx_exchange_inc = 'K',
        ltse = 'L',
        chicago_stock_exchange = 'M',
        nyse_euronext = 'N',
        nyse_arca_exchange = 'P',
        nasdaq_omx_utp = 'Q',
        nasdaq_omx_cta = 'T',
        memx = 'U',
        iex = 'V',
        cboe_stock_exchange = 'W',
        nasdaq_omx_phlx = 'X',
        bats_y = 'Y',
        bats = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Packet Length: Length of the packet, including the header and application data
struct packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Packet Type: protocol packet type
struct packet_type {
    enum class type : std::uint8_t {
        heartbeat = 0,
        start_of_session = 1,
        end_of_session = 2,
        application_message = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Priority Quote Width: Maximum allowable width for a quote for this Option during regular trading in order to be considered as Priority Quote. 0 when Priority Quote Width is not applicable.
struct priority_quote_width {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session and is valid for that session.
struct product_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reference Correction Number: Correction Number of the trade that was just corrected/adjusted. 0 for new trades.
struct reference_correction_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reference Trade Id: 0 (zero) if new trade. Trade ID of the original trade if this trade originated as a correction of the original trade.
struct reference_trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Refresh Message Type: Identifies the data set the firm is requesting a refresh of.
struct refresh_message_type {
    enum class type : char {
        simple_series_update_refresh = 'P',
        simple_top_of_market_refresh = 'Q',
        underlying_trading_status_refresh = 'U',
        system_state_refresh = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Requested Sequence Number: Specifies client requested sequence number
struct requested_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Requested Trading Session Id: Specifies the session the client would like to log into, or zero to log into the currently active session
struct requested_trading_session_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 8: Reserved for future use
struct reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Restricted Option: Restricted Option value
struct restricted_option {
    enum class type : char {
        accept_position_closing = 'Y',
        accept_open_and_close = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seconds: Seconds part of the time that applies to all messages that gets disseminated until this message gets sent again.
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Symbol: Option Security Symbol
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Sequence Number: Original sequence number from the live feed.
struct sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequenced Message Type: Market-data application message type carried over the SesM sequenced channel (matches the MACH UDP Message Type byte; Miax Options uses Ascii message codes)
struct sequenced_message_type {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Sesm Packet Length: The length of rest of the packet
struct sesm_packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sesm Packet Type: SesM protocol packet type
struct sesm_packet_type {
    enum class type : char {
        sequenced_data_packet = 's',
        unsequenced_data_packet = 'U',
        login_request = 'l',
        login_response = 'r',
        synchronization_complete = 'c',
        retransmission_request = 'a',
        logout_request = 'X',
        goodbye_packet = 'G',
        trading_session_update = 'u',
        server_heartbeat = '0',
        client_heartbeat = '1',
        test_packet = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sesm Version: Protocol version
struct sesm_version {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Session Id: MIAX assigned ID for the current trading session
struct session_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Number: protocol packet type
struct session_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Start Sequence Number: Sequence number of the first packet to be retransmitted
struct start_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price: Explicit strike price of the option. Refer to data types for field processing notes
struct strike_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Status: Current system status
struct system_status {
    enum class type : char {
        start_of_system_hours = 'S',
        end_of_system_hours = 'C',
        start_of_test_session = '1',
        end_of_test_session = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Test Text: Free form human readable text
struct test_text {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr test_text(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// To M Version: Eg: TOM2.1
struct to_m_version {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Trade Condition: Trade Condition Values. Please refer to Appendix A.
struct trade_condition {
    enum class type : char {
        regular = ' ',
        cancel_of_trade_previously_reported_other_than_as_the_last_or_opening = 'A',
        late_and_is_out_of_sequence = 'B',
        cancel_of_the_last_reported_trade = 'C',
        late_and_is_in_correct_sequence = 'D',
        cancel_of_the_first_reported_trade = 'E',
        late_report_of_the_opening_trade_and_is_out_of_sequence = 'F',
        cancel_of_the_only_reported_trade = 'G',
        late_report_of_the_opening_trade_and_is_in_correct_sequence = 'H',
        auto_value = 'I',
        reopening_of_an_option = 'J',
        reserved = 'K',
        a_buy_and_a_sell_in_the_same_class = 'L',
        a_buy_and_a_sell_in_a_put_and_a_call = 'M',
        reserved_2 = 'N',
        reserved_3 = 'O',
        buy_or_sell_of_a_call_or_put = 'P',
        buy_of_a_call_and_a_sell_of_a_put_for_the_same_underlying_stock_or_index = 'Q',
        execution_of_an_order_which_was_stopped_at_a_price_that_did_not_constitute_a_trade_through_on_another_market_at_the_time_of_the_stop = 'R',
        execution_of_an_iso_order = 'S',
        reserved_4 = 'T',
        trade_through_exempt = 'X',
        paired_prime = 'a',
        iso_paired_prime = 'b',
        prime_customer_to_customer_cross_or_prime_qcc = 'c',
        reserved_5 = 'd',
        reserved_6 = 'e',
        complex_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging = 'f',
        complex_prime_transaction_that_is_not_complex_stock_tied_and_does_not_involve_legging = 'g',
        complex_prime_customer_to_customer_cross_or_complex_prime_qcc_transaction_that_is_not_complex_stock_tied = 'h',
        reserved_7 = 'i',
        complex_legging_transaction_that_is_not_complex_stock_tied = 'j',
        complex_prime_stock_tied_transaction_that_does_not_involve_legging = 'k',
        complex_prime_legging_transaction_that_is_not_complex_stock_tied = 'l',
        reserved_8 = 'm',
        complex_stock_tied_transaction_that_does_not_involve_legging = 'n',
        complex_customer_to_customer_cross_stock_tied_or_complex_qcc_stock_tied_transaction = 'o',
        reserved_9 = 'p',
        reserved_10 = 'q',
        reserved_11 = 'r',
        reserved_12 = 's',
        reserved_13 = 't',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Id: Unique Trade ID assigned to every Trade.
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price: Price at which this product traded
struct trade_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Size: Number of contracts executed in this trade
struct trade_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Session Id: The current trading session ID of the corresponding Matching Engine
struct trading_session_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Status: Trading Status value
struct trading_status {
    enum class type : char {
        halted = 'H',
        resumed = 'R',
        opened = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Symbol: Stock Symbol for the option.
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Unsequenced Message Type: Market-data Refresh request/response discriminator carried over the SesM unsequenced channel (Request Type R, Response Type r, End of Refresh E)
struct unsequenced_message_type {
    enum class type : char {
        refresh_request_message = 'R',
        refresh_response_message = 'r',
        end_of_refresh_notification_message = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Username: issued by MIAX during initial setup
struct username {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Test Packet: Test packets are intended to provide human readable text that may aid in debugging problems
struct test_packet {
    static constexpr std::string_view name = "Test Packet";
    static constexpr bool is_message = true;
};

// Client Heartbeat
struct client_heartbeat {
    static constexpr std::string_view name = "Client Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Server Heartbeat
struct server_heartbeat {
    static constexpr std::string_view name = "Server Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Trading Session Update
struct trading_session_update {
    static constexpr std::string_view name = "Trading Session Update";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Goodbye Packet Section 1
struct goodbye_packet_section_1 {
    static constexpr std::string_view name = "Goodbye Packet Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        logout_reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(logout_reason);
};

static_assert(sizeof(goodbye_packet_section_1) == goodbye_packet_section_1::size, "goodbye_packet_section_1 lies over its bytes exactly");

// Goodbye Packet: The server may send a GoodBye packet to inform the client a reason for termination of the connection just before it terminates the connection
struct goodbye_packet {
    static constexpr std::string_view name = "Goodbye Packet";
    static constexpr bool is_message = true;
};

// Logout Request Section 1
struct logout_request_section_1 {
    static constexpr std::string_view name = "Logout Request Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        logout_reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(logout_reason);
};

static_assert(sizeof(logout_request_section_1) == logout_request_section_1::size, "logout_request_section_1 lies over its bytes exactly");

// Logout Request: The client may send a Logout request packet to request the connection be terminated
struct logout_request {
    static constexpr std::string_view name = "Logout Request";
    static constexpr bool is_message = true;
};

// Retransmission Request: The SesM client uses this packet to request a retransmission server to retransmit a range of packets
struct retransmission_request {
    static constexpr std::string_view name = "Retransmission Request";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        start_sequence_number,
        end_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(start_sequence_number);
    MACHFIELD(end_sequence_number);
};

static_assert(sizeof(retransmission_request) == retransmission_request::size, "retransmission_request lies over its bytes exactly");

// Synchronization Complete: The SesM server sends a Login response packet in response a Login request packet from the client
struct synchronization_complete {
    static constexpr std::string_view name = "Synchronization Complete";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        number_of_matching_engines>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(number_of_matching_engines);
};

static_assert(sizeof(synchronization_complete) == synchronization_complete::size, "synchronization_complete lies over its bytes exactly");

// Login Response: The SesM server sends a Login response packet in response a Login request packet from the client
struct login_response {
    static constexpr std::string_view name = "Login Response";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        number_of_matching_engines,
        login_status,
        trading_session_id,
        highest_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(number_of_matching_engines);
    MACHFIELD(login_status);
    MACHFIELD(trading_session_id);
    MACHFIELD(highest_sequence_number);
};

static_assert(sizeof(login_response) == login_response::size, "login_response lies over its bytes exactly");

// Login Request: The SesM client must send a Login request packet immediately upon establishing a new TCP/IP socket connection to the server
struct login_request {
    static constexpr std::string_view name = "Login Request";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sesm_version,
        username,
        computer_id,
        application_protocol,
        requested_trading_session_id,
        requested_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sesm_version);
    MACHFIELD(username);
    MACHFIELD(computer_id);
    MACHFIELD(application_protocol);
    MACHFIELD(requested_trading_session_id);
    MACHFIELD(requested_sequence_number);
};

static_assert(sizeof(login_request) == login_request::size, "login_request lies over its bytes exactly");

// End Of Refresh Notification Message: Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet) when the refresh response is complete.
struct end_of_refresh_notification_message {
    static constexpr std::string_view name = "End Of Refresh Notification Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        refresh_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(refresh_message_type);
};

static_assert(sizeof(end_of_refresh_notification_message) == end_of_refresh_notification_message::size, "end_of_refresh_notification_message lies over its bytes exactly");

// Underlying Trading Status Notification Message: This message format will be used to notify firms of changes to the trading status of all the options of an underlying.
struct underlying_trading_status_notification_message {
    static constexpr std::string_view name = "Underlying Trading Status Notification Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        underlying_symbol,
        trading_status,
        event_reason,
        expected_event_time_seconds_part,
        expected_event_time_nano_seconds_part>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(underlying_symbol);
    MACHFIELD(trading_status);
    MACHFIELD(event_reason);
    MACHFIELD(expected_event_time_seconds_part);
    MACHFIELD(expected_event_time_nano_seconds_part);
};

static_assert(sizeof(underlying_trading_status_notification_message) == underlying_trading_status_notification_message::size, "underlying_trading_status_notification_message lies over its bytes exactly");

// Trade Cancel Message: This is the message format that will be used to disseminate canceled Trades that are resulting from Trade cancellations or corrections on MIAX during the current trading session.
struct trade_cancel_message {
    static constexpr std::string_view name = "Trade Cancel Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        trade_id,
        correction_number,
        trade_price,
        trade_size,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(trade_id);
    MACHFIELD(correction_number);
    MACHFIELD(trade_price);
    MACHFIELD(trade_size);
    MACHFIELD(trade_condition);
};

static_assert(sizeof(trade_cancel_message) == trade_cancel_message::size, "trade_cancel_message lies over its bytes exactly");

// Last Sale Message: This is the message format that will be used to disseminate Trades that are resulting from executions on MIAX during the current trading session.
struct last_sale_message {
    static constexpr std::string_view name = "Last Sale Message";
    static constexpr std::size_t size = 27;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        trade_id,
        correction_number,
        reference_trade_id,
        reference_correction_number,
        trade_price,
        trade_size,
        trade_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(trade_id);
    MACHFIELD(correction_number);
    MACHFIELD(reference_trade_id);
    MACHFIELD(reference_correction_number);
    MACHFIELD(trade_price);
    MACHFIELD(trade_size);
    MACHFIELD(trade_condition);
};

static_assert(sizeof(last_sale_message) == last_sale_message::size, "last_sale_message lies over its bytes exactly");

// Simple Double Sided Top Of Market Best Bid Or Offer Wide Message: This is the message format that will be used in the real-time feed and refresh service to disseminate both sides of the MIAX Simple Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) sizes.
struct simple_double_sided_top_of_market_best_bid_or_offer_wide_message {
    static constexpr std::string_view name = "Simple Double Sided Top Of Market Best Bid Or Offer Wide Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        bid_price_long,
        bid_size_long,
        bid_priority_customer_size_long,
        bid_condition,
        offer_price_long,
        offer_size_long,
        offer_priority_customer_size_long,
        offer_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(bid_price_long);
    MACHFIELD(bid_size_long);
    MACHFIELD(bid_priority_customer_size_long);
    MACHFIELD(bid_condition);
    MACHFIELD(offer_price_long);
    MACHFIELD(offer_size_long);
    MACHFIELD(offer_priority_customer_size_long);
    MACHFIELD(offer_condition);
};

static_assert(sizeof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message) == simple_double_sided_top_of_market_best_bid_or_offer_wide_message::size, "simple_double_sided_top_of_market_best_bid_or_offer_wide_message lies over its bytes exactly");

// Simple Double Sided Top Of Market Best Bid Or Offer Compact Message: This is the message format that will be used in the real-time feed and refresh service to disseminate both sides of the MIAX Simple Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size.
struct simple_double_sided_top_of_market_best_bid_or_offer_compact_message {
    static constexpr std::string_view name = "Simple Double Sided Top Of Market Best Bid Or Offer Compact Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        bid_price_short,
        bid_size_short,
        bid_priority_customer_size_short,
        bid_condition,
        offer_price_short,
        offer_size_short,
        offer_priority_customer_size_short,
        offer_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(bid_price_short);
    MACHFIELD(bid_size_short);
    MACHFIELD(bid_priority_customer_size_short);
    MACHFIELD(bid_condition);
    MACHFIELD(offer_price_short);
    MACHFIELD(offer_size_short);
    MACHFIELD(offer_priority_customer_size_short);
    MACHFIELD(offer_condition);
};

static_assert(sizeof(simple_double_sided_top_of_market_best_bid_or_offer_compact_message) == simple_double_sided_top_of_market_best_bid_or_offer_compact_message::size, "simple_double_sided_top_of_market_best_bid_or_offer_compact_message lies over its bytes exactly");

// Simple Top Of Market Best Bid Or Offer Wide Offer Message: This is the message format that will be used to disseminate MIAX Simple Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) size. "o" = Simple Top of Market on Offer side (wide).
struct simple_top_of_market_best_bid_or_offer_wide_offer_message {
    static constexpr std::string_view name = "Simple Top Of Market Best Bid Or Offer Wide Offer Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        mbbo_price_long,
        mbbo_size_long,
        mbbo_priority_customer_size_long,
        mbbo_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(mbbo_price_long);
    MACHFIELD(mbbo_size_long);
    MACHFIELD(mbbo_priority_customer_size_long);
    MACHFIELD(mbbo_condition);
};

static_assert(sizeof(simple_top_of_market_best_bid_or_offer_wide_offer_message) == simple_top_of_market_best_bid_or_offer_wide_offer_message::size, "simple_top_of_market_best_bid_or_offer_wide_offer_message lies over its bytes exactly");

// Simple Top Of Market Best Bid Or Offer Wide Bid Message: This is the message format that will be used to disseminate MIAX Simple Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) size. "b" = Simple Top of Market on Bid side (wide).
struct simple_top_of_market_best_bid_or_offer_wide_bid_message {
    static constexpr std::string_view name = "Simple Top Of Market Best Bid Or Offer Wide Bid Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        mbbo_price_long,
        mbbo_size_long,
        mbbo_priority_customer_size_long,
        mbbo_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(mbbo_price_long);
    MACHFIELD(mbbo_size_long);
    MACHFIELD(mbbo_priority_customer_size_long);
    MACHFIELD(mbbo_condition);
};

static_assert(sizeof(simple_top_of_market_best_bid_or_offer_wide_bid_message) == simple_top_of_market_best_bid_or_offer_wide_bid_message::size, "simple_top_of_market_best_bid_or_offer_wide_bid_message lies over its bytes exactly");

// Simple Top Of Market Best Bid Or Offer Compact Offer Message: This is the message format that will be used to disseminate each side of the MIAX Simple Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size. "O" = Simple Top of Market on Offer side.
struct simple_top_of_market_best_bid_or_offer_compact_offer_message {
    static constexpr std::string_view name = "Simple Top Of Market Best Bid Or Offer Compact Offer Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        mbbo_price_short,
        mbbo_size_short,
        mbbo_priority_customer_size_short,
        mbbo_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(mbbo_price_short);
    MACHFIELD(mbbo_size_short);
    MACHFIELD(mbbo_priority_customer_size_short);
    MACHFIELD(mbbo_condition);
};

static_assert(sizeof(simple_top_of_market_best_bid_or_offer_compact_offer_message) == simple_top_of_market_best_bid_or_offer_compact_offer_message::size, "simple_top_of_market_best_bid_or_offer_compact_offer_message lies over its bytes exactly");

// Simple Top Of Market Best Bid Or Offer Compact Bid Message: This is the message format that will be used to disseminate each side of the MIAX Simple Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size. "B" = Simple Top of Market on Bid side.
struct simple_top_of_market_best_bid_or_offer_compact_bid_message {
    static constexpr std::string_view name = "Simple Top Of Market Best Bid Or Offer Compact Bid Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        mbbo_price_short,
        mbbo_size_short,
        mbbo_priority_customer_size_short,
        mbbo_condition>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(mbbo_price_short);
    MACHFIELD(mbbo_size_short);
    MACHFIELD(mbbo_priority_customer_size_short);
    MACHFIELD(mbbo_condition);
};

static_assert(sizeof(simple_top_of_market_best_bid_or_offer_compact_bid_message) == simple_top_of_market_best_bid_or_offer_compact_bid_message::size, "simple_top_of_market_best_bid_or_offer_compact_bid_message lies over its bytes exactly");

// System State Message: This message format is used to notify the firms of the state changes of the system. This is a notification that applies to each Underlying group. Firms can use notifications as triggers in their system to ensure electronic synchronization of systems.
struct system_state_message {
    static constexpr std::string_view name = "System State Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        to_m_version,
        session_id,
        system_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(to_m_version);
    MACHFIELD(session_id);
    MACHFIELD(system_status);
};

static_assert(sizeof(system_state_message) == system_state_message::size, "system_state_message lies over its bytes exactly");

// Simple Series Update Message: This is the message format that will be used to disseminate all Option series traded on MIAX for the current session. The product ID sent in this message is what will be disseminated in Top of Market BBO and Last Sale messages.
struct simple_series_update_message {
    static constexpr std::string_view name = "Simple Series Update Message";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        product_id,
        underlying_symbol,
        security_symbol,
        expiration_date,
        strike_price,
        call_or_put,
        opening_time,
        closing_time,
        restricted_option,
        long_term_option,
        active_on_miax,
        miax_bbo_posting_increment_indicator,
        liquidity_acceptance_increment_indicator,
        opening_underlying_market_code,
        priority_quote_width,
        reserved_8>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(product_id);
    MACHFIELD(underlying_symbol);
    MACHFIELD(security_symbol);
    MACHFIELD(expiration_date);
    MACHFIELD(strike_price);
    MACHFIELD(call_or_put);
    MACHFIELD(opening_time);
    MACHFIELD(closing_time);
    MACHFIELD(restricted_option);
    MACHFIELD(long_term_option);
    MACHFIELD(active_on_miax);
    MACHFIELD(miax_bbo_posting_increment_indicator);
    MACHFIELD(liquidity_acceptance_increment_indicator);
    MACHFIELD(opening_underlying_market_code);
    MACHFIELD(priority_quote_width);
    MACHFIELD(reserved_8);
};

static_assert(sizeof(simple_series_update_message) == simple_series_update_message::size, "simple_series_update_message lies over its bytes exactly");

// System Time Message: This is the message format that will be used to disseminate the "seconds" part of the timestamp that is applicable to all messages that are sent in the current second.
struct system_time_message {
    static constexpr std::string_view name = "System Time Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        seconds>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(seconds);
};

static_assert(sizeof(system_time_message) == system_time_message::size, "system_time_message lies over its bytes exactly");

// Data: Branch
struct data_type {
    static constexpr std::string_view name = "Data";
    static constexpr bool is_message = false;
};

// Application Message Section 1
struct application_message_section_1 {
    static constexpr std::string_view name = "Application Message Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(message_type);
};

static_assert(sizeof(application_message_section_1) == application_message_section_1::size, "application_message_section_1 lies over its bytes exactly");

// Application Message
struct application_message {
    static constexpr std::string_view name = "Application Message";
    static constexpr bool is_message = false;
};

// Refresh Response Message Section 1
struct refresh_response_message_section_1 {
    static constexpr std::string_view name = "Refresh Response Message Section 1";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sequence_number);
};

static_assert(sizeof(refresh_response_message_section_1) == refresh_response_message_section_1::size, "refresh_response_message_section_1 lies over its bytes exactly");

// Refresh Response Message: Sent by MIAX Options over the ToM Retransmission Interface (SesM Unsequenced Data Packet) carrying one Application Message that satisfies a previous Refresh Request. Note: MIAX Options PDF assigns Response Type "R" (uppercase) to this message, colliding with the Request Type "R" byte; lowercase "r" is used here to match the Pearl convention for case-distinct discrimination.
struct refresh_response_message {
    static constexpr std::string_view name = "Refresh Response Message";
    static constexpr bool is_message = false;
};

// Refresh Request Message: Sent by the firm over the ToM Retransmission Interface (SesM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type.
struct refresh_request_message {
    static constexpr std::string_view name = "Refresh Request Message";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        refresh_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(refresh_message_type);
};

static_assert(sizeof(refresh_request_message) == refresh_request_message::size, "refresh_request_message lies over its bytes exactly");

// Unsequenced Message: Branch
struct unsequenced_message {
    static constexpr std::string_view name = "Unsequenced Message";
    static constexpr bool is_message = false;
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
    MACHFIELD(unsequenced_message_type);
};

static_assert(sizeof(unsequenced_data_packet_section_1) == unsequenced_data_packet_section_1::size, "unsequenced_data_packet_section_1 lies over its bytes exactly");

// Unsequenced Data Packet: Each unsequenced data packet carries one unsequenced message from the higher-lever protocol
struct unsequenced_data_packet {
    static constexpr std::string_view name = "Unsequenced Data Packet";
    static constexpr bool is_message = false;
};

// Sequenced Message
struct sequenced_message {
    static constexpr std::string_view name = "Sequenced Message";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = false;
};

// Sequenced Data Packet Section 1
struct sequenced_data_packet_section_1 {
    static constexpr std::string_view name = "Sequenced Data Packet Section 1";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequence_number,
        matching_engine_id,
        sequenced_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sequence_number);
    MACHFIELD(matching_engine_id);
    MACHFIELD(sequenced_message_type);
};

static_assert(sizeof(sequenced_data_packet_section_1) == sequenced_data_packet_section_1::size, "sequenced_data_packet_section_1 lies over its bytes exactly");

// Sequenced Data Packet: The SesM server uses Sequenced data packets to send all messages that must be recoverable by the client in case of a connection loss
struct sequenced_data_packet {
    static constexpr std::string_view name = "Sequenced Data Packet";
    static constexpr bool is_message = true;
};

// Sesm Payload: Branch
struct sesm_payload {
    static constexpr std::string_view name = "Sesm Payload";
    static constexpr bool is_message = false;
};

// Sesm Packet Header
struct sesm_packet_header {
    static constexpr std::string_view name = "Sesm Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        sesm_packet_length,
        sesm_packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sesm_packet_length);
    MACHFIELD(sesm_packet_type);
};

static_assert(sizeof(sesm_packet_header) == sesm_packet_header::size, "sesm_packet_header lies over its bytes exactly");

// Sesm Tcp Packet
struct sesm_tcp_packet {
    static constexpr std::string_view name = "Sesm Tcp Packet";
    static constexpr bool is_message = false;
};

// Tcp Packet: SesM Packet
struct tcp_packet {
    static constexpr std::string_view name = "Tcp Packet";
    static constexpr bool is_message = false;
};

// End Of Session
struct end_of_session {
    static constexpr std::string_view name = "End Of Session";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Start Of Session
struct start_of_session {
    static constexpr std::string_view name = "Start Of Session";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Heartbeat
struct heartbeat {
    static constexpr std::string_view name = "Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Mach Message Section 1
struct mach_message_section_1 {
    static constexpr std::string_view name = "Mach Message Section 1";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequence_number,
        packet_length,
        packet_type,
        session_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sequence_number);
    MACHFIELD(packet_length);
    MACHFIELD(packet_type);
    MACHFIELD(session_number);
};

static_assert(sizeof(mach_message_section_1) == mach_message_section_1::size, "mach_message_section_1 lies over its bytes exactly");

// Mach Message
struct mach_message {
    static constexpr std::string_view name = "Mach Message";
    static constexpr bool is_message = false;
};

// Udp Packet
struct udp_packet {
    static constexpr std::string_view name = "Udp Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
