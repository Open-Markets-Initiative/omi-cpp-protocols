#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Number of whole seconds from midnight Central Time.
struct TimeReference {

    static constexpr const char* name = "Time Reference";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TimeReference()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeReference(const std::uint32_t value)
     : value{ value } {}

    // get value of TimeReference field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
