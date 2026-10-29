#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_10 {


// Identifies the daily established drop level value associated with decline Level 1: 7% of Previous Close SP 500 Value
struct MarketWideCircuitBreakerLevelIndicator {

    static constexpr auto name = "Market Wide Circuit Breaker Level Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketWideCircuitBreakerLevelIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketWideCircuitBreakerLevelIndicator(const char &value)
     : value{ value } {}

    // get value of MarketWideCircuitBreakerLevelIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
