#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The price reported on the corrected trade transaction
struct CorrectedTradePriceLong {

    static constexpr const char* name = "Corrected Trade Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr CorrectedTradePriceLong()
     : value{ 0 } {}

    // constructor for CorrectedTradePriceLong field
    constexpr explicit CorrectedTradePriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of CorrectedTradePriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of CorrectedTradePriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
