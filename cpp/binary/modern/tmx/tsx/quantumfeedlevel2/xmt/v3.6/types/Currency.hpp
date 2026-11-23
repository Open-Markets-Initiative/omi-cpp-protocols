// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/Currency.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// The Currency Associated With A Reported Price
struct Currency {

    static constexpr auto name = "Currency";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Currency()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Currency(const char &value)
     : value{ value } {}

    // get value of Currency field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
