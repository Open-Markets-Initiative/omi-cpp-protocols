// Lseg Lse Level2Mbo Gtp 26.2 Template Meta Programming

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
#ifndef GTPFIELD
#define GTPFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef GTPSEQUENCE
#define GTPSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace lseg::lse::level2mbo::gtp::v26_2 {

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

// Auction Info: Populated if the Statistic Type is 1.
struct auction_info {
    enum class type : char {
        not_applicable = '0',
        buy_imbalance = 'B',
        no_imbalance = 'N',
        insufficient_orders_for_auction = 'O',
        sell_imbalance = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Auction Type: The value in this field is only relevant when Trade Type is 1.
struct auction_type {
    enum class type : char {
        closing_auction = 'C',
        opening_auction = 'O',
        aesp = 'A',
        edsp = 'B',
        resume_auction = 'E',
        periodic_auction = 'F',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Average Daily Turnover Adt: Not Applicable to LSE.
struct average_daily_turnover_adt {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Currency: Currency Code as per ISO 4217.
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Depth: Total number of orders disseminated including this one, on this side of the book as indicated by Side field.
struct depth {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Dynamic Circuit Breaker Tolerances: Dynamic Circuit Breaker Tolerance (%) of the instrument.
struct dynamic_circuit_breaker_tolerances {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Electronic Order Book
struct electronic_order_book {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Event Code: Start or end of day event code.
struct event_code {
    enum class type : char {
        end_of_day = 'C',
        start_of_day = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Size: Total executed quantity.
struct executed_size {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Firm Quote Book
struct firm_quote_book {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Fourth Reserved 8: Reserved for future use.
struct fourth_reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Hidden Execution Indicator: For London Stock Exchange, during continuous trading and CPX session, 1[2] will be sent for execution of visible[hidden] quantities. For London Stock Exchange Auction Trades, 0 will be sent indicating 'Not Applicable' (N/A).
struct hidden_execution_indicator {
    enum class type : std::uint8_t {
        na = 0,
        visible = 1,
        hidden = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Quantity: Quantity that is eligible to be matched at the indicative price but will not be matched.
struct imbalance_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Instrument: GTP Instrument identifier.
struct instrument {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Isin: ISIN Code of an instrument.
struct isin {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Length: Length of the message block including the header and all payload messages
struct length_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Data Group: Identity of the market data group the payload messages relate to
struct market_data_group {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Message Count: Number of payload messages that will follow the header
struct message_count {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Length of message including this field
struct message_length {
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
    enum class type : std::uint8_t {
        system_event_message = 83,
        instrument_directory_message = 112,
        instrument_status_message = 72,
        add_order_mbo_message = 65,
        add_order_short_mbo_message = 101,
        order_book_clear_message = 121,
        trade_message = 80,
        statistics_message = 119,
        statistics_update_message = 106,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// New End Time: New time the session will end. The field will contain only spaces if Session Change Reason is '0' or the Session Change Reason is not present. New End Time will be in terms of the local time on the server (i.e., not UTC).
struct new_end_time {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Number Of Trades: Count of all trades for the day.
struct number_of_trades {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Trades On Book Only: Count of trades for the day excluding off-book trades.
struct number_of_trades_on_book_only {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Off Book: Off-book
struct off_book {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Opening Closing Price Indicator: Populated if the Statistic Type is 2 or 3.
struct opening_closing_price_indicator {
    enum class type : char {
        ut = 'A',
        at = 'B',
        mid_of_bbo = 'C',
        last_at = 'D',
        last_ut = 'E',
        manual = 'F',
        previous_close = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Book Type: Order book the status applies to.
struct order_book_type {
    enum class type : std::uint8_t {
        firm_quote_book = 1,
        off_book = 2,
        electronic_order_book = 3,
        private_rfq = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Id: Unique identifier of the order.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant: Identity of trading participant that submitted the order.
struct participant {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Partition Id: Trading System's partition in which the instrument is traded.
struct partition_id {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Price: Limit price of the order.
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Private Rfq
struct private_rfq {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
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

// Reserved 11: Reserved for future use.
struct reserved_11 {
    using type = std::span<const std::byte, 11>;
    static constexpr std::size_t size = 11;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 11> value_;
};

// Reserved 12: Reserved for future use.
struct reserved_12 {
    using type = std::span<const std::byte, 12>;
    static constexpr std::size_t size = 12;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 12> value_;
};

// Reserved 4: Reserved for future use.
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 8: Reserved for future use.
struct reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Reserved 8: Reserved for future use.
struct second_reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Segment: Segment the instrument is assigned to.
struct segment {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Sequence Number: Sequence number of the first payload message
struct sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Change Reason: Reason the trading session changed.
struct session_change_reason {
    enum class type : std::uint8_t {
        scheduled_transition = 0,
        extended_by_market_ops = 1,
        shortened_by_market_ops = 2,
        market_order_imbalance = 3,
        price_outside_range = 4,
        aesp_circuit_breaker_tripped = 5,
        unavailable = 9,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side: Side of the order.
struct side {
    enum class type : char {
        buy_order = 'B',
        sell_order = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Size: Displayed size of the order.
struct size_type {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Source Venue: Venue from which market data is received for the instrument.
struct source_venue {
    enum class type : std::uint16_t {
        london_stock_exchange = 1,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Static Circuit Breaker Tolerances: Static Circuit Breaker Tolerance (%) of the instrument.
struct static_circuit_breaker_tolerances {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Statistic Price: The value of price type statistics. If the Opening or Closing Price is cleared manually by the venue, '-1' will be stamped.
struct statistic_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Statistic Size: The value of size type statistics.
struct statistic_size {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Statistic Type: The statistic that is disseminated with this message instance.
struct statistic_type {
    enum class type : std::uint16_t {
        indicative_auction_uncrossing_data = 1,
        official_opening_price = 2,
        official_closing_price = 3,
        trade_high_on_book = 4,
        trade_low_on_book = 5,
        trade_high_all_trades = 6,
        trade_low_all_trades = 7,
        fifty_two_week_trade_high_all_trades = 8,
        fifty_two_week_trade_low_all_trades = 9,
        best_closing_bid = 10,
        best_closing_ask = 11,
        static_reference_price = 16,
        dynamic_reference_price = 17,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Third Reserved 8: Reserved for future use.
struct third_reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tick Id: The tick structure applicable for the instrument.
struct tick_id {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Timestamp: Time the message was generated.
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Cancellation
struct trade_cancellation {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Trade Correction
struct trade_correction {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Trade Id: Unique identifier of the trade.
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Qualifier: Qualifier of the trade.
struct trade_qualifier {
    enum class type : char {
        na = ' ',
        closing_price_cross_cpx = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Type: Type of the trade.
struct trade_type {
    enum class type : std::uint8_t {
        regular_or_continuous_trade = 0,
        auction_trade_bulk = 1,
        auction_trade_individual = 2,
        on_book_trade_cancellation = 9,
        trade_correction = 11,
        rfq_trade = 22,
        rfq_trade_cancellation = 23,
        rfq_trade_correction = 24,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Status: Current trading status of the instrument.
struct trading_status {
    enum class type : char {
        halt = 'H',
        halt_matching_partition_suspended = 'J',
        halt_system_suspended = 'K',
        regular_trading_start_trade_reporting = 'T',
        halt_regulatory = 'P',
        end_trade_reporting = 't',
        opening_auction_call = 'a',
        post_close = 'b',
        closed = 'c',
        closing_auction_call = 'd',
        aesp_auction_call = 'e',
        resume_auction = 'f',
        pre_mandatory = 'm',
        mandatory = 'n',
        post_mandatory = 'o',
        edsp_auction_call = 'q',
        periodic_auction_call = 'r',
        inactive = '1',
        suspended = '2',
        no_active_session = 'w',
        end_of_post_close = 'x',
        closing_price_crossing_session = 'u',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Transaction Time: Execution timestamp as reported by the supported market. If a trade is cancelled or amended, this field will contain the transaction time of the original trade.
struct transaction_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Turnover: Turnover of all trades for the day.
struct turnover {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Turnover On Book Only: Turnover for the day excluding off-book trades.
struct turnover_on_book_only {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unused 1: Reserved
struct unused_1 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Unused 3: Reserved
struct unused_3 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xE0ULL;
    static constexpr int shift = 5;
};

// Unused 6: Reserved
struct unused_6 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFCULL;
    static constexpr int shift = 2;
};

// Venue Instrument Id: Instrument identifier used by the source venue.
struct venue_instrument_id {
    using type = std::string_view;
    static constexpr std::size_t size = 11;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 11> value_;
};

// Volume: Cumulative volume of all trades for the trading day.
struct volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume On Book Only: Cumulative volume for the trading day excluding off-book trades.
struct volume_on_book_only {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Vwap: Volume weighted average price for the day for all trades.
struct vwap {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Vwap On Book Only: Volume weighted average price for the day excluding off-book trades.
struct vwap_on_book_only {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Statistics Update Message: Contains a set of statistics that are not updated frequently.
struct statistics_update_message {
    static constexpr std::string_view name = "Statistics Update Message";
    static constexpr std::size_t size = 47;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument,
        source_venue,
        statistic_type,
        statistic_price,
        statistic_size,
        auction_type,
        imbalance_quantity,
        auction_info,
        opening_closing_price_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(instrument);
    GTPFIELD(source_venue);
    GTPFIELD(statistic_type);
    GTPFIELD(statistic_price);
    GTPFIELD(statistic_size);
    GTPFIELD(auction_type);
    GTPFIELD(imbalance_quantity);
    GTPFIELD(auction_info);
    GTPFIELD(opening_closing_price_indicator);
};

static_assert(sizeof(statistics_update_message) == statistics_update_message::size, "statistics_update_message lies over its bytes exactly");

// Statistics Message: Contains a set of statistics that are updated frequently, usually as a result of executions.
struct statistics_message {
    static constexpr std::string_view name = "Statistics Message";
    static constexpr std::size_t size = 74;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument,
        source_venue,
        volume,
        volume_on_book_only,
        vwap,
        vwap_on_book_only,
        number_of_trades,
        number_of_trades_on_book_only,
        turnover,
        turnover_on_book_only>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(instrument);
    GTPFIELD(source_venue);
    GTPFIELD(volume);
    GTPFIELD(volume_on_book_only);
    GTPFIELD(vwap);
    GTPFIELD(vwap_on_book_only);
    GTPFIELD(number_of_trades);
    GTPFIELD(number_of_trades_on_book_only);
    GTPFIELD(turnover);
    GTPFIELD(turnover_on_book_only);
};

static_assert(sizeof(statistics_message) == statistics_message::size, "statistics_message lies over its bytes exactly");

// Trade Flags
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

// Trade Message: Sent to indicate trades executed on supported markets.
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 63;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        transaction_time,
        source_venue,
        executed_size,
        instrument,
        price,
        reserved_8,
        trade_id,
        trade_type,
        auction_type,
        trade_flags,
        hidden_execution_indicator,
        trade_qualifier>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(transaction_time);
    GTPFIELD(source_venue);
    GTPFIELD(executed_size);
    GTPFIELD(instrument);
    GTPFIELD(price);
    GTPFIELD(reserved_8);
    GTPFIELD(trade_id);
    GTPFIELD(trade_type);
    GTPFIELD(auction_type);
    GTPFIELD(trade_flags);
    GTPFIELD(hidden_execution_indicator);
    GTPFIELD(trade_qualifier);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Book Clear Message: Sent to instruct recipients to remove all orders from the order book for the specified instrument.
struct order_book_clear_message {
    static constexpr std::string_view name = "Order Book Clear Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        source_venue,
        instrument,
        order_book_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(source_venue);
    GTPFIELD(instrument);
    GTPFIELD(order_book_type);
};

static_assert(sizeof(order_book_clear_message) == order_book_clear_message::size, "order_book_clear_message lies over its bytes exactly");

// Add Order Short Mbo Message: Used to indicate individual orders of an MBO snapshot.
struct add_order_short_mbo_message {
    static constexpr std::string_view name = "Add Order Short Mbo Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_id,
        size_type,
        price,
        reserved_8,
        participant>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(order_id);
    GTPFIELD(size_type);
    GTPFIELD(price);
    GTPFIELD(reserved_8);
    GTPFIELD(participant);
};

static_assert(sizeof(add_order_short_mbo_message) == add_order_short_mbo_message::size, "add_order_short_mbo_message lies over its bytes exactly");

// Add Order Mbo Message: Indicates the first order of a given side of an MBO snapshot.
struct add_order_mbo_message {
    static constexpr std::string_view name = "Add Order Mbo Message";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        order_id,
        side,
        size_type,
        instrument,
        price,
        reserved_8,
        source_venue,
        order_book_type,
        participant,
        depth>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(order_id);
    GTPFIELD(side);
    GTPFIELD(size_type);
    GTPFIELD(instrument);
    GTPFIELD(price);
    GTPFIELD(reserved_8);
    GTPFIELD(source_venue);
    GTPFIELD(order_book_type);
    GTPFIELD(participant);
    GTPFIELD(depth);
};

static_assert(sizeof(add_order_mbo_message) == add_order_mbo_message::size, "add_order_mbo_message lies over its bytes exactly");

// Instrument Status Message: Used to communicate scheduled and unscheduled session changes. When sent in the recovery channel, used to indicate the current trading status of an instrument.
struct instrument_status_message {
    static constexpr std::string_view name = "Instrument Status Message";
    static constexpr std::size_t size = 27;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument,
        source_venue,
        trading_status,
        session_change_reason,
        new_end_time,
        order_book_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(instrument);
    GTPFIELD(source_venue);
    GTPFIELD(trading_status);
    GTPFIELD(session_change_reason);
    GTPFIELD(new_end_time);
    GTPFIELD(order_book_type);
};

static_assert(sizeof(instrument_status_message) == instrument_status_message::size, "instrument_status_message lies over its bytes exactly");

// Allowed Book Types: Defines the order-book types that are allowed for the instrument
struct allowed_book_types {
    static constexpr std::string_view name = "Allowed Book Types";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(allowed_book_types) == allowed_book_types::size, "allowed_book_types lies over its bytes exactly");

// Instrument Directory Message: Used to disseminate a common and limited set of data for all configured instrument types, except strategy instruments, on the real-time channels.
struct instrument_directory_message {
    static constexpr std::string_view name = "Instrument Directory Message";
    static constexpr std::size_t size = 138;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        instrument,
        isin,
        allowed_book_types,
        source_venue,
        venue_instrument_id,
        tick_id,
        reserved_8,
        dynamic_circuit_breaker_tolerances,
        static_circuit_breaker_tolerances,
        segment,
        reserved_12,
        reserved_11,
        currency,
        partition_id,
        reserved_4,
        average_daily_turnover_adt,
        second_reserved_8,
        reserved_1,
        third_reserved_8,
        fourth_reserved_8>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(instrument);
    GTPFIELD(isin);
    GTPFIELD(allowed_book_types);
    GTPFIELD(source_venue);
    GTPFIELD(venue_instrument_id);
    GTPFIELD(tick_id);
    GTPFIELD(reserved_8);
    GTPFIELD(dynamic_circuit_breaker_tolerances);
    GTPFIELD(static_circuit_breaker_tolerances);
    GTPFIELD(segment);
    GTPFIELD(reserved_12);
    GTPFIELD(reserved_11);
    GTPFIELD(currency);
    GTPFIELD(partition_id);
    GTPFIELD(reserved_4);
    GTPFIELD(average_daily_turnover_adt);
    GTPFIELD(second_reserved_8);
    GTPFIELD(reserved_1);
    GTPFIELD(third_reserved_8);
    GTPFIELD(fourth_reserved_8);
};

static_assert(sizeof(instrument_directory_message) == instrument_directory_message::size, "instrument_directory_message lies over its bytes exactly");

// System Event Message: Sent to indicate the start and end of the day.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        event_code,
        source_venue>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(timestamp);
    GTPFIELD(event_code);
    GTPFIELD(source_venue);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Gtp Udp Message Header
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
    GTPFIELD(message_length);
    GTPFIELD(message_type);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Unit Header
struct unit_header {
    static constexpr std::string_view name = "Unit Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        length_type,
        message_count,
        market_data_group,
        sequence_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    GTPFIELD(length_type);
    GTPFIELD(message_count);
    GTPFIELD(market_data_group);
    GTPFIELD(sequence_number);
};

static_assert(sizeof(unit_header) == unit_header::size, "unit_header lies over its bytes exactly");

// Packet: Gtp Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    GTPSEQUENCE(message);
};

#pragma pack(pop)

} // namespace lseg::lse::level2mbo::gtp::v26_2
