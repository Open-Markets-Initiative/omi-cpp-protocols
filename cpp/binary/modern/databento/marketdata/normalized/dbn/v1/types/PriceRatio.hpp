// Databento.MarketData.Normalized.Dbn.v1: types/PriceRatio.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The price ratio, where every 1 unit corresponds to 1e-9
struct PriceRatio {

    static constexpr const char* name = "Price Ratio";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr PriceRatio()
     : value{ no_value } {}

    // constructor for PriceRatio field
    constexpr explicit PriceRatio(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of PriceRatio field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does PriceRatio hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of PriceRatio field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
