#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The price reported on the original trade transaction
struct OriginalTradePriceLong {

    static constexpr const char* name = "Original Trade Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalTradePriceLong()
     : value{ 0 } {}

    // constructor for OriginalTradePriceLong field
    constexpr explicit OriginalTradePriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OriginalTradePriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OriginalTradePriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
