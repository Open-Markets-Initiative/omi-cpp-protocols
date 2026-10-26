#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// The Bed OFFER Denominator Code field indicates the position of the floating decimal point within the Best Offer Price field.
struct BestOfferDenominatorCode {

    static constexpr auto name = "Best Offer Denominator Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BestOfferDenominatorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestOfferDenominatorCode(const char &value)
     : value{ value } {}

    // get value of BestOfferDenominatorCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
