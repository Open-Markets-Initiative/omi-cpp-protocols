#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// min_price_increment
struct min_price_increment {

    static constexpr const char* name = "min_price_increment";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -7;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr min_price_increment()
     : value{ 0 } {}

    constexpr min_price_increment(std::int64_t v)
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
