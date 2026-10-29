#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Trading Collar Variation Type
struct TradingCollarVariationType {

    static constexpr auto name = "Trading Collar Variation Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradingCollarVariationType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingCollarVariationType(const char &value)
     : value{ value } {}

    // get value of TradingCollarVariationType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
