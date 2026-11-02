#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The value for non-price statistics
struct Quantity {

    static constexpr const char* name = "Quantity";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr Quantity()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit Quantity(const std::int64_t value)
     : value{ value } {}

    // get value of Quantity field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
