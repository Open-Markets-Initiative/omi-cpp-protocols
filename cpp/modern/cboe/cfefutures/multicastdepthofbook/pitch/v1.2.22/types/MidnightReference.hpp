#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Midnight Central Time reference time for subsequent Time messages, expressed as number of whole seconds since the Epoch (Midnight January 1, 1970 UTC).
struct MidnightReference {

    static constexpr const char* name = "Midnight Reference";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MidnightReference()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MidnightReference(const std::uint32_t value)
     : value{ value } {}

    // get value of MidnightReference field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
