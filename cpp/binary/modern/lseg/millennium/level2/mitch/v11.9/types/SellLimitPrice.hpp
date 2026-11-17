// Lseg.Millennium.Level2.Mitch.v11.9: types/SellLimitPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Best offer price. Will contain zero if there are no visible limit orders on the sell side
struct SellLimitPrice {

    static constexpr const char* name = "Sell Limit Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr SellLimitPrice()
     : value{ 0 } {}

    // constructor for SellLimitPrice field
    constexpr explicit SellLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of SellLimitPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of SellLimitPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
