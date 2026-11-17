// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: types/BuildNumber.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// build_number
struct build_number {

    static constexpr const char* name = "build_number";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr std::uint8_t null_value = 255;

    using result_type = std::optional<std::uint8_t>;
    using storage_type = result_type;

    constexpr build_number()
     : value{ null_value } {}

    constexpr build_number(std::uint8_t v)
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
