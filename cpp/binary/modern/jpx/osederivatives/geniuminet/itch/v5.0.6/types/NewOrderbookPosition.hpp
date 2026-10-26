#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// New rank within orderbook
struct NewOrderbookPosition {

    static constexpr const char* name = "New Orderbook Position";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NewOrderbookPosition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewOrderbookPosition(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NewOrderbookPosition field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
