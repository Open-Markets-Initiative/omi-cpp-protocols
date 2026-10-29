#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Total volume at third price level
struct ThirdLevelVolume {

    static constexpr const char* name = "Third Level Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ThirdLevelVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ThirdLevelVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of ThirdLevelVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
