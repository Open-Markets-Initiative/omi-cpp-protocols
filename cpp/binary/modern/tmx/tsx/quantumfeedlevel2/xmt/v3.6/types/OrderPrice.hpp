// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/OrderPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Price In A Valid Currency
struct OrderPrice {

    static constexpr const char* name = "Order Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderPrice()
     : value{ 0 } {}

    // constructor for OrderPrice field
    constexpr explicit OrderPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of OrderPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of OrderPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
