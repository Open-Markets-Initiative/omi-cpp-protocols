#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The price associated with the trade transaction being reported
struct TradePriceLong {

    static constexpr const char* name = "Trade Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr TradePriceLong()
     : value{ 0 } {}

    // constructor for TradePriceLong field
    constexpr explicit TradePriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of TradePriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of TradePriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
