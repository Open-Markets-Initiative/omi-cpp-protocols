#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// canceled_short_quantity
struct canceled_short_quantity {

    static constexpr const char* name = "canceled_short_quantity";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr canceled_short_quantity()
     : value{ 0 } {}

    constexpr canceled_short_quantity(std::uint16_t v)
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
