#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Not used for complex series. Will contain zero value.
struct CompositeMarketOfferPrice {

    static constexpr const char* name = "Composite Market Offer Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr CompositeMarketOfferPrice()
     : value{ 0 } {}

    // constructor for CompositeMarketOfferPrice field
    constexpr explicit CompositeMarketOfferPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of CompositeMarketOfferPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of CompositeMarketOfferPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
