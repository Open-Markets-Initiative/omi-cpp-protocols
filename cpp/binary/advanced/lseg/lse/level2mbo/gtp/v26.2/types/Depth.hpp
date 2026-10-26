#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// depth
struct depth {

    static constexpr const char* name = "depth";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint8_t>;
    using storage_type = result_type;

    constexpr depth()
     : value{ 0 } {}

    constexpr depth(std::uint8_t v)
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
