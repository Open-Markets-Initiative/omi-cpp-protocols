#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The Lower Band of the Daily Trading Limit of a Futures Product
struct LowLimitPrice {

    static constexpr const char* name = "Low Limit Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr LowLimitPrice()
     : value{ 0 } {}

    // constructor for LowLimitPrice field
    constexpr explicit LowLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LowLimitPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LowLimitPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
