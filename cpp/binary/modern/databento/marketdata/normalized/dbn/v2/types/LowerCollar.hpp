// Databento.MarketData.Normalized.Dbn.v2: types/LowerCollar.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// Reserved for future use
struct LowerCollar {

    static constexpr const char* name = "Lower Collar";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr LowerCollar()
     : value{ no_value } {}

    // constructor for LowerCollar field
    constexpr explicit LowerCollar(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LowerCollar field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LowerCollar field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
