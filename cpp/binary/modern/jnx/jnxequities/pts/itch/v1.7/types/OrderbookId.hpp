#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_7 {

// 4 digit Quick code.
struct OrderbookId {

    static constexpr const char* name = "Orderbook Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrderbookId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderbookId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderbookId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
