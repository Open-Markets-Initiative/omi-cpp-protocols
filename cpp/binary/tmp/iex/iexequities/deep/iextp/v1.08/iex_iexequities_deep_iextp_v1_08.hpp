// Iex IexEquities Deep IexTp 1.08 Template Meta Programming

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
#ifndef IEXTPFIELD
#define IEXTPFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef IEXTPSEQUENCE
#define IEXTPSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace iex::iexequities::deep::iextp::v1_08 {

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

// Adjusted Poc Price: Corporate action adjusted previous official closing price
struct adjusted_poc_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Book Clearing Price: Clearing price using orders on the Auction Book
struct auction_book_clearing_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Type: Auction type identifier
struct auction_type {
    enum class type : char {
        opening_auction = 'O',
        closing_auction = 'C',
        ipo_auction = 'I',
        halt_auction = 'H',
        volatility_auction = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Channel Id: Identifies the stream of bytes sequenced messages
struct channel_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Collar Reference Price: Reference priced used for the auction collar, if any
struct collar_reference_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Detail: Detail of the Reg. SHO short sale price test restriction status
struct detail {
    enum class type : char {
        no_price_test_in_place = ' ',
        short_sale_price_test_restriction_in_effect_due_to_an_intraday_price_drop_in_the_security = 'A',
        short_sale_price_test_restriction_remains_in_effect_from_prior_day = 'C',
        short_sale_price_test_restriction_deactivated = 'D',
        not_available = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Etp: Symbol is an ETP
struct etp {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Event Flags: Identifies event processing by the System
struct event_flags {
    enum class type : std::uint8_t {
        order_book_is_processing_an_event = 0,
        event_processing_complete = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Extended Hours: Extended Hours Trade
struct extended_hours {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Extension Number: Number of extensions an auction received
struct extension_number {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// First Message Sequence Number: Sequence of the first message in the segment
struct first_message_sequence_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Shares: Number of unpaired shares at the Reference Price using orders on the Auction Book
struct imbalance_shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Side: Side of the unpaired shares at the Reference Price using orders on the Auction Book
struct imbalance_side {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        none = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Indicative Clearing Price: Clearing price using Eligible Auction Orders
struct indicative_clearing_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Intermarket Sweep: Intermarket Sweep Order
struct intermarket_sweep {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Lower Auction Collar: Lower threshold price of the auction collar, if any
struct lower_auction_collar {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Luld Tier: Indicates which Limit Up-Limit Down price band calculation parameter is to be used
struct luld_tier {
    enum class type : std::uint8_t {
        not_applicable = 0,
        tier_1_nms_stock = 1,
        tier_2_nms_stock = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Count: Number of messages in the payload
struct message_count {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Length of the message
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Protocol Id: Unique identifier of the higher layer protocol
struct message_protocol_id {
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
        system_event_message = 'S',
        security_directory_message = 'D',
        trading_status_message = 'H',
        retail_liquidity_indicator_message = 'I',
        operational_halt_status_message = 'O',
        short_sale_price_test_status_message = 'P',
        security_event_message = 'E',
        price_level_buy_update_message = '8',
        price_level_sell_update_message = '5',
        trade_report_message = 'T',
        official_price_message = 'X',
        trade_break_message = 'B',
        auction_information_message = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Odd Lot
struct odd_lot {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Official Price: Official opening or closing price, as specified
struct official_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Operational Halt Status: Operational halt status identifier
struct operational_halt_status {
    enum class type : char {
        iex_specific_operational_trading_halt = 'O',
        not_operationally_halted_on_iex = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Paired Shares: Number of shares paired at the Reference Price using orders on the Auction Book
struct paired_shares {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Payload Length: Byte length of the payload
struct payload_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: Price level to add/update in the IEX Order Book
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Type: Price type identifier
struct price_type {
    enum class type : char {
        iex_official_opening_price = 'Q',
        iex_official_closing_price = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reason: Reason for the trading status change
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reference Price: Clearing price at or within the Reference Price Range using orders on the Auction Book
struct reference_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved: Reserved byte
struct reserved {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Retail Liquidity Indicator: Retail Liquidity Indicator identifier
struct retail_liquidity_indicator {
    enum class type : char {
        not_applicable = ' ',
        buy_interest = 'A',
        sell_interest = 'B',
        buy_and_sell_interest = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Round Lot Size: Number of shares that represent a round lot
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Scheduled Auction Time: Projected time of the auction match
struct scheduled_auction_time {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Event: Security event identifier
struct security_event {
    enum class type : char {
        opening_process_complete = 'O',
        closing_process_complete = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Send Time: Send time of segment
struct send_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: Identifies the session
struct session_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Short Sale Price Test Status: Reg. SHO short sale price test restriction status
struct short_sale_price_test_status {
    enum class type : std::uint8_t {
        not_in_effect = 0,
        in_effect = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Single Price Cross Trade: Trade resulting from a single-price cross
struct single_price_cross_trade {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Size: Aggregate quoted size
struct size_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stream Offset: Byte offset of the data stream
struct stream_offset {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol: Security identifier
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 8;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 8> value_;
};

// System Event: System event identifier
struct system_event {
    enum class type : char {
        start_of_messages = 'O',
        start_of_system_hours = 'S',
        start_of_regular_market_hours = 'R',
        end_of_regular_market_hours = 'M',
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

// Test Security: Symbol is a test security
struct test_security {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Timestamp: Time stamp of the system event
struct timestamp {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: IEX Generated Identifier. Trade ID is also
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Through Exempt: Trade is not subject to Rule 611
struct trade_through_exempt {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Trading Status: Trading status identifier
struct trading_status {
    enum class type : char {
        trading_halted_across_all_us_equity_markets = 'H',
        trading_halt_released_into_an_order_acceptance_period_on_iex = 'O',
        trading_paused_and_order_acceptance_period_on_iex = 'P',
        trading_on_iex = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Unused 3: Unused
struct unused_3 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x7ULL;
    static constexpr int shift = 0;
};

// Unused 5: Unused
struct unused_5 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x1FULL;
    static constexpr int shift = 0;
};

// Upper Auction Collar: Upper threshold price of the auction collar, if any
struct upper_auction_collar {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Version: Version of transport specification
struct version {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// When Issued: Symbol is a when issued security
struct when_issued {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Auction Information Message: Broadcasts an Auction Information Message every one second between the Lock-in Time and the auction match for Opening and Closing Auctions, and during the Display Only Period for IPO, Halt, and Volatility Auctions.
struct auction_information_message {
    static constexpr std::string_view name = "Auction Information Message";
    static constexpr std::size_t size = 79;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        auction_type,
        timestamp,
        symbol,
        paired_shares,
        reference_price,
        indicative_clearing_price,
        imbalance_shares,
        imbalance_side,
        extension_number,
        scheduled_auction_time,
        auction_book_clearing_price,
        collar_reference_price,
        lower_auction_collar,
        upper_auction_collar>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(auction_type);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(paired_shares);
    IEXTPFIELD(reference_price);
    IEXTPFIELD(indicative_clearing_price);
    IEXTPFIELD(imbalance_shares);
    IEXTPFIELD(imbalance_side);
    IEXTPFIELD(extension_number);
    IEXTPFIELD(scheduled_auction_time);
    IEXTPFIELD(auction_book_clearing_price);
    IEXTPFIELD(collar_reference_price);
    IEXTPFIELD(lower_auction_collar);
    IEXTPFIELD(upper_auction_collar);
};

static_assert(sizeof(auction_information_message) == auction_information_message::size, "auction_information_message lies over its bytes exactly");

// Sale Condition Flags
struct sale_condition_flags {
    static constexpr std::string_view name = "Sale Condition Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(sale_condition_flags) == sale_condition_flags::size, "sale_condition_flags lies over its bytes exactly");

// Trade Break Message: Trade Break Messages are sent when an execution on IEX is broken on that same trading day
struct trade_break_message {
    static constexpr std::string_view name = "Trade Break Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_condition_flags,
        timestamp,
        symbol,
        size_type,
        price,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(sale_condition_flags);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(size_type);
    IEXTPFIELD(price);
    IEXTPFIELD(trade_id);
};

static_assert(sizeof(trade_break_message) == trade_break_message::size, "trade_break_message lies over its bytes exactly");

// Official Price Message: Official Price Messages are sent for each IEX-listed security to indicate the IEX Official Opening Price and IEX Official Closing Price.
struct official_price_message {
    static constexpr std::string_view name = "Official Price Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price_type,
        timestamp,
        symbol,
        official_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(price_type);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(official_price);
};

static_assert(sizeof(official_price_message) == official_price_message::size, "official_price_message lies over its bytes exactly");

// Trade Report Message: Trade Report Messages are sent when an order on the IEX Order Book is executed in whole or in part
struct trade_report_message {
    static constexpr std::string_view name = "Trade Report Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        sale_condition_flags,
        timestamp,
        symbol,
        size_type,
        price,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(sale_condition_flags);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(size_type);
    IEXTPFIELD(price);
    IEXTPFIELD(trade_id);
};

static_assert(sizeof(trade_report_message) == trade_report_message::size, "trade_report_message lies over its bytes exactly");

// Price Level Sell Update Message: Deep broadcasts a real-time Price Level Update Message each time a displayed price level on IEX is updated during the trading day
struct price_level_sell_update_message {
    static constexpr std::string_view name = "Price Level Sell Update Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        event_flags,
        timestamp,
        symbol,
        size_type,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(event_flags);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(size_type);
    IEXTPFIELD(price);
};

static_assert(sizeof(price_level_sell_update_message) == price_level_sell_update_message::size, "price_level_sell_update_message lies over its bytes exactly");

// Price Level Buy Update Message: Deep broadcasts a real-time Price Level Update Message each time a displayed price level on IEX is updated during the trading day
struct price_level_buy_update_message {
    static constexpr std::string_view name = "Price Level Buy Update Message";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        event_flags,
        timestamp,
        symbol,
        size_type,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(event_flags);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(size_type);
    IEXTPFIELD(price);
};

static_assert(sizeof(price_level_buy_update_message) == price_level_buy_update_message::size, "price_level_buy_update_message lies over its bytes exactly");

// Security Event Message: The Security Event Message is used to indicate events that apply to a security
struct security_event_message {
    static constexpr std::string_view name = "Security Event Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_event,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(security_event);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
};

static_assert(sizeof(security_event_message) == security_event_message::size, "security_event_message lies over its bytes exactly");

// Short Sale Price Test Status Message: The Short Sale Price Test Message is used to indicate when a short sale price test restriction is in effect for a security.
struct short_sale_price_test_status_message {
    static constexpr std::string_view name = "Short Sale Price Test Status Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        short_sale_price_test_status,
        timestamp,
        symbol,
        detail>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(short_sale_price_test_status);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(detail);
};

static_assert(sizeof(short_sale_price_test_status_message) == short_sale_price_test_status_message::size, "short_sale_price_test_status_message lies over its bytes exactly");

// Operational Halt Status Message: The Exchange may suspend trading of one or more securities on IEX for operational reasons and indicates such operational halt using the Operational Halt Status Message.
struct operational_halt_status_message {
    static constexpr std::string_view name = "Operational Halt Status Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        operational_halt_status,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(operational_halt_status);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
};

static_assert(sizeof(operational_halt_status_message) == operational_halt_status_message::size, "operational_halt_status_message lies over its bytes exactly");

// Retail Liquidity Indicator Message: broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to IEX's eligible retail liquidity interest during the trading day
struct retail_liquidity_indicator_message {
    static constexpr std::string_view name = "Retail Liquidity Indicator Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        retail_liquidity_indicator,
        timestamp,
        symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(retail_liquidity_indicator);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
};

static_assert(sizeof(retail_liquidity_indicator_message) == retail_liquidity_indicator_message::size, "retail_liquidity_indicator_message lies over its bytes exactly");

// Trading Status Message: The Trading Status Message is used to indicate the current trading status of a security.
struct trading_status_message {
    static constexpr std::string_view name = "Trading Status Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trading_status,
        timestamp,
        symbol,
        reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(trading_status);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(reason);
};

static_assert(sizeof(trading_status_message) == trading_status_message::size, "trading_status_message lies over its bytes exactly");

// Security Directory Flags
struct security_directory_flags {
    static constexpr std::string_view name = "Security Directory Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(security_directory_flags) == security_directory_flags::size, "security_directory_flags lies over its bytes exactly");

// Security Directory Message: The System Event Message is used to indicate events that apply to the market or the data feed.
struct security_directory_message {
    static constexpr std::string_view name = "Security Directory Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_directory_flags,
        timestamp,
        symbol,
        round_lot_size,
        adjusted_poc_price,
        luld_tier>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(security_directory_flags);
    IEXTPFIELD(timestamp);
    IEXTPFIELD(symbol);
    IEXTPFIELD(round_lot_size);
    IEXTPFIELD(adjusted_poc_price);
    IEXTPFIELD(luld_tier);
};

static_assert(sizeof(security_directory_message) == security_directory_message::size, "security_directory_message lies over its bytes exactly");

// System Event Message: The System Event Message is used to indicate events that apply to the market or the data feed.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        system_event,
        timestamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(system_event);
    IEXTPFIELD(timestamp);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Message Data: Branch
struct message_data {
    static constexpr std::string_view name = "Message Data";
    static constexpr bool is_message = false;
};

// Message Header: IexTp message header
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
    IEXTPFIELD(message_length);
    IEXTPFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: IexTp message
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
    IEXTPSEQUENCE(message);
};

// Iextp Header: IexTp packet header
struct iextp_header {
    static constexpr std::string_view name = "Iextp Header";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        version,
        reserved,
        message_protocol_id,
        channel_id,
        session_id,
        payload_length,
        message_count,
        stream_offset,
        first_message_sequence_number,
        send_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    IEXTPFIELD(version);
    IEXTPFIELD(reserved);
    IEXTPFIELD(message_protocol_id);
    IEXTPFIELD(channel_id);
    IEXTPFIELD(session_id);
    IEXTPFIELD(payload_length);
    IEXTPFIELD(message_count);
    IEXTPFIELD(stream_offset);
    IEXTPFIELD(first_message_sequence_number);
    IEXTPFIELD(send_time);
};

static_assert(sizeof(iextp_header) == iextp_header::size, "iextp_header lies over its bytes exactly");

// Packet: IexTp Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace iex::iexequities::deep::iextp::v1_08
