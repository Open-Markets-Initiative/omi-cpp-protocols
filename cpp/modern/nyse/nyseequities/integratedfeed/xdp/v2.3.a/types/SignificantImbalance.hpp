#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// Significant Imbalance Values
struct SignificantImbalance {

    static constexpr auto name = "Significant Imbalance";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SignificantImbalance()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SignificantImbalance(const char &value)
     : value{ value } {}

    // get value of SignificantImbalance field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
