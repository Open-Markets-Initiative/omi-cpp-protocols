#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates the reported number of shares on the trade transaction
struct TradeSize {

    static constexpr const char* name = "Trade Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
