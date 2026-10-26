// Asx AsxDerivatives Ntp Itch 1.05 Template Meta Programming

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

namespace asx::asxderivatives::ntp::itch::v1_05 {

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

// Aot Lower Price: Lower range of the AOT.
struct aot_lower_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Aot Price: Anomalous Order Threshold price (AOT).
struct aot_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Aot Upper Price: Upper range of the AOT.
struct aot_upper_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Quantity: Total Ask Quantity available for execution.
struct ask_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Basis Of Quotation: Blank filled. Not available for ASX 24 products.
struct basis_of_quotation {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Bid Quantity: Total Bid Quantity available for execution.
struct bid_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Lot Size: Indicates the number of lots that represent a block lot for the order book.
struct block_lot_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buyer Combination Trade Id: A non-zero value indicates that this trade is part of an execution cycle for a combination trade from the E or P message.
struct buyer_combination_trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buyer Order Id: Reference number of the Buyer’s order – 0 if order is aggressive.
struct buyer_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buyer Participant Id: Buying participant identifier of the owner of the aggressive order.
struct buyer_participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Buyer Side: Type of order
struct buyer_side {
    enum class type : char {
        sell = 'S',
        buy = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Buyer Tradeable Instrument Id: Identifier of the Buyers Order Book.
struct buyer_tradeable_instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cfi Code: Indicates the type of security using ISO 10962 standard, CFI code values.
struct cfi_code {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Combination Trade Id: A non-zero value indicates that this trade is part of an execution cycle for a combination trade.
struct combination_trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Counter Party Id: Participant identifier of the aggressive party to the execution in non-anonymous markets. Space filled for anonymous instruments.
struct counter_party_id {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Coupon Rate: The coupon percentage rate for bonds.
struct coupon_rate {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cumulative Volume: Volume traded for the specified VOI Trade Date.
struct cumulative_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Currency: Currency of contract.
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Equilibrium Price: Price at which matching will occur.
struct equilibrium_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Etr Lower Price: Lower range of the ETR.
struct etr_lower_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Etr Price: Extreme Trade Range price (ETR), if zero, then MIR is not enforced.
struct etr_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Etr Upper Price: Upper range of the ETR.
struct etr_upper_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Code
struct event_code {
    enum class type : char {
        business_trade_date_has_ended = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Exchange: Denotes the exchange identifier of the contract
struct exchange {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Executed Quantity: Volume traded.
struct executed_quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiry Date: The Settlement Date as specified in the ASX 24 Contract Specifications. Reported in Unix Time (number of seconds since 00:00 1 January 1970 GMT). Convert to AEST/ADST as appropriate to determine the date.
struct expiry_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiry Month: Month of expiry for futures contract types, zero otherwise.
struct expiry_month {
    enum class type : std::uint8_t {
        jan = 1,
        feb = 2,
        mar = 3,
        apr = 4,
        may = 5,
        jun = 6,
        jul = 7,
        aug = 8,
        sep = 9,
        oct = 10,
        nov = 11,
        dec = 12,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Expiry Year: Year of expiry (YYYY) for futures contract types, zero otherwise.
struct expiry_year {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Highest Trade: Highest Traded Price.
struct highest_trade {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Instrument: Denotes the instrument identifier of the contract.
struct instrument {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Isin: Reserved for future use.
struct isin {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Last Trade: Last Traded Price.
struct last_trade {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Trading Date: The Last Trading Day as specified in the ASX 24 Contract Specifications. Reported in Unix Time (number of seconds since 00:00 1 January 1970 GMT). Convert to AEST/ADST as appropriate to determine the date.
struct last_trading_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Volume: Last Traded Volume.
struct last_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Legs: Number of legs.
struct legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Long Name: Additional instrument series information.
struct long_name {
    using type = std::string_view;
    static constexpr std::size_t size = 60;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 60> value_;
};

// Lot Size Or Face Value: The Contract Unit as specified in the ASX 24 Contract Specifications.
struct lot_size_or_face_value {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lowest Trade: Lowest Traded Price.
struct lowest_trade {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Matched Quantity: The indicative auction volume.
struct matched_quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maturity Value: The number of days or years to maturity for bills or bonds as specified in the ASX 24 Contract Specifications.
struct maturity_value {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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
        end_of_business_trade_date_message = 'S',
        future_symbol_directory_message = 'f',
        options_symbol_directory_message = 'h',
        combination_symbol_directory_message = 'M',
        bundles_symbol_directory = 'm',
        order_book_state_message = 'O',
        add_order_message = 'A',
        order_volume_cancelled_message = 'X',
        order_deleted_message = 'D',
        order_executed_message = 'E',
        auction_order_executed_message = 'C',
        combination_order_executed_message = 'e',
        implied_order_added_message = 'j',
        implied_order_replaced_message = 'l',
        implied_order_deleted_message = 'k',
        trade_executed_message = 'P',
        combination_trade_executed_message = 'p',
        trade_cancellation_message = 'B',
        equilibrium_price_message = 'Z',
        open_high_low_last_trade_adjustment_message = 't',
        market_settlement_message = 'Y',
        text_message = 'x',
        request_for_quote_message = 'q',
        anomalous_order_threshold_publish_message = 'W',
        volume_and_open_interest_message = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Interest: Number of open contracts at EOD for the specified VOI Trade Date.
struct open_interest {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opening Trade: Opening Traded Price.
struct opening_trade {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opposite Order Id: Public Order Id of the order to be removed from the opposite side of the same Order Book id, as order has traded out.
struct opposite_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opposite Side: Type of order
struct opposite_side {
    enum class type : char {
        sell = 'S',
        buy = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Opposite Tradeable Instrument Id: Identifier of the opposite Tradeable Instrument Id (references the combination Tradeable Instrument Id party to this trade).
struct opposite_tradeable_instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Option Type: Indicates the type of option
struct option_type {
    enum class type : char {
        put = 'P',
        call = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Book Priority: Time priority of this order within the order book.
struct order_book_priority {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: Public order id of the order.
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id Buyer: Participant identifier of the owner of the buying order. Blank for anonymous instruments.
struct participant_id_buyer {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Participant Id Seller: Participant identifier of the owner of the selling order. Blank for anonymous instruments.
struct participant_id_seller {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Payments Per Year: Number of payments per year for bonds.
struct payments_per_year {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: Price of the order.
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Display Decimals: Suggested number of decimals to display the price at.
struct price_display_decimals {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Fractional Denominator: Denominator of the price to yield the floating point price.
struct price_fractional_denominator {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Leg: Price of the leg
struct price_leg {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Method: Pricing method
struct price_method {
    enum class type : std::uint8_t {
        net_price = 0,
        yield_difference = 2,
        individual = 3,
        average_price = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price Minimum Tick: Minimum tick size. Divide by the Price Fractional Denominator to determine the floating point value.
struct price_minimum_tick {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prior Day Settlement: Prior Day Settlement price. Divide by the Price Fractional Denominator to determine the floating point value.
struct prior_day_settlement {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity: Number of lots added to the book (all volume is visible).
struct quantity {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity Remaining: Volume remaining on Order after matching, if 0, order has traded out and should be deleted.
struct quantity_remaining {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ratio Leg: Ratio of the leg
struct ratio_leg {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Rfq Side: Identifies side of the RFQ
struct rfq_side {
    enum class type : char {
        two_sided_quote = 'T',
        bid_quote = 'B',
        ask_quote = 'S',
        crossing = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Second: Unix time (number of seconds since 1970-01-01 00:00:00 UTC).
struct second {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seller Combination Trade Id: A non-zero value indicates that this trade is part of an execution cycle for a combination trade from the E or P message.
struct seller_combination_trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seller Order Id: Reference number of the Seller’s order – 0 if order is aggressive.
struct seller_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seller Participant Id: Selling participant identifier of the owner of the aggressive order.
struct seller_participant_id {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Seller Side: Type of order
struct seller_side {
    enum class type : char {
        sell = 'S',
        buy = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seller Tradeable Instrument Id: Identifier of the Seller’s Order Book.
struct seller_tradeable_instrument_id {
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

// Session State: Indicates the current session state for the contract as per
struct session_state {
    enum class type : char {
        pre_open = 'P',
        opened = 'O',
        regulatory_halt = 'R',
        halted = 'H',
        closed = 'C',
        maintenance = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side: Type of order
struct side {
    enum class type : char {
        sell = 'S',
        buy = 'B',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side Leg: Side of the leg
struct side_leg {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        not_defined = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Source Id: Indicates source of message.
struct source_id {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Strike: Strike price of contract. Divide by the Strike Price Fractional Denominator to determine the floating point value.
struct strike {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Decimal Position: Number of decimals to display the strike price.
struct strike_price_decimal_position {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Fractional Denominator: Denominator of the Strike Price to yield the floating point strike price.
struct strike_price_fractional_denominator {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Minimum Tick: Minimum tick size for the Strike Price. Divide by the Strike Price Fractional Denominator to determine the floating point value.
struct strike_price_minimum_tick {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol Name: The unique tradable instrument name.
struct symbol_name {
    using type = std::string_view;
    static constexpr std::size_t size = 32;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 32> value_;
};

// Text: Message being communicated.
struct text {
    using type = std::string_view;
    static constexpr std::size_t size = 100;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 100> value_;
};

// Total Traded Volume: Total Traded Volume.
struct total_traded_volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Date: Trade Date. Represented as number of days since 1 January 1970.
struct trade_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: Public trade id of the trade.
struct trade_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Price: Price of trade (may be negative for combination trades).
struct trade_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -2;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Type: Nature of the match
struct trade_type {
    enum class type : char {
        normal_trade = 'T',
        normal_cross = 't',
        auction_trade = 'L',
        auction_cross = 'l',
        combination_to_underlying_trade = 'S',
        combination_to_underlying_cross = 's',
        combination_to_combination_trade = 'R',
        combination_to_combination_cross = 'r',
        strip_to_strip_trade = 'A',
        strip_to_strip_cross = 'a',
        strip_to_outright_trade = 'B',
        strip_to_outright_cross = 'b',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Tradeable Instrument Id: Identifier of the Order Book.
struct tradeable_instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tradeable Instrument Id Leg: Instrument Id of the leg
struct tradeable_instrument_id_leg {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Tradeable Instrument Id: Identifier of the Underlying Tradeable Instrument (can be zero if underlying not defined).
struct underlying_tradeable_instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Voi Trade Date: Trade Date the VOI information is applicable to.
struct voi_trade_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volatility: Volatility for an option contract.
struct volatility {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
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

// Volume And Open Interest Message: This message disseminates Volume and Open Interest (VOI) information for each trade date
struct volume_and_open_interest_message {
    static constexpr std::string_view name = "Volume And Open Interest Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        cumulative_volume,
        open_interest,
        voi_trade_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(cumulative_volume);
    ITCHFIELD(open_interest);
    ITCHFIELD(voi_trade_date);
};

static_assert(sizeof(volume_and_open_interest_message) == volume_and_open_interest_message::size, "volume_and_open_interest_message lies over its bytes exactly");

// Anomalous Order Threshold Publish Message: This message disseminates price band information to the market advising the setting, zeroing or adjusting of the Extreme Trade Range price, the Anomalous Order Threshold price and the associated ranges for a contract that requires Market Integrity Rules enforcement
struct anomalous_order_threshold_publish_message {
    static constexpr std::string_view name = "Anomalous Order Threshold Publish Message";
    static constexpr std::size_t size = 58;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        aot_price,
        aot_upper_price,
        aot_lower_price,
        etr_price,
        etr_upper_price,
        etr_lower_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(aot_price);
    ITCHFIELD(aot_upper_price);
    ITCHFIELD(aot_lower_price);
    ITCHFIELD(etr_price);
    ITCHFIELD(etr_upper_price);
    ITCHFIELD(etr_lower_price);
};

static_assert(sizeof(anomalous_order_threshold_publish_message) == anomalous_order_threshold_publish_message::size, "anomalous_order_threshold_publish_message lies over its bytes exactly");

// Request For Quote Message: This message is disseminated for anonymous Request for Quotes (RFQs) from the market
struct request_for_quote_message {
    static constexpr std::string_view name = "Request For Quote Message";
    static constexpr std::size_t size = 15;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        rfq_side,
        quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(rfq_side);
    ITCHFIELD(quantity);
};

static_assert(sizeof(request_for_quote_message) == request_for_quote_message::size, "request_for_quote_message lies over its bytes exactly");

// Text Message: This message disseminates free text information describing ad-hoc market events
struct text_message {
    static constexpr std::string_view name = "Text Message";
    static constexpr std::size_t size = 112;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        source_id,
        text>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(source_id);
    ITCHFIELD(text);
};

static_assert(sizeof(text_message) == text_message::size, "text_message lies over its bytes exactly");

// Market Settlement Message: This message disseminates the final settlement price of a future or option contracts order book for the trade date it pertains to
struct market_settlement_message {
    static constexpr std::string_view name = "Market Settlement Message";
    static constexpr std::size_t size = 54;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        opening_trade,
        highest_trade,
        lowest_trade,
        last_trade,
        last_volume,
        total_traded_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(opening_trade);
    ITCHFIELD(highest_trade);
    ITCHFIELD(lowest_trade);
    ITCHFIELD(last_trade);
    ITCHFIELD(last_volume);
    ITCHFIELD(total_traded_volume);
};

static_assert(sizeof(market_settlement_message) == market_settlement_message::size, "market_settlement_message lies over its bytes exactly");

// Open High Low Last Trade Adjustment Message: Market trade price adjustments are sent resulting from modifications of Open, High, Low, Last and volume statistics due to market operations, prior to the instrument moving to the next session within the trade date, or at the close of instrument
struct open_high_low_last_trade_adjustment_message {
    static constexpr std::string_view name = "Open High Low Last Trade Adjustment Message";
    static constexpr std::size_t size = 54;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        opening_trade,
        highest_trade,
        lowest_trade,
        last_trade,
        last_volume,
        total_traded_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(opening_trade);
    ITCHFIELD(highest_trade);
    ITCHFIELD(lowest_trade);
    ITCHFIELD(last_trade);
    ITCHFIELD(last_volume);
    ITCHFIELD(total_traded_volume);
};

static_assert(sizeof(open_high_low_last_trade_adjustment_message) == open_high_low_last_trade_adjustment_message::size, "open_high_low_last_trade_adjustment_message lies over its bytes exactly");

// Equilibrium Price Message: This message is disseminated in response to changes in the equilibrium price for an order book during a pre-open period
struct equilibrium_price_message {
    static constexpr std::string_view name = "Equilibrium Price Message";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        equilibrium_price,
        matched_quantity,
        bid_quantity,
        ask_quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(equilibrium_price);
    ITCHFIELD(matched_quantity);
    ITCHFIELD(bid_quantity);
    ITCHFIELD(ask_quantity);
};

static_assert(sizeof(equilibrium_price_message) == equilibrium_price_message::size, "equilibrium_price_message lies over its bytes exactly");

// Trade Cancellation Message: This message is sent whenever a trade is cancelled by ASX
struct trade_cancellation_message {
    static constexpr std::string_view name = "Trade Cancellation Message";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(trade_id);
};

static_assert(sizeof(trade_cancellation_message) == trade_cancellation_message::size, "trade_cancellation_message lies over its bytes exactly");

// Combination Trade Executed Message: The Combination Trade Executed Message is designed to provide details for executions where one or both orders are resting from a different order book id from the order book id of the trade
struct combination_trade_executed_message {
    static constexpr std::string_view name = "Combination Trade Executed Message";
    static constexpr std::size_t size = 79;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        trade_type,
        trade_id,
        executed_quantity,
        trade_price,
        buyer_tradeable_instrument_id,
        buyer_side,
        buyer_order_id,
        buyer_combination_trade_id,
        buyer_participant_id,
        seller_tradeable_instrument_id,
        seller_side,
        seller_order_id,
        seller_combination_trade_id,
        seller_participant_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(trade_type);
    ITCHFIELD(trade_id);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(trade_price);
    ITCHFIELD(buyer_tradeable_instrument_id);
    ITCHFIELD(buyer_side);
    ITCHFIELD(buyer_order_id);
    ITCHFIELD(buyer_combination_trade_id);
    ITCHFIELD(buyer_participant_id);
    ITCHFIELD(seller_tradeable_instrument_id);
    ITCHFIELD(seller_side);
    ITCHFIELD(seller_order_id);
    ITCHFIELD(seller_combination_trade_id);
    ITCHFIELD(seller_participant_id);
};

static_assert(sizeof(combination_trade_executed_message) == combination_trade_executed_message::size, "combination_trade_executed_message lies over its bytes exactly");

// Trade Executed Message: The Trade Message is designed to provide details for executions in combination order books. Trade Executed messages are reported in the same sequence as order execution messages are reported
struct trade_executed_message {
    static constexpr std::string_view name = "Trade Executed Message";
    static constexpr std::size_t size = 45;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        trade_type,
        trade_id,
        executed_quantity,
        trade_price,
        combination_trade_id,
        participant_id_buyer,
        participant_id_seller>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(trade_type);
    ITCHFIELD(trade_id);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(trade_price);
    ITCHFIELD(combination_trade_id);
    ITCHFIELD(participant_id_buyer);
    ITCHFIELD(participant_id_seller);
};

static_assert(sizeof(trade_executed_message) == trade_executed_message::size, "trade_executed_message lies over its bytes exactly");

// Implied Order Deleted Message: This message is sent whenever the implied pricing or volume has changed due to price or volume movement of “real” orders for a side of a single contract number. When received, any implied volume is no longer accessible so the “implied” order of the indicated side must be removed from the book
struct implied_order_deleted_message {
    static constexpr std::string_view name = "Implied Order Deleted Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
};

static_assert(sizeof(implied_order_deleted_message) == implied_order_deleted_message::size, "implied_order_deleted_message lies over its bytes exactly");

// Implied Order Replaced Message: This message notifies the subscriber that an existing implied order is to be replaced when the implied price, volume or priority has changed due to a price or volume movement of “real” orders for a side of a single Tradeable Instrument Id
struct implied_order_replaced_message {
    static constexpr std::string_view name = "Implied Order Replaced Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        order_book_priority,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_priority);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
};

static_assert(sizeof(implied_order_replaced_message) == implied_order_replaced_message::size, "implied_order_replaced_message lies over its bytes exactly");

// Implied Order Added Message: This message is a similar format to the Order Added message, except the nature of this order is it has an implied price, implied volume and a priority that is derived from two or more “real” orders deriving the implied price
struct implied_order_added_message {
    static constexpr std::string_view name = "Implied Order Added Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        order_book_priority,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_priority);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
};

static_assert(sizeof(implied_order_added_message) == implied_order_added_message::size, "implied_order_added_message lies over its bytes exactly");

// Combination Order Executed Message: This message is sent whenever a resting order is matched with an open leg of a resting combination order in whole or in part
struct combination_order_executed_message {
    static constexpr std::string_view name = "Combination Order Executed Message";
    static constexpr std::size_t size = 65;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        quantity_remaining,
        trade_type,
        trade_id,
        executed_quantity,
        trade_price,
        opposite_tradeable_instrument_id,
        opposite_side,
        opposite_order_id,
        combination_trade_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(quantity_remaining);
    ITCHFIELD(trade_type);
    ITCHFIELD(trade_id);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(trade_price);
    ITCHFIELD(opposite_tradeable_instrument_id);
    ITCHFIELD(opposite_side);
    ITCHFIELD(opposite_order_id);
    ITCHFIELD(combination_trade_id);
};

static_assert(sizeof(combination_order_executed_message) == combination_order_executed_message::size, "combination_order_executed_message lies over its bytes exactly");

// Auction Order Executed Message: This message is sent when orders are executed in the auction at the open of the market
struct auction_order_executed_message {
    static constexpr std::string_view name = "Auction Order Executed Message";
    static constexpr std::size_t size = 52;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        quantity_remaining,
        trade_type,
        trade_id,
        executed_quantity,
        trade_price,
        opposite_order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(quantity_remaining);
    ITCHFIELD(trade_type);
    ITCHFIELD(trade_id);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(trade_price);
    ITCHFIELD(opposite_order_id);
};

static_assert(sizeof(auction_order_executed_message) == auction_order_executed_message::size, "auction_order_executed_message lies over its bytes exactly");

// Order Executed Message: This message is sent whenever a resting order of the book is executed in whole or in part and the counterparty to the trade is an aggressive order
struct order_executed_message {
    static constexpr std::string_view name = "Order Executed Message";
    static constexpr std::size_t size = 55;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        quantity_remaining,
        trade_type,
        trade_id,
        executed_quantity,
        trade_price,
        combination_trade_id,
        counter_party_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(quantity_remaining);
    ITCHFIELD(trade_type);
    ITCHFIELD(trade_id);
    ITCHFIELD(executed_quantity);
    ITCHFIELD(trade_price);
    ITCHFIELD(combination_trade_id);
    ITCHFIELD(counter_party_id);
};

static_assert(sizeof(order_executed_message) == order_executed_message::size, "order_executed_message lies over its bytes exactly");

// Order Deleted Message: This message is sent whenever an order in the book is cancelled by the owner, expired, cancelled by the exchange, purged or volume cancelled
struct order_deleted_message {
    static constexpr std::string_view name = "Order Deleted Message";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
};

static_assert(sizeof(order_deleted_message) == order_deleted_message::size, "order_deleted_message lies over its bytes exactly");

// Order Volume Cancelled Message: An Order Volume Cancelled message is sent when an order is modified as a result of partial cancellation of volume
struct order_volume_cancelled_message {
    static constexpr std::string_view name = "Order Volume Cancelled Message";
    static constexpr std::size_t size = 23;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        quantity>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(quantity);
};

static_assert(sizeof(order_volume_cancelled_message) == order_volume_cancelled_message::size, "order_volume_cancelled_message lies over its bytes exactly");

// Add Order Message: An Order Added message indicates a new order or a restated order that has been accepted by the matching engine and added to the order book
struct add_order_message {
    static constexpr std::string_view name = "Add Order Message";
    static constexpr std::size_t size = 39;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        side,
        order_id,
        order_book_priority,
        quantity,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(side);
    ITCHFIELD(order_id);
    ITCHFIELD(order_book_priority);
    ITCHFIELD(quantity);
    ITCHFIELD(price);
};

static_assert(sizeof(add_order_message) == add_order_message::size, "add_order_message lies over its bytes exactly");

// Order Book State Message: This message indicates the current session state of a contract to the market
struct order_book_state_message {
    static constexpr std::string_view name = "Order Book State Message";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        session_state>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(session_state);
};

static_assert(sizeof(order_book_state_message) == order_book_state_message::size, "order_book_state_message lies over its bytes exactly");

// Bundle Leg
struct bundle_leg {
    static constexpr std::string_view name = "Bundle Leg";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        tradeable_instrument_id_leg,
        side_leg,
        ratio_leg,
        price_leg>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tradeable_instrument_id_leg);
    ITCHFIELD(side_leg);
    ITCHFIELD(ratio_leg);
    ITCHFIELD(price_leg);
};

static_assert(sizeof(bundle_leg) == bundle_leg::size, "bundle_leg lies over its bytes exactly");

// Bundles Symbol Directory: The Bundles Symbol Directory is a specialised reference data message used for defining combinations with legs greater than 6, specifically Bundle products with legs of 8, 12, 16 or 20 legs
struct bundles_symbol_directory {
    static constexpr std::string_view name = "Bundles Symbol Directory";
    static constexpr std::size_t size = 136;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        symbol_name,
        long_name,
        cfi_code,
        price_method,
        price_display_decimals,
        price_fractional_denominator,
        price_minimum_tick,
        legs,
        bundle_leg>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(symbol_name);
    ITCHFIELD(long_name);
    ITCHFIELD(cfi_code);
    ITCHFIELD(price_method);
    ITCHFIELD(price_display_decimals);
    ITCHFIELD(price_fractional_denominator);
    ITCHFIELD(price_minimum_tick);
    ITCHFIELD(legs);
    ITCHFIELD(bundle_leg);
};

static_assert(sizeof(bundles_symbol_directory) == bundles_symbol_directory::size, "bundles_symbol_directory lies over its bytes exactly");

// Combination Leg
struct combination_leg {
    static constexpr std::string_view name = "Combination Leg";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        tradeable_instrument_id_leg,
        side_leg,
        ratio_leg,
        price_leg>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(tradeable_instrument_id_leg);
    ITCHFIELD(side_leg);
    ITCHFIELD(ratio_leg);
    ITCHFIELD(price_leg);
};

static_assert(sizeof(combination_leg) == combination_leg::size, "combination_leg lies over its bytes exactly");

// Combination Symbol Directory Message: The Combination Symbol Directory is a specialised reference data message used for defining combinations with up to 6 legs. It represents both standard combinations defined by ASX and user defined combinations created by participants
struct combination_symbol_directory_message {
    static constexpr std::string_view name = "Combination Symbol Directory Message";
    static constexpr std::size_t size = 136;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        symbol_name,
        long_name,
        cfi_code,
        price_method,
        price_display_decimals,
        price_fractional_denominator,
        price_minimum_tick,
        legs,
        combination_leg>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(symbol_name);
    ITCHFIELD(long_name);
    ITCHFIELD(cfi_code);
    ITCHFIELD(price_method);
    ITCHFIELD(price_display_decimals);
    ITCHFIELD(price_fractional_denominator);
    ITCHFIELD(price_minimum_tick);
    ITCHFIELD(legs);
    ITCHFIELD(combination_leg);
};

static_assert(sizeof(combination_symbol_directory_message) == combination_symbol_directory_message::size, "combination_symbol_directory_message lies over its bytes exactly");

// Options Symbol Directory Message: The Options Symbol Directory message describes options and warrants contracts.
struct options_symbol_directory_message {
    static constexpr std::string_view name = "Options Symbol Directory Message";
    static constexpr std::size_t size = 219;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        symbol_name,
        long_name,
        isin,
        exchange,
        instrument,
        cfi_code,
        expiry_year,
        expiry_month,
        option_type,
        strike,
        underlying_tradeable_instrument_id,
        price_display_decimals,
        price_fractional_denominator,
        price_minimum_tick,
        strike_price_decimal_position,
        strike_price_fractional_denominator,
        strike_price_minimum_tick,
        last_trading_date,
        prior_day_settlement,
        volatility,
        currency,
        lot_size_or_face_value,
        maturity_value,
        coupon_rate,
        payments_per_year,
        block_lot_size,
        expiry_date,
        basis_of_quotation>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(symbol_name);
    ITCHFIELD(long_name);
    ITCHFIELD(isin);
    ITCHFIELD(exchange);
    ITCHFIELD(instrument);
    ITCHFIELD(cfi_code);
    ITCHFIELD(expiry_year);
    ITCHFIELD(expiry_month);
    ITCHFIELD(option_type);
    ITCHFIELD(strike);
    ITCHFIELD(underlying_tradeable_instrument_id);
    ITCHFIELD(price_display_decimals);
    ITCHFIELD(price_fractional_denominator);
    ITCHFIELD(price_minimum_tick);
    ITCHFIELD(strike_price_decimal_position);
    ITCHFIELD(strike_price_fractional_denominator);
    ITCHFIELD(strike_price_minimum_tick);
    ITCHFIELD(last_trading_date);
    ITCHFIELD(prior_day_settlement);
    ITCHFIELD(volatility);
    ITCHFIELD(currency);
    ITCHFIELD(lot_size_or_face_value);
    ITCHFIELD(maturity_value);
    ITCHFIELD(coupon_rate);
    ITCHFIELD(payments_per_year);
    ITCHFIELD(block_lot_size);
    ITCHFIELD(expiry_date);
    ITCHFIELD(basis_of_quotation);
};

static_assert(sizeof(options_symbol_directory_message) == options_symbol_directory_message::size, "options_symbol_directory_message lies over its bytes exactly");

// Future Symbol Directory Message: The Future Symbol Directory message describes futures contract
struct future_symbol_directory_message {
    static constexpr std::string_view name = "Future Symbol Directory Message";
    static constexpr std::size_t size = 179;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        tradeable_instrument_id,
        symbol_name,
        long_name,
        isin,
        exchange,
        instrument,
        cfi_code,
        expiry_year,
        expiry_month,
        price_display_decimals,
        price_fractional_denominator,
        price_minimum_tick,
        last_trading_date,
        prior_day_settlement,
        currency,
        lot_size_or_face_value,
        maturity_value,
        coupon_rate,
        payments_per_year,
        block_lot_size,
        expiry_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(tradeable_instrument_id);
    ITCHFIELD(symbol_name);
    ITCHFIELD(long_name);
    ITCHFIELD(isin);
    ITCHFIELD(exchange);
    ITCHFIELD(instrument);
    ITCHFIELD(cfi_code);
    ITCHFIELD(expiry_year);
    ITCHFIELD(expiry_month);
    ITCHFIELD(price_display_decimals);
    ITCHFIELD(price_fractional_denominator);
    ITCHFIELD(price_minimum_tick);
    ITCHFIELD(last_trading_date);
    ITCHFIELD(prior_day_settlement);
    ITCHFIELD(currency);
    ITCHFIELD(lot_size_or_face_value);
    ITCHFIELD(maturity_value);
    ITCHFIELD(coupon_rate);
    ITCHFIELD(payments_per_year);
    ITCHFIELD(block_lot_size);
    ITCHFIELD(expiry_date);
};

static_assert(sizeof(future_symbol_directory_message) == future_symbol_directory_message::size, "future_symbol_directory_message lies over its bytes exactly");

// End Of Business Trade Date Message: This message will be sent as the last message for a Business Trade Date to signal no further messages will be disseminated for that date.
struct end_of_business_trade_date_message {
    static constexpr std::string_view name = "End Of Business Trade Date Message";
    static constexpr std::size_t size = 7;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        nanoseconds,
        trade_date,
        event_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(nanoseconds);
    ITCHFIELD(trade_date);
    ITCHFIELD(event_code);
};

static_assert(sizeof(end_of_business_trade_date_message) == end_of_business_trade_date_message::size, "end_of_business_trade_date_message lies over its bytes exactly");

// Seconds Message: A ‘seconds’ Nanoseconds is issued every second and any message thereafter will be stamped with the number of nanoseconds past the last Time message received as a time reference point
struct seconds_message {
    static constexpr std::string_view name = "Seconds Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        second>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    ITCHFIELD(second);
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

} // namespace asx::asxderivatives::ntp::itch::v1_05
