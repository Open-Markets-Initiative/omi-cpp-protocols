// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/UnitOfMeasureQuantity.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// unit_of_measure_quantity
struct unit_of_measure_quantity {

    static constexpr const char* name = "unit_of_measure_quantity";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr unit_of_measure_quantity()
     : value{ 0 } {}

    constexpr unit_of_measure_quantity(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
