// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/StockGroup.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// stock_group
struct stock_group {

    static constexpr const char* name = "stock_group";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr std::uint8_t null_value = 0;

    using result_type = std::optional<std::uint8_t>;
    using storage_type = result_type;

    constexpr stock_group()
     : value{ null_value } {}

    constexpr stock_group(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint8_t value;
};
}
