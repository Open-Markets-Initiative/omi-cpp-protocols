#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The consolidated high price for the issue for the trading day
struct ConsolidatedHighPriceLong {

    static constexpr const char* name = "Consolidated High Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedHighPriceLong()
     : value{ 0 } {}

    // constructor for ConsolidatedHighPriceLong field
    constexpr explicit ConsolidatedHighPriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedHighPriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedHighPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
