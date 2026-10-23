#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// dynamic_circuit_breaker_tolerances
struct dynamic_circuit_breaker_tolerances {

    static constexpr const char* name = "dynamic_circuit_breaker_tolerances";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -8;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr dynamic_circuit_breaker_tolerances()
     : value{ 0 } {}

    constexpr dynamic_circuit_breaker_tolerances(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
