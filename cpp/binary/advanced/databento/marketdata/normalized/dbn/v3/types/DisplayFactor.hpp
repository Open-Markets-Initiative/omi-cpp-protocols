// Databento.MarketData.Normalized.Dbn.v3: types/DisplayFactor.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// display_factor
struct display_factor {

    static constexpr const char* name = "display_factor";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::int64_t null_value = 9223372036854775807LL;
    static constexpr int exponent = -9;

    using result_type = std::optional<std::int64_t>;
    using storage_type = result_type;

    constexpr display_factor()
     : value{ null_value } {}

    constexpr display_factor(std::int64_t v)
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
