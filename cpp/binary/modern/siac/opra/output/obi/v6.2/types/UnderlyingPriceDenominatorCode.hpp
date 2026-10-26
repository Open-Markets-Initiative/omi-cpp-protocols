#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// The Underlying Price Denominator Code field indicates the position of the floating decimal point within the Underlying Price field.
struct UnderlyingPriceDenominatorCode {

    static constexpr auto name = "Underlying Price Denominator Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr UnderlyingPriceDenominatorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingPriceDenominatorCode(const char &value)
     : value{ value } {}

    // get value of UnderlyingPriceDenominatorCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
