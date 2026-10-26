#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the price of the Upper Auction Collar Threshold
struct UpperPriceRangeCollar {

    static constexpr const char* name = "Upper Price Range Collar";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr UpperPriceRangeCollar()
     : value{ 0 } {}

    // constructor for UpperPriceRangeCollar field
    constexpr explicit UpperPriceRangeCollar(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of UpperPriceRangeCollar field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of UpperPriceRangeCollar field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
