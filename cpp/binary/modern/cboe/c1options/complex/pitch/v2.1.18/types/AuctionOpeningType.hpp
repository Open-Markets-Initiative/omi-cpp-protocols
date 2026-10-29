#pragma once

#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Auction Opening Type
struct AuctionOpeningType {

    static constexpr auto name = "Auction Opening Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AuctionOpeningType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionOpeningType(const char &value)
     : value{ value } {}

    // get value of AuctionOpeningType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
