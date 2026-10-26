#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// For Pillar-powered markets, the price at which all eligible auction-only interest would trade, subject to auction collars For NYSE, the price closest to the reference price where the imbalance of closing-only interest is 0. If a closing-only clearing price is not reached, it is defaulted to 0.
struct AuctionInterestClearingPrice {

    static constexpr const char* name = "Auction Interest Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AuctionInterestClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionInterestClearingPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of AuctionInterestClearingPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
