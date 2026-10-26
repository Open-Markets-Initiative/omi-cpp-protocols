#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Total number of shares in the order
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
