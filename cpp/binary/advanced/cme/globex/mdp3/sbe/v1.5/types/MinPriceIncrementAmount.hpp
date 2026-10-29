#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace cme::mdp3::v5 {

// min_price_increment_amount
struct min_price_increment_amount {

    static constexpr const char* name = "min_price_increment_amount";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::int64_t null_value = 9223372036854775807LL;
    static constexpr int exponent = -7;

    using result_type = std::optional<std::int64_t>;
    using storage_type = result_type;

    constexpr min_price_increment_amount()
     : value{ 0 } {}

    constexpr min_price_increment_amount(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::int64_t v) {
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
    std::int64_t value;
};
}
