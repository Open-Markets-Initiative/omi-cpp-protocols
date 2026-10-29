#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {


// The side of the TotalImbalanceQty
struct ImbalanceSide {

    static constexpr auto name = "Imbalance Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ImbalanceSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImbalanceSide(const char &value)
     : value{ value } {}

    // get value of ImbalanceSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
