// Lseg.Millennium.Level2.Mitch.v11.9: types/BuyLimitPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Best bid price. Will contain zero if there are no visible limit orders on the buy side
struct BuyLimitPrice {

    static constexpr const char* name = "Buy Limit Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr BuyLimitPrice()
     : value{ 0 } {}

    // constructor for BuyLimitPrice field
    constexpr explicit BuyLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of BuyLimitPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of BuyLimitPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
