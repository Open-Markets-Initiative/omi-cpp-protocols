#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Orderbook ID of Leg instrument
struct LegOrderbookId {

    static constexpr const char* name = "Leg Orderbook Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LegOrderbookId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegOrderbookId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LegOrderbookId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
