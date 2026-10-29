#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Total quantity of ‘Customer’ orders available at the above Bid price.
struct BidCustomerVolume {

    static constexpr const char* name = "Bid Customer Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidCustomerVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of BidCustomerVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
