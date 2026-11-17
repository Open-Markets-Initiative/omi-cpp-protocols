// Databento.MarketData.Normalized.Dbn.v2: types/SignificantImbalance.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v2 {


// Venue-specific character code; for Nasdaq, contains the raw Price Variation Indicator
struct SignificantImbalance {

    static constexpr auto name = "Significant Imbalance";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SignificantImbalance()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SignificantImbalance(const char &value)
     : value{ value } {}

    // get value of SignificantImbalance field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
