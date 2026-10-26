#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// index_pct
struct index_pct {

    static constexpr const char* name = "index_pct";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::int64_t null_value = 0LL;
    static constexpr int exponent = -9;

    using result_type = std::optional<std::int64_t>;
    using storage_type = result_type;

    constexpr index_pct()
     : value{ 0 } {}

    constexpr index_pct(std::int64_t v)
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
