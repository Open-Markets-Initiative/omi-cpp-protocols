// Databento.MarketData.Normalized.Dbn.v1: types/Low.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// low
struct low {

    static constexpr const char* name = "low";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::int64_t null_value = 9223372036854775807LL;
    static constexpr int exponent = -9;

    using result_type = std::optional<std::int64_t>;
    using storage_type = result_type;

    constexpr low()
     : value{ null_value } {}

    constexpr low(std::int64_t v)
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
