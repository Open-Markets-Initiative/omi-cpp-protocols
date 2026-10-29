#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// underlying_px_exponent
struct underlying_px_exponent {

    static constexpr const char* name = "underlying_px_exponent";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::int8_t>;
    using storage_type = result_type;

    constexpr underlying_px_exponent()
     : value{ 0 } {}

    constexpr underlying_px_exponent(std::int8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int8_t value;
};
}
