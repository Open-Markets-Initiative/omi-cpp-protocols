// Miax PearlEquities DepthOfMarket Mach 1.3.d Template Meta Programming

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

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

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

// Attributable Id: MPID of the firm if attributed; "RTAL" if attributed as such; space-filled if no attribution specified.
struct attributable_id {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Closing Time: Expressed in HH:MM:SS format. Eg: 20:00:00.
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

// Correction Number: Trade correction number. Set to zero for new trades. Increments by 1 for each subsequent correction.
struct correction_number {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Do M Version: Eg: DoM1.0.
struct do_m_version {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
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

// Esesm Packet Length: The length of rest of the packet
struct esesm_packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Esesm Packet Type: ESesM protocol packet type
struct esesm_packet_type {
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

// Esesm Version: Protocol version
struct esesm_version {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
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

// Lot Size: Round Lot size in shares.
struct lot_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mach Packet Length: Length of the packet
struct mach_packet_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mach Packet Type
struct mach_packet_type {
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

// Market State: Current market state.
struct market_state {
    enum class type : std::uint8_t {
        pre_opening = 1,
        early_trading_session = 2,
        regular_trading_session = 3,
        late_trading_session = 4,
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

// Message Type: Code identifying this message type
struct message_type {
    enum class type : std::uint8_t {
        system_time_message = 49,
        symbol_update_message = 1,
        system_state_message = 83,
        security_trading_status_notification_message = 4,
        symbol_clear_message = 5,
        add_order_message = 20,
        modify_order_message = 21,
        delete_order_message = 23,
        order_execution_message = 24,
        trade_message = 10,
        trade_cancel_message = 11,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Nanoseconds: Nanosecond part of Matching Engine time.
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

// Opening Time: Expressed in HH:MM:SS format. Eg: 04:00:00.
struct opening_time {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// Order Id: Matching engine assigned Order ID.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Position: 0 - Order kept its position in the book; 1 - Order lost its position in the book.
struct order_position {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Order Side: Side of order. B - Buy, S - Sell.
struct order_side {
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

// Price: Displayed price.
struct price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Primary Market Code: Primary listing exchange code for the security.
struct primary_market_code {
    enum class type : char {
        nyse_american = 'A',
        nasdaq_texas = 'B',
        nyse_national = 'C',
        texas_stock_exchange = 'F',
        n24x_exchange = 'G',
        miax_pearl_equities = 'H',
        nasdaq_ise = 'I',
        cboe_edga_exchange = 'J',
        cboe_edgx_exchange = 'K',
        long_term_stock_exchange = 'L',
        nyse_texas = 'M',
        new_york_stock_exchange = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        members_exchange = 'U',
        investors_exchange = 'V',
        cboe_stock_exchange = 'W',
        nasdaq_phlx = 'X',
        cboe_byx_exchange = 'Y',
        cboe_bzx_exchange = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Refresh Message Type: Identifies the data set the firm is requesting a refresh of.
struct refresh_message_type {
    enum class type : char {
        symbol_update_refresh = 'S',
        security_trading_status_refresh = 't',
        system_state_refresh = 's',
        order_book_refresh = 'O',
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

// Reserved 1: Reserved for future use.
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 6: Reserved for future use.
struct reserved_6 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFCULL;
    static constexpr int shift = 2;
};

// Reserved 7: Undefined.
struct reserved_7 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFEULL;
    static constexpr int shift = 1;
};

// Retail Trade Indicator: 0 - Neither side is Retail; 1 - At least one side is Retail.
struct retail_trade_indicator {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Second Reserved 1: Reserved for future use.
struct second_reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Sequence Number: For Symbol Update/Trading Status/System State refreshes this is the original sequence number from the live feed; for Order Book refresh this is the last sequence number on the live feed at the time of the refresh request.
struct sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequenced Message Type: Market-data application message type carried over the ESesM sequenced channel (matches the MACH UDP Message Type byte)
struct sequenced_message_type {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: Current trading session identifier.
struct session_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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

// Short Sale Restriction: Current state of short sale restriction.
struct short_sale_restriction {
    enum class type : char {
        short_sale_restriction_is_in_effect = 'Y',
        short_sale_restriction_is_not_in_effect = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sip Reporting: 0 - Not reportable to the SIP; 1 - Reportable to the SIP.
struct sip_reporting {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Size: Number of displayed shares of the order.
struct size_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
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

// Symbol Id: Symbol ID mapped to a given symbol. It is assigned per trading session and is valid for that session.
struct symbol_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// System Status: Current state of the system.
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

// Test Security Indicator: Y - Yes, N - No.
struct test_security_indicator {
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

// Ticker Symbol: Ticker symbol for the security in NASDAQ Integrated Platform format.
struct ticker_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Trade Id: Unique ID assigned by the Matching Engine.
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Traded Against Retail: 0 - Did not trade against Retail; 1 - Traded against Retail.
struct traded_against_retail {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
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

// Trading Status: Current trading status of the security.
struct trading_status {
    enum class type : std::uint8_t {
        pre_open = 1,
        trading = 2,
        halt = 3,
        operational_halt = 4,
        closed = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Unsequenced Message Type: Market-data Refresh request/response discriminator carried over the ESesM unsequenced channel (Request Type R, Response Type r, End of Refresh E)
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

// Retransmission Request: The ESesM client uses this packet to request a retransmission server to retransmit a range of packets
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

// Synchronization Complete: The ESesM server sends a Login response packet in response a Login request packet from the client
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
        esesm_version,
        username,
        computer_id,
        application_protocol,
        requested_trading_session_id,
        requested_sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(esesm_version);
    MACHFIELD(username);
    MACHFIELD(computer_id);
    MACHFIELD(application_protocol);
    MACHFIELD(requested_trading_session_id);
    MACHFIELD(requested_sequence_number);
};

static_assert(sizeof(login_request) == login_request::size, "login_request lies over its bytes exactly");

// End Of Refresh Notification Message: Sent by MIAX Pearl Equities over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) when the refresh response is complete.
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

// Refresh Response Message: Sent by MIAX Pearl Equities over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) carrying one Application Message that satisfies a previous Refresh Request.
struct refresh_response_message {
    static constexpr std::string_view name = "Refresh Response Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sequence_number);
};

static_assert(sizeof(refresh_response_message) == refresh_response_message::size, "refresh_response_message lies over its bytes exactly");

// Refresh Request Message: Sent by the firm over the DoM Retransmission Interface (ESeSM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type.
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

// Sequenced Data Packet: The ESesM server uses Sequenced data packets to send all messages that must be recoverable by the client in case of a connection loss
struct sequenced_data_packet {
    static constexpr std::string_view name = "Sequenced Data Packet";
    static constexpr bool is_message = true;
};

// Esesm Payload: Branch
struct esesm_payload {
    static constexpr std::string_view name = "Esesm Payload";
    static constexpr bool is_message = false;
};

// Esesm Packet Header
struct esesm_packet_header {
    static constexpr std::string_view name = "Esesm Packet Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        esesm_packet_length,
        esesm_packet_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(esesm_packet_length);
    MACHFIELD(esesm_packet_type);
};

static_assert(sizeof(esesm_packet_header) == esesm_packet_header::size, "esesm_packet_header lies over its bytes exactly");

// Esesm Tcp Packet
struct esesm_tcp_packet {
    static constexpr std::string_view name = "Esesm Tcp Packet";
    static constexpr bool is_message = false;
};

// Tcp Packet: ESesM Packet
struct tcp_packet {
    static constexpr std::string_view name = "Tcp Packet";
    static constexpr bool is_message = false;
};

// Trade Cancel Message: This message format is used to publish cancellation of a trade which was previously published via an Order Execution Message or a Trade Message.
struct trade_cancel_message {
    static constexpr std::string_view name = "Trade Cancel Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        trade_id,
        correction_number,
        price,
        size_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(trade_id);
    MACHFIELD(correction_number);
    MACHFIELD(price);
    MACHFIELD(size_type);
};

static_assert(sizeof(trade_cancel_message) == trade_cancel_message::size, "trade_cancel_message lies over its bytes exactly");

// Trade Flags: Trade flags. Bit 0 indicates SIP reportability; bit 1 indicates Retail Trade participation; bits 2-7 are reserved.
struct trade_flags {
    static constexpr std::string_view name = "Trade Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(trade_flags) == trade_flags::size, "trade_flags lies over its bytes exactly");

// Trade Message: This message format is used to publish trade executions for orders not displayed on the book. Executions for orders routed and executed in another trading center and trade corrections are also published using this message.
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        trade_id,
        correction_number,
        price,
        size_type,
        trade_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(trade_id);
    MACHFIELD(correction_number);
    MACHFIELD(price);
    MACHFIELD(size_type);
    MACHFIELD(trade_flags);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Execution Flags: Order Execution flags. Bit 0 indicates SIP reportability; bit 1 indicates Traded Against Retail; bits 2-7 are reserved.
struct order_execution_flags {
    static constexpr std::string_view name = "Order Execution Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(order_execution_flags) == order_execution_flags::size, "order_execution_flags lies over its bytes exactly");

// Order Execution Message: This message format is used when a displayed order on the book executes in whole or in part. The execution is identified by a unique Trade ID that is unique across the exchange for the trading day. Subsequent partial executions of the order would be published with the same Order ID but different Trade ID.
struct order_execution_message {
    static constexpr std::string_view name = "Order Execution Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        order_id,
        trade_id,
        price,
        size_type,
        order_execution_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(order_id);
    MACHFIELD(trade_id);
    MACHFIELD(price);
    MACHFIELD(size_type);
    MACHFIELD(order_execution_flags);
};

static_assert(sizeof(order_execution_message) == order_execution_message::size, "order_execution_message lies over its bytes exactly");

// Delete Order Message: This message format is used to indicate that a displayed order has been removed from the MIAX Pearl Equities book.
struct delete_order_message {
    static constexpr std::string_view name = "Delete Order Message";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(order_id);
};

static_assert(sizeof(delete_order_message) == delete_order_message::size, "delete_order_message lies over its bytes exactly");

// Modify Order Flags: Modify Order flags. Bit 0 indicates Order Position; bits 1-7 are undefined.
struct modify_order_flags {
    static constexpr std::string_view name = "Modify Order Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(modify_order_flags) == modify_order_flags::size, "modify_order_flags lies over its bytes exactly");

// Modify Order Message: This message format is used to publish price/size changes for an existing displayed order on MIAX Pearl Equities book.
struct modify_order_message {
    static constexpr std::string_view name = "Modify Order Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        order_id,
        price,
        size_type,
        modify_order_flags>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(order_id);
    MACHFIELD(price);
    MACHFIELD(size_type);
    MACHFIELD(modify_order_flags);
};

static_assert(sizeof(modify_order_message) == modify_order_message::size, "modify_order_message lies over its bytes exactly");

// Add Order Message: This is the message format that will be used when a displayed order is received and added to MIAX Pearl Equities book. It includes an Order ID that is unique to the order across the exchange and across trading days.
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 33;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        order_id,
        order_side,
        price,
        size_type,
        attributable_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(order_id);
    MACHFIELD(order_side);
    MACHFIELD(price);
    MACHFIELD(size_type);
    MACHFIELD(attributable_id);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Symbol Clear Message: This message format is used to indicate that the MIAX Pearl Equities book for a symbol has been cleared of all orders.
struct symbol_clear_message {
    static constexpr std::string_view name = "Symbol Clear Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
};

static_assert(sizeof(symbol_clear_message) == symbol_clear_message::size, "symbol_clear_message lies over its bytes exactly");

// Security Trading Status Notification Message: This message is used to notify firms of changes to the trading status of a particular security.
struct security_trading_status_notification_message {
    static constexpr std::string_view name = "Security Trading Status Notification Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        trading_status,
        market_state,
        short_sale_restriction>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(trading_status);
    MACHFIELD(market_state);
    MACHFIELD(short_sale_restriction);
};

static_assert(sizeof(security_trading_status_notification_message) == security_trading_status_notification_message::size, "security_trading_status_notification_message lies over its bytes exactly");

// System State Message: This is the message format that will be used to notify firms of the state changes of the system. This is a notification that applies to all symbols on the feed.
struct system_state_message {
    static constexpr std::string_view name = "System State Message";
    static constexpr std::size_t size = 14;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        do_m_version,
        session_id,
        system_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(do_m_version);
    MACHFIELD(session_id);
    MACHFIELD(system_status);
};

static_assert(sizeof(system_state_message) == system_state_message::size, "system_state_message lies over its bytes exactly");

// Symbol Update Message: This is the message format that will be used to disseminate all security symbols traded on MIAX Pearl Equities for the current trading session. The Symbol ID sent in this message will be disseminated in Depth of Market messages.
struct symbol_update_message {
    static constexpr std::string_view name = "Symbol Update Message";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        symbol_id,
        ticker_symbol,
        reserved_1,
        test_security_indicator,
        second_reserved_1,
        lot_size,
        opening_time,
        closing_time,
        primary_market_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(nanoseconds);
    MACHFIELD(symbol_id);
    MACHFIELD(ticker_symbol);
    MACHFIELD(reserved_1);
    MACHFIELD(test_security_indicator);
    MACHFIELD(second_reserved_1);
    MACHFIELD(lot_size);
    MACHFIELD(opening_time);
    MACHFIELD(closing_time);
    MACHFIELD(primary_market_code);
};

static_assert(sizeof(symbol_update_message) == symbol_update_message::size, "symbol_update_message lies over its bytes exactly");

// System Time Message: This message is used to disseminate the "seconds" part of the timestamp that is applicable to all messages that are sent in the current second.
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
        mach_packet_length,
        mach_packet_type,
        session_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MACHFIELD(sequence_number);
    MACHFIELD(mach_packet_length);
    MACHFIELD(mach_packet_type);
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

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
