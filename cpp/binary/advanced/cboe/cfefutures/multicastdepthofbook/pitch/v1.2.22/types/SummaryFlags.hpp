#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// summary_flags
struct summary_flags {

    using type = uint8_t;

    static constexpr type high_price_valid = type{1} << 0;
    static constexpr type high_price_is_bid = type{1} << 1;
    static constexpr type low_price_valid = type{1} << 2;
    static constexpr type low_price_is_offer = type{1} << 3;
    static constexpr type open_close_valid = type{1} << 4;

    static constexpr const char* name = "summary_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr summary_flags()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint8_t v) {
        value = v;
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(v.value());
        else
            set(type{0});
    }

    [[nodiscard]] constexpr bool has(type bit) const { return (value & bit) != 0; }
    constexpr void set(type bit, bool enabled) { if (enabled) value |= bit; else value &= static_cast<type>(~bit); }

    [[nodiscard]] constexpr bool has_high_price_valid() const { return has(high_price_valid); }
    [[nodiscard]] constexpr bool has_high_price_is_bid() const { return has(high_price_is_bid); }
    [[nodiscard]] constexpr bool has_low_price_valid() const { return has(low_price_valid); }
    [[nodiscard]] constexpr bool has_low_price_is_offer() const { return has(low_price_is_offer); }
    [[nodiscard]] constexpr bool has_open_close_valid() const { return has(open_close_valid); }

    constexpr void set_high_price_valid(bool v) { set(high_price_valid, v); }
    constexpr void set_high_price_is_bid(bool v) { set(high_price_is_bid, v); }
    constexpr void set_low_price_valid(bool v) { set(low_price_valid, v); }
    constexpr void set_low_price_is_offer(bool v) { set(low_price_is_offer, v); }
    constexpr void set_open_close_valid(bool v) { set(open_close_valid, v); }

  protected:
    type value;
};
}
