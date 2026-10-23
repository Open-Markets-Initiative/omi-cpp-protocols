#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// contract_multiplier_unit
struct contract_multiplier_unit {

    static constexpr const char* name = "contract_multiplier_unit";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr std::int8_t null_value = 127;

    using result_type = std::optional<std::int8_t>;
    using storage_type = result_type;

    constexpr contract_multiplier_unit()
     : value{ 0 } {}

    constexpr contract_multiplier_unit(std::int8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::int8_t v) {
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
    std::int8_t value;
};
}
