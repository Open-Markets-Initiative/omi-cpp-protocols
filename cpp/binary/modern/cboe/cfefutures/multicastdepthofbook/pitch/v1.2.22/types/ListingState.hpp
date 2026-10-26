#pragma once

#include <cstddef>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Listing State Values
struct ListingState {

    static constexpr auto name = "Listing State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ListingState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ListingState(const char &value)
     : value{ value } {}

    // get value of ListingState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
