#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Total number of block and derived contracts traded for the day.
struct BlockVolume {

    static constexpr const char* name = "Block Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BlockVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of BlockVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
