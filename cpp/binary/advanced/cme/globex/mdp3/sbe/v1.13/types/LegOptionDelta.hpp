#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// leg_option_delta
struct leg_option_delta {

    static constexpr const char* name = "leg_option_delta";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::int32_t null_value = 2147483647;
    static constexpr int exponent = -4;

    using result_type = std::optional<std::int32_t>;
    using storage_type = result_type;

    constexpr leg_option_delta()
     : value{ 0 } {}

    constexpr leg_option_delta(std::int32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::int32_t v) {
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
    std::int32_t value;
};
}
