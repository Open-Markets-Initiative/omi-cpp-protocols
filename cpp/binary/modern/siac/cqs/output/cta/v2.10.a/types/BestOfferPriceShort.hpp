#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the Best Offer Price on a consolidated basis. Has implied 2 decimal places
struct BestOfferPriceShort {

    static constexpr const char* name = "Best Offer Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr BestOfferPriceShort()
     : value{ 0 } {}

    // constructor for BestOfferPriceShort field
    constexpr explicit BestOfferPriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestOfferPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BestOfferPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
