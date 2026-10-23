#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Minimum constant tick for the instrument, sent only if instrument is non-VTT (Variable Tick table) eligible
struct MinPriceIncrement {

    static constexpr const char* name = "Min Price Increment";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 7;
    static constexpr double denominator = 10000000;
    using type = std::int64_t;

    // default constructor
    constexpr MinPriceIncrement()
     : value{ 0 } {}

    // constructor for MinPriceIncrement field
    constexpr explicit MinPriceIncrement(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrement field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MinPriceIncrement field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
