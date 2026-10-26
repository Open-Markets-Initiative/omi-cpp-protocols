#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// The Bed Bid Denominator Code field indicates the position of the floating decimal point within the Best Bid Price field.
struct BestBidDenominatorCode {

    static constexpr auto name = "Best Bid Denominator Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BestBidDenominatorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestBidDenominatorCode(const char &value)
     : value{ value } {}

    // get value of BestBidDenominatorCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
