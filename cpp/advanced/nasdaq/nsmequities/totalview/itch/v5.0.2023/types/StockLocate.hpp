#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// stock_locate
struct stock_locate {

    static constexpr const char* name = "stock_locate";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr stock_locate()
     : value{ 0 } {}

    stock_locate(std::uint16_t v)
     : value{ static_cast<std::uint16_t>(__builtin_bswap16(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint16_t>(__builtin_bswap16(value))};
    }

    void set(std::uint16_t v) {
        value = __builtin_bswap16(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
