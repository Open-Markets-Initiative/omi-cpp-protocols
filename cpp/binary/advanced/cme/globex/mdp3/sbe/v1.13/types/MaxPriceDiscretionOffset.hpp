#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// max_price_discretion_offset
struct max_price_discretion_offset {

    static constexpr const char* name = "max_price_discretion_offset";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -9;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr max_price_discretion_offset()
     : value{ 0 } {}

    constexpr max_price_discretion_offset(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
