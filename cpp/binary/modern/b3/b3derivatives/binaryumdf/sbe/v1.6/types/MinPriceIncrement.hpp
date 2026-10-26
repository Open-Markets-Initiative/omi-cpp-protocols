#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// minPriceIncrement
struct MinPriceIncrement {

    static constexpr const char* name = "Min Price Increment";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr MinPriceIncrement()
     : value{ 0 } {}

    // constructor for MinPriceIncrement field
    constexpr explicit MinPriceIncrement(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrement field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MinPriceIncrement field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
