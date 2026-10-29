#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume of customer orders at the third level
struct ThirdLevelCustomerVolume {

    static constexpr const char* name = "Third Level Customer Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ThirdLevelCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ThirdLevelCustomerVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of ThirdLevelCustomerVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
