#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Identifies the market condition of a quote for a security.
struct MarketCondition {

    static constexpr auto name = "Market Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketCondition(const char &value)
     : value{ value } {}

    // get value of MarketCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
