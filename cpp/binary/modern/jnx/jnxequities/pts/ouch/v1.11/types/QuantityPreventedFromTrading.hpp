#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Number of shares that would have executed if the trade had occurred
struct QuantityPreventedFromTrading {

    static constexpr const char* name = "Quantity Prevented From Trading";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr QuantityPreventedFromTrading()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuantityPreventedFromTrading(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of QuantityPreventedFromTrading field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
