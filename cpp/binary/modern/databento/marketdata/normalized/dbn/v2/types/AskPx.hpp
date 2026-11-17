// Databento.MarketData.Normalized.Dbn.v2: types/AskPx.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The ask price
struct AskPx {

    static constexpr const char* name = "Ask Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr AskPx()
     : value{ no_value } {}

    // constructor for AskPx field
    constexpr explicit AskPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AskPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AskPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
