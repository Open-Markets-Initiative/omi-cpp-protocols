#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {

// Clearing price using Eligible Auction Orders
struct IndicativeClearingPrice {

    static constexpr const char* name = "Indicative Clearing Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr IndicativeClearingPrice()
     : value{ 0 } {}

    // constructor for IndicativeClearingPrice field
    constexpr explicit IndicativeClearingPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of IndicativeClearingPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of IndicativeClearingPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
