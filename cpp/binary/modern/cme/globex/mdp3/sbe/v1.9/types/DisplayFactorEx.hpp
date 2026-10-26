#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Contains the multiplier to convert the CME Globex display price to the conventional price
struct DisplayFactorEx {

    static constexpr const char* name = "Display Factor Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr DisplayFactorEx()
     : value{ 0 } {}

    // constructor for DisplayFactorEx field
    constexpr explicit DisplayFactorEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of DisplayFactorEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of DisplayFactorEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
