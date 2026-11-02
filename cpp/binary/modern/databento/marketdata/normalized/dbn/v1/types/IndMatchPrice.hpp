#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// Reserved for future use
struct IndMatchPrice {

    static constexpr const char* name = "Ind Match Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr IndMatchPrice()
     : value{ no_value } {}

    // constructor for IndMatchPrice field
    constexpr explicit IndMatchPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of IndMatchPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of IndMatchPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
