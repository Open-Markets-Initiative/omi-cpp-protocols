#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Number of shares removed from the display size
struct CanceledQuantity {

    static constexpr const char* name = "Canceled Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CanceledQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CanceledQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
