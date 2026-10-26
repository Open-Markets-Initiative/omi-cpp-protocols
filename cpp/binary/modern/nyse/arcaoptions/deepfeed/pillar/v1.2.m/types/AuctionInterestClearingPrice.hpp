#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The price at which all eligible auction-only interest would trade, subject to auction collars.
struct AuctionInterestClearingPrice {

    static constexpr const char* name = "Auction Interest Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr AuctionInterestClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionInterestClearingPrice(const std::int32_t value)
     : value{ value } {}

    // get value of AuctionInterestClearingPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
