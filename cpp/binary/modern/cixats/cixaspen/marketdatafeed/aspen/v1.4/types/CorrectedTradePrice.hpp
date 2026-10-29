#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Price the trade is being amended/corrected to
struct CorrectedTradePrice {

    static constexpr const char* name = "Corrected Trade Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr CorrectedTradePrice()
     : value{ 0 } {}

    // constructor for CorrectedTradePrice field
    constexpr explicit CorrectedTradePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of CorrectedTradePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of CorrectedTradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
