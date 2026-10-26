#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Market price of the collateral, either from external market sources or a result of trading activity on the platform. Clean price
struct CollateralMarketPrice {

    static constexpr const char* name = "Collateral Market Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr CollateralMarketPrice()
     : value{ 0 } {}

    // constructor for CollateralMarketPrice field
    constexpr explicit CollateralMarketPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of CollateralMarketPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of CollateralMarketPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
