#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The Nav offset that should be applied to the consolidated opening proxy price
struct NavOffsetAmountOpen {

    static constexpr const char* name = "Nav Offset Amount Open";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr NavOffsetAmountOpen()
     : value{ 0 } {}

    // constructor for NavOffsetAmountOpen field
    constexpr explicit NavOffsetAmountOpen(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of NavOffsetAmountOpen field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of NavOffsetAmountOpen field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
