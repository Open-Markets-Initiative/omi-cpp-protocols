#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// reference_price
struct reference_price {

    static constexpr const char* name = "reference_price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -4;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr reference_price()
     : value{ 0 } {}

    constexpr reference_price(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
