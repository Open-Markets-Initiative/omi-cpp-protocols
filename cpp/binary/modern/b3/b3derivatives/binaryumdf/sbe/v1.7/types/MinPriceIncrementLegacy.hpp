// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: types/MinPriceIncrementLegacy.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// minPriceIncrement
struct MinPriceIncrementLegacy {

    static constexpr const char* name = "Min Price Increment Legacy";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor: the null the model states, where it states one
    constexpr MinPriceIncrementLegacy()
     : value{ no_value } {}

    // constructor for MinPriceIncrementLegacy field
    constexpr explicit MinPriceIncrementLegacy(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrementLegacy field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does MinPriceIncrementLegacy hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of MinPriceIncrementLegacy field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
