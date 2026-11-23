// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/ListingMarket.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// The Market On Which A Security Is Listed
struct ListingMarket {

    static constexpr auto name = "Listing Market";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ListingMarket()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ListingMarket(const char &value)
     : value{ value } {}

    // get value of ListingMarket field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
