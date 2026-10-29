#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Aggregate market quantity on Ask side.
struct AskMarketSize {

    static constexpr const char* name = "Ask Market Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskMarketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskMarketSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskMarketSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
