#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Must be unique per Ouch account within a trading day and increase on each subsequent transaction
struct OrderToken {

    static constexpr const char* name = "Order Token";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrderToken()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderToken(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderToken field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
