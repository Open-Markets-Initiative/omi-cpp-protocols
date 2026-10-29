#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// trade_volume_short
struct trade_volume_short {

    static constexpr const char* name = "trade_volume_short";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr trade_volume_short()
     : value{ 0 } {}

    trade_volume_short(std::uint16_t v)
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
