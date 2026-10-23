#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Offer Price of the prevailing Composite Market.
struct CompositeMarketOfferPrice {

    static constexpr const char* name = "Composite Market Offer Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr CompositeMarketOfferPrice()
     : value{ 0 } {}

    // constructor for CompositeMarketOfferPrice field
    constexpr explicit CompositeMarketOfferPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of CompositeMarketOfferPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of CompositeMarketOfferPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
