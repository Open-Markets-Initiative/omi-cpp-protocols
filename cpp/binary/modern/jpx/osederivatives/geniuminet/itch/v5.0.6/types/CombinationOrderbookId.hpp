#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Identifier of combo orderbook
struct CombinationOrderbookId {

    static constexpr const char* name = "Combination Orderbook Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CombinationOrderbookId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CombinationOrderbookId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CombinationOrderbookId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
