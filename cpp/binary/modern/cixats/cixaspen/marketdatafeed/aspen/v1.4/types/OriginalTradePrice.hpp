#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Price of the trade being corrected
struct OriginalTradePrice {

    static constexpr const char* name = "Original Trade Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr OriginalTradePrice()
     : value{ 0 } {}

    // constructor for OriginalTradePrice field
    constexpr explicit OriginalTradePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of OriginalTradePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of OriginalTradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
