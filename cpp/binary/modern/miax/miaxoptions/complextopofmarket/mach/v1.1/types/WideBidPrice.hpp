#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// MIAX Best Bid net price.
struct WideBidPrice {

    static constexpr const char* name = "Wide Bid Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr WideBidPrice()
     : value{ 0 } {}

    // constructor for WideBidPrice field
    constexpr explicit WideBidPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of WideBidPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of WideBidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
