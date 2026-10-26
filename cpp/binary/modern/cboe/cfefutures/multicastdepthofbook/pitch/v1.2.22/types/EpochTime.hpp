#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Number of whole seconds since the Epoch (Midnight January 1, 1970 UTC).
struct EpochTime {

    static constexpr const char* name = "Epoch Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr EpochTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EpochTime(const std::uint32_t value)
     : value{ value } {}

    // get value of EpochTime field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
