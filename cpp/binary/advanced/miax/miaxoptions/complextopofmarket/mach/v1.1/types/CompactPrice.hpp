// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/CompactPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// compact_price
struct compact_price {

    static constexpr const char* name = "compact_price";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -2;

    using result_type = required<std::int16_t>;
    using storage_type = result_type;

    constexpr compact_price()
     : value{ 0 } {}

    constexpr compact_price(std::int16_t v)
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
