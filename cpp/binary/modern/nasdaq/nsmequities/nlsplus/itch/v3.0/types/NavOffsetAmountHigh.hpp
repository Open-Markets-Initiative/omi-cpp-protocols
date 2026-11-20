// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0: types/NavOffsetAmountHigh.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The Nav offset that should be applied to the consolidated high proxy price
struct NavOffsetAmountHigh {

    static constexpr const char* name = "Nav Offset Amount High";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr NavOffsetAmountHigh()
     : value{ 0 } {}

    // constructor for NavOffsetAmountHigh field
    constexpr explicit NavOffsetAmountHigh(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of NavOffsetAmountHigh field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of NavOffsetAmountHigh field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
