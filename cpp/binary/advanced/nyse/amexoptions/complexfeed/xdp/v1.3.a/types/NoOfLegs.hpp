#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// no_of_legs
struct no_of_legs {

    static constexpr const char* name = "no_of_legs";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr no_of_legs()
     : value{ 0 } {}

    constexpr no_of_legs(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
