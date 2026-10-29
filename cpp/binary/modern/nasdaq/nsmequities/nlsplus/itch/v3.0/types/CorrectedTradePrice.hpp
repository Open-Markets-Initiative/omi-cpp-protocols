#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The price reported on the corrected trade transaction
struct CorrectedTradePrice {

    static constexpr const char* name = "Corrected Trade Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr CorrectedTradePrice()
     : value{ 0 } {}

    // constructor for CorrectedTradePrice field
    constexpr explicit CorrectedTradePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of CorrectedTradePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of CorrectedTradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
