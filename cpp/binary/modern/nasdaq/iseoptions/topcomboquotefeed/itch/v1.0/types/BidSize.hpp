#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Aggregated number of contracts on the bid side being displayed in the options market at the current time.
struct BidSize {

    static constexpr const char* name = "Bid Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
