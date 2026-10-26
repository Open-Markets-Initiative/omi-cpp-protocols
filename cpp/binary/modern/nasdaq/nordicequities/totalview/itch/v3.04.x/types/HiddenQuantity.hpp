#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Total hidden quantity matched
struct HiddenQuantity {

    static constexpr const char* name = "Hidden Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr HiddenQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HiddenQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of HiddenQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
