#pragma once

#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Option or Equity instrument
struct LegSecurityType {

    static constexpr auto name = "Leg Security Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LegSecurityType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSecurityType(const char &value)
     : value{ value } {}

    // get value of LegSecurityType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
