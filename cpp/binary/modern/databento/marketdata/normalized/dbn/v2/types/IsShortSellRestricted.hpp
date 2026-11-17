// Databento.MarketData.Normalized.Dbn.v2: types/IsShortSellRestricted.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v2 {


// The state of short sell restrictions for the instrument
struct IsShortSellRestricted {

    static constexpr auto name = "Is Short Sell Restricted";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IsShortSellRestricted()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsShortSellRestricted(const char &value)
     : value{ value } {}

    // get value of IsShortSellRestricted field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
