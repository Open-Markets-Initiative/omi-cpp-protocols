// Databento.MarketData.Normalized.Dbn.v3: types/Low.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The low price for the bar
struct Low {

    static constexpr const char* name = "Low";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr Low()
     : value{ no_value } {}

    // constructor for Low field
    constexpr explicit Low(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Low field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Low field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
