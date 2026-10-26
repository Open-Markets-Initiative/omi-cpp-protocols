#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Represents the first price paid for an option during the trading day.
struct PremiumPriceDenominatorCode {

    static constexpr auto name = "Premium Price Denominator Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PremiumPriceDenominatorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PremiumPriceDenominatorCode(const char &value)
     : value{ value } {}

    // get value of PremiumPriceDenominatorCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
