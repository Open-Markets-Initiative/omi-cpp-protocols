// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/PriceOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// price
struct PriceOptional {

    static constexpr const char* name = "Price Optional";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor: the null the model states, where it states one
    constexpr PriceOptional()
     : value{ no_value } {}

    // constructor for PriceOptional field
    constexpr explicit PriceOptional(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of PriceOptional field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does PriceOptional hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of PriceOptional field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
