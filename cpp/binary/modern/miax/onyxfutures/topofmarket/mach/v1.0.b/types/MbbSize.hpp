#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Aggregate size in contracts at the displayed offer price
struct MbbSize {

    static constexpr const char* name = "Mbb Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MbbSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MbbSize(const std::uint32_t value)
     : value{ value } {}

    // get value of MbbSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
