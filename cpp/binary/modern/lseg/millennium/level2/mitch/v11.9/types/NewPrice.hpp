// Lseg.Millennium.Level2.Mitch.v11.9: types/NewPrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// New limit price of the order.
struct NewPrice {

    static constexpr const char* name = "New Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr NewPrice()
     : value{ 0 } {}

    // constructor for NewPrice field
    constexpr explicit NewPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of NewPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of NewPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
