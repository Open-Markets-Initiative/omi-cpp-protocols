#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The aggregate market size on Bid side.
struct BidMarketSize {

    static constexpr const char* name = "Bid Market Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidMarketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidMarketSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidMarketSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
