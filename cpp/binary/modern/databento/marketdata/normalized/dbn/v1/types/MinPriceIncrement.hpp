// Databento.MarketData.Normalized.Dbn.v1: types/MinPriceIncrement.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The min price increment, where every 1 unit corresponds to 1e-9
struct MinPriceIncrement {

    static constexpr const char* name = "Min Price Increment";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr MinPriceIncrement()
     : value{ no_value } {}

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
