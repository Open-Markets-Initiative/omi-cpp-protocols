#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume at First price level
struct FirstVolume {

    static constexpr const char* name = "First Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr FirstVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirstVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of FirstVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
