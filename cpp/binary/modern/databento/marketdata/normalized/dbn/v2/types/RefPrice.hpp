// Databento.MarketData.Normalized.Dbn.v2: types/RefPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The price at which the imbalance shares are calculated
struct RefPrice {

    static constexpr const char* name = "Ref Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr RefPrice()
     : value{ no_value } {}

    // constructor for RefPrice field
    constexpr explicit RefPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of RefPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does RefPrice hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of RefPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
