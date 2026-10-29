#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The aggregate market size.
struct MarketSize {

    static constexpr const char* name = "Market Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MarketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MarketSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
