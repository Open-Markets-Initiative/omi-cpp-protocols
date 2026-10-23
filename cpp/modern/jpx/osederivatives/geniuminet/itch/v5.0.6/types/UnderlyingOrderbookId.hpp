#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Underlying instrument ID
struct UnderlyingOrderbookId {

    static constexpr const char* name = "Underlying Orderbook Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnderlyingOrderbookId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingOrderbookId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of UnderlyingOrderbookId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
