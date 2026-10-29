#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Total quantity of customer orders at the Bid price
struct BidCustomerVolume {

    static constexpr const char* name = "Bid Customer Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidCustomerVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of BidCustomerVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
