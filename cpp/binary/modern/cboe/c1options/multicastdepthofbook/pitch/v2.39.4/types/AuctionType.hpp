#pragma once

#include <cstddef>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


// Auction type value
struct AuctionType {

    static constexpr auto name = "Auction Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AuctionType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionType(const char &value)
     : value{ value } {}

    // get value of AuctionType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
