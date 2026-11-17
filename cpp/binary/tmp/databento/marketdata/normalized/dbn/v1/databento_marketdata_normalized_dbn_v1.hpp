// Databento.MarketData.Normalized.Dbn.v1: databento_marketdata_normalized_dbn_v1.hpp
// Databento MarketData Normalized Dbn 1 Template Meta Programming

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
#ifndef DBNFIELD
#define DBNFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef DBNSEQUENCE
#define DBNSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace databento::marketdata::normalized::dbn::v1 {

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

// Action: The event action
struct action {
    enum class type : char {
        add = 'A',
        cancel = 'C',
        fill_value = 'F',
        modify = 'M',
        none = 'N',
        clear = 'R',
        trade = 'T',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Activation: The time of instrument activation expressed as the number of nanoseconds since the UNIX epoch
struct activation {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Appl Id: The appl id
struct appl_id {
    using type = std::int16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Ct: The number of ask orders
struct ask_ct {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Pb: The publisher ID indicating the venue containing the best ask
struct ask_pb {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Px: The ask price
struct ask_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ask Sz: The ask size
struct ask_sz {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Asset: The asset
struct asset {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Auct Interest Clr Price: The hypothetical auction-clearing price for cross orders only
struct auct_interest_clr_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Status: Reserved for future use
struct auction_status {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Time: Reserved for future use
struct auction_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Auction Type: Venue-specific character code indicating the auction type; ~ when unused
struct auction_type {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Bad Ts Recv: Indicates the ts_recv value is inaccurate due to clock issues or packet reordering (bit 3)
struct bad_ts_recv {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Bid Ct: The number of bid orders
struct bid_ct {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Pb: The publisher ID indicating the venue containing the best bid
struct bid_pb {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Px: The bid price
struct bid_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Sz: The bid size
struct bid_sz {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cfi: The cfi
struct cfi {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Channel: The channel ID assigned by Databento as an incrementing integer starting at zero
struct channel {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Channel Id: The channel ID assigned by Databento as an incrementing integer starting at zero
struct channel_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Close: The close price for the bar
struct close {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cont Book Clr Price: The hypothetical auction-clearing price for both cross and continuous orders
struct cont_book_clr_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier: The contract multiplier
struct contract_multiplier {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier Unit: The contract multiplier unit
struct contract_multiplier_unit {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Control Fields: ASCII key=value pairs separated by the | character, terminated by a newline character
struct control_fields {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr control_fields(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Currency: The currency
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Dataset: The dataset code
struct dataset {
    using type = std::string_view;
    static constexpr std::size_t size = 16;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 16> value_;
};

// Decay Quantity: The decay quantity
struct decay_quantity {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Decay Start Date: The decay start date
struct decay_start_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Depth: The book level where the update event occurred
struct depth {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Display Factor: The display factor, where every 1 unit corresponds to 1e-9
struct display_factor {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Dummy 3: Reserved, 3 bytes
struct dummy_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Dummy 4: Reserved, 4 bytes
struct dummy_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// End: The end time of query range in UNIX epoch nanoseconds; no value when unbounded
struct end_type {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// End Date: The UTC end date of the mapping interval, as a YYYYMMDD integer
struct end_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// End Ts: The end of the mapping interval expressed as the number of nanoseconds since the UNIX epoch
struct end_ts {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Err: The error message
struct err {
    using type = std::string_view;
    static constexpr std::size_t size = 64;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 64> value_;
};

// Exchange: The exchange
struct exchange {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Expiration: The last eligible trade time expressed as the number of nanoseconds since the UNIX epoch
struct expiration {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Flow Schedule Type: The flow schedule type
struct flow_schedule_type {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Freeze Status: Reserved for future use
struct freeze_status {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Group: The group
struct group {
    using type = std::string_view;
    static constexpr std::size_t size = 21;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 21> value_;
};

// High: The high price for the bar
struct high {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// High Limit Price: The high limit price, where every 1 unit corresponds to 1e-9
struct high_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ind Match Price: Reserved for future use
struct ind_match_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Inst Attrib Value: A bitmap of instrument eligibility attributes; venue-specific
struct inst_attrib_value {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Instrument Class: The classification of the instrument
struct instrument_class {
    enum class type : char {
        bond = 'B',
        call = 'C',
        future = 'F',
        index = 'I',
        stock = 'K',
        mixed_spread = 'M',
        put = 'P',
        future_spread = 'S',
        option_spread = 'T',
        fx_spot = 'X',
        commodity_spot = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Instrument Id: The numeric instrument ID
struct instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Interval Count: The number of mapping intervals of the symbol
struct interval_count {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Is Quoting: The state of quoting in the instrument
struct is_quoting {
    enum class type : char {
        not_available = '~',
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

// Is Short Sell Restricted: The state of short sell restrictions for the instrument
struct is_short_sell_restricted {
    enum class type : char {
        not_available = '~',
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

// Is Trading: The state of trading in the instrument
struct is_trading {
    enum class type : char {
        not_available = '~',
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

// Last: Marks the last record in a single event for a given instrument_id (bit 7)
struct last {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Limit: The maximum number of records to return; no value when unlimited
struct limit {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low: The low price for the bar
struct low {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Limit Price: The low limit price, where every 1 unit corresponds to 1e-9
struct low_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Lower Collar: Reserved for future use
struct lower_collar {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Magic: The DBN magic string
struct magic {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Main Fraction: The main fraction
struct main_fraction {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mapped Symbol: The resolved symbol for this interval
struct mapped_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Mappings Count: The number of symbol mappings
struct mappings_count {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Depth: The market depth
struct market_depth {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Depth Implied: The market depth implied
struct market_depth_implied {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Imbalance Qty: Reserved for future use
struct market_imbalance_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Segment Id: The market segment id
struct market_segment_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Match Algorithm: The matching algorithm used for the instrument, typically FIFO
struct match_algorithm {
    enum class type : char {
        undefined = ' ',
        allocation = 'A',
        pro_rata = 'C',
        fifo = 'F',
        configurable = 'K',
        threshold_pro_rata = 'O',
        time_pro_rata = 'P',
        threshold_pro_rata_lmm = 'Q',
        fifo_top_lmm = 'S',
        fifo_lmm = 'T',
        institutional_prioritization = 'V',
        eurodollar_futures = 'Y',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Maturity Day: The maturity day
struct maturity_day {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maturity Month: The maturity month
struct maturity_month {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maturity Week: The maturity week
struct maturity_week {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maturity Year: The maturity year
struct maturity_year {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Price Variation: The max price variation, where every 1 unit corresponds to 1e-9
struct max_price_variation {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Trade Vol: The max trade vol
struct max_trade_vol {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maybe Bad Book: Indicates an unrecoverable gap was detected in the channel (bit 2)
struct maybe_bad_book {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Mbp: Indicates an aggregated price level message, not an individual order (bit 4)
struct mbp {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Md Security Trading Status: The current trading state of the instrument
struct md_security_trading_status {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Metadata Length: The length of the metadata after this field, in bytes
struct metadata_length {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Metadata Reserved: Reserved, 47 bytes
struct metadata_reserved {
    using type = std::span<const std::byte, 47>;
    static constexpr std::size_t size = 47;

    constexpr type value() const noexcept { return type{ value_ }; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 47> value_;
};

// Metadata Reserved 8: Reserved, 8 bytes; the deprecated record count
struct metadata_reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Lot Size: The min lot size
struct min_lot_size {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Lot Size Block: The min lot size block
struct min_lot_size_block {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Lot Size Round Lot: The min lot size round lot
struct min_lot_size_round_lot {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Price Increment: The min price increment, where every 1 unit corresponds to 1e-9
struct min_price_increment {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Price Increment Amount: The min price increment amount, where every 1 unit corresponds to 1e-9
struct min_price_increment_amount {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Trade Vol: The min trade vol
struct min_trade_vol {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Msg: The message from the Databento Live Subscription Gateway (LSG)
struct msg {
    using type = std::string_view;
    static constexpr std::size_t size = 64;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 64> value_;
};

// Not Found Count: The number of symbols that did not resolve for any day in the query time range
struct not_found_count {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Not Found Symbol: One of the symbols that did not resolve for any day in the query time range
struct not_found_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Num Extensions: Reserved for future use
struct num_extensions {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open: The open price for the bar
struct open {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: The order ID assigned at the venue
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Original Contract Size: The original contract size
struct original_contract_size {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Paired Qty: The quantity of shares that are eligible to be matched at ref_price
struct paired_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Partial Count: The number of symbols that did not resolve for at least one day in the query time range
struct partial_count {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Partial Symbol: One of the symbols that did not resolve for at least one day in the query time range
struct partial_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Price: The price where every 1 unit corresponds to 1e-9
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Display Format: The price display format
struct price_display_format {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Ratio: The price ratio, where every 1 unit corresponds to 1e-9
struct price_ratio {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Publisher Id: The publisher ID assigned by Databento, which denotes the dataset and venue
struct publisher_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Publisher Specific: Indicates a publisher-specific event (bit 1)
struct publisher_specific {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Quantity: The value for non-price statistics
struct quantity {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Raw Instrument Id: The instrument ID assigned by the publisher; may be the same as instrument_id
struct raw_instrument_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Raw Symbol: The raw symbol
struct raw_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Raw Symbol In: The symbol assigned by publisher
struct raw_symbol_in {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Record Length: The length of the record in 32-bit words, including this header and any ts_out trailer
struct record_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ref Price: The price at which the imbalance shares are calculated
struct ref_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 1: Reserved, 1 byte
struct reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 2: Reserved, 2 bytes
struct reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 4: Reserved, 4 bytes
struct reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved 6: Reserved, 6 bytes
struct reserved_6 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Reserved 7: Reserved, 7 bytes
struct reserved_7 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 7;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 7> value_;
};

// Reserved 8: Reserved, 8 bytes
struct reserved_8 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved Flag: Bit 0, unused
struct reserved_flag {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Rtype: The record type, which selects the record that follows the header
struct rtype {
    enum class type : std::uint8_t {
        market_by_price_0 = 0,
        market_by_price_1 = 1,
        market_by_price_10 = 10,
        ohlcv_deprecated = 17,
        status = 18,
        instrument_definition = 19,
        imbalance = 20,
        error = 21,
        symbol_mapping = 22,
        system = 23,
        statistics = 24,
        ohlcv_1_second = 32,
        ohlcv_1_minute = 33,
        ohlcv_1_hour = 34,
        ohlcv_1_day = 35,
        ohlcv_end_of_day = 36,
        market_by_order = 160,
        consolidated_market_by_price_1 = 177,
        consolidated_bbo_1_second = 192,
        consolidated_bbo_1_minute = 193,
        trade_with_consolidated_bbo = 194,
        bbo_1_second = 195,
        bbo_1_minute = 196,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Schema: The data record schema; no value for a file of mixed schemas
struct schema {
    enum class type : std::uint16_t {
        mbo = 0,
        mbp1 = 1,
        mbp10 = 2,
        tbbo = 3,
        trades = 4,
        ohlcv1_s = 5,
        ohlcv1_m = 6,
        ohlcv1_h = 7,
        ohlcv1_d = 8,
        definition = 9,
        statistics = 10,
        status = 11,
        imbalance = 12,
        ohlcv_eod = 13,
        cmbp1 = 14,
        cbbo1_s = 15,
        cbbo1_m = 16,
        tcbbo = 17,
        bbo1_s = 18,
        bbo1_m = 19,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Schema Definition: The schema definition; always empty
struct schema_definition {
    using type = std::span<const std::byte>;
    static constexpr bool dynamic = true;

    constexpr schema_definition(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { data_, length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Schema Definition Length: The length of the schema definition; always 0
struct schema_definition_length {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Reserved 1: Reserved, 1 byte
struct second_reserved_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Reserved 2: Reserved, 2 bytes
struct second_reserved_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Second Reserved 4: Reserved, 4 bytes
struct second_reserved_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Secsubtype: The secsubtype
struct secsubtype {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Security Type: The security type
struct security_type {
    using type = std::string_view;
    static constexpr std::size_t size = 7;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 7> value_;
};

// Security Update Action: Indicates if the instrument definition has been added, modified, or deleted
struct security_update_action {
    enum class type : char {
        add = 'A',
        delete_value = 'D',
        modify = 'M',
        invalid = '~',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sequence: The message sequence number assigned at the venue
struct sequence {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settl Currency: The settl currency
struct settl_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Settl Price Type: The type indicators for the settlement price, as a bitmap
struct settl_price_type {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side: The side that initiates the event
struct side {
    enum class type : char {
        ask = 'A',
        bid = 'B',
        none = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Significant Imbalance: Venue-specific character code; for Nasdaq, contains the raw Price Variation Indicator
struct significant_imbalance {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Size: The order quantity
struct size_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Snapshot: Indicates the message was sourced from a replay, such as a snapshot server (bit 5)
struct snapshot {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Ssr Filling Price: Reserved for future use
struct ssr_filling_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Start: The start time of query range in UNIX epoch nanoseconds
struct start_type {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Start Date: The UTC start date of the mapping interval, as a YYYYMMDD integer
struct start_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Start Ts: The start of the mapping interval expressed as the number of nanoseconds since the UNIX epoch
struct start_ts {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stat Flags: Additional flags associated with certain stat types
struct stat_flags {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stat Type: The type of statistic value contained in the message
struct stat_type {
    enum class type : std::uint16_t {
        opening_price = 1,
        indicative_opening_price = 2,
        settlement_price = 3,
        trading_session_low_price = 4,
        trading_session_high_price = 5,
        cleared_volume = 6,
        lowest_offer = 7,
        highest_bid = 8,
        open_interest = 9,
        fixing_price = 10,
        close_price = 11,
        net_change = 12,
        vwap = 13,
        volatility = 14,
        delta = 15,
        uncrossing_price = 16,
        upper_price_limit = 17,
        lower_price_limit = 18,
        block_volume = 19,
        indicative_close_price = 20,
        mwcb_level1 = 21,
        mwcb_level2 = 22,
        mwcb_level3 = 23,
        auction_collar_reference_price = 24,
        auction_collar_upper_price = 25,
        auction_collar_lower_price = 26,
        venue_specific_volume1 = 10001,
        venue_specific_price1 = 10002,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Status Action: The type of status change
struct status_action {
    enum class type : std::uint16_t {
        none = 0,
        pre_open = 1,
        pre_cross = 2,
        quoting = 3,
        cross = 4,
        rotation = 5,
        new_price_indication = 6,
        trading = 7,
        halt = 8,
        pause = 9,
        suspend = 10,
        pre_close = 11,
        close = 12,
        post_close = 13,
        ssr_change = 14,
        not_available_for_trading = 15,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Status Reason: Additional details about the cause of the status change
struct status_reason {
    enum class type : std::uint16_t {
        none = 0,
        scheduled = 1,
        surveillance_intervention = 2,
        market_event = 3,
        instrument_activation = 4,
        instrument_expiration = 5,
        recovery_in_process = 6,
        regulatory = 10,
        administrative = 11,
        non_compliance = 12,
        filings_not_current = 13,
        sec_trading_suspension = 14,
        new_issue = 15,
        issue_available = 16,
        issues_reviewed = 17,
        filing_reqs_satisfied = 18,
        news_pending = 30,
        news_released = 31,
        news_and_resumption_times = 32,
        news_not_forthcoming = 33,
        order_imbalance = 40,
        luld_pause = 50,
        operational = 60,
        additional_information_requested = 70,
        merger_effective = 80,
        etf = 90,
        corporate_action = 100,
        new_security_offering = 110,
        market_wide_halt_level1 = 120,
        market_wide_halt_level2 = 121,
        market_wide_halt_level3 = 122,
        market_wide_halt_carryover = 123,
        market_wide_halt_resumption = 124,
        quotation_not_available = 130,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Strike Price: The strike price, where every 1 unit corresponds to 1e-9
struct strike_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Price Currency: The strike price currency
struct strike_price_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Stype In: The input symbology type
struct stype_in {
    enum class type : std::uint8_t {
        instrument_id = 0,
        raw_symbol = 1,
        smart = 2,
        continuous = 3,
        parent = 4,
        nasdaq_symbol = 5,
        cms_symbol = 6,
        isin = 7,
        us_code = 8,
        bbg_comp_id = 9,
        bbg_comp_ticker = 10,
        figi = 11,
        figi_ticker = 12,
        listing_id = 13,
        issuer_id = 14,
        security_id = 15,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stype In Symbol: The input symbol
struct stype_in_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Stype Out: The output symbology type
struct stype_out {
    enum class type : std::uint8_t {
        instrument_id = 0,
        raw_symbol = 1,
        smart = 2,
        continuous = 3,
        parent = 4,
        nasdaq_symbol = 5,
        cms_symbol = 6,
        isin = 7,
        us_code = 8,
        bbg_comp_id = 9,
        bbg_comp_ticker = 10,
        figi = 11,
        figi_ticker = 12,
        listing_id = 13,
        issuer_id = 14,
        security_id = 15,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stype Out Symbol: The output symbol
struct stype_out_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Sub Fraction: The sub fraction
struct sub_fraction {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol: One of the query input symbols
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 22;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 22> value_;
};

// Symbols Count: The number of query input symbols
struct symbols_count {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tick Rule: The tick rule
struct tick_rule {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tob: Indicates a top-of-book message, not an individual order (bit 6)
struct tob {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Total Imbalance Qty: The quantity of shares that are not paired at ref_price
struct total_imbalance_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Event: Further information about a status update
struct trading_event {
    enum class type : std::uint16_t {
        none = 0,
        no_cancel = 1,
        change_trading_session = 2,
        implied_matching_on = 3,
        implied_matching_off = 4,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Reference Date: The trading session date corresponding to the settlement price in trading_reference_price, in number of days since the UNIX epoch
struct trading_reference_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Reference Price: The trading session settlement price on trading_reference_date, where every 1 unit corresponds to 1e-9
struct trading_reference_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ts Event: The matching-engine-received timestamp expressed as the number of nanoseconds since the UNIX epoch
struct ts_event {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ts In Delta: The matching-engine-sending timestamp expressed as the number of nanoseconds before ts_recv
struct ts_in_delta {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ts Out: Whether every record carries a ts_out trailer, the live gateway send timestamp
struct ts_out {
    enum class type : std::uint8_t {
        no = 0,
        yes = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ts Out Time: The live gateway send timestamp, present on every record when the metadata ts_out flag is set
struct ts_out_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds since the UNIX epoch
struct ts_recv {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ts Ref: The reference timestamp of the statistic value expressed as the number of nanoseconds since the UNIX epoch
struct ts_ref {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying: The underlying
struct underlying {
    using type = std::string_view;
    static constexpr std::size_t size = 21;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 21> value_;
};

// Underlying Id: The underlying id
struct underlying_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Product: The underlying product
struct underlying_product {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unit Of Measure: The unit of measure
struct unit_of_measure {
    using type = std::string_view;
    static constexpr std::size_t size = 31;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 31> value_;
};

// Unit Of Measure Qty: The unit of measure qty, where every 1 unit corresponds to 1e-9
struct unit_of_measure_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unpaired Qty: Reserved for future use
struct unpaired_qty {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unpaired Side: Reserved for future use
struct unpaired_side {
    enum class type : char {
        ask = 'A',
        bid = 'B',
        none = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Update Action: Indicates if the statistic is newly added or deleted
struct update_action {
    enum class type : std::uint8_t {
        new_value = 1,
        delete_value = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Upper Collar: Reserved for future use
struct upper_collar {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// User Defined Instrument: Indicates if the instrument is user defined
struct user_defined_instrument {
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

// Version: The DBN schema version number
struct version {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume: The total volume traded during the aggregation period
struct volume {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Control Message: A control message: key=value fields separated by |, ending on a newline
struct control_message {
    static constexpr std::string_view name = "Control Message";
    static constexpr bool is_message = false;
};

// Client Stream: The client's control messages: authentication, subscriptions and the session start
struct client_stream {
    static constexpr std::string_view name = "Client Stream";
    static constexpr bool is_message = false;
};

// Bid Ask Pair: A level
struct bid_ask_pair {
    static constexpr std::string_view name = "Bid Ask Pair";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        bid_px,
        ask_px,
        bid_sz,
        ask_sz,
        bid_ct,
        ask_ct>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(bid_px);
    DBNFIELD(ask_px);
    DBNFIELD(bid_sz);
    DBNFIELD(ask_sz);
    DBNFIELD(bid_ct);
    DBNFIELD(ask_ct);
};

static_assert(sizeof(bid_ask_pair) == bid_ask_pair::size, "bid_ask_pair lies over its bytes exactly");

// Flags: A bit field indicating event end, message characteristics, and data quality; declared least significant bit first
struct flags {
    static constexpr std::string_view name = "Flags";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(flags) == flags::size, "flags lies over its bytes exactly");

// Bbo Msg: Subsampled market by price with a known book depth of 1; the record of the bbo-1s and bbo-1m schemas
struct bbo_msg {
    static constexpr std::string_view name = "Bbo Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price,
        size_type,
        reserved_1,
        side,
        flags,
        second_reserved_1,
        ts_recv,
        reserved_4,
        sequence,
        bid_ask_pair>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(reserved_1);
    DBNFIELD(side);
    DBNFIELD(flags);
    DBNFIELD(second_reserved_1);
    DBNFIELD(ts_recv);
    DBNFIELD(reserved_4);
    DBNFIELD(sequence);
    DBNFIELD(bid_ask_pair);
};

static_assert(sizeof(bbo_msg) == bbo_msg::size, "bbo_msg lies over its bytes exactly");

// Consolidated Bid Ask Pair: A price level consolidated from multiple venues
struct consolidated_bid_ask_pair {
    static constexpr std::string_view name = "Consolidated Bid Ask Pair";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        bid_px,
        ask_px,
        bid_sz,
        ask_sz,
        bid_pb,
        reserved_2,
        ask_pb,
        second_reserved_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(bid_px);
    DBNFIELD(ask_px);
    DBNFIELD(bid_sz);
    DBNFIELD(ask_sz);
    DBNFIELD(bid_pb);
    DBNFIELD(reserved_2);
    DBNFIELD(ask_pb);
    DBNFIELD(second_reserved_2);
};

static_assert(sizeof(consolidated_bid_ask_pair) == consolidated_bid_ask_pair::size, "consolidated_bid_ask_pair lies over its bytes exactly");

// Cbbo Msg: Subsampled consolidated market by price with a known book depth of 1; the record of the cbbo-1s and cbbo-1m schemas
struct cbbo_msg {
    static constexpr std::string_view name = "Cbbo Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price,
        size_type,
        reserved_1,
        side,
        flags,
        second_reserved_1,
        ts_recv,
        reserved_8,
        consolidated_bid_ask_pair>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(reserved_1);
    DBNFIELD(side);
    DBNFIELD(flags);
    DBNFIELD(second_reserved_1);
    DBNFIELD(ts_recv);
    DBNFIELD(reserved_8);
    DBNFIELD(consolidated_bid_ask_pair);
};

static_assert(sizeof(cbbo_msg) == cbbo_msg::size, "cbbo_msg lies over its bytes exactly");

// Cmbp 1 Msg: Consolidated market by price implementation with a known book depth of 1; the record of the cmbp-1 and tcbbo schemas
struct cmbp_1_msg {
    static constexpr std::string_view name = "Cmbp 1 Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price,
        size_type,
        action,
        side,
        flags,
        reserved_1,
        ts_recv,
        ts_in_delta,
        reserved_4,
        consolidated_bid_ask_pair>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(action);
    DBNFIELD(side);
    DBNFIELD(flags);
    DBNFIELD(reserved_1);
    DBNFIELD(ts_recv);
    DBNFIELD(ts_in_delta);
    DBNFIELD(reserved_4);
    DBNFIELD(consolidated_bid_ask_pair);
};

static_assert(sizeof(cmbp_1_msg) == cmbp_1_msg::size, "cmbp_1_msg lies over its bytes exactly");

// Mbo Msg: A market-by-order (MBO) tick message
struct mbo_msg {
    static constexpr std::string_view name = "Mbo Msg";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_id,
        price,
        size_type,
        flags,
        channel_id,
        action,
        side,
        ts_recv,
        ts_in_delta,
        sequence>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(order_id);
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(flags);
    DBNFIELD(channel_id);
    DBNFIELD(action);
    DBNFIELD(side);
    DBNFIELD(ts_recv);
    DBNFIELD(ts_in_delta);
    DBNFIELD(sequence);
};

static_assert(sizeof(mbo_msg) == mbo_msg::size, "mbo_msg lies over its bytes exactly");

// Stat Msg: A statistics message; the record of the statistics schema
struct stat_msg {
    static constexpr std::string_view name = "Stat Msg";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        ts_recv,
        ts_ref,
        price,
        quantity,
        sequence,
        ts_in_delta,
        stat_type,
        channel,
        update_action,
        stat_flags,
        reserved_6>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(ts_recv);
    DBNFIELD(ts_ref);
    DBNFIELD(price);
    DBNFIELD(quantity);
    DBNFIELD(sequence);
    DBNFIELD(ts_in_delta);
    DBNFIELD(stat_type);
    DBNFIELD(channel);
    DBNFIELD(update_action);
    DBNFIELD(stat_flags);
    DBNFIELD(reserved_6);
};

static_assert(sizeof(stat_msg) == stat_msg::size, "stat_msg lies over its bytes exactly");

// System Msg: A non-error message from the Databento Live Subscription Gateway (LSG); also used for heartbeating
struct system_msg {
    static constexpr std::string_view name = "System Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        msg>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(msg);
};

static_assert(sizeof(system_msg) == system_msg::size, "system_msg lies over its bytes exactly");

// Symbol Mapping Msg: A symbol mapping message, which maps a symbol of one SType to another
struct symbol_mapping_msg {
    static constexpr std::string_view name = "Symbol Mapping Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        stype_in_symbol,
        stype_out_symbol,
        dummy_4,
        start_ts,
        end_ts>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(stype_in_symbol);
    DBNFIELD(stype_out_symbol);
    DBNFIELD(dummy_4);
    DBNFIELD(start_ts);
    DBNFIELD(end_ts);
};

static_assert(sizeof(symbol_mapping_msg) == symbol_mapping_msg::size, "symbol_mapping_msg lies over its bytes exactly");

// Error Msg: An error message from the Databento Live Subscription Gateway (LSG)
struct error_msg {
    static constexpr std::string_view name = "Error Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        err>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(err);
};

static_assert(sizeof(error_msg) == error_msg::size, "error_msg lies over its bytes exactly");

// Imbalance Msg: An auction imbalance message; the record of the imbalance schema
struct imbalance_msg {
    static constexpr std::string_view name = "Imbalance Msg";
    static constexpr std::size_t size = 96;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        ts_recv,
        ref_price,
        auction_time,
        cont_book_clr_price,
        auct_interest_clr_price,
        ssr_filling_price,
        ind_match_price,
        upper_collar,
        lower_collar,
        paired_qty,
        total_imbalance_qty,
        market_imbalance_qty,
        unpaired_qty,
        auction_type,
        side,
        auction_status,
        freeze_status,
        num_extensions,
        unpaired_side,
        significant_imbalance,
        reserved_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(ts_recv);
    DBNFIELD(ref_price);
    DBNFIELD(auction_time);
    DBNFIELD(cont_book_clr_price);
    DBNFIELD(auct_interest_clr_price);
    DBNFIELD(ssr_filling_price);
    DBNFIELD(ind_match_price);
    DBNFIELD(upper_collar);
    DBNFIELD(lower_collar);
    DBNFIELD(paired_qty);
    DBNFIELD(total_imbalance_qty);
    DBNFIELD(market_imbalance_qty);
    DBNFIELD(unpaired_qty);
    DBNFIELD(auction_type);
    DBNFIELD(side);
    DBNFIELD(auction_status);
    DBNFIELD(freeze_status);
    DBNFIELD(num_extensions);
    DBNFIELD(unpaired_side);
    DBNFIELD(significant_imbalance);
    DBNFIELD(reserved_1);
};

static_assert(sizeof(imbalance_msg) == imbalance_msg::size, "imbalance_msg lies over its bytes exactly");

// Instrument Def Msg: A definition of an instrument; the record of the definition schema
struct instrument_def_msg {
    static constexpr std::string_view name = "Instrument Def Msg";
    static constexpr std::size_t size = 344;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        ts_recv,
        min_price_increment,
        display_factor,
        expiration,
        activation,
        high_limit_price,
        low_limit_price,
        max_price_variation,
        trading_reference_price,
        unit_of_measure_qty,
        min_price_increment_amount,
        price_ratio,
        inst_attrib_value,
        underlying_id,
        raw_instrument_id,
        market_depth_implied,
        market_depth,
        market_segment_id,
        max_trade_vol,
        min_lot_size,
        min_lot_size_block,
        min_lot_size_round_lot,
        min_trade_vol,
        reserved_4,
        contract_multiplier,
        decay_quantity,
        original_contract_size,
        second_reserved_4,
        trading_reference_date,
        appl_id,
        maturity_year,
        decay_start_date,
        channel,
        currency,
        settl_currency,
        secsubtype,
        raw_symbol,
        group,
        exchange,
        asset,
        cfi,
        security_type,
        unit_of_measure,
        underlying,
        strike_price_currency,
        instrument_class,
        reserved_2,
        strike_price,
        reserved_6,
        match_algorithm,
        md_security_trading_status,
        main_fraction,
        price_display_format,
        settl_price_type,
        sub_fraction,
        underlying_product,
        security_update_action,
        maturity_month,
        maturity_day,
        maturity_week,
        user_defined_instrument,
        contract_multiplier_unit,
        flow_schedule_type,
        tick_rule,
        dummy_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(ts_recv);
    DBNFIELD(min_price_increment);
    DBNFIELD(display_factor);
    DBNFIELD(expiration);
    DBNFIELD(activation);
    DBNFIELD(high_limit_price);
    DBNFIELD(low_limit_price);
    DBNFIELD(max_price_variation);
    DBNFIELD(trading_reference_price);
    DBNFIELD(unit_of_measure_qty);
    DBNFIELD(min_price_increment_amount);
    DBNFIELD(price_ratio);
    DBNFIELD(inst_attrib_value);
    DBNFIELD(underlying_id);
    DBNFIELD(raw_instrument_id);
    DBNFIELD(market_depth_implied);
    DBNFIELD(market_depth);
    DBNFIELD(market_segment_id);
    DBNFIELD(max_trade_vol);
    DBNFIELD(min_lot_size);
    DBNFIELD(min_lot_size_block);
    DBNFIELD(min_lot_size_round_lot);
    DBNFIELD(min_trade_vol);
    DBNFIELD(reserved_4);
    DBNFIELD(contract_multiplier);
    DBNFIELD(decay_quantity);
    DBNFIELD(original_contract_size);
    DBNFIELD(second_reserved_4);
    DBNFIELD(trading_reference_date);
    DBNFIELD(appl_id);
    DBNFIELD(maturity_year);
    DBNFIELD(decay_start_date);
    DBNFIELD(channel);
    DBNFIELD(currency);
    DBNFIELD(settl_currency);
    DBNFIELD(secsubtype);
    DBNFIELD(raw_symbol);
    DBNFIELD(group);
    DBNFIELD(exchange);
    DBNFIELD(asset);
    DBNFIELD(cfi);
    DBNFIELD(security_type);
    DBNFIELD(unit_of_measure);
    DBNFIELD(underlying);
    DBNFIELD(strike_price_currency);
    DBNFIELD(instrument_class);
    DBNFIELD(reserved_2);
    DBNFIELD(strike_price);
    DBNFIELD(reserved_6);
    DBNFIELD(match_algorithm);
    DBNFIELD(md_security_trading_status);
    DBNFIELD(main_fraction);
    DBNFIELD(price_display_format);
    DBNFIELD(settl_price_type);
    DBNFIELD(sub_fraction);
    DBNFIELD(underlying_product);
    DBNFIELD(security_update_action);
    DBNFIELD(maturity_month);
    DBNFIELD(maturity_day);
    DBNFIELD(maturity_week);
    DBNFIELD(user_defined_instrument);
    DBNFIELD(contract_multiplier_unit);
    DBNFIELD(flow_schedule_type);
    DBNFIELD(tick_rule);
    DBNFIELD(dummy_3);
};

static_assert(sizeof(instrument_def_msg) == instrument_def_msg::size, "instrument_def_msg lies over its bytes exactly");

// Status Msg: A trading status update message; the record of the status schema
struct status_msg {
    static constexpr std::string_view name = "Status Msg";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        ts_recv,
        status_action,
        status_reason,
        trading_event,
        is_trading,
        is_quoting,
        is_short_sell_restricted,
        reserved_7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(ts_recv);
    DBNFIELD(status_action);
    DBNFIELD(status_reason);
    DBNFIELD(trading_event);
    DBNFIELD(is_trading);
    DBNFIELD(is_quoting);
    DBNFIELD(is_short_sell_restricted);
    DBNFIELD(reserved_7);
};

static_assert(sizeof(status_msg) == status_msg::size, "status_msg lies over its bytes exactly");

// Ohlcv Msg: Open, high, low, close, and volume; the record of the ohlcv schemas
struct ohlcv_msg {
    static constexpr std::string_view name = "Ohlcv Msg";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        open,
        high,
        low,
        close,
        volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(open);
    DBNFIELD(high);
    DBNFIELD(low);
    DBNFIELD(close);
    DBNFIELD(volume);
};

static_assert(sizeof(ohlcv_msg) == ohlcv_msg::size, "ohlcv_msg lies over its bytes exactly");

// Mbp 10 Msg: Market by price implementation with a known book depth of 10
struct mbp_10_msg {
    static constexpr std::string_view name = "Mbp 10 Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price,
        size_type,
        action,
        side,
        flags,
        depth,
        ts_recv,
        ts_in_delta,
        sequence,
        bid_ask_pair>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(action);
    DBNFIELD(side);
    DBNFIELD(flags);
    DBNFIELD(depth);
    DBNFIELD(ts_recv);
    DBNFIELD(ts_in_delta);
    DBNFIELD(sequence);
    DBNFIELD(bid_ask_pair);
};

static_assert(sizeof(mbp_10_msg) == mbp_10_msg::size, "mbp_10_msg lies over its bytes exactly");

// Mbp 1 Msg: Market by price implementation with a known book depth of 1; the record of the mbp-1 and tbbo schemas
struct mbp_1_msg {
    static constexpr std::string_view name = "Mbp 1 Msg";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price,
        size_type,
        action,
        side,
        flags,
        depth,
        ts_recv,
        ts_in_delta,
        sequence,
        bid_ask_pair>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(action);
    DBNFIELD(side);
    DBNFIELD(flags);
    DBNFIELD(depth);
    DBNFIELD(ts_recv);
    DBNFIELD(ts_in_delta);
    DBNFIELD(sequence);
    DBNFIELD(bid_ask_pair);
};

static_assert(sizeof(mbp_1_msg) == mbp_1_msg::size, "mbp_1_msg lies over its bytes exactly");

// Trade Msg: Market by price implementation with a book depth of 0; equivalent to MBP-0, the record of the trades schema
struct trade_msg {
    static constexpr std::string_view name = "Trade Msg";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        price,
        size_type,
        action,
        side,
        flags,
        depth,
        ts_recv,
        ts_in_delta,
        sequence>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(price);
    DBNFIELD(size_type);
    DBNFIELD(action);
    DBNFIELD(side);
    DBNFIELD(flags);
    DBNFIELD(depth);
    DBNFIELD(ts_recv);
    DBNFIELD(ts_in_delta);
    DBNFIELD(sequence);
};

static_assert(sizeof(trade_msg) == trade_msg::size, "trade_msg lies over its bytes exactly");

// Record Body: Branch
struct record_body {
    static constexpr std::string_view name = "Record Body";
    static constexpr bool is_message = false;
};

// Record Header: DBN common header of every record
struct record_header {
    static constexpr std::string_view name = "Record Header";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        record_length,
        rtype,
        publisher_id,
        instrument_id,
        ts_event>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(record_length);
    DBNFIELD(rtype);
    DBNFIELD(publisher_id);
    DBNFIELD(instrument_id);
    DBNFIELD(ts_event);
};

static_assert(sizeof(record_header) == record_header::size, "record_header lies over its bytes exactly");

// Record: a struct of a size only its bytes state, reading a Optional rule's Stored parameter, 'gatewaystream.metadata.tsout', not generated yet

// Mapping Interval: The resolution of a symbol for a date range
struct mapping_interval {
    static constexpr std::string_view name = "Mapping Interval";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        start_date,
        end_date,
        mapped_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(start_date);
    DBNFIELD(end_date);
    DBNFIELD(mapped_symbol);
};

static_assert(sizeof(mapping_interval) == mapping_interval::size, "mapping_interval lies over its bytes exactly");

// Symbol Mapping Section 1
struct symbol_mapping_section_1 {
    static constexpr std::string_view name = "Symbol Mapping Section 1";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        raw_symbol_in,
        interval_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(raw_symbol_in);
    DBNFIELD(interval_count);
};

static_assert(sizeof(symbol_mapping_section_1) == symbol_mapping_section_1::size, "symbol_mapping_section_1 lies over its bytes exactly");

// Symbol Mapping: The mappings of one raw symbol
struct symbol_mapping {
    static constexpr std::string_view name = "Symbol Mapping";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    DBNSEQUENCE(mapping_interval);
};

// Metadata Section 1
struct metadata_section_1 {
    static constexpr std::string_view name = "Metadata Section 1";
    static constexpr std::size_t size = 112;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        magic,
        version,
        metadata_length,
        dataset,
        schema,
        start_type,
        end_type,
        limit,
        metadata_reserved_8,
        stype_in,
        stype_out,
        ts_out,
        metadata_reserved,
        schema_definition_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(magic);
    DBNFIELD(version);
    DBNFIELD(metadata_length);
    DBNFIELD(dataset);
    DBNFIELD(schema);
    DBNFIELD(start_type);
    DBNFIELD(end_type);
    DBNFIELD(limit);
    DBNFIELD(metadata_reserved_8);
    DBNFIELD(stype_in);
    DBNFIELD(stype_out);
    DBNFIELD(ts_out);
    DBNFIELD(metadata_reserved);
    DBNFIELD(schema_definition_length);
};

static_assert(sizeof(metadata_section_1) == metadata_section_1::size, "metadata_section_1 lies over its bytes exactly");

// Metadata Section 2
struct metadata_section_2 {
    static constexpr std::string_view name = "Metadata Section 2";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbols_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(symbols_count);
};

static_assert(sizeof(metadata_section_2) == metadata_section_2::size, "metadata_section_2 lies over its bytes exactly");

// Metadata Section 3
struct metadata_section_3 {
    static constexpr std::string_view name = "Metadata Section 3";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        partial_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(partial_count);
};

static_assert(sizeof(metadata_section_3) == metadata_section_3::size, "metadata_section_3 lies over its bytes exactly");

// Metadata Section 4
struct metadata_section_4 {
    static constexpr std::string_view name = "Metadata Section 4";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        not_found_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(not_found_count);
};

static_assert(sizeof(metadata_section_4) == metadata_section_4::size, "metadata_section_4 lies over its bytes exactly");

// Metadata Section 5
struct metadata_section_5 {
    static constexpr std::string_view name = "Metadata Section 5";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        mappings_count>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    DBNFIELD(mappings_count);
};

static_assert(sizeof(metadata_section_5) == metadata_section_5::size, "metadata_section_5 lies over its bytes exactly");

// Metadata: DBN metadata header, once at the start of a file or stream
struct metadata {
    static constexpr std::string_view name = "Metadata";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    DBNSEQUENCE(symbol);
    DBNSEQUENCE(partial_symbol);
    DBNSEQUENCE(not_found_symbol);
    DBNSEQUENCE(symbol_mapping);
};

// Authentication Response: The gateway sends this response following the client's authentication request (success, and error or session_id)
struct authentication_response {
    static constexpr std::string_view name = "Authentication Response";
    static constexpr bool is_message = false;
};

// Challenge Request: The gateway sends this message immediately following the greeting message to authenticate the client (cram: a randomly-generated challenge string)
struct challenge_request {
    static constexpr std::string_view name = "Challenge Request";
    static constexpr bool is_message = false;
};

// Greeting: The message sent by the gateway immediately after a client connects (lsg_version: the live gateway version)
struct greeting {
    static constexpr std::string_view name = "Greeting";
    static constexpr bool is_message = false;
};

// Gateway Stream: the packet, reading a Optional rule's Stored parameter, 'gatewaystream.metadata.tsout', not generated yet

// File: the packet, reading a Optional rule's Stored parameter, 'file.metadata.tsout', not generated yet

#pragma pack(pop)

} // namespace databento::marketdata::normalized::dbn::v1
