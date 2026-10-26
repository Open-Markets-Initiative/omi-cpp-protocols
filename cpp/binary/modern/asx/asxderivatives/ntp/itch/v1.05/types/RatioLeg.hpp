#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Ratio of the leg
struct RatioLeg {

    static constexpr const char* name = "Ratio Leg";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr RatioLeg()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RatioLeg(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of RatioLeg field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
