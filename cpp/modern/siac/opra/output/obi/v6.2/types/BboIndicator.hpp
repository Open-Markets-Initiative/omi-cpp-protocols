#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Indicates the effect the new quote has on the Best Bid and/or the Best Offer.
struct BboIndicator {

    static constexpr auto name = "Bbo Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BboIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BboIndicator(const char &value)
     : value{ value } {}

    // get value of BboIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
