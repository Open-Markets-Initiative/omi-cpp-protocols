// Eurex T7 Eobi Fbe 13.0 Template Meta Programming

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
#ifndef EOBIFIELD
#define EOBIFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef EOBISEQUENCE
#define EOBISEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace eurex::t7::eobi::fbe::v13_0 {

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

// Aggressor Side
struct aggressor_side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(2);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Aggressor Time
struct aggressor_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Algorithmic Trade Indicator
struct algorithmic_trade_indicator {
    enum class type : std::uint8_t {
        algorithmic_trade = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Appl Seq Num: Application sequence number per Market Segment / Partition
struct appl_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(4294967294ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Appl Seq Reset Indicator: Indicates whether Application Sequence Number was reset for this Market Segment
struct appl_seq_reset_indicator {
    enum class type : std::uint8_t {
        no_reset = 0,
        reset = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bid Ord Type
struct bid_ord_type {
    enum class type : std::uint8_t {
        market = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Bid Px
struct bid_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bid Size
struct bid_size {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Body Len: Total packet body length in bytes (header + messages)
struct body_len {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(65534ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Completion Indicator: End-of-event marker (0 = more to follow, 1 = last packet of event)
struct completion_indicator {
    enum class type : std::uint8_t {
        incomplete = 0,
        complete = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Contract Date
struct contract_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(18000101ULL);
    static constexpr type maximum = static_cast<type>(99991231ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cross Request Type
struct cross_request_type {
    enum class type : std::uint8_t {
        cross_announcement = 1,
        liquidity_improvement_cross = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(2);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Display Qty
struct display_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// DSCP: Copy of DSCP from IP protocol header
struct dscp {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0xFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(254ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exec Id
struct exec_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exercise Style
struct exercise_style {
    enum class type : std::uint8_t {
        european = 0,
        american = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Fast Market Indicator
struct fast_market_indicator {
    enum class type : std::uint8_t {
        no = 0,
        yes = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Hhi Indicator
struct hhi_indicator {
    enum class type : std::int8_t {
        no_update = -1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(128);
    static constexpr type minimum = static_cast<type>(-1);
    static constexpr type maximum = static_cast<type>(100);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// High Px
struct high_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Qty
struct imbalance_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Implied Market Indicator
struct implied_market_indicator {
    enum class type : std::uint8_t {
        not_implied = 0,
        implied_in_out = 3,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(3);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Input Source
struct input_source {
    enum class type : std::uint8_t {
        clip_client_broker = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Instrument Scope Product Complex
struct instrument_scope_product_complex {
    enum class type : std::uint8_t {
        simple_instrument = 1,
        standard_option_strategy = 2,
        non_standard_option_strategy = 3,
        volatility_strategy = 4,
        futures_spread = 5,
        inter_product_spread = 6,
        standard_futures_strategy = 7,
        pack_and_bundle = 8,
        strip = 9,
        flexible_instrument = 10,
        commodity_strip = 11,
        scaled_simple_instrument = 12,
        non_standard_volatility_strategy = 13,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(13);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Fragment
struct last_fragment {
    enum class type : std::uint8_t {
        n = 0,
        y = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Msg Seq Num Processed
struct last_msg_seq_num_processed {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(4294967294ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Px
struct last_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Qty
struct last_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Update Time
struct last_update_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Price
struct leg_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio Multiplier
struct leg_ratio_multiplier {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(1ULL);
    static constexpr type maximum = static_cast<type>(2147483647ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio Qty
struct leg_ratio_qty {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x80000000LL);
    static constexpr type minimum = static_cast<type>(-2147483647LL);
    static constexpr type maximum = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Id
struct leg_security_id {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Type
struct leg_security_type {
    enum class type : std::uint8_t {
        leg_security_multi_leg = 1,
        leg_security_underlying_leg = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(2);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Side
struct leg_side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(2);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Symbol
struct leg_symbol {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x80000000LL);
    static constexpr type minimum = static_cast<type>(-2147483647LL);
    static constexpr type maximum = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Px
struct low_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Condition
struct market_condition {
    enum class type : std::uint8_t {
        normal = 0,
        stressed = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Market Segment Id: Market Segment identifier for the partition
struct market_segment_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x80000000LL);
    static constexpr type minimum = static_cast<type>(-2147483647LL);
    static constexpr type maximum = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mass Market Condition
struct mass_market_condition {
    enum class type : std::uint8_t {
        normal = 0,
        stressed = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mass Sold Out Indicator
struct mass_sold_out_indicator {
    enum class type : std::uint8_t {
        sold_out = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Sub Type
struct match_sub_type {
    enum class type : std::uint8_t {
        opening_auction = 1,
        closing_auction = 2,
        intraday_auction = 3,
        circuit_breaker_auction = 4,
        ipo_auction = 5,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(5);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Match Type
struct match_type {
    enum class type : std::uint8_t {
        confirmed_trade_report = 3,
        cross_auction = 5,
        call_auction = 7,
        liquidity_improvement_cross = 13,
        continuous_auction = 14,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(3);
    static constexpr type maximum = static_cast<type>(14);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Maturity Date
struct maturity_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(18000101ULL);
    static constexpr type maximum = static_cast<type>(99991231ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Px
struct md_entry_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size
struct md_entry_size {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Type
struct md_entry_type {
    enum class type : std::uint8_t {
        trade = 2,
        opening_price = 4,
        closing_price = 5,
        high_price = 7,
        low_price = 8,
        trade_volume = 66,
        previous_closing_price = 101,
        opening_auction = 200,
        intraday_auction = 201,
        circuit_breaker_auction = 202,
        closing_auction = 203,
        ipo_auction = 204,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(2);
    static constexpr type maximum = static_cast<type>(204);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Origin Type
struct md_origin_type {
    enum class type : std::uint8_t {
        book = 0,
        off_book = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Msg Seq Num: Per-packet sequence number; 0xFFFFFFFF for unsequenced packets (heartbeats)
struct msg_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(4294967294ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Multi Leg Price Model
struct multi_leg_price_model {
    enum class type : std::uint8_t {
        standard = 0,
        user_defined = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Multi Leg Reporting Type
struct multi_leg_reporting_type {
    enum class type : std::uint8_t {
        single_security = 1,
        individual_leg_of_a_multi_leg_security = 2,
        multi_leg_security = 3,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(3);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// No Legs
struct no_legs {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0xFFULL);
    static constexpr type minimum = static_cast<type>(2ULL);
    static constexpr type maximum = static_cast<type>(20ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Md Entries
struct no_md_entries {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0xFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(15ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// No Related Sym
struct no_related_sym {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0xFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(24ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Non Disclosed Trade Volume
struct non_disclosed_trade_volume {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Buy Orders
struct number_of_buy_orders {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(65534ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Buy Sides
struct number_of_buy_sides {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(65534ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Sell Orders
struct number_of_sell_orders {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(65534ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Sell Sides
struct number_of_sell_sides {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(65534ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Ord Type
struct offer_ord_type {
    enum class type : std::uint8_t {
        market = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Offer Px
struct offer_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offer Size
struct offer_size {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Opt Attribute
struct opt_attribute {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(4294967294ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ord Type
struct ord_type {
    enum class type : std::uint8_t {
        market = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Pad1
struct pad1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pad2
struct pad2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pad3
struct pad3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Pad4
struct pad4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pad5
struct pad5 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 5;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 5> value_;
};

// Pad6
struct pad6 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Pad7
struct pad7 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 7;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 7> value_;
};

// Partition Id: Partition identifier within the market segment
struct partition_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0xFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(254ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Potential Security Trading Event
struct potential_security_trading_event {
    enum class type : std::uint8_t {
        none = 0,
        price_volatility_auction_is_extended = 10,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(10);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Prev Display Qty
struct prev_display_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Price
struct prev_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prev Price Hhi Indicator
struct prev_price_hhi_indicator {
    enum class type : std::int8_t {
        no_update = -1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(128);
    static constexpr type minimum = static_cast<type>(-1);
    static constexpr type maximum = static_cast<type>(100);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Product Complex
struct product_complex {
    enum class type : std::uint8_t {
        simple_instrument = 1,
        standard_option_strategy = 2,
        non_standard_option_strategy = 3,
        volatility_strategy = 4,
        futures_spread = 5,
        inter_product_spread = 6,
        standard_futures_strategy = 7,
        pack_and_bundle = 8,
        strip = 9,
        flexible_instrument = 10,
        commodity_strip = 11,
        scaled_simple_instrument = 12,
        non_standard_volatility_strategy = 13,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(13);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Put Or Call
struct put_or_call {
    enum class type : std::uint8_t {
        put = 0,
        call = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quantity Scaling Factor
struct quantity_scaling_factor {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(1ULL);
    static constexpr type maximum = static_cast<type>(1000ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Related Security Id
struct related_security_id {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Request Time
struct request_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Resting Cxl Qty
struct resting_cxl_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Resting Hidden Qty
struct resting_hidden_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Desc
struct security_desc {
    using type = std::string_view;
    static constexpr std::size_t size = 40;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 40> value_;
};

// Security Id
struct security_id {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Mass Status
struct security_mass_status {
    enum class type : std::uint8_t {
        active = 1,
        inactive = 2,
        expired = 4,
        knocked_out = 6,
        knock_out_revoked = 7,
        suspended = 9,
        pending_deletion = 11,
        knocked_out_and_suspended = 12,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(12);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Mass Trading Event
struct security_mass_trading_event {
    enum class type : std::uint8_t {
        price_volatility_auction_is_extended = 10,
        price_volatility_auction_is_extended_again = 11,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(10);
    static constexpr type maximum = static_cast<type>(11);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Mass Trading Status
struct security_mass_trading_status {
    enum class type : std::uint8_t {
        trading_halt = 2,
        market_imbalance_buy = 7,
        market_imbalance_sell = 8,
        closed = 200,
        restricted = 201,
        book = 202,
        continuous = 203,
        opening_auction = 204,
        opening_auction_freeze = 205,
        intraday_auction = 206,
        intraday_auction_freeze = 207,
        circuit_breaker_auction = 208,
        circuit_breaker_auction_freeze = 209,
        closing_auction = 210,
        closing_auction_freeze = 211,
        ipo_auction = 212,
        ipo_auction_freeze = 213,
        pre_call = 214,
        call = 215,
        freeze = 216,
        trade_at_close = 217,
        circuit_breaker_auction_triggered_by_static_limit_breach = 220,
        circuit_breaker_auction_triggered_by_static_limit_breach_freeze = 221,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(2);
    static constexpr type maximum = static_cast<type>(221);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Reference Data Supplement
struct security_reference_data_supplement {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(18000101ULL);
    static constexpr type maximum = static_cast<type>(99991231ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Status
struct security_status {
    enum class type : std::uint8_t {
        active = 1,
        inactive = 2,
        expired = 4,
        knocked_out = 6,
        knock_out_revoked = 7,
        suspended = 9,
        pending_deletion = 11,
        knocked_out_and_suspended = 12,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(12);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Sub Type
struct security_sub_type {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x80000000LL);
    static constexpr type minimum = static_cast<type>(-2147483647LL);
    static constexpr type maximum = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Trading Event
struct security_trading_event {
    enum class type : std::uint8_t {
        price_volatility_auction_is_extended = 10,
        price_volatility_auction_is_extended_again = 11,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(10);
    static constexpr type maximum = static_cast<type>(11);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Trading Status
struct security_trading_status {
    enum class type : std::uint8_t {
        trading_halt = 2,
        market_imbalance_buy = 7,
        market_imbalance_sell = 8,
        closed = 200,
        restricted = 201,
        book = 202,
        continuous = 203,
        opening_auction = 204,
        opening_auction_freeze = 205,
        intraday_auction = 206,
        intraday_auction_freeze = 207,
        circuit_breaker_auction = 208,
        circuit_breaker_auction_freeze = 209,
        closing_auction = 210,
        closing_auction_freeze = 211,
        ipo_auction = 212,
        ipo_auction_freeze = 213,
        pre_call = 214,
        call = 215,
        freeze = 216,
        trade_at_close = 217,
        circuit_breaker_auction_triggered_by_static_limit_breach = 220,
        circuit_breaker_auction_triggered_by_static_limit_breach_freeze = 221,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(2);
    static constexpr type maximum = static_cast<type>(221);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type
struct security_type {
    enum class type : std::uint8_t {
        opt = 1,
        fut = 2,
        mleg = 3,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(3);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Settl Method
struct settl_method {
    enum class type : std::uint8_t {
        cash = 0,
        physical = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side
struct side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(2);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sold Out Indicator
struct sold_out_indicator {
    enum class type : std::uint8_t {
        sold_out = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Strike Price
struct strike_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0x8000000000000000LL);
    static constexpr type minimum = static_cast<type>(-9223372036854775807LL);
    static constexpr type maximum = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Template Id: SBE template identifier of the packet header (e.g., 13004 RefreshHeader / 13005 BeaconMessage)
struct template_id {
    enum class type : std::uint16_t {
        add_complex_instrument = 13400,
        add_flexible_instrument = 13401,
        add_scaled_simple_instrument = 13402,
        auction_bbo = 13500,
        auction_clearing_price = 13501,
        cross_request = 13502,
        execution_summary = 13202,
        full_order_execution = 13104,
        heartbeat = 13001,
        instrument_state_change = 13301,
        instrument_summary = 13601,
        mass_instrument_state_change = 13302,
        order_add = 13100,
        order_delete = 13102,
        order_mass_delete = 13103,
        order_modify = 13101,
        order_modify_same_prio = 13106,
        packet_header = 13004,
        partial_order_execution = 13105,
        product_state_change = 13300,
        product_summary = 13600,
        quote_request = 13503,
        snapshot_order = 13602,
        tes_trade_report = 13203,
        top_of_book = 13504,
        trade_report = 13201,
        trade_reversal = 13200,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535);
    static constexpr type minimum = static_cast<type>(0);
    static constexpr type maximum = static_cast<type>(65534);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Tes Security Mass Status
struct tes_security_mass_status {
    enum class type : std::uint8_t {
        active = 1,
        inactive = 2,
        expired = 4,
        suspended = 9,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(9);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Tes Security Status
struct tes_security_status {
    enum class type : std::uint8_t {
        active = 1,
        inactive = 2,
        expired = 4,
        suspended = 9,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(9);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Tes Trad Ses Status
struct tes_trad_ses_status {
    enum class type : std::uint8_t {
        halted = 1,
        open = 2,
        closed = 3,
        pre_close = 5,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(5);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Tot No Orders
struct tot_no_orders {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(65534ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trad Ses Status
struct trad_ses_status {
    enum class type : std::uint8_t {
        halted = 1,
        open = 2,
        closed = 3,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(3);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trade Condition
struct trade_condition {
    enum class type : std::uint16_t {
        implied_trade = 1,
        out_of_sequence = 107,
        midpoint_price = 155,
        trading_on_terms_of_issue = 156,
        special_auction = 596,
        trade_at_close = 624,
        retail = 743,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(743);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Hhi Indicator
struct trading_hhi_indicator {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0xFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(100ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Session Id
struct trading_session_id {
    enum class type : std::uint8_t {
        day = 1,
        morning = 3,
        evening = 5,
        after_hours = 6,
        holiday = 7,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(7);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Session Sub Id
struct trading_session_sub_id {
    enum class type : std::uint8_t {
        pre_trading = 1,
        continuous = 3,
        closing = 4,
        post_trading = 5,
        quiescent = 7,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(7);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trans Bkd Time
struct trans_bkd_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
struct transact_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Match Id
struct trd_match_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(4294967294ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Execution Time
struct trd_reg_ts_execution_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Prev Time Priority
struct trd_reg_ts_prev_time_priority {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Reg Ts Time Priority
struct trd_reg_ts_time_priority {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0xFFFFFFFFFFFFFFFFULL);
    static constexpr type minimum = static_cast<type>(0ULL);
    static constexpr type maximum = static_cast<type>(18446744073709551614ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Type
struct trd_type {
    enum class type : std::uint16_t {
        block_trade = 1,
        efp = 2,
        efs = 12,
        otc = 54,
        exchange_basis_facility = 55,
        vola_trade = 1000,
        efp_fin_trade = 1001,
        efp_index_futures_trade = 1002,
        block_trade_at_market = 1004,
        xetra_eurex_enlight_triggered_trade = 1006,
        block_qtpip_trade = 1007,
        delta_trade_at_market = 1017,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535);
    static constexpr type minimum = static_cast<type>(1);
    static constexpr type maximum = static_cast<type>(1017);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Md Trade Entry Grp Comp
struct md_trade_entry_grp_comp {
    static constexpr std::string_view name = "Md Trade Entry Grp Comp";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        md_entry_size,
        md_entry_type,
        pad7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(md_entry_px);
    EOBIFIELD(md_entry_size);
    EOBIFIELD(md_entry_type);
    EOBIFIELD(pad7);
};

static_assert(sizeof(md_trade_entry_grp_comp) == md_trade_entry_grp_comp::size, "md_trade_entry_grp_comp lies over its bytes exactly");

// Trade Reversal
struct trade_reversal {
    static constexpr std::string_view name = "Trade Reversal";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        last_qty,
        last_px,
        trd_reg_ts_execution_time,
        trd_match_id,
        trade_condition,
        md_origin_type,
        no_md_entries,
        md_trade_entry_grp_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
    EOBIFIELD(trd_reg_ts_execution_time);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(trade_condition);
    EOBIFIELD(md_origin_type);
    EOBIFIELD(no_md_entries);
    EOBIFIELD(md_trade_entry_grp_comp);
};

static_assert(sizeof(trade_reversal) == trade_reversal::size, "trade_reversal lies over its bytes exactly");

// Trade Report
struct trade_report {
    static constexpr std::string_view name = "Trade Report";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        last_qty,
        last_px,
        trd_match_id,
        match_type,
        match_sub_type,
        algorithmic_trade_indicator,
        pad1,
        trade_condition,
        pad6>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(match_type);
    EOBIFIELD(match_sub_type);
    EOBIFIELD(algorithmic_trade_indicator);
    EOBIFIELD(pad1);
    EOBIFIELD(trade_condition);
    EOBIFIELD(pad6);
};

static_assert(sizeof(trade_report) == trade_report::size, "trade_report lies over its bytes exactly");

// Top Of Book
struct top_of_book {
    static constexpr std::string_view name = "Top Of Book";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_id,
        bid_px,
        offer_px,
        bid_size,
        offer_size,
        number_of_buy_orders,
        number_of_sell_orders,
        pad4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(bid_px);
    EOBIFIELD(offer_px);
    EOBIFIELD(bid_size);
    EOBIFIELD(offer_size);
    EOBIFIELD(number_of_buy_orders);
    EOBIFIELD(number_of_sell_orders);
    EOBIFIELD(pad4);
};

static_assert(sizeof(top_of_book) == top_of_book::size, "top_of_book lies over its bytes exactly");

// Tes Trade Report
struct tes_trade_report {
    static constexpr std::string_view name = "Tes Trade Report";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        last_qty,
        last_px,
        trd_match_id,
        trd_type,
        trade_condition,
        multi_leg_reporting_type,
        multi_leg_price_model,
        pad6,
        non_disclosed_trade_volume,
        trans_bkd_time,
        number_of_buy_sides,
        number_of_sell_sides,
        pad4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(trd_type);
    EOBIFIELD(trade_condition);
    EOBIFIELD(multi_leg_reporting_type);
    EOBIFIELD(multi_leg_price_model);
    EOBIFIELD(pad6);
    EOBIFIELD(non_disclosed_trade_volume);
    EOBIFIELD(trans_bkd_time);
    EOBIFIELD(number_of_buy_sides);
    EOBIFIELD(number_of_sell_sides);
    EOBIFIELD(pad4);
};

static_assert(sizeof(tes_trade_report) == tes_trade_report::size, "tes_trade_report lies over its bytes exactly");

// Order Details Comp
struct order_details_comp {
    static constexpr std::string_view name = "Order Details Comp";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_time_priority,
        display_qty,
        side,
        ord_type,
        hhi_indicator,
        pad5,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_time_priority);
    EOBIFIELD(display_qty);
    EOBIFIELD(side);
    EOBIFIELD(ord_type);
    EOBIFIELD(hhi_indicator);
    EOBIFIELD(pad5);
    EOBIFIELD(price);
};

static_assert(sizeof(order_details_comp) == order_details_comp::size, "order_details_comp lies over its bytes exactly");

// Snapshot Order
struct snapshot_order {
    static constexpr std::string_view name = "Snapshot Order";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_details_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(order_details_comp);
};

static_assert(sizeof(snapshot_order) == snapshot_order::size, "snapshot_order lies over its bytes exactly");

// Quote Request
struct quote_request {
    static constexpr std::string_view name = "Quote Request";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        last_qty,
        side,
        pad7,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(last_qty);
    EOBIFIELD(side);
    EOBIFIELD(pad7);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(quote_request) == quote_request::size, "quote_request lies over its bytes exactly");

// Product Summary
struct product_summary {
    static constexpr std::string_view name = "Product Summary";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_msg_seq_num_processed,
        trading_session_id,
        trading_session_sub_id,
        trad_ses_status,
        market_condition,
        fast_market_indicator,
        tes_trad_ses_status,
        pad6>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(last_msg_seq_num_processed);
    EOBIFIELD(trading_session_id);
    EOBIFIELD(trading_session_sub_id);
    EOBIFIELD(trad_ses_status);
    EOBIFIELD(market_condition);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(tes_trad_ses_status);
    EOBIFIELD(pad6);
};

static_assert(sizeof(product_summary) == product_summary::size, "product_summary lies over its bytes exactly");

// Product State Change
struct product_state_change {
    static constexpr std::string_view name = "Product State Change";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        trading_session_id,
        trading_session_sub_id,
        trad_ses_status,
        market_condition,
        fast_market_indicator,
        tes_trad_ses_status,
        pad2,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trading_session_id);
    EOBIFIELD(trading_session_sub_id);
    EOBIFIELD(trad_ses_status);
    EOBIFIELD(market_condition);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(tes_trad_ses_status);
    EOBIFIELD(pad2);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(product_state_change) == product_state_change::size, "product_state_change lies over its bytes exactly");

// Partial Order Execution
struct partial_order_execution {
    static constexpr std::string_view name = "Partial Order Execution";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        ord_type,
        algorithmic_trade_indicator,
        hhi_indicator,
        trd_match_id,
        price,
        trd_reg_ts_time_priority,
        security_id,
        last_qty,
        last_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(side);
    EOBIFIELD(ord_type);
    EOBIFIELD(algorithmic_trade_indicator);
    EOBIFIELD(hhi_indicator);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(price);
    EOBIFIELD(trd_reg_ts_time_priority);
    EOBIFIELD(security_id);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
};

static_assert(sizeof(partial_order_execution) == partial_order_execution::size, "partial_order_execution lies over its bytes exactly");

// Order Modify Same Prio
struct order_modify_same_prio {
    static constexpr std::string_view name = "Order Modify Same Prio";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        request_time,
        transact_time,
        prev_display_qty,
        security_id,
        order_details_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(request_time);
    EOBIFIELD(transact_time);
    EOBIFIELD(prev_display_qty);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details_comp);
};

static_assert(sizeof(order_modify_same_prio) == order_modify_same_prio::size, "order_modify_same_prio lies over its bytes exactly");

// Order Modify
struct order_modify {
    static constexpr std::string_view name = "Order Modify";
    static constexpr std::size_t size = 80;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        request_time,
        trd_reg_ts_prev_time_priority,
        prev_price,
        prev_display_qty,
        security_id,
        order_details_comp,
        prev_price_hhi_indicator,
        pad7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(request_time);
    EOBIFIELD(trd_reg_ts_prev_time_priority);
    EOBIFIELD(prev_price);
    EOBIFIELD(prev_display_qty);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details_comp);
    EOBIFIELD(prev_price_hhi_indicator);
    EOBIFIELD(pad7);
};

static_assert(sizeof(order_modify) == order_modify::size, "order_modify lies over its bytes exactly");

// Order Mass Delete
struct order_mass_delete {
    static constexpr std::string_view name = "Order Mass Delete";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(order_mass_delete) == order_mass_delete::size, "order_mass_delete lies over its bytes exactly");

// Order Delete
struct order_delete {
    static constexpr std::string_view name = "Order Delete";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        request_time,
        transact_time,
        security_id,
        order_details_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(request_time);
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details_comp);
};

static_assert(sizeof(order_delete) == order_delete::size, "order_delete lies over its bytes exactly");

// Order Add
struct order_add {
    static constexpr std::string_view name = "Order Add";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        request_time,
        security_id,
        order_details_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(request_time);
    EOBIFIELD(security_id);
    EOBIFIELD(order_details_comp);
};

static_assert(sizeof(order_add) == order_add::size, "order_add lies over its bytes exactly");

// Sec Mass Stat Grp Comp
struct sec_mass_stat_grp_comp {
    static constexpr std::string_view name = "Sec Mass Stat Grp Comp";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        high_px,
        low_px,
        security_status,
        security_trading_status,
        market_condition,
        security_trading_event,
        sold_out_indicator,
        tes_security_status,
        pad2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(high_px);
    EOBIFIELD(low_px);
    EOBIFIELD(security_status);
    EOBIFIELD(security_trading_status);
    EOBIFIELD(market_condition);
    EOBIFIELD(security_trading_event);
    EOBIFIELD(sold_out_indicator);
    EOBIFIELD(tes_security_status);
    EOBIFIELD(pad2);
};

static_assert(sizeof(sec_mass_stat_grp_comp) == sec_mass_stat_grp_comp::size, "sec_mass_stat_grp_comp lies over its bytes exactly");

// Mass Instrument State Change
struct mass_instrument_state_change {
    static constexpr std::string_view name = "Mass Instrument State Change";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        instrument_scope_product_complex,
        security_mass_status,
        security_mass_trading_status,
        mass_market_condition,
        fast_market_indicator,
        security_mass_trading_event,
        mass_sold_out_indicator,
        tes_security_mass_status,
        transact_time,
        last_fragment,
        no_related_sym,
        pad6,
        sec_mass_stat_grp_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(instrument_scope_product_complex);
    EOBIFIELD(security_mass_status);
    EOBIFIELD(security_mass_trading_status);
    EOBIFIELD(mass_market_condition);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(security_mass_trading_event);
    EOBIFIELD(mass_sold_out_indicator);
    EOBIFIELD(tes_security_mass_status);
    EOBIFIELD(transact_time);
    EOBIFIELD(last_fragment);
    EOBIFIELD(no_related_sym);
    EOBIFIELD(pad6);
    EOBIFIELD(sec_mass_stat_grp_comp);
};

static_assert(sizeof(mass_instrument_state_change) == mass_instrument_state_change::size, "mass_instrument_state_change lies over its bytes exactly");

// Md Instrument Entry Grp Comp
struct md_instrument_entry_grp_comp {
    static constexpr std::string_view name = "Md Instrument Entry Grp Comp";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        md_entry_size,
        md_origin_type,
        md_entry_type,
        trade_condition,
        trd_type,
        multi_leg_reporting_type,
        multi_leg_price_model,
        non_disclosed_trade_volume>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(md_entry_px);
    EOBIFIELD(md_entry_size);
    EOBIFIELD(md_origin_type);
    EOBIFIELD(md_entry_type);
    EOBIFIELD(trade_condition);
    EOBIFIELD(trd_type);
    EOBIFIELD(multi_leg_reporting_type);
    EOBIFIELD(multi_leg_price_model);
    EOBIFIELD(non_disclosed_trade_volume);
};

static_assert(sizeof(md_instrument_entry_grp_comp) == md_instrument_entry_grp_comp::size, "md_instrument_entry_grp_comp lies over its bytes exactly");

// Instrument Summary
struct instrument_summary {
    static constexpr std::string_view name = "Instrument Summary";
    static constexpr std::size_t size = 88;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        last_update_time,
        trd_reg_ts_execution_time,
        tot_no_orders,
        security_status,
        security_trading_status,
        market_condition,
        fast_market_indicator,
        security_trading_event,
        sold_out_indicator,
        high_px,
        low_px,
        product_complex,
        no_md_entries,
        tes_security_status,
        pad5,
        md_instrument_entry_grp_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(last_update_time);
    EOBIFIELD(trd_reg_ts_execution_time);
    EOBIFIELD(tot_no_orders);
    EOBIFIELD(security_status);
    EOBIFIELD(security_trading_status);
    EOBIFIELD(market_condition);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(security_trading_event);
    EOBIFIELD(sold_out_indicator);
    EOBIFIELD(high_px);
    EOBIFIELD(low_px);
    EOBIFIELD(product_complex);
    EOBIFIELD(no_md_entries);
    EOBIFIELD(tes_security_status);
    EOBIFIELD(pad5);
    EOBIFIELD(md_instrument_entry_grp_comp);
};

static_assert(sizeof(instrument_summary) == instrument_summary::size, "instrument_summary lies over its bytes exactly");

// Instrument State Change
struct instrument_state_change {
    static constexpr std::string_view name = "Instrument State Change";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        security_status,
        security_trading_status,
        market_condition,
        fast_market_indicator,
        security_trading_event,
        sold_out_indicator,
        pad2,
        high_px,
        low_px,
        transact_time,
        tes_security_status,
        pad7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(security_status);
    EOBIFIELD(security_trading_status);
    EOBIFIELD(market_condition);
    EOBIFIELD(fast_market_indicator);
    EOBIFIELD(security_trading_event);
    EOBIFIELD(sold_out_indicator);
    EOBIFIELD(pad2);
    EOBIFIELD(high_px);
    EOBIFIELD(low_px);
    EOBIFIELD(transact_time);
    EOBIFIELD(tes_security_status);
    EOBIFIELD(pad7);
};

static_assert(sizeof(instrument_state_change) == instrument_state_change::size, "instrument_state_change lies over its bytes exactly");

// Heartbeat
struct heartbeat {
    static constexpr std::string_view name = "Heartbeat";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_msg_seq_num_processed,
        pad4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(last_msg_seq_num_processed);
    EOBIFIELD(pad4);
};

static_assert(sizeof(heartbeat) == heartbeat::size, "heartbeat lies over its bytes exactly");

// Full Order Execution
struct full_order_execution {
    static constexpr std::string_view name = "Full Order Execution";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        ord_type,
        algorithmic_trade_indicator,
        hhi_indicator,
        trd_match_id,
        price,
        trd_reg_ts_time_priority,
        security_id,
        last_qty,
        last_px>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(side);
    EOBIFIELD(ord_type);
    EOBIFIELD(algorithmic_trade_indicator);
    EOBIFIELD(hhi_indicator);
    EOBIFIELD(trd_match_id);
    EOBIFIELD(price);
    EOBIFIELD(trd_reg_ts_time_priority);
    EOBIFIELD(security_id);
    EOBIFIELD(last_qty);
    EOBIFIELD(last_px);
};

static_assert(sizeof(full_order_execution) == full_order_execution::size, "full_order_execution lies over its bytes exactly");

// Remaining Order Details Comp
struct remaining_order_details_comp {
    static constexpr std::string_view name = "Remaining Order Details Comp";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        trd_reg_ts_prev_time_priority,
        display_qty,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(trd_reg_ts_prev_time_priority);
    EOBIFIELD(display_qty);
    EOBIFIELD(price);
};

static_assert(sizeof(remaining_order_details_comp) == remaining_order_details_comp::size, "remaining_order_details_comp lies over its bytes exactly");

// Execution Summary
struct execution_summary {
    static constexpr std::string_view name = "Execution Summary";
    static constexpr std::size_t size = 96;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        request_time,
        exec_id,
        last_qty,
        aggressor_side,
        pad1,
        trade_condition,
        trading_hhi_indicator,
        pad3,
        last_px,
        remaining_order_details_comp,
        resting_hidden_qty,
        resting_cxl_qty,
        aggressor_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(request_time);
    EOBIFIELD(exec_id);
    EOBIFIELD(last_qty);
    EOBIFIELD(aggressor_side);
    EOBIFIELD(pad1);
    EOBIFIELD(trade_condition);
    EOBIFIELD(trading_hhi_indicator);
    EOBIFIELD(pad3);
    EOBIFIELD(last_px);
    EOBIFIELD(remaining_order_details_comp);
    EOBIFIELD(resting_hidden_qty);
    EOBIFIELD(resting_cxl_qty);
    EOBIFIELD(aggressor_time);
};

static_assert(sizeof(execution_summary) == execution_summary::size, "execution_summary lies over its bytes exactly");

// Cross Request
struct cross_request {
    static constexpr std::string_view name = "Cross Request";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        last_px,
        last_qty,
        side,
        cross_request_type,
        input_source,
        pad5,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(last_px);
    EOBIFIELD(last_qty);
    EOBIFIELD(side);
    EOBIFIELD(cross_request_type);
    EOBIFIELD(input_source);
    EOBIFIELD(pad5);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(cross_request) == cross_request::size, "cross_request lies over its bytes exactly");

// Auction Clearing Price
struct auction_clearing_price {
    static constexpr std::string_view name = "Auction Clearing Price";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_id,
        last_px,
        last_qty,
        imbalance_qty,
        security_trading_status,
        potential_security_trading_event,
        pad6>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(last_px);
    EOBIFIELD(last_qty);
    EOBIFIELD(imbalance_qty);
    EOBIFIELD(security_trading_status);
    EOBIFIELD(potential_security_trading_event);
    EOBIFIELD(pad6);
};

static_assert(sizeof(auction_clearing_price) == auction_clearing_price::size, "auction_clearing_price lies over its bytes exactly");

// Auction Bbo
struct auction_bbo {
    static constexpr std::string_view name = "Auction Bbo";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_id,
        bid_px,
        offer_px,
        bid_size,
        offer_size,
        potential_security_trading_event,
        bid_ord_type,
        offer_ord_type,
        pad5>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(transact_time);
    EOBIFIELD(security_id);
    EOBIFIELD(bid_px);
    EOBIFIELD(offer_px);
    EOBIFIELD(bid_size);
    EOBIFIELD(offer_size);
    EOBIFIELD(potential_security_trading_event);
    EOBIFIELD(bid_ord_type);
    EOBIFIELD(offer_ord_type);
    EOBIFIELD(pad5);
};

static_assert(sizeof(auction_bbo) == auction_bbo::size, "auction_bbo lies over its bytes exactly");

// Related Instrument Grp Comp
struct related_instrument_grp_comp {
    static constexpr std::string_view name = "Related Instrument Grp Comp";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        related_security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(related_security_id);
};

static_assert(sizeof(related_instrument_grp_comp) == related_instrument_grp_comp::size, "related_instrument_grp_comp lies over its bytes exactly");

// Add Scaled Simple Instrument
struct add_scaled_simple_instrument {
    static constexpr std::string_view name = "Add Scaled Simple Instrument";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        security_desc,
        security_type,
        pad1,
        quantity_scaling_factor,
        pad4,
        related_instrument_grp_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(security_desc);
    EOBIFIELD(security_type);
    EOBIFIELD(pad1);
    EOBIFIELD(quantity_scaling_factor);
    EOBIFIELD(pad4);
    EOBIFIELD(related_instrument_grp_comp);
};

static_assert(sizeof(add_scaled_simple_instrument) == add_scaled_simple_instrument::size, "add_scaled_simple_instrument lies over its bytes exactly");

// Add Flexible Instrument
struct add_flexible_instrument {
    static constexpr std::string_view name = "Add Flexible Instrument";
    static constexpr std::size_t size = 88;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        security_desc,
        security_type,
        put_or_call,
        exercise_style,
        settl_method,
        maturity_date,
        strike_price,
        opt_attribute,
        contract_date,
        security_reference_data_supplement,
        pad4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(security_desc);
    EOBIFIELD(security_type);
    EOBIFIELD(put_or_call);
    EOBIFIELD(exercise_style);
    EOBIFIELD(settl_method);
    EOBIFIELD(maturity_date);
    EOBIFIELD(strike_price);
    EOBIFIELD(opt_attribute);
    EOBIFIELD(contract_date);
    EOBIFIELD(security_reference_data_supplement);
    EOBIFIELD(pad4);
};

static_assert(sizeof(add_flexible_instrument) == add_flexible_instrument::size, "add_flexible_instrument lies over its bytes exactly");

// Instrmt Leg Grp Comp
struct instrmt_leg_grp_comp {
    static constexpr std::string_view name = "Instrmt Leg Grp Comp";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_symbol,
        pad4,
        leg_security_id,
        leg_price,
        leg_ratio_qty,
        leg_security_type,
        leg_side,
        pad2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(leg_symbol);
    EOBIFIELD(pad4);
    EOBIFIELD(leg_security_id);
    EOBIFIELD(leg_price);
    EOBIFIELD(leg_ratio_qty);
    EOBIFIELD(leg_security_type);
    EOBIFIELD(leg_side);
    EOBIFIELD(pad2);
};

static_assert(sizeof(instrmt_leg_grp_comp) == instrmt_leg_grp_comp::size, "instrmt_leg_grp_comp lies over its bytes exactly");

// Add Complex Instrument
struct add_complex_instrument {
    static constexpr std::string_view name = "Add Complex Instrument";
    static constexpr std::size_t size = 104;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        transact_time,
        security_desc,
        security_sub_type,
        product_complex,
        implied_market_indicator,
        quantity_scaling_factor,
        leg_ratio_multiplier,
        no_legs,
        pad2,
        last_fragment,
        instrmt_leg_grp_comp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(security_id);
    EOBIFIELD(transact_time);
    EOBIFIELD(security_desc);
    EOBIFIELD(security_sub_type);
    EOBIFIELD(product_complex);
    EOBIFIELD(implied_market_indicator);
    EOBIFIELD(quantity_scaling_factor);
    EOBIFIELD(leg_ratio_multiplier);
    EOBIFIELD(no_legs);
    EOBIFIELD(pad2);
    EOBIFIELD(last_fragment);
    EOBIFIELD(instrmt_leg_grp_comp);
};

static_assert(sizeof(add_complex_instrument) == add_complex_instrument::size, "add_complex_instrument lies over its bytes exactly");

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header Comp
struct message_header_comp {
    static constexpr std::string_view name = "Message Header Comp";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        body_len,
        template_id,
        msg_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(body_len);
    EOBIFIELD(template_id);
    EOBIFIELD(msg_seq_num);
};

static_assert(sizeof(message_header_comp) == message_header_comp::size, "message_header_comp lies over its bytes exactly");

// Message: Eurex Eobi Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Eobi Header: EOBI PacketHeader MessageHeaderComp (BodyLen + TemplateID + MsgSeqNum) — first 8 bytes of every Eurex T7 EOBI packet.
struct eobi_header {
    static constexpr std::string_view name = "Eobi Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        body_len,
        template_id,
        msg_seq_num>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(body_len);
    EOBIFIELD(template_id);
    EOBIFIELD(msg_seq_num);
};

static_assert(sizeof(eobi_header) == eobi_header::size, "eobi_header lies over its bytes exactly");

// Packet Header: Eurex Eobi Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        eobi_header,
        appl_seq_num,
        market_segment_id,
        partition_id,
        completion_indicator,
        appl_seq_reset_indicator,
        dscp,
        pad4,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    EOBIFIELD(eobi_header);
    EOBIFIELD(appl_seq_num);
    EOBIFIELD(market_segment_id);
    EOBIFIELD(partition_id);
    EOBIFIELD(completion_indicator);
    EOBIFIELD(appl_seq_reset_indicator);
    EOBIFIELD(dscp);
    EOBIFIELD(pad4);
    EOBIFIELD(transact_time);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: Eurex Eobi Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace eurex::t7::eobi::fbe::v13_0
