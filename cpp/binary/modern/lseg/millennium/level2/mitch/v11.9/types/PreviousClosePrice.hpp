// Lseg.Millennium.Level2.Mitch.v11.9: types/PreviousClosePrice.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Previous Close Price of instrument
struct PreviousClosePrice {

    static constexpr const char* name = "Previous Close Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr PreviousClosePrice()
     : value{ 0 } {}

    // constructor for PreviousClosePrice field
    constexpr explicit PreviousClosePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of PreviousClosePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of PreviousClosePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
