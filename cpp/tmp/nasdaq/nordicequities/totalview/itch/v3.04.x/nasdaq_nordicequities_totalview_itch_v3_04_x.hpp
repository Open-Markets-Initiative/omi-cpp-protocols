// Nasdaq NordicEquities TotalView Itch 3.04.X Template Meta Programming

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

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

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

// Add Quantity: Lit volume of the aggressive order added to the book
struct add_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Aggressing Side: Side of the incoming aggressive order
struct aggressing_side {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        none = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Aod Mic: Venue Mic if an auction on demand order book applies
struct aod_mic {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Attribution: Market participant identifier of the order
struct attribution {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Bb Buy Back
struct bb_buy_back {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Best Ask Price: Best ask price, or zero if the book is crossed
struct best_ask_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Ask Quantity: Ask volume at top of book
struct best_ask_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Bid Price: Best bid price, or zero if the book is crossed
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

// Best Bid Quantity: Bid volume at top of book
struct best_bid_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Br Company Bankruptcy
struct br_company_bankruptcy {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Bs Excluding Comb Bonus Split
struct bs_excluding_comb_bonus_split {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Buy Sell Indicator: The type of order being added
struct buy_sell_indicator {
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

// Canceled Quantity: Number of shares removed from the display size
struct canceled_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ce Capped By Esma
struct ce_capped_by_esma {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Cross Level: The level the cross is being generated for
struct cross_level {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        mid = 'M',
        limit = 'L',
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

// Cross Type: The cross session the message is generated for
struct cross_type {
    enum class type : char {
        opening_cross = 'O',
        scheduled_intraday_cross = 'I',
        closing_cross = 'C',
        cross_for_halted_securities = 'H',
        auction_on_demand = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Cs Cent Shares
struct cs_cent_shares {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Currency: Currency of the notional amount
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Da Digital Asset
struct da_digital_asset {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Em Exceptional Circumstances Related To Market Maker
struct em_exceptional_circumstances_related_to_market_maker {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Equilibrium Price: Equilibrium price if the order book is crossed
struct equilibrium_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code: System event code
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

// Ew Marketwide Exceptional Circumstance
struct ew_marketwide_exceptional_circumstance {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Executed Quantity: The number of shares executed
struct executed_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Extension: Whether the cross has been extended
struct extension {
    enum class type : char {
        cross_extension = 'E',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Far Price: Highest or lowest price of the match
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

// Fe Foreign Non Eueea Entity
struct fe_foreign_non_eueea_entity {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Financial Product: Type of financial product
struct financial_product {
    enum class type : std::uint8_t {
        stock = 1,
        equity_warrant = 2,
        equity_right = 3,
        bond = 4,
        lottery_bond_series = 6,
        convertible = 7,
        warrant = 8,
        unit_trust_certificate = 11,
        index_fund_unit = 12,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Fn First North Company
struct fn_first_north_company {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Hidden Quantity: Total hidden quantity matched
struct hidden_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Direction: The market side of the order imbalance
struct imbalance_direction {
    enum class type : char {
        buy_imbalance = 'B',
        sell_imbalance = 'S',
        no_imbalance = 'N',
        insufficient_orders_to_calculate = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Quantity: Shares not paired at the reference price
struct imbalance_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Isin: Isin code identifying security
struct isin {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Kb Knock Out Buy Back
struct kb_knock_out_buy_back {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Kn Knockout Buy Back Into Next Trading Day
struct kn_knockout_buy_back_into_next_trading_day {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Market Segment Id: Market segment this order book belongs to
struct market_segment_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Match Number: Day unique match number of this execution
struct match_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
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
        system_event_message = 'S',
        order_book_trading_action_message = 'H',
        order_book_directory_message = 'R',
        add_order_message = 'A',
        add_order_mpid_attribution_message = 'F',
        order_executed_message = 'E',
        order_executed_with_price_message = 'C',
        order_cancel_message = 'X',
        order_delete_message = 'D',
        order_book_flush_message = 'Y',
        order_replace_message = 'U',
        trade_message = 'P',
        cross_trade_message = 'Q',
        broken_trade_message = 'B',
        noii_message = 'I',
        moii_message = 'J',
        execution_summary_message = 'K',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mic: Market identifier code
struct mic {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Mpid: The Mpid of the order, if public
struct mpid {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Mpid Counterparty: The Mpid of the counterparty, if public
struct mpid_counterparty {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Mpid Owner: The Mpid of the order, if public
struct mpid_owner {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Multiplier For Calculating Quantity In Measurement Unit: Multiplier to calculate quantity in measurement units
struct multiplier_for_calculating_quantity_in_measurement_unit {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// New Order Reference Number: New reference number for this order
struct new_order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nm New Market Company
struct nm_new_market_company {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Nordic Mid Mic: Venue Mic if a Nordic At Mid order book applies
struct nordic_mid_mic {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Notation Of Qty: Measurement units the quantity is expressed in
struct notation_of_qty {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Notional Amount: Notional amount if specified
struct notional_amount {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -5;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Lit Executions: Total number of partial lit executions
struct number_of_lit_executions {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Trades: Number of trades in the cross
struct number_of_trades {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ob Observation Status
struct ob_observation_status {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Order Book: Order book id
struct order_book {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Reference Number: Unique reference number assigned to the new order
struct order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Order Reference Number: Reference number of the order being replaced
struct original_order_reference_number {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Quantity: Shares eligible to match at the reference price
struct paired_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id Buyer: The Mpid of the buyer, if public
struct participant_id_buyer {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Participant Id Seller: The Mpid of the seller, if public
struct participant_id_seller {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Pd Price Discrepancy Historical Average Share Classes
struct pd_price_discrepancy_historical_average_share_classes {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Po Company Subject To Public Offer
struct po_company_subject_to_public_offer {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Price: Display price of the new order
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

// Price Notation: Populated with M if price is monetary value
struct price_notation {
    enum class type : char {
        monetary_value = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Printable: Whether the execution should be reflected in statistics
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

// Pure Stream Mic: Venue Mic if a PureStream order book applies
struct pure_stream_mic {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Quantity: Total number of shares in the order
struct quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reason: Halt reason code
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Reserved 18
struct reserved_18 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xFFULL;
    static constexpr int shift = 0;
};

// Reserved 23
struct reserved_23 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0x6ULL;
    static constexpr int shift = 1;
};

// Reserved 5
struct reserved_5 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Reserved 58
struct reserved_58 {
    using type = std::uint8_t;
    static constexpr std::uint64_t mask = 0xF0ULL;
    static constexpr int shift = 4;
};

// Rl Removal From Listing In Process
struct rl_removal_from_listing_in_process {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Round Lot Size: Number of shares representing a round lot
struct round_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Rs Reversed Split
struct rs_reversed_split {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
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

// Sk Soft Knock
struct sk_soft_knock {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Sl Other Surveillance List Reason
struct sl_other_surveillance_list_reason {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Sm Stressed Market
struct sm_stressed_market {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// So Sold Out Buy Back
struct so_sold_out_buy_back {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Sp Excluding Participating In Split
struct sp_excluding_participating_in_split {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Sr Excluding Comb Split And Issue Rights
struct sr_excluding_comb_split_and_issue_rights {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Ss Excluding Comb Split Redemption Share
struct ss_excluding_comb_split_redemption_share {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Stp Cancel Quantity: Quantity deleted due to self trade prevention
struct stp_cancel_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Su Suspension
struct su_suspension {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Symbol: Human readable name of the security
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 16;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 16> value_;
};

// Symbol State: Trading state of the order book
struct symbol_state {
    enum class type : char {
        closed = 'C',
        pre_open = 'P',
        opening_auction = 'O',
        continuous_trading = 'T',
        scheduled_intraday_auction = 'I',
        closing_auction = 'L',
        post_trade = 'S',
        halted = 'H',
        auction_period = 'Q',
        trading_at_closing_price = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Timestamp: Nanoseconds since midnight
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// To A Significant Reverse Takeover Pending
struct to_a_significant_reverse_takeover_pending {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Tracking Number: Nasdaq Nordic internal tracking number
struct tracking_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price: The price at which the order execution occurred
struct trade_price {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Type: Where a non displayed order has been executed
struct trade_type {
    enum class type : char {
        main_book = 'B',
        nordic_mid = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Ud Under Drawing
struct ud_under_drawing {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Ul Un Listed
struct ul_un_listed {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Un Underlying Not Quoted
struct un_underlying_not_quoted {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Wi When Issued
struct wi_when_issued {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Xd Excluding Dividend
struct xd_excluding_dividend {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Xr Excluding Participating In Rights
struct xr_excluding_participating_in_rights {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Execution Summary Message: Summary information disseminated before the individual trades
struct execution_summary_message {
    static constexpr std::string_view name = "Execution Summary Message";
    static constexpr std::size_t size = 37;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_book,
        aggressing_side,
        quantity,
        hidden_quantity,
        stp_cancel_quantity,
        far_price,
        add_quantity,
        number_of_lit_executions>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_book);
    ITCHFIELD(aggressing_side);
    ITCHFIELD(quantity);
    ITCHFIELD(hidden_quantity);
    ITCHFIELD(stp_cancel_quantity);
    ITCHFIELD(far_price);
    ITCHFIELD(add_quantity);
    ITCHFIELD(number_of_lit_executions);
};

static_assert(sizeof(execution_summary_message) == execution_summary_message::size, "execution_summary_message lies over its bytes exactly");

// Moii Message: Auction on demand order imbalance indicator
struct moii_message {
    static constexpr std::string_view name = "Moii Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        paired_quantity,
        order_book,
        equilibrium_price,
        cross_type,
        cross_level>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(paired_quantity);
    ITCHFIELD(order_book);
    ITCHFIELD(equilibrium_price);
    ITCHFIELD(cross_type);
    ITCHFIELD(cross_level);
};

static_assert(sizeof(moii_message) == moii_message::size, "moii_message lies over its bytes exactly");

// Noii Message: Net order imbalance indicator disseminated during a cross auction
struct noii_message {
    static constexpr std::string_view name = "Noii Message";
    static constexpr std::size_t size = 60;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        paired_quantity,
        imbalance_quantity,
        imbalance_direction,
        order_book,
        equilibrium_price,
        cross_type,
        best_bid_price,
        best_bid_quantity,
        best_ask_price,
        best_ask_quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(paired_quantity);
    ITCHFIELD(imbalance_quantity);
    ITCHFIELD(imbalance_direction);
    ITCHFIELD(order_book);
    ITCHFIELD(equilibrium_price);
    ITCHFIELD(cross_type);
    ITCHFIELD(best_bid_price);
    ITCHFIELD(best_bid_quantity);
    ITCHFIELD(best_ask_price);
    ITCHFIELD(best_ask_quantity);
};

static_assert(sizeof(noii_message) == noii_message::size, "noii_message lies over its bytes exactly");

// Broken Trade Message: An execution has been broken and cannot be reinstated
struct broken_trade_message {
    static constexpr std::string_view name = "Broken Trade Message";
    static constexpr std::size_t size = 14;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        match_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(match_number);
};

static_assert(sizeof(broken_trade_message) == broken_trade_message::size, "broken_trade_message lies over its bytes exactly");

// Cross Trade Message: The cross process has completed for a specific security
struct cross_trade_message {
    static constexpr std::string_view name = "Cross Trade Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        quantity,
        order_book,
        cross_price,
        match_number,
        cross_type,
        number_of_trades>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(quantity);
    ITCHFIELD(order_book);
    ITCHFIELD(cross_price);
    ITCHFIELD(match_number);
    ITCHFIELD(cross_type);
    ITCHFIELD(number_of_trades);
};

static_assert(sizeof(cross_trade_message) == cross_trade_message::size, "cross_trade_message lies over its bytes exactly");

// Trade Message: Execution details for a match involving non displayable order types
struct trade_message {
    static constexpr std::string_view name = "Trade Message";
    static constexpr std::size_t size = 43;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number,
        trade_type,
        quantity,
        order_book,
        match_number,
        trade_price,
        participant_id_buyer,
        participant_id_seller>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(trade_type);
    ITCHFIELD(quantity);
    ITCHFIELD(order_book);
    ITCHFIELD(match_number);
    ITCHFIELD(trade_price);
    ITCHFIELD(participant_id_buyer);
    ITCHFIELD(participant_id_seller);
};

static_assert(sizeof(trade_message) == trade_message::size, "trade_message lies over its bytes exactly");

// Order Replace Message: An order on the book has been cancel replaced
struct order_replace_message {
    static constexpr std::string_view name = "Order Replace Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        original_order_reference_number,
        new_order_reference_number,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(original_order_reference_number);
    ITCHFIELD(new_order_reference_number);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
};

static_assert(sizeof(order_replace_message) == order_replace_message::size, "order_replace_message lies over its bytes exactly");

// Order Book Flush Message: An order book is flushed and all orders removed
struct order_book_flush_message {
    static constexpr std::string_view name = "Order Book Flush Message";
    static constexpr std::size_t size = 14;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_book>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_book);
};

static_assert(sizeof(order_book_flush_message) == order_book_flush_message::size, "order_book_flush_message lies over its bytes exactly");

// Order Delete Message: An order on the book being cancelled in full
struct order_delete_message {
    static constexpr std::string_view name = "Order Delete Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
};

static_assert(sizeof(order_delete_message) == order_delete_message::size, "order_delete_message lies over its bytes exactly");

// Order Cancel Message: An order on the book modified by a partial cancellation
struct order_cancel_message {
    static constexpr std::string_view name = "Order Cancel Message";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number,
        canceled_quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(canceled_quantity);
};

static_assert(sizeof(order_cancel_message) == order_cancel_message::size, "order_cancel_message lies over its bytes exactly");

// Order Executed With Price Message: An order executed at a price different to its display price
struct order_executed_with_price_message {
    static constexpr std::string_view name = "Order Executed With Price Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number,
        executed_quantity,
        match_number,
        printable,
        trade_price,
        mpid_owner,
        mpid_counterparty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(match_number);
    ITCHFIELD(printable);
    ITCHFIELD(trade_price);
    ITCHFIELD(mpid_owner);
    ITCHFIELD(mpid_counterparty);
};

static_assert(sizeof(order_executed_with_price_message) == order_executed_with_price_message::size, "order_executed_with_price_message lies over its bytes exactly");

// Order Executed Message: Sent whenever an order on the book is executed in whole or in part
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 34;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number,
        executed_quantity,
        match_number,
        mpid,
        mpid_counterparty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(match_number);
    ITCHFIELD(mpid);
    ITCHFIELD(mpid_counterparty);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Add Order Mpid Attribution Message: An order added to the book with Mpid attribution
struct add_order_mpid_attribution_message {
    static constexpr std::string_view name = "Add Order Mpid Attribution Message";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number,
        buy_sell_indicator,
        quantity,
        order_book,
        price,
        attribution>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(buy_sell_indicator);
    ITCHFIELD(quantity);
    ITCHFIELD(order_book);
    ITCHFIELD(price);
    ITCHFIELD(attribution);
};

static_assert(sizeof(add_order_mpid_attribution_message) == add_order_mpid_attribution_message::size, "add_order_mpid_attribution_message lies over its bytes exactly");

// Add Order Message: An order added to the book without Mpid attribution
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 31;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_reference_number,
        buy_sell_indicator,
        quantity,
        order_book,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_reference_number);
    ITCHFIELD(buy_sell_indicator);
    ITCHFIELD(quantity);
    ITCHFIELD(order_book);
    ITCHFIELD(price);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Note Codes Bit Field 8: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_8 {
    static constexpr std::string_view name = "Note Codes Bit Field 8";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_8) == note_codes_bit_field_8::size, "note_codes_bit_field_8 lies over its bytes exactly");

// Note Codes Bit Field 7: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_7 {
    static constexpr std::string_view name = "Note Codes Bit Field 7";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_7) == note_codes_bit_field_7::size, "note_codes_bit_field_7 lies over its bytes exactly");

// Note Codes Bit Field 6: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_6 {
    static constexpr std::string_view name = "Note Codes Bit Field 6";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_6) == note_codes_bit_field_6::size, "note_codes_bit_field_6 lies over its bytes exactly");

// Note Codes Bit Field 5: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_5 {
    static constexpr std::string_view name = "Note Codes Bit Field 5";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_5) == note_codes_bit_field_5::size, "note_codes_bit_field_5 lies over its bytes exactly");

// Note Codes Bit Field 4: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_4 {
    static constexpr std::string_view name = "Note Codes Bit Field 4";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_4) == note_codes_bit_field_4::size, "note_codes_bit_field_4 lies over its bytes exactly");

// Note Codes Bit Field 3: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_3 {
    static constexpr std::string_view name = "Note Codes Bit Field 3";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_3) == note_codes_bit_field_3::size, "note_codes_bit_field_3 lies over its bytes exactly");

// Note Codes Bit Field 2: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_2 {
    static constexpr std::string_view name = "Note Codes Bit Field 2";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_2) == note_codes_bit_field_2::size, "note_codes_bit_field_2 lies over its bytes exactly");

// Note Codes Bit Field 1: Note codes, logical Or is used to identify multiple note codes
struct note_codes_bit_field_1 {
    static constexpr std::string_view name = "Note Codes Bit Field 1";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(note_codes_bit_field_1) == note_codes_bit_field_1::size, "note_codes_bit_field_1 lies over its bytes exactly");

// Order Book Directory Message: Disseminated for all active order books at the start of each trading day
struct order_book_directory_message {
    static constexpr std::string_view name = "Order Book Directory Message";
    static constexpr std::size_t size = 100;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_book,
        symbol,
        isin,
        financial_product,
        trading_currency,
        mic,
        market_segment_id,
        note_codes_bit_field_1,
        note_codes_bit_field_2,
        note_codes_bit_field_3,
        note_codes_bit_field_4,
        note_codes_bit_field_5,
        note_codes_bit_field_6,
        note_codes_bit_field_7,
        note_codes_bit_field_8,
        round_lot_size,
        nordic_mid_mic,
        aod_mic,
        notation_of_qty,
        notional_amount,
        currency,
        price_notation,
        multiplier_for_calculating_quantity_in_measurement_unit,
        pure_stream_mic>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_book);
    ITCHFIELD(symbol);
    ITCHFIELD(isin);
    ITCHFIELD(financial_product);
    ITCHFIELD(trading_currency);
    ITCHFIELD(mic);
    ITCHFIELD(market_segment_id);
    ITCHFIELD(note_codes_bit_field_1);
    ITCHFIELD(note_codes_bit_field_2);
    ITCHFIELD(note_codes_bit_field_3);
    ITCHFIELD(note_codes_bit_field_4);
    ITCHFIELD(note_codes_bit_field_5);
    ITCHFIELD(note_codes_bit_field_6);
    ITCHFIELD(note_codes_bit_field_7);
    ITCHFIELD(note_codes_bit_field_8);
    ITCHFIELD(round_lot_size);
    ITCHFIELD(nordic_mid_mic);
    ITCHFIELD(aod_mic);
    ITCHFIELD(notation_of_qty);
    ITCHFIELD(notional_amount);
    ITCHFIELD(currency);
    ITCHFIELD(price_notation);
    ITCHFIELD(multiplier_for_calculating_quantity_in_measurement_unit);
    ITCHFIELD(pure_stream_mic);
};

static_assert(sizeof(order_book_directory_message) == order_book_directory_message::size, "order_book_directory_message lies over its bytes exactly");

// Order Book Trading Action Message: Indicates the current trading status of a security
struct order_book_trading_action_message {
    static constexpr std::string_view name = "Order Book Trading Action Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        order_book,
        symbol_state,
        extension,
        reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
    ITCHFIELD(order_book);
    ITCHFIELD(symbol_state);
    ITCHFIELD(extension);
    ITCHFIELD(reason);
};

static_assert(sizeof(order_book_trading_action_message) == order_book_trading_action_message::size, "order_book_trading_action_message lies over its bytes exactly");

// System Event Message: Signals a market or data feed handler event
struct system_event_message {
    static constexpr std::string_view name = "System Event Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        timestamp,
        tracking_number,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(timestamp);
    ITCHFIELD(tracking_number);
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

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
