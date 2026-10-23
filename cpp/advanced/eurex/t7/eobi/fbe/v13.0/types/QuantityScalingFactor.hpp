#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// quantity_scaling_factor
struct quantity_scaling_factor {

    static constexpr const char* name = "quantity_scaling_factor";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = true;
    static constexpr std::uint16_t null_value = 0xFFFF;

    using result_type = std::optional<std::uint16_t>;
    using storage_type = result_type;

    constexpr quantity_scaling_factor()
     : value{ 0 } {}

    constexpr quantity_scaling_factor(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint16_t v) {
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
    std::uint16_t value;
};
}
