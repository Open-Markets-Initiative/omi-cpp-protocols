#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// FOR FUTURE USE. Filled with Hex 0x00.
struct TradeIdentifier {

    static constexpr const char* name = "Trade Identifier";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeIdentifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeIdentifier(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeIdentifier field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
