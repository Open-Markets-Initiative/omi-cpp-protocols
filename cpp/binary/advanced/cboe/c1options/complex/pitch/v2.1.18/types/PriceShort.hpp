#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// price_short
struct price_short {

    static constexpr const char* name = "price_short";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -2;

    using result_type = required<std::int16_t>;
    using storage_type = result_type;

    constexpr price_short()
     : value{ 0 } {}

    constexpr price_short(std::int16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int16_t value;
};
}
