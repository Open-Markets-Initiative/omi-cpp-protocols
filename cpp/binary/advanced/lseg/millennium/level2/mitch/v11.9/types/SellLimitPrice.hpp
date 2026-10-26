#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// sell_limit_price
struct sell_limit_price {

    static constexpr const char* name = "sell_limit_price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr sell_limit_price()
     : value{ 0 } {}

    constexpr sell_limit_price(std::int64_t v)
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
