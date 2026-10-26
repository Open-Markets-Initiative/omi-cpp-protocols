#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// bid_price_short
struct bid_price_short {

    static constexpr const char* name = "bid_price_short";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -2;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr bid_price_short()
     : value{ 0 } {}

    bid_price_short(std::uint16_t v)
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
