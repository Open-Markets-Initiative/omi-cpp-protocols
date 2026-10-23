#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Identifies the Quote Condition associated with the Best Bid Price on a consolidated basis
struct BestBidQuoteCondition {

    static constexpr auto name = "Best Bid Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BestBidQuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestBidQuoteCondition(const char &value)
     : value{ value } {}

    // get value of BestBidQuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
