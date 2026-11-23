// Databento.MarketData.Normalized.Dbn.v3: types/UpperCollar.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// Reserved for future use
struct UpperCollar {

    static constexpr const char* name = "Upper Collar";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr UpperCollar()
     : value{ no_value } {}

    // constructor for UpperCollar field
    constexpr explicit UpperCollar(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UpperCollar field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does UpperCollar hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of UpperCollar field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
