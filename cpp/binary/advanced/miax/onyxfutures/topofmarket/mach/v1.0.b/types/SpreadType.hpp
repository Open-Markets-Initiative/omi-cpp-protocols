// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/SpreadType.hpp
#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// spread_type
struct spread_type {

    static constexpr const char* name = "spread_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr spread_type()
     : value{ 0 } {}

    constexpr spread_type(char v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(char v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    char value;
};
}
