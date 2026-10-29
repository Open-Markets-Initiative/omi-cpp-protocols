#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume of customer orders at the first level
struct FirstLevelCustomerVolume {

    static constexpr const char* name = "First Level Customer Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr FirstLevelCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirstLevelCustomerVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of FirstLevelCustomerVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
