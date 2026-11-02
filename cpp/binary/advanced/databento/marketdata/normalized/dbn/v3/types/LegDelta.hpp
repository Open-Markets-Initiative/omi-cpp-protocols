#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// leg_delta
struct leg_delta {

    static constexpr const char* name = "leg_delta";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::int64_t null_value = 9223372036854775807LL;
    static constexpr int exponent = -9;

    using result_type = std::optional<std::int64_t>;
    using storage_type = result_type;

    constexpr leg_delta()
     : value{ null_value } {}

    constexpr leg_delta(std::int64_t v)
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
