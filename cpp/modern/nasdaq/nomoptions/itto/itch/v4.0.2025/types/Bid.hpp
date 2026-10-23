#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display bid price of the new quote.
struct Bid {

    static constexpr const char* name = "Bid";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Bid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Bid(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Bid field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
