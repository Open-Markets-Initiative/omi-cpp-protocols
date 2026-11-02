#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The bid size
struct BidSz {

    static constexpr const char* name = "Bid Sz";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidSz()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSz(const std::uint32_t value)
     : value{ value } {}

    // get value of BidSz field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
