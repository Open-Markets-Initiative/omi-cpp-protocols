#pragma once

#include <cstddef>

namespace iex::iexequities::deep::snap::v1_6 {


// Side of the unpaired shares at the Reference Price using orders on the Auction Book
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
