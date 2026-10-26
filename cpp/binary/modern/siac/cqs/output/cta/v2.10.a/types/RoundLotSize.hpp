#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Round-lot size for a symbol can consist of 1, 10, 40 or 100 shares
struct RoundLotSize {

    static constexpr const char* name = "Round Lot Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr RoundLotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RoundLotSize(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of RoundLotSize field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
