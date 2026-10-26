#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// md_price_level
struct md_price_level {

    static constexpr const char* name = "md_price_level";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint8_t>;
    using storage_type = result_type;

    constexpr md_price_level()
     : value{ 0 } {}

    constexpr md_price_level(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint8_t value;
};
}
