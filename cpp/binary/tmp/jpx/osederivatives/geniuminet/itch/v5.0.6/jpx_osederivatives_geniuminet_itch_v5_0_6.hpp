// Jpx OseDerivatives GeniumInet Itch 5.0.6 Template Meta Programming

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

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

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

// Available Ask Quantity At Equilibrium Price: Quantity at equilibrium price on the ask side
struct available_ask_quantity_at_equilibrium_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Available Bid Quantity At Equilibrium Price: Quantity at equilibrium price on the bid side
struct available_bid_quantity_at_equilibrium_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Lot Size
struct block_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Combination Orderbook Id: Identifier of combo orderbook
struct combination_orderbook_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Combo Group Id: Used to group combination executions
struct combo_group_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Counterparty Participant Id: Counterparty ID (blank for anonymous markets)
struct counterparty_participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Decimals In Nominal Value: Number of decimals in Nominal Value
struct decimals_in_nominal_value {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Decimals In Price: Number of decimals in price (256=fractions)
struct decimals_in_price {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Decimals In Strike Price
struct decimals_in_strike_price {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Equilibrium Price
struct equilibrium_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code: O=Start of Messages, C=End of Messages
struct event_code {
    enum class type : char {
        start_of_messages = 'O',
        end_of_messages = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executed Quantity: The quantity being executed
struct executed_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Date: Date of expiration
struct expiration_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Financial Product: Product type
struct financial_product {
    enum class type : std::uint8_t {
        option = 1,
        forward = 2,
        future = 3,
        fra = 4,
        cash = 5,
        payment = 6,
        exchange_rate = 7,
        interest_rate_swap = 8,
        repo = 9,
        synthetic_box_leg_or_reference = 10,
        combination = 11,
        guarantee = 12,
        otc_general = 13,
        equity_warrant = 14,
        security_lending = 15,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Force
struct force {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Isin: ISIN code
struct isin {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Leg Orderbook Id: Orderbook ID of Leg instrument
struct leg_orderbook_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio
struct leg_ratio {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Side
struct leg_side {
    enum class type : char {
        as_defined = 'B',
        opposite = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Long Name: Human-readable long name
struct long_name {
    using type = std::string_view;
    static constexpr std::size_t size = 32;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 32> value_;
};

// Lot Type
struct lot_type {
    enum class type : std::uint8_t {
        undefined = 0,
        odd_lot = 1,
        round_lot = 2,
        block_lot = 3,
        all_or_none_lot = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Bid
struct market_bid {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Match Id: Assigned by the system to each match executed
struct match_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

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
        seconds_message = 'T',
        order_book_directory = 'R',
        combination_orderbook_leg = 'M',
        tick_size_table_entry = 'L',
        system_event_message = 'S',
        order_book_state_message = 'O',
        add_order_no_mpid = 'A',
        add_order_with_mpid = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_replace_message = 'U',
        order_delete_message = 'D',
        trade_message = 'P',
        equilibrium_price_update = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Nanoseconds: Nanoseconds portion
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New Orderbook Position: New rank within orderbook
struct new_orderbook_position {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nominal Value
struct nominal_value {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Legs: Only for combination instruments
struct number_of_legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Occurred At Cross: Y=Yes, N=No
struct occurred_at_cross {
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

// Odd Lot Size
struct odd_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Book Id: Primary identifier of an order book
struct order_book_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Book Position: Rank within orderbook
struct order_book_position {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: Identifier assigned to the new order
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Override Crossing
struct override_crossing {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Owner Participant Id: Owner ID (blank for anonymous markets)
struct owner_participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Participant Id: Market participant identifier
struct participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Participant Id Counterparty: Counterparty ID (blank for anonymous markets)
struct participant_id_counterparty {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Participant Id Owner: Owner ID (blank for anonymous markets)
struct participant_id_owner {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Price: Display price
struct price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price From: Start of price range
struct price_from {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Stabilization
struct price_stabilization {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Price To: End of price range
struct price_to {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Printable: Y=Printable, N=Non-printable
struct printable {
    enum class type : char {
        non_printable = 'N',
        printable = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Put Or Call: 1=Call, 2=Put
struct put_or_call {
    enum class type : std::uint8_t {
        call = 1,
        put = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quantity: Visible quantity
struct quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 24: Reserved
struct reserved_24 {
    using type = std::span<const std::byte, 24>;
    static constexpr std::size_t size = 24;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 24> value_;
};

// Round Lot Size
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seconds: Unix time (seconds since 1970-01-01 00:00:00 UTC)
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Short Sell
struct short_sell {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Side: B=Buy, S=Sell
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

// State Name: Name of Order Book State
struct state_name {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Strike Price: Derivative strike price
struct strike_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol: Security short name
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 32;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 32> value_;
};

// Tick Size: Tick Size for the range
struct tick_size {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price: Execution price
struct trade_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Currency
struct trading_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Underlying Orderbook Id: Underlying instrument ID
struct underlying_orderbook_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Undisclosed
struct undisclosed {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Unused
struct unused {
    using type = std::uint16_t;
    static constexpr std::uint64_t mask = 0xFFC0ULL;
    static constexpr int shift = 6;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Equilibrium Price Update: Provides changes in equilibrium price during auctions.
struct equilibrium_price_update {
    static constexpr std::string_view name = "Equilibrium Price Update";
    static constexpr std::size_t size = 52;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_book_id,
        available_bid_quantity_at_equilibrium_price,
        available_ask_quantity_at_equilibrium_price,
        equilibrium_price,
        reserved_24>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_book_id);
    ITCHFIELD(available_bid_quantity_at_equilibrium_price);
    ITCHFIELD(available_ask_quantity_at_equilibrium_price);
    ITCHFIELD(equilibrium_price);
    ITCHFIELD(reserved_24);
};

static_assert(sizeof(equilibrium_price_update) == equilibrium_price_update::size, "equilibrium_price_update lies over its bytes exactly");

// Trade Message: Execution details for normal match events involving non-displayable order types or cross trades.
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 49;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        match_id,
        combo_group_id,
        side,
        quantity,
        order_book_id,
        trade_price,
        owner_participant_id,
        counterparty_participant_id,
        printable,
        occurred_at_cross>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(match_id);
    ITCHFIELD(combo_group_id);
    ITCHFIELD(side);
    ITCHFIELD(quantity);
    ITCHFIELD(order_book_id);
    ITCHFIELD(trade_price);
    ITCHFIELD(owner_participant_id);
    ITCHFIELD(counterparty_participant_id);
    ITCHFIELD(printable);
    ITCHFIELD(occurred_at_cross);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Delete Message: Sent whenever an order on the book is being deleted. There will be no remaining quantity.
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_id,
        order_book_id,
        side>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_id);
    ITCHFIELD(side);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Order Attributes: Additional order attributes
struct order_attributes {
    static constexpr std::string_view name = "Order Attributes";
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    type value_;
};

static_assert(sizeof(order_attributes) == order_attributes::size, "order_attributes lies over its bytes exactly");

// Order Replace Message: Sent whenever an existing order on the book has been modified. Note: Specification says this message is not used, but remains for future reference.
struct order_replace_message {
    static constexpr std::string_view name = "Order Replace Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_id,
        order_book_id,
        side,
        new_orderbook_position,
        quantity,
        price,
        order_attributes>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_id);
    ITCHFIELD(side);
    ITCHFIELD(new_orderbook_position);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
    ITCHFIELD(order_attributes);
};

static_assert(sizeof(order_replace_message) == order_replace_message::size, "order_replace_message lies over its bytes exactly");

// Order Executed With Price Message: Sent when an order is executed at a price different than the initial display price.
struct order_executed_with_price_message {
    static constexpr std::string_view name = "Order Executed With Price Message";
    static constexpr std::size_t size = 57;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_id,
        order_book_id,
        side,
        executed_quantity,
        match_id,
        combo_group_id,
        owner_participant_id,
        counterparty_participant_id,
        trade_price,
        occurred_at_cross,
        printable>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_id);
    ITCHFIELD(side);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(match_id);
    ITCHFIELD(combo_group_id);
    ITCHFIELD(owner_participant_id);
    ITCHFIELD(counterparty_participant_id);
    ITCHFIELD(trade_price);
    ITCHFIELD(occurred_at_cross);
    ITCHFIELD(printable);
};

static_assert(sizeof(order_executed_with_price_message) == order_executed_with_price_message::size, "order_executed_with_price_message lies over its bytes exactly");

// Order Executed Message: Sent whenever an order on the book is executed in whole or in part.
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 51;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_id,
        order_book_id,
        side,
        executed_quantity,
        match_id,
        combo_group_id,
        participant_id_owner,
        participant_id_counterparty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_id);
    ITCHFIELD(side);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(match_id);
    ITCHFIELD(combo_group_id);
    ITCHFIELD(participant_id_owner);
    ITCHFIELD(participant_id_counterparty);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Add Order With Mpid: New order accepted (attributed).
struct add_order_with_mpid {
    static constexpr std::string_view name = "Add Order With Mpid";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_id,
        order_book_id,
        side,
        order_book_position,
        quantity,
        price,
        order_attributes,
        lot_type,
        participant_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_id);
    ITCHFIELD(side);
    ITCHFIELD(order_book_position);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
    ITCHFIELD(order_attributes);
    ITCHFIELD(lot_type);
    ITCHFIELD(participant_id);
};

static_assert(sizeof(add_order_with_mpid) == add_order_with_mpid::size, "add_order_with_mpid lies over its bytes exactly");

// Add Order No Mpid: New order accepted (unattributed).
struct add_order_no_mpid {
    static constexpr std::string_view name = "Add Order No Mpid";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_id,
        order_book_id,
        side,
        order_book_position,
        quantity,
        price,
        order_attributes,
        lot_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_id);
    ITCHFIELD(side);
    ITCHFIELD(order_book_position);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
    ITCHFIELD(order_attributes);
    ITCHFIELD(lot_type);
};

static_assert(sizeof(add_order_no_mpid) == add_order_no_mpid::size, "add_order_no_mpid lies over its bytes exactly");

// Order Book State Message: Relays information on state changes.
struct order_book_state_message {
    static constexpr std::string_view name = "Order Book State Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_book_id,
        state_name>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_book_id);
    ITCHFIELD(state_name);
};

static_assert(sizeof(order_book_state_message) == order_book_state_message::size, "order_book_state_message lies over its bytes exactly");

// System Event Message: Signals a market or data feed handler event.
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(event_code);
};

static_assert(sizeof(system_event_message) == system_event_message::size, "system_event_message lies over its bytes exactly");

// Tick Size Table Entry: Information on a tick size for a price range.
struct tick_size_table_entry {
    static constexpr std::string_view name = "Tick Size Table Entry";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_book_id,
        tick_size,
        price_from,
        price_to>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_book_id);
    ITCHFIELD(tick_size);
    ITCHFIELD(price_from);
    ITCHFIELD(price_to);
};

static_assert(sizeof(tick_size_table_entry) == tick_size_table_entry::size, "tick_size_table_entry lies over its bytes exactly");

// Combination Orderbook Leg: Mapping between a combination orderbook and its leg orderbooks.
struct combination_orderbook_leg {
    static constexpr std::string_view name = "Combination Orderbook Leg";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        combination_orderbook_id,
        leg_orderbook_id,
        leg_side,
        leg_ratio>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(combination_orderbook_id);
    ITCHFIELD(leg_orderbook_id);
    ITCHFIELD(leg_side);
    ITCHFIELD(leg_ratio);
};

static_assert(sizeof(combination_orderbook_leg) == combination_orderbook_leg::size, "combination_orderbook_leg lies over its bytes exactly");

// Order Book Directory: Disseminated for all active securities at start of day or intra-day.
struct order_book_directory {
    static constexpr std::string_view name = "Order Book Directory";
    static constexpr std::size_t size = 128;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        order_book_id,
        symbol,
        long_name,
        isin,
        financial_product,
        trading_currency,
        decimals_in_price,
        decimals_in_nominal_value,
        odd_lot_size,
        round_lot_size,
        block_lot_size,
        nominal_value,
        number_of_legs,
        underlying_orderbook_id,
        strike_price,
        expiration_date,
        decimals_in_strike_price,
        put_or_call>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(order_book_id);
    ITCHFIELD(symbol);
    ITCHFIELD(long_name);
    ITCHFIELD(isin);
    ITCHFIELD(financial_product);
    ITCHFIELD(trading_currency);
    ITCHFIELD(decimals_in_price);
    ITCHFIELD(decimals_in_nominal_value);
    ITCHFIELD(odd_lot_size);
    ITCHFIELD(round_lot_size);
    ITCHFIELD(block_lot_size);
    ITCHFIELD(nominal_value);
    ITCHFIELD(number_of_legs);
    ITCHFIELD(underlying_orderbook_id);
    ITCHFIELD(strike_price);
    ITCHFIELD(expiration_date);
    ITCHFIELD(decimals_in_strike_price);
    ITCHFIELD(put_or_call);
};

static_assert(sizeof(order_book_directory) == order_book_directory::size, "order_book_directory lies over its bytes exactly");

// Seconds Message: Sent every second for which at least one ITCH message is being generated
struct seconds_message {
    static constexpr std::string_view name = "Seconds Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        seconds>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(seconds);
};

static_assert(sizeof(seconds_message) == seconds_message::size, "seconds_message lies over its bytes exactly");

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

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
