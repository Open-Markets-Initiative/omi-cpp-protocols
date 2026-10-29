#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume of customer orders at the second level
struct SecondLevelCustomerVolume {

    static constexpr const char* name = "Second Level Customer Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SecondLevelCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondLevelCustomerVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of SecondLevelCustomerVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
