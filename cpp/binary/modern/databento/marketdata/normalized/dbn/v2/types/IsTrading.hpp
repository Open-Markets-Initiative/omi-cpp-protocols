// Databento.MarketData.Normalized.Dbn.v2: types/IsTrading.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v2 {


// The state of trading in the instrument
struct IsTrading {

    static constexpr auto name = "Is Trading";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IsTrading()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsTrading(const char &value)
     : value{ value } {}

    // get value of IsTrading field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
