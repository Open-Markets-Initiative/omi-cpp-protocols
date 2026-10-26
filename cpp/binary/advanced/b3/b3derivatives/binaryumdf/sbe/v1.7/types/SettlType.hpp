#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// settl_type
struct settl_type {

    static constexpr const char* name = "settl_type";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = true;
    static constexpr std::uint16_t null_value = 65535;

    using result_type = std::optional<std::uint16_t>;
    using storage_type = result_type;

    constexpr settl_type()
     : value{ 0 } {}

    constexpr settl_type(std::uint16_t v)
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
