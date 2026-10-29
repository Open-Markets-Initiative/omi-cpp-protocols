#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// prev_close_volume
struct prev_close_volume {

    static constexpr const char* name = "prev_close_volume";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr prev_close_volume()
     : value{ 0 } {}

    constexpr prev_close_volume(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
