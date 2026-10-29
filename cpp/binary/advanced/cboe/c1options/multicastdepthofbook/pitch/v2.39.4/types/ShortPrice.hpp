#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// short_price
struct short_price {

    static constexpr const char* name = "short_price";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -2;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr short_price()
     : value{ 0 } {}

    constexpr short_price(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
