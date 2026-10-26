#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Minimum price offset better than the best Standard Tick order for an order to be allowed into the market
struct AltPriceIncrementConstraint {

    static constexpr const char* name = "Alt Price Increment Constraint";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr AltPriceIncrementConstraint()
     : value{ 0 } {}

    // constructor for AltPriceIncrementConstraint field
    constexpr explicit AltPriceIncrementConstraint(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AltPriceIncrementConstraint field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AltPriceIncrementConstraint field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
