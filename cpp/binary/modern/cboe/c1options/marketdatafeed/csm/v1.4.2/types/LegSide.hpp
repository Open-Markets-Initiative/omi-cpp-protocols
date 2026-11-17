// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/LegSide.hpp
#pragma once

#include <cstddef>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct LegSide {

    static constexpr auto name = "Leg Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LegSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSide(const char &value)
     : value{ value } {}

    // get value of LegSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
