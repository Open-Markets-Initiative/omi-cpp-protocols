// Databento.MarketData.Normalized.Dbn.v2: types/TradingReferencePrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The trading session settlement price on trading_reference_date, where every 1 unit corresponds to 1e-9
struct TradingReferencePrice {

    static constexpr const char* name = "Trading Reference Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr TradingReferencePrice()
     : value{ no_value } {}

    // constructor for TradingReferencePrice field
    constexpr explicit TradingReferencePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of TradingReferencePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of TradingReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
