// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/SecurityExchange.hpp
#pragma once

#include <cstddef>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct SecurityExchange {

    static constexpr auto name = "Security Exchange";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityExchange()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityExchange(const char &value)
     : value{ value } {}

    // get value of SecurityExchange field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
