#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Contains the multiplier to convert the CME Globex display price to the conventional price
struct DisplayFactor {

    static constexpr const char* name = "Display Factor";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr DisplayFactor()
     : value{ 0 } {}

    // constructor for DisplayFactor field
    constexpr explicit DisplayFactor(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of DisplayFactor field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of DisplayFactor field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
