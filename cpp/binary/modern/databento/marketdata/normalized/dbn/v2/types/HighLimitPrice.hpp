// Databento.MarketData.Normalized.Dbn.v2: types/HighLimitPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The high limit price, where every 1 unit corresponds to 1e-9
struct HighLimitPrice {

    static constexpr const char* name = "High Limit Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr HighLimitPrice()
     : value{ no_value } {}

    // constructor for HighLimitPrice field
    constexpr explicit HighLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of HighLimitPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does HighLimitPrice hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of HighLimitPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
