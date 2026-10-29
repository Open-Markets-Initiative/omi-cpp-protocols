#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume at Third price level
struct ThirdVolume {

    static constexpr const char* name = "Third Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ThirdVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ThirdVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of ThirdVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
