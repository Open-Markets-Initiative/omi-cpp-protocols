#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Order Entry Price Tick of the Product
struct Tick {

    static constexpr const char* name = "Tick";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr Tick()
     : value{ 0 } {}

    // constructor for Tick field
    constexpr explicit Tick(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Tick field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Tick field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
