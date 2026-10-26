#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Best bid or ask price, the side determined by the Message Type.
struct Price4 {

    static constexpr const char* name = "Price 4";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr Price4()
     : value{ 0 } {}

    // constructor for Price4 field
    constexpr explicit Price4(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Price4 field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Price4 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
