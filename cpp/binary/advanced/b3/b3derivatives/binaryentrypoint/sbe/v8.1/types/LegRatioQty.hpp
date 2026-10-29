#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// leg_ratio_qty
struct leg_ratio_qty {

    static constexpr const char* name = "leg_ratio_qty";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -7;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr leg_ratio_qty()
     : value{ 0 } {}

    constexpr leg_ratio_qty(std::int64_t v)
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
