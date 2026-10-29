#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// Projected Auction Time (hhmm)
struct AuctionTime {

    static constexpr const char* name = "Auction Time";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr AuctionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionTime(const std::uint16_t value)
     : value{ value } {}

    // get value of AuctionTime field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
