#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Number of lots added to the book (all volume is visible).
struct Quantity {

    static constexpr const char* name = "Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Quantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Quantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Quantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
