#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Total number of shares added to the book; ignore if reference price message.
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
