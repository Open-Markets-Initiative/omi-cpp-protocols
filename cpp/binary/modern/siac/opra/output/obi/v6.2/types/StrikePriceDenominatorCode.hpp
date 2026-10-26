#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// The Strike Price Denominator Code field indicates the position of the floating decimal point within the Strike Price field.
struct StrikePriceDenominatorCode {

    static constexpr auto name = "Strike Price Denominator Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr StrikePriceDenominatorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceDenominatorCode(const char &value)
     : value{ value } {}

    // get value of StrikePriceDenominatorCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
