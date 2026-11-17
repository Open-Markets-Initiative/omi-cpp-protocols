// Databento.MarketData.Normalized.Dbn.v2: types/Close.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The close price for the bar
struct Close {

    static constexpr const char* name = "Close";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr Close()
     : value{ no_value } {}

    // constructor for Close field
    constexpr explicit Close(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Close field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Close field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
