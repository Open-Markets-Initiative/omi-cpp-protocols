#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Primary identifier of an order book
struct OrderBookId {

    static constexpr const char* name = "Order Book Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrderBookId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderBookId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderBookId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
