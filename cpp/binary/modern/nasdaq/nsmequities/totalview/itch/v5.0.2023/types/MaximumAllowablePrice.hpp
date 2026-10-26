#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// 80% above Registration Statement Highest Price
struct MaximumAllowablePrice {

    static constexpr const char* name = "Maximum Allowable Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr MaximumAllowablePrice()
     : value{ 0 } {}

    // constructor for MaximumAllowablePrice field
    constexpr explicit MaximumAllowablePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of MaximumAllowablePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of MaximumAllowablePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
