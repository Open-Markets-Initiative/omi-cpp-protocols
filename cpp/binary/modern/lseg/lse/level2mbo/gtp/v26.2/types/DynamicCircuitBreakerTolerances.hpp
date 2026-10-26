#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Dynamic Circuit Breaker Tolerance (%) of the instrument.
struct DynamicCircuitBreakerTolerances {

    static constexpr const char* name = "Dynamic Circuit Breaker Tolerances";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr DynamicCircuitBreakerTolerances()
     : value{ 0 } {}

    // constructor for DynamicCircuitBreakerTolerances field
    constexpr explicit DynamicCircuitBreakerTolerances(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of DynamicCircuitBreakerTolerances field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of DynamicCircuitBreakerTolerances field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
