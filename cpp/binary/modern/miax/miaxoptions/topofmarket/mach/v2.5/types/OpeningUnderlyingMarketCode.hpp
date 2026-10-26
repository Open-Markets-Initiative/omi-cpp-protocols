#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Options opening will be triggered on receipt of Opening quote/trade from this Underlying market
struct OpeningUnderlyingMarketCode {

    static constexpr auto name = "Opening Underlying Market Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpeningUnderlyingMarketCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpeningUnderlyingMarketCode(const char &value)
     : value{ value } {}

    // get value of OpeningUnderlyingMarketCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
