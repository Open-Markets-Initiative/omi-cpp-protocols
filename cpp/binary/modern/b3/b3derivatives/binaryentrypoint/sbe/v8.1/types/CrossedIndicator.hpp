// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/CrossedIndicator.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// crossedIndicator
struct CrossedIndicator {

    static constexpr const char* name = "Crossed Indicator";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr CrossedIndicator()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit CrossedIndicator(const std::uint16_t value)
     : value{ value } {}

    // get value of CrossedIndicator field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
