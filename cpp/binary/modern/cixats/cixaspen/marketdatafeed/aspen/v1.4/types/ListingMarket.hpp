#pragma once

#include <cstddef>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Code identifying the primary listing market
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
