#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Identifies Retail Price Improvement interest priced better than the Protected Best Bid or Offer by a minimum of $0.001
struct RetailInterestIndicator {

    static constexpr auto name = "Retail Interest Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RetailInterestIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RetailInterestIndicator(const char &value)
     : value{ value } {}

    // get value of RetailInterestIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
