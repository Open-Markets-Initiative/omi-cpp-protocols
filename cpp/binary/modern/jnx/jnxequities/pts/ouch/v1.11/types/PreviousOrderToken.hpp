#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Order token of replaced order
struct PreviousOrderToken {

    static constexpr const char* name = "Previous Order Token";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PreviousOrderToken()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PreviousOrderToken(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PreviousOrderToken field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
