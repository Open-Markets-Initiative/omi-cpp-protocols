#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Total quantity available at the above Bid price.
struct BidVolume {

    static constexpr const char* name = "Bid Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of BidVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
