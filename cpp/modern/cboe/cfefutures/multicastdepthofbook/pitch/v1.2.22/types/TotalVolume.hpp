#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Total number of contracts traded for the day, including block and ECRP trades.
struct TotalVolume {

    static constexpr const char* name = "Total Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of TotalVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
