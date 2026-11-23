// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8: types/MinPriceIncrementOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// minPriceIncrement
struct MinPriceIncrementOptional {

    static constexpr const char* name = "Min Price Increment Optional";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor: the null the model states, where it states one
    constexpr MinPriceIncrementOptional()
     : value{ no_value } {}

    // constructor for MinPriceIncrementOptional field
    constexpr explicit MinPriceIncrementOptional(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrementOptional field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does MinPriceIncrementOptional hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of MinPriceIncrementOptional field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
