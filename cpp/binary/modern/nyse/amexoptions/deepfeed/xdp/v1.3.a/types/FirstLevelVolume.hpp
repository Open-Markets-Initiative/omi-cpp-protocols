#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume at first price level
struct FirstLevelVolume {

    static constexpr const char* name = "First Level Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr FirstLevelVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirstLevelVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of FirstLevelVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
