#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Must match current live order
struct ExistingOrderToken {

    static constexpr const char* name = "Existing Order Token";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExistingOrderToken()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExistingOrderToken(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExistingOrderToken field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
