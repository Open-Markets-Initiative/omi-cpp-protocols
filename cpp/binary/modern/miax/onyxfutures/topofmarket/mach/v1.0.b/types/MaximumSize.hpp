#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Maximum Order Size
struct MaximumSize {

    static constexpr const char* name = "Maximum Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MaximumSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaximumSize(const std::uint32_t value)
     : value{ value } {}

    // get value of MaximumSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
