// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/LegRatioAndSide.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// leg_ratio_and_side
struct leg_ratio_and_side {

    static constexpr const char* name = "leg_ratio_and_side";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr leg_ratio_and_side()
     : value{ 0 } {}

    constexpr leg_ratio_and_side(std::int32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int32_t value;
};
}
