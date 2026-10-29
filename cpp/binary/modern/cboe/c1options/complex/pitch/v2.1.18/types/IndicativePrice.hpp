#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// SNBBO Collared Volume Maximizing Imbalance Minimizing Price computed on combined Auction-Only and Continuous Book (if any).
struct IndicativePrice {

    static constexpr const char* name = "Indicative Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr IndicativePrice()
     : value{ 0 } {}

    // constructor for IndicativePrice field
    constexpr explicit IndicativePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of IndicativePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of IndicativePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
