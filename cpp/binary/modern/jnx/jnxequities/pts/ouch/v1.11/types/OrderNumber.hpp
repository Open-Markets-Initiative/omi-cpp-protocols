#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Order reference number unique within trading day
struct OrderNumber {

    static constexpr const char* name = "Order Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
