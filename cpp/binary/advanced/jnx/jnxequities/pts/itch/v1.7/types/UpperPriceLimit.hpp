#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// upper_price_limit
struct upper_price_limit {

    static constexpr const char* name = "upper_price_limit";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -1;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr upper_price_limit()
     : value{ 0 } {}

    upper_price_limit(std::uint32_t v)
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
