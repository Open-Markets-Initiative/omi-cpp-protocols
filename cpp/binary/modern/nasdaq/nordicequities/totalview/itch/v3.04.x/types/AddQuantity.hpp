#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Lit volume of the aggressive order added to the book
struct AddQuantity {

    static constexpr const char* name = "Add Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AddQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AddQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AddQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
