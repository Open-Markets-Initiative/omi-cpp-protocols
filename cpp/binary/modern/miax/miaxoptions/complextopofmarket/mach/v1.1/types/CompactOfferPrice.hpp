#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// MIAX Best Offer net price
struct CompactOfferPrice {

    static constexpr const char* name = "Compact Offer Price";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int16_t;

    // default constructor
    constexpr CompactOfferPrice()
     : value{ 0 } {}

    // constructor for CompactOfferPrice field
    constexpr explicit CompactOfferPrice(const std::int16_t value)
     : value{ value } {}

    // get underlying integer of CompactOfferPrice field
    [[nodiscard]] std::int16_t integer() const {
        return value;
    }

    // decimal value of CompactOfferPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int16_t value;
};
}
