#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Denotes the Nasdaq exchange's best offer price, or the lowest price for market sell order(s) in the execution system.
struct BestOfferPrice {

    static constexpr const char* name = "Best Offer Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr BestOfferPrice()
     : value{ 0 } {}

    // constructor for BestOfferPrice field
    constexpr explicit BestOfferPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestOfferPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BestOfferPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
