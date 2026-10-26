#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Max allowed discretionary offset from Limit order price. When the value in this field = 0, discretionary price cannot be submitted for the instrument
struct MaxPriceDiscretionOffset {

    static constexpr const char* name = "Max Price Discretion Offset";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr MaxPriceDiscretionOffset()
     : value{ 0 } {}

    // constructor for MaxPriceDiscretionOffset field
    constexpr explicit MaxPriceDiscretionOffset(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MaxPriceDiscretionOffset field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MaxPriceDiscretionOffset field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
