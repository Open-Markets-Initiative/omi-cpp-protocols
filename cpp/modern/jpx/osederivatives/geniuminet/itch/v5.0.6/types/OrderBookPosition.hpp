#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Rank within orderbook
struct OrderBookPosition {

    static constexpr const char* name = "Order Book Position";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrderBookPosition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderBookPosition(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderBookPosition field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
