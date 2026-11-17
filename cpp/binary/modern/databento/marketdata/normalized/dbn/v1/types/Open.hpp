// Databento.MarketData.Normalized.Dbn.v1: types/Open.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The open price for the bar
struct Open {

    static constexpr const char* name = "Open";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr Open()
     : value{ no_value } {}

    // constructor for Open field
    constexpr explicit Open(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Open field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Open field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
