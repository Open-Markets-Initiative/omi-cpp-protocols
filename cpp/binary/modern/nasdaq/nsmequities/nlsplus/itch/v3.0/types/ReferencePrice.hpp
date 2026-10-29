#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the reference price to be used for intraday net change calculations
struct ReferencePrice {

    static constexpr const char* name = "Reference Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ReferencePrice()
     : value{ 0 } {}

    // constructor for ReferencePrice field
    constexpr explicit ReferencePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ReferencePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
