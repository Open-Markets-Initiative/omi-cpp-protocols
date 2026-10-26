#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Minimum constant tick for the instrument, sent only if instrument is non-VTT (Variable Tick table) eligible
struct MinPriceIncrementEx {

    static constexpr const char* name = "Min Price Increment Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr MinPriceIncrementEx()
     : value{ 0 } {}

    // constructor for MinPriceIncrementEx field
    constexpr explicit MinPriceIncrementEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrementEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MinPriceIncrementEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
