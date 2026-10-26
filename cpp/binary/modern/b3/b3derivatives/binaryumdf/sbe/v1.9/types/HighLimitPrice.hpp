#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// highLimitPrice
struct HighLimitPrice {

    static constexpr const char* name = "High Limit Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr HighLimitPrice()
     : value{ 0 } {}

    // constructor for HighLimitPrice field
    constexpr explicit HighLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of HighLimitPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of HighLimitPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
