#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// 20% below Registration Statement Lower Price
struct MinimumAllowablePrice {

    static constexpr const char* name = "Minimum Allowable Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr MinimumAllowablePrice()
     : value{ 0 } {}

    // constructor for MinimumAllowablePrice field
    constexpr explicit MinimumAllowablePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of MinimumAllowablePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of MinimumAllowablePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
