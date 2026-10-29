#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Minimum acceptable quantity to execute
struct MinimumQuantity {

    static constexpr const char* name = "Minimum Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MinimumQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MinimumQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
