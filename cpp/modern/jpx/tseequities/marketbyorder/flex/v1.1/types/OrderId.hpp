#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Identifier assigned per issue on an order basis, unique and sequential each business day
struct OrderId {

    static constexpr const char* name = "Order Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrderId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
