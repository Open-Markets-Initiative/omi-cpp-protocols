#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// leg_ratio_qty
struct leg_ratio_qty {

    static constexpr const char* name = "leg_ratio_qty";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::int32_t null_value = -2147483648;

    using result_type = std::optional<std::int32_t>;
    using storage_type = result_type;

    constexpr leg_ratio_qty()
     : value{ 0 } {}

    constexpr leg_ratio_qty(std::int32_t v)
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
