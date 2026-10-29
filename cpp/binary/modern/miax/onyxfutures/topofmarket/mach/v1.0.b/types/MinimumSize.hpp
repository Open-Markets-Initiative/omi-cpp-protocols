#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Minimum Order Size
struct MinimumSize {

    static constexpr const char* name = "Minimum Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MinimumSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumSize(const std::uint32_t value)
     : value{ value } {}

    // get value of MinimumSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
