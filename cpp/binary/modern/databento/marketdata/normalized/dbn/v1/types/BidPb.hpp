#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The publisher ID indicating the venue containing the best bid
struct BidPb {

    static constexpr const char* name = "Bid Pb";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidPb()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidPb(const std::uint16_t value)
     : value{ value } {}

    // get value of BidPb field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
