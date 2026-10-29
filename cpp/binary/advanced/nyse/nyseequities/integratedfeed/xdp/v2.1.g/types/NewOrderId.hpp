#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// new_order_id
struct new_order_id {

    static constexpr const char* name = "new_order_id";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr new_order_id()
     : value{ 0 } {}

    constexpr new_order_id(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
