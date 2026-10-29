#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

// original_trade_id
struct original_trade_id {

    static constexpr const char* name = "original_trade_id";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr original_trade_id()
     : value{ 0 } {}

    constexpr original_trade_id(std::uint32_t v)
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
