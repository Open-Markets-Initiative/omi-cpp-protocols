#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// MIAX Best Bid net price.
struct CompactBidPrice {

    static constexpr const char* name = "Compact Bid Price";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int16_t;

    // default constructor
    constexpr CompactBidPrice()
     : value{ 0 } {}

    // constructor for CompactBidPrice field
    constexpr explicit CompactBidPrice(const std::int16_t value)
     : value{ value } {}

    // get underlying integer of CompactBidPrice field
    [[nodiscard]] std::int16_t integer() const {
        return value;
    }

    // decimal value of CompactBidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int16_t value;
};
}
