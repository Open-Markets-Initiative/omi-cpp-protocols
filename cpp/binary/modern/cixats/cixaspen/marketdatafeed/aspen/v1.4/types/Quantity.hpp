#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Quantity - 6 implied decimals
struct Quantity {

    static constexpr const char* name = "Quantity";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Quantity()
     : value{ 0 } {}

    // constructor for Quantity field
    constexpr explicit Quantity(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of Quantity field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of Quantity field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
