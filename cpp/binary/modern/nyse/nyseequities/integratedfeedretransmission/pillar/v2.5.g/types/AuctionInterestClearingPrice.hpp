#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// The price at which auction only interest would trade.
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
