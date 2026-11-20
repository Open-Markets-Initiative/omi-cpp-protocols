// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0: types/NavOffsetAmountOpen.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// nav_offset_amount_open
struct nav_offset_amount_open {

    static constexpr const char* name = "nav_offset_amount_open";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -4;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr nav_offset_amount_open()
     : value{ 0 } {}

    nav_offset_amount_open(std::int32_t v)
     : value{ static_cast<std::int32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::int32_t>(__builtin_bswap32(value))};
    }

    void set(std::int32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int32_t value;
};
}
