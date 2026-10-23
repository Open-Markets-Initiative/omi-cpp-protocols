#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Total number of contracts traded for the day.
struct EcrpVolume {

    static constexpr const char* name = "Ecrp Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr EcrpVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EcrpVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of EcrpVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
