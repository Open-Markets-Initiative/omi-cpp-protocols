#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume at second price level
struct SecondLevelVolume {

    static constexpr const char* name = "Second Level Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SecondLevelVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondLevelVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of SecondLevelVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
