#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// lowLimitPrice
struct LowLimitPrice {

    static constexpr const char* name = "Low Limit Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr LowLimitPrice()
     : value{ 0 } {}

    // constructor for LowLimitPrice field
    constexpr explicit LowLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LowLimitPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LowLimitPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
