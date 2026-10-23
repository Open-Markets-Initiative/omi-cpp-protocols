#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// lowest_trade
struct lowest_trade {

    static constexpr const char* name = "lowest_trade";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -2;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr lowest_trade()
     : value{ 0 } {}

    lowest_trade(std::int64_t v)
     : value{ static_cast<std::int64_t>(__builtin_bswap64(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::int64_t>(__builtin_bswap64(value))};
    }

    void set(std::int64_t v) {
        value = __builtin_bswap64(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
