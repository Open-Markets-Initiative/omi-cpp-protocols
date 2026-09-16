#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Locate Code uniquely assigned to the security symbol for the day
struct StockLocate {

    static constexpr const char* name = "Stock Locate";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StockLocate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StockLocate(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of StockLocate field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
