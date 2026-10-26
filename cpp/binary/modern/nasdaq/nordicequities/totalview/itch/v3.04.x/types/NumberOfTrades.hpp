#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Number of trades in the cross
struct NumberOfTrades {

    static constexpr const char* name = "Number Of Trades";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NumberOfTrades()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfTrades(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NumberOfTrades field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
