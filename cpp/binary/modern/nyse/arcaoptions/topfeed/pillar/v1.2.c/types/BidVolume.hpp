#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Total quantity available at the above Bid price.
struct BidVolume {

    static constexpr const char* name = "Bid Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of BidVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
