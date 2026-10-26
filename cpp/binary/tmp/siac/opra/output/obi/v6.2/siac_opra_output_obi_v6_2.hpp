// Siac Opra Output Obi 6.2 Template Meta Programming

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
#ifndef OPRAFIELD
#define OPRAFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef OPRASEQUENCE
#define OPRASEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace siac::opra::output::obi::v6_2 {

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

// Administrative Message Type: Message type
struct administrative_message_type {
    enum class type : char {
        administrative = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bbo Indicator: Indicates the effect the new quote has on the Best Bid and/or the Best Offer.
struct bbo_indicator {
    enum class type : char {
        no_best_bid_change_or_best_offer_change = 'A',
        no_best_bid_change_quote_contains_best_offer = 'B',
        no_best_bid_change_best_offer_appendage = 'C',
        no_best_bid_change_no_best_offer = 'D',
        quote_contains_best_bid_no_best_offer_change = 'E',
        quote_contains_best_bid_quote_contains_best_offer = 'F',
        quote_contains_best_bid_best_offer_appendage = 'G',
        quote_contains_best_bid_no_best_offer = 'H',
        no_best_bid_no_best_offer_change = 'I',
        no_best_bid_quote_contains_best_offer = 'J',
        no_best_bid_best_offer_appendage = 'K',
        no_best_bid_no_best_offer = 'L',
        best_bid_appendage_no_best_offer_change = 'M',
        best_bid_appendage_quote_contains_best_offer = 'N',
        best_bid_appendage_best_offer_appendage = 'O',
        best_bid_appendage_no_best_offer = 'P',
        not_included_in_the_bbo = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Bid Denominator Code: The Bed Bid Denominator Code field indicates the position of the floating decimal point within the Best Bid Price field.
struct best_bid_denominator_code {
    enum class type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        million = 'F',
        ten_million = 'G',
        hundred_million = 'H',
        no_fraction = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Bid Participant Id: Identifies the participant that entered the Best Bid.
struct best_bid_participant_id {
    enum class type : char {
        nyse_american = 'A',
        boston_options_exchange = 'B',
        cboe_options_exchange = 'C',
        miax_emerald = 'D',
        cboe_edgx_options = 'E',
        nasdaq_gemx = 'H',
        nasdaq_ise = 'I',
        nasdaq_mrx = 'J',
        miami_international_securities_exchange = 'M',
        nyse_arca = 'N',
        options_price_reporting_authority = 'O',
        miax_pearl = 'P',
        nasdaq_options_market = 'Q',
        nasdaq_bx_options = 'T',
        cboe_c_2_options = 'W',
        nasdaq_phlx = 'X',
        cboe_bzx_options_exchange = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Bid Price: Represents the best price at which a buyer is willing to buy an option.
struct best_bid_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Bid Size: The Best Bid Size identifies the number of contracts being bought for an option at the Best Bid price.
struct best_bid_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Denominator Code: The Bed OFFER Denominator Code field indicates the position of the floating decimal point within the Best Offer Price field.
struct best_offer_denominator_code {
    enum class type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        million = 'F',
        ten_million = 'G',
        hundred_million = 'H',
        no_fraction = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Offer Participant Id: Identifies the participant that entered the Best Bid.
struct best_offer_participant_id {
    enum class type : char {
        nyse_american = 'A',
        boston_options_exchange = 'B',
        cboe_options_exchange = 'C',
        miax_emerald = 'D',
        cboe_edgx_options = 'E',
        nasdaq_gemx = 'H',
        nasdaq_ise = 'I',
        nasdaq_mrx = 'J',
        miami_international_securities_exchange = 'M',
        nyse_arca = 'N',
        options_price_reporting_authority = 'O',
        miax_pearl = 'P',
        nasdaq_options_market = 'Q',
        nasdaq_bx_options = 'T',
        cboe_c_2_options = 'W',
        nasdaq_phlx = 'X',
        cboe_bzx_options_exchange = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Best Offer Price: Represents the best price at which a seller is offering to sell an option.
struct best_offer_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Best Offer Size: The Best Offer Size identifies the number of contracts being bought for an option at the Best Offer price.
struct best_offer_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Index Value: The Bid Index Value represents the value of the index’s calculation formula using the current bid values of the component securities.
struct bid_index_value {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price: Represents the price at which a buyer is willing to buy an option.
struct bid_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Price Short: Represents the price at which a buyer is willing to buy an option.
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

// Bid Size: The Bid Size identifies the number of contracts being bought for an option at the Bid Price.
struct bid_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size Short: The Bid Size identifies the number of contracts being bought for an option at the Bid Price.
struct bid_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Checksum: Lower 16 bits of the 32 bit sum of all bytes in the block, excluding the Block Checksum field
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

// Block Size: Size in bytes of entire transmission block
struct block_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Control Message Type
struct control_message_type {
    enum class type : char {
        start_of_day = 'C',
        start_of_summary = 'E',
        end_of_summary = 'F',
        end_of_day = 'J',
        reset_block_sequence_number = 'K',
        start_of_open_interest = 'L',
        end_of_open_interest = 'M',
        line_integrity = 'N',
        disaster_recovery_data_center_activation = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Data Feed Indicator: Value is ‘O’ for OPRA
struct data_feed_indicator {
    enum class type : char {
        opra = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Equity And Index End Of Day Summary Message Type
struct equity_and_index_end_of_day_summary_message_type {
    enum class type : char {
        equity_and_index_end_of_day_summary = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Equity And Index Last Sale Message Type: Message type
struct equity_and_index_last_sale_message_type {
    enum class type : char {
        canc = 'A',
        oseq = 'B',
        cncl = 'C',
        late = 'D',
        cnco = 'E',
        open = 'F',
        cnol = 'G',
        opnl = 'H',
        auto_value = 'I',
        reop = 'J',
        ajst = 'K',
        sprd = 'L',
        stdl = 'M',
        stpd = 'N',
        cstp = 'O',
        bwrt = 'P',
        cmbo = 'Q',
        spim = 'R',
        isoi = 'S',
        bnmt = 'T',
        xmpt = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Expiration Day: Contains Hex 0x01 to 0x1F (decimal 1 to 31), indicating the day of the month the series expires.
struct expiration_day {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Expiration Month: Indicates the expiration month and identifies the option as a Call or a Put.
struct expiration_month {
    enum class type : char {
        january_call = 'A',
        january_put = 'M',
        february_call = 'B',
        february_put = 'N',
        march_call = 'C',
        march_put = 'O',
        april_call = 'D',
        april_put = 'P',
        may_call = 'E',
        may_put = 'Q',
        june_call = 'F',
        june_put = 'R',
        july_call = 'G',
        july_put = 'S',
        august_call = 'H',
        august_put = 'T',
        september_call = 'I',
        september_put = 'U',
        october_call = 'J',
        october_put = 'V',
        november_call = 'K',
        november_put = 'W',
        december_call = 'L',
        december_put = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Expiration Year: Contains Hex 0x00 to 0x63 (decimal 0 to 99). Represents the year, starting with year 2000.
struct expiration_year {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// High Price: Represents the highest price paid for an option during the trading day.
struct high_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Index Value: Contains the index value using last sale values of index components.
struct index_value {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Index Value Denominator Code: Contains the index value using last sale values of index components.
struct index_value_denominator_code {
    enum class type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        million = 'F',
        ten_million = 'G',
        no_fraction = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Price: Represents the last price paid for an option during the trading day.
struct last_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Long Equity And Index Quote Message Type
struct long_equity_and_index_quote_message_type {
    enum class type : char {
        regular_trading = ' ',
        non_firm_quote = 'F',
        indicative_value = 'I',
        rotation = 'R',
        trading_halted = 'T',
        eligible_for_automatic_execution = 'A',
        bid_contains_customer_trading_interest = 'B',
        offer_contains_customer_trading_interest = 'O',
        both_bid_and_offer_contain_customer_trading_interest = 'C',
        offer_side_of_quote_not_firm_bid_side_firm = 'X',
        bid_side_of_quote_not_firm_offer_side_firm = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Low Price: Represents the lowest price paid for an option during the trading day.
struct low_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Category: Message identifier
struct message_category {
    enum class type : char {
        administrative = 'C',
        control = 'H',
        equity_and_index_last_sale = 'a',
        open_interest = 'd',
        equity_and_index_end_of_day_summary = 'f',
        long_equity_and_index_quote = 'k',
        short_equity_and_index_quote = 'q',
        underlying_value = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Data: Represents the Message Data field.
struct message_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr message_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Message Data Length: Represents the length of the Message Data field
struct message_data_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Indicator: Message identifier
struct message_indicator {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Messages In Block: The number of messages contained in the block data of the transmission block.
struct messages_in_block {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Nanoseconds: the nanosecond portion of the time currently rounded to the nearest microsecond
struct nanoseconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Net Change: Represents the change in the price of an option from the closing price of one day to the closing price on the next day on which the option is traded.
struct net_change {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Index Value: The Offer Index Value represents the value of the index’s calculation formula using the current Offer values of the component securities.
struct offer_index_value {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Price: Represents the price at which a seller is offering to sell an option.
struct offer_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Price Short: Represents the price at which a seller is offering to sell an option.
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

// Offer Size: The Offer Size identifies the number of contracts for sale for an option at the Offer Price.
struct offer_size {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Size Short: The Offer Size identifies the number of contracts for sale for an option at the Offer Price.
struct offer_size_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Interest Message Type
struct open_interest_message_type {
    enum class type : char {
        open_interest = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Open Interest Volume: Represents the total number of outstanding option contracts that have not been exercised and have not yet reached expiration.
struct open_interest_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Price: Represents the first price paid for an option during the trading day.
struct open_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Participant Id: ASCII character that identifies the Participant or Processor that initiated the message.
struct participant_id {
    enum class type : char {
        amex = 'A',
        box = 'B',
        cboe = 'C',
        emerald = 'D',
        edgx = 'E',
        gemx = 'H',
        ise = 'I',
        mrx = 'J',
        miax = 'M',
        nyse = 'N',
        opra = 'O',
        pearl = 'P',
        nasd = 'Q',
        sphr = 'S',
        bx = 'T',
        memx = 'U',
        c_2 = 'W',
        phlx = 'X',
        bats = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Participant Reference Number: The PRN is for optional use by the Participant
struct participant_reference_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Premium Price: Represents the price of an option contract, determined in the competitive marketplace, which the buyer of the option pays to the option writer for the rights conveyed by the option contract.
struct premium_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Premium Price Denominator Code: Represents the first price paid for an option during the trading day.
struct premium_price_denominator_code {
    enum class type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        million = 'F',
        ten_million = 'G',
        no_fraction = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Reserved 1: One reserved byte
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 4: Four reserved bytes
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Retransmission Indicator: Contains either a space; not a retransmitted message or V; indicating a retransmission of the block.
struct retransmission_indicator {
    enum class type : char {
        not_retransmitted = ' ',
        retransmitted = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Seconds: Contains the number seconds from epoch 1/1/1970, 00:00:00 UTC
struct seconds {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Symbol: Identifies the unique symbol assigned to the underlying security.
struct security_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Security Symbol Short: Identifies the unique symbol assigned to the underlying security.
struct security_symbol_short {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Session Indicator: 0x00 for regular trading session
struct session_indicator {
    enum class type : std::uint8_t {
        regular = 0,
        pre_market = 88,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Short Equity And Index Quote Message Type
struct short_equity_and_index_quote_message_type {
    enum class type : char {
        regular_trading = ' ',
        non_firm_quote = 'F',
        indicative_value = 'I',
        rotation = 'R',
        trading_halted = 'T',
        eligible_for_automatic_execution = 'A',
        bid_contains_customer_trading_interest = 'B',
        offer_contains_customer_trading_interest = 'O',
        both_bid_and_offer_contain_customer_trading_interest = 'C',
        offer_side_of_quote_not_firm_bid_side_firm = 'X',
        bid_side_of_quote_not_firm_offer_side_firm = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Strike Price: Represents the stated price per share for which the underlying security may be purchased (in the case of a call) or sold (in the case of a put) by the option holder upon exercise of the option contract.
struct strike_price {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Denominator Code: The Strike Price Denominator Code field indicates the position of the floating decimal point within the Strike Price field.
struct strike_price_denominator_code {
    enum class type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        no_fraction = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Strike Price Short: Represents the stated price per share for which the underlying security may be purchased (in the case of a call) or sold (in the case of a put) by the option holder upon exercise of the option contract.
struct strike_price_short {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;
    static constexpr int exponent = -1;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Identifier: FOR FUTURE USE. Filled with Hex 0x00.
struct trade_identifier {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transaction Id: Reserved for Internal Use only
struct transaction_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Price: Represents the price of the underlying security.
struct underlying_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Price Denominator Code: The Underlying Price Denominator Code field indicates the position of the floating decimal point within the Underlying Price field.
struct underlying_price_denominator_code {
    enum class type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        million = 'F',
        ten_million = 'G',
        hundred_million = 'H',
        no_fraction = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Value Message Type
struct underlying_value_message_type {
    enum class type : char {
        index_based_on_last_sale = ' ',
        index_based_on_bid_and_offer = 'I',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Version: Designates the OPRA binary version
struct version {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume: Represents the total number of contracts traded for an option in one trade, or the total number of contracts traded for an option for the entire trading day.
struct volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
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

// Underlying Value Bid And Offer Message
struct underlying_value_bid_and_offer_message {
    static constexpr std::string_view name = "Underlying Value Bid And Offer Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol,
        reserved_1,
        index_value_denominator_code,
        bid_index_value,
        offer_index_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol);
    OPRAFIELD(reserved_1);
    OPRAFIELD(index_value_denominator_code);
    OPRAFIELD(bid_index_value);
    OPRAFIELD(offer_index_value);
};

static_assert(sizeof(underlying_value_bid_and_offer_message) == underlying_value_bid_and_offer_message::size, "underlying_value_bid_and_offer_message lies over its bytes exactly");

// Underlying Value Last Sale Message
struct underlying_value_last_sale_message {
    static constexpr std::string_view name = "Underlying Value Last Sale Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol,
        reserved_1,
        index_value_denominator_code,
        index_value,
        reserved_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol);
    OPRAFIELD(reserved_1);
    OPRAFIELD(index_value_denominator_code);
    OPRAFIELD(index_value);
    OPRAFIELD(reserved_4);
};

static_assert(sizeof(underlying_value_last_sale_message) == underlying_value_last_sale_message::size, "underlying_value_last_sale_message lies over its bytes exactly");

// Underlying Value Message Payload: Branch
struct underlying_value_message_payload {
    static constexpr std::string_view name = "Underlying Value Message Payload";
    static constexpr bool is_message = false;
};

// Underlying Value Category Section 1
struct underlying_value_category_section_1 {
    static constexpr std::string_view name = "Underlying Value Category Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_value_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(underlying_value_message_type);
};

static_assert(sizeof(underlying_value_category_section_1) == underlying_value_category_section_1::size, "underlying_value_category_section_1 lies over its bytes exactly");

// Underlying Value Category: Underlying Value Message
struct underlying_value_category {
    static constexpr std::string_view name = "Underlying Value Category";
    static constexpr bool is_message = false;
};

// Best Bid And Offer Appendage
struct best_bid_and_offer_appendage {
    static constexpr std::string_view name = "Best Bid And Offer Appendage";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_bid_participant_id,
        best_bid_denominator_code,
        best_bid_price,
        best_bid_size,
        best_offer_participant_id,
        best_offer_denominator_code,
        best_offer_price,
        best_offer_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(best_bid_participant_id);
    OPRAFIELD(best_bid_denominator_code);
    OPRAFIELD(best_bid_price);
    OPRAFIELD(best_bid_size);
    OPRAFIELD(best_offer_participant_id);
    OPRAFIELD(best_offer_denominator_code);
    OPRAFIELD(best_offer_price);
    OPRAFIELD(best_offer_size);
};

static_assert(sizeof(best_bid_and_offer_appendage) == best_bid_and_offer_appendage::size, "best_bid_and_offer_appendage lies over its bytes exactly");

// Best Offer Appendage
struct best_offer_appendage {
    static constexpr std::string_view name = "Best Offer Appendage";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_offer_participant_id,
        best_offer_denominator_code,
        best_offer_price,
        best_offer_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(best_offer_participant_id);
    OPRAFIELD(best_offer_denominator_code);
    OPRAFIELD(best_offer_price);
    OPRAFIELD(best_offer_size);
};

static_assert(sizeof(best_offer_appendage) == best_offer_appendage::size, "best_offer_appendage lies over its bytes exactly");

// Best Bid Appendage
struct best_bid_appendage {
    static constexpr std::string_view name = "Best Bid Appendage";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        best_bid_participant_id,
        best_bid_denominator_code,
        best_bid_price,
        best_bid_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(best_bid_participant_id);
    OPRAFIELD(best_bid_denominator_code);
    OPRAFIELD(best_bid_price);
    OPRAFIELD(best_bid_size);
};

static_assert(sizeof(best_bid_appendage) == best_bid_appendage::size, "best_bid_appendage lies over its bytes exactly");

// Expiration Block
struct expiration_block {
    static constexpr std::string_view name = "Expiration Block";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        expiration_month,
        expiration_day,
        expiration_year>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(expiration_month);
    OPRAFIELD(expiration_day);
    OPRAFIELD(expiration_year);
};

static_assert(sizeof(expiration_block) == expiration_block::size, "expiration_block lies over its bytes exactly");

// Short Equity And Index Quote Message Section 1
struct short_equity_and_index_quote_message_section_1 {
    static constexpr std::string_view name = "Short Equity And Index Quote Message Section 1";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bbo_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol_short,
        expiration_block,
        strike_price_short,
        bid_price_short,
        bid_size_short,
        offer_price_short,
        offer_size_short>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(bbo_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol_short);
    OPRAFIELD(expiration_block);
    OPRAFIELD(strike_price_short);
    OPRAFIELD(bid_price_short);
    OPRAFIELD(bid_size_short);
    OPRAFIELD(offer_price_short);
    OPRAFIELD(offer_size_short);
};

static_assert(sizeof(short_equity_and_index_quote_message_section_1) == short_equity_and_index_quote_message_section_1::size, "short_equity_and_index_quote_message_section_1 lies over its bytes exactly");

// Short Equity And Index Quote Message
struct short_equity_and_index_quote_message {
    static constexpr std::string_view name = "Short Equity And Index Quote Message";
    static constexpr bool is_message = true;
};

// Short Equity And Index Quote Message Payload: Branch
struct short_equity_and_index_quote_message_payload {
    static constexpr std::string_view name = "Short Equity And Index Quote Message Payload";
    static constexpr bool is_message = false;
};

// Short Equity And Index Quote Category Section 1
struct short_equity_and_index_quote_category_section_1 {
    static constexpr std::string_view name = "Short Equity And Index Quote Category Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        short_equity_and_index_quote_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(short_equity_and_index_quote_message_type);
};

static_assert(sizeof(short_equity_and_index_quote_category_section_1) == short_equity_and_index_quote_category_section_1::size, "short_equity_and_index_quote_category_section_1 lies over its bytes exactly");

// Short Equity And Index Quote Category: Short Equity And Index Quote Message
struct short_equity_and_index_quote_category {
    static constexpr std::string_view name = "Short Equity And Index Quote Category";
    static constexpr bool is_message = false;
};

// Long Equity And Index Quote Message Section 1
struct long_equity_and_index_quote_message_section_1 {
    static constexpr std::string_view name = "Long Equity And Index Quote Message Section 1";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bbo_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol,
        reserved_1,
        expiration_block,
        strike_price_denominator_code,
        strike_price,
        premium_price_denominator_code,
        bid_price,
        bid_size,
        offer_price,
        offer_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(bbo_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol);
    OPRAFIELD(reserved_1);
    OPRAFIELD(expiration_block);
    OPRAFIELD(strike_price_denominator_code);
    OPRAFIELD(strike_price);
    OPRAFIELD(premium_price_denominator_code);
    OPRAFIELD(bid_price);
    OPRAFIELD(bid_size);
    OPRAFIELD(offer_price);
    OPRAFIELD(offer_size);
};

static_assert(sizeof(long_equity_and_index_quote_message_section_1) == long_equity_and_index_quote_message_section_1::size, "long_equity_and_index_quote_message_section_1 lies over its bytes exactly");

// Long Equity And Index Quote Message
struct long_equity_and_index_quote_message {
    static constexpr std::string_view name = "Long Equity And Index Quote Message";
    static constexpr bool is_message = true;
};

// Long Equity And Index Quote Message Payload: Branch
struct long_equity_and_index_quote_message_payload {
    static constexpr std::string_view name = "Long Equity And Index Quote Message Payload";
    static constexpr bool is_message = false;
};

// Long Equity And Index Quote Category Section 1
struct long_equity_and_index_quote_category_section_1 {
    static constexpr std::string_view name = "Long Equity And Index Quote Category Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        long_equity_and_index_quote_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(long_equity_and_index_quote_message_type);
};

static_assert(sizeof(long_equity_and_index_quote_category_section_1) == long_equity_and_index_quote_category_section_1::size, "long_equity_and_index_quote_category_section_1 lies over its bytes exactly");

// Long Equity And Index Quote Category: Long Equity And Index Quote Message
struct long_equity_and_index_quote_category {
    static constexpr std::string_view name = "Long Equity And Index Quote Category";
    static constexpr bool is_message = false;
};

// Equity And Index End Of Day Summary Message
struct equity_and_index_end_of_day_summary_message {
    static constexpr std::string_view name = "Equity And Index End Of Day Summary Message";
    static constexpr std::size_t size = 69;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol,
        reserved_1,
        expiration_block,
        strike_price_denominator_code,
        strike_price,
        volume,
        open_interest_volume,
        premium_price_denominator_code,
        open_price,
        high_price,
        low_price,
        last_price,
        net_change,
        underlying_price_denominator_code,
        underlying_price,
        bid_price,
        offer_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol);
    OPRAFIELD(reserved_1);
    OPRAFIELD(expiration_block);
    OPRAFIELD(strike_price_denominator_code);
    OPRAFIELD(strike_price);
    OPRAFIELD(volume);
    OPRAFIELD(open_interest_volume);
    OPRAFIELD(premium_price_denominator_code);
    OPRAFIELD(open_price);
    OPRAFIELD(high_price);
    OPRAFIELD(low_price);
    OPRAFIELD(last_price);
    OPRAFIELD(net_change);
    OPRAFIELD(underlying_price_denominator_code);
    OPRAFIELD(underlying_price);
    OPRAFIELD(bid_price);
    OPRAFIELD(offer_price);
};

static_assert(sizeof(equity_and_index_end_of_day_summary_message) == equity_and_index_end_of_day_summary_message::size, "equity_and_index_end_of_day_summary_message lies over its bytes exactly");

// Equity And Index End Of Day Summary Message Payload: Branch
struct equity_and_index_end_of_day_summary_message_payload {
    static constexpr std::string_view name = "Equity And Index End Of Day Summary Message Payload";
    static constexpr bool is_message = false;
};

// Equity And Index End Of Day Summary Category Section 1
struct equity_and_index_end_of_day_summary_category_section_1 {
    static constexpr std::string_view name = "Equity And Index End Of Day Summary Category Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        equity_and_index_end_of_day_summary_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(equity_and_index_end_of_day_summary_message_type);
};

static_assert(sizeof(equity_and_index_end_of_day_summary_category_section_1) == equity_and_index_end_of_day_summary_category_section_1::size, "equity_and_index_end_of_day_summary_category_section_1 lies over its bytes exactly");

// Equity And Index End Of Day Summary Category: Equity And Index End Of Day Summary Message
struct equity_and_index_end_of_day_summary_category {
    static constexpr std::string_view name = "Equity And Index End Of Day Summary Category";
    static constexpr bool is_message = false;
};

// Open Interest Message
struct open_interest_message {
    static constexpr std::string_view name = "Open Interest Message";
    static constexpr std::size_t size = 27;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol,
        reserved_1,
        expiration_block,
        strike_price_denominator_code,
        strike_price,
        open_interest_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol);
    OPRAFIELD(reserved_1);
    OPRAFIELD(expiration_block);
    OPRAFIELD(strike_price_denominator_code);
    OPRAFIELD(strike_price);
    OPRAFIELD(open_interest_volume);
};

static_assert(sizeof(open_interest_message) == open_interest_message::size, "open_interest_message lies over its bytes exactly");

// Open Interest Message Payload: Branch
struct open_interest_message_payload {
    static constexpr std::string_view name = "Open Interest Message Payload";
    static constexpr bool is_message = false;
};

// Open Interest Category Section 1
struct open_interest_category_section_1 {
    static constexpr std::string_view name = "Open Interest Category Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        open_interest_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(open_interest_message_type);
};

static_assert(sizeof(open_interest_category_section_1) == open_interest_category_section_1::size, "open_interest_category_section_1 lies over its bytes exactly");

// Open Interest Category: Open Interest Message
struct open_interest_category {
    static constexpr std::string_view name = "Open Interest Category";
    static constexpr bool is_message = false;
};

// Equity And Index Last Sale Message
struct equity_and_index_last_sale_message {
    static constexpr std::string_view name = "Equity And Index Last Sale Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number,
        security_symbol,
        reserved_1,
        expiration_block,
        strike_price_denominator_code,
        strike_price,
        volume,
        premium_price_denominator_code,
        premium_price,
        trade_identifier,
        reserved_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(security_symbol);
    OPRAFIELD(reserved_1);
    OPRAFIELD(expiration_block);
    OPRAFIELD(strike_price_denominator_code);
    OPRAFIELD(strike_price);
    OPRAFIELD(volume);
    OPRAFIELD(premium_price_denominator_code);
    OPRAFIELD(premium_price);
    OPRAFIELD(trade_identifier);
    OPRAFIELD(reserved_4);
};

static_assert(sizeof(equity_and_index_last_sale_message) == equity_and_index_last_sale_message::size, "equity_and_index_last_sale_message lies over its bytes exactly");

// Equity And Index Last Sale Message Payload: Branch
struct equity_and_index_last_sale_message_payload {
    static constexpr std::string_view name = "Equity And Index Last Sale Message Payload";
    static constexpr bool is_message = false;
};

// Equity And Index Last Sale Category Section 1
struct equity_and_index_last_sale_category_section_1 {
    static constexpr std::string_view name = "Equity And Index Last Sale Category Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        equity_and_index_last_sale_message_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(equity_and_index_last_sale_message_type);
};

static_assert(sizeof(equity_and_index_last_sale_category_section_1) == equity_and_index_last_sale_category_section_1::size, "equity_and_index_last_sale_category_section_1 lies over its bytes exactly");

// Equity And Index Last Sale Category: Equity And Index Last Sale Message
struct equity_and_index_last_sale_category {
    static constexpr std::string_view name = "Equity And Index Last Sale Category";
    static constexpr bool is_message = false;
};

// Control Message
struct control_message {
    static constexpr std::string_view name = "Control Message";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
};

static_assert(sizeof(control_message) == control_message::size, "control_message lies over its bytes exactly");

// Control Message Payload: Branch
struct control_message_payload {
    static constexpr std::string_view name = "Control Message Payload";
    static constexpr bool is_message = false;
};

// Control Category Section 1
struct control_category_section_1 {
    static constexpr std::string_view name = "Control Category Section 1";
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
    OPRAFIELD(control_message_type);
};

static_assert(sizeof(control_category_section_1) == control_category_section_1::size, "control_category_section_1 lies over its bytes exactly");

// Control Category: Control Message
struct control_category {
    static constexpr std::string_view name = "Control Category";
    static constexpr bool is_message = false;
};

// Administrative Message Section 1
struct administrative_message_section_1 {
    static constexpr std::string_view name = "Administrative Message Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_indicator,
        transaction_id,
        participant_reference_number,
        message_data_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(message_indicator);
    OPRAFIELD(transaction_id);
    OPRAFIELD(participant_reference_number);
    OPRAFIELD(message_data_length);
};

static_assert(sizeof(administrative_message_section_1) == administrative_message_section_1::size, "administrative_message_section_1 lies over its bytes exactly");

// Administrative Message
struct administrative_message {
    static constexpr std::string_view name = "Administrative Message";
    static constexpr bool is_message = true;
};

// Administrative Message Payload: Branch
struct administrative_message_payload {
    static constexpr std::string_view name = "Administrative Message Payload";
    static constexpr bool is_message = false;
};

// Administrative Category Section 1
struct administrative_category_section_1 {
    static constexpr std::string_view name = "Administrative Category Section 1";
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
    OPRAFIELD(administrative_message_type);
};

static_assert(sizeof(administrative_category_section_1) == administrative_category_section_1::size, "administrative_category_section_1 lies over its bytes exactly");

// Administrative Category: Administrative Message
struct administrative_category {
    static constexpr std::string_view name = "Administrative Category";
    static constexpr bool is_message = false;
};

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: Opra Message Header first level dispatch
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        participant_id,
        message_category>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(participant_id);
    OPRAFIELD(message_category);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Message: Opra Obi Block Data containing messages
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Block Timestamp: Opra packet timestamp
struct block_timestamp {
    static constexpr std::string_view name = "Block Timestamp";
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
    OPRAFIELD(seconds);
    OPRAFIELD(nanoseconds);
};

static_assert(sizeof(block_timestamp) == block_timestamp::size, "block_timestamp lies over its bytes exactly");

// Block Header: Opra packet header
struct block_header {
    static constexpr std::string_view name = "Block Header";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        version,
        block_size,
        data_feed_indicator,
        retransmission_indicator,
        session_indicator,
        block_sequence_number,
        messages_in_block,
        block_timestamp,
        block_checksum>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    OPRAFIELD(version);
    OPRAFIELD(block_size);
    OPRAFIELD(data_feed_indicator);
    OPRAFIELD(retransmission_indicator);
    OPRAFIELD(session_indicator);
    OPRAFIELD(block_sequence_number);
    OPRAFIELD(messages_in_block);
    OPRAFIELD(block_timestamp);
    OPRAFIELD(block_checksum);
};

static_assert(sizeof(block_header) == block_header::size, "block_header lies over its bytes exactly");

// Packet: Opra Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    OPRASEQUENCE(message);
};

#pragma pack(pop)

} // namespace siac::opra::output::obi::v6_2
