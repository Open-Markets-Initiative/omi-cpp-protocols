#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Identifies the Quote Condition associated with the Best Offer Price on a consolidated basis
struct BestOfferQuoteCondition {

    static constexpr auto name = "Best Offer Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BestOfferQuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestOfferQuoteCondition(const char &value)
     : value{ value } {}

    // get value of BestOfferQuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
