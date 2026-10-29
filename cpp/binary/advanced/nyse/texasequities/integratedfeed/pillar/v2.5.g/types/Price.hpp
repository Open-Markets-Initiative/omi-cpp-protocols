#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// price
struct price {

    static constexpr const char* name = "price";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr price()
     : value{ 0 } {}

    constexpr price(std::int32_t v)
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
