#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Auction ID for CUBE/COA
struct AuctionId {

    static constexpr const char* name = "Auction Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AuctionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionId(const std::uint64_t value)
     : value{ value } {}

    // get value of AuctionId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
