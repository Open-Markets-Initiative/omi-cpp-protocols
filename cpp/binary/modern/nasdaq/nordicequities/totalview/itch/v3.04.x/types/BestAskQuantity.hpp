#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Ask volume at top of book
struct BestAskQuantity {

    static constexpr const char* name = "Best Ask Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr BestAskQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestAskQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of BestAskQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
