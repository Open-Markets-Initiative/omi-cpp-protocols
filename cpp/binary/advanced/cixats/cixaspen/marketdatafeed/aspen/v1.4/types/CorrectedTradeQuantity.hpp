#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// corrected_trade_quantity
struct corrected_trade_quantity {

    static constexpr const char* name = "corrected_trade_quantity";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -6;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr corrected_trade_quantity()
     : value{ 0 } {}

    constexpr corrected_trade_quantity(std::uint64_t v)
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
