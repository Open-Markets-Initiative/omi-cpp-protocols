// Databento.MarketData.Normalized.Dbn.v3: types/IsQuoting.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v3 {


// The state of quoting in the instrument
struct IsQuoting {

    static constexpr auto name = "Is Quoting";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IsQuoting()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsQuoting(const char &value)
     : value{ value } {}

    // get value of IsQuoting field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
