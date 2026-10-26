#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// payments_per_year
struct payments_per_year {

    static constexpr const char* name = "payments_per_year";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint8_t>;
    using storage_type = result_type;

    constexpr payments_per_year()
     : value{ 0 } {}

    constexpr payments_per_year(std::uint8_t v)
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
