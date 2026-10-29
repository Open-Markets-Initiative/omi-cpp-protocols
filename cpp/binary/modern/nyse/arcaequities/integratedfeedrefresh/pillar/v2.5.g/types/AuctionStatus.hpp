#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {


// Indicates whether the auction will run.
struct AuctionStatus {

    static constexpr auto name = "Auction Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AuctionStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of AuctionStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
