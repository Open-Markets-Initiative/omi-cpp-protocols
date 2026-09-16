#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// lower_price_range_collar
struct lower_price_range_collar {

    static constexpr const char* name = "lower_price_range_collar";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -4;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr lower_price_range_collar()
     : value{ 0 } {}

    lower_price_range_collar(std::uint32_t v)
     : value{ static_cast<std::uint32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint32_t>(__builtin_bswap32(value))};
    }

    void set(std::uint32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
