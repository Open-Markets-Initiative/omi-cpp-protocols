#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The Nav offset that should be applied to the Proxy Price
struct NavOffsetAmount {

    static constexpr const char* name = "Nav Offset Amount";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr NavOffsetAmount()
     : value{ 0 } {}

    // constructor for NavOffsetAmount field
    constexpr explicit NavOffsetAmount(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of NavOffsetAmount field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of NavOffsetAmount field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
