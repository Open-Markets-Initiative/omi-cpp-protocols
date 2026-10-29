#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// How long the order remains in effect
struct TimeInForce {

    static constexpr const char* name = "Time In Force";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TimeInForce()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TimeInForce(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TimeInForce field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
