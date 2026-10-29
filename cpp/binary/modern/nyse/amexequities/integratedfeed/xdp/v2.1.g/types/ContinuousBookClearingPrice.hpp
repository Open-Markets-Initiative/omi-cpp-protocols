#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// For Pillar-powered markets, the price at which all interest on the book can trade, including auction and imbalance offset interest, and disregarding auction collars. For NYSE, the indicative matching price, i.e. the price closest to the reference price where the imbalance is 0. If a continuous book clearing price is not reached, it is defaulted to 0.
struct ContinuousBookClearingPrice {

    static constexpr const char* name = "Continuous Book Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ContinuousBookClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContinuousBookClearingPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of ContinuousBookClearingPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
