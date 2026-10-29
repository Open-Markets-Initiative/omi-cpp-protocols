#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Number of shares decremented from order
struct DecrementQuantity {

    static constexpr const char* name = "Decrement Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr DecrementQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DecrementQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of DecrementQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
