#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// When Retail Price Improvement (RPI) interest is priced better than the Protected Best Bid or Offer (PBBO) by a minimum of $0.001, an indication of interest on the Bid, Offer, or both the Bid and Offer will identify that interest will be eligible to interact with incoming Retail Order interest.
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
