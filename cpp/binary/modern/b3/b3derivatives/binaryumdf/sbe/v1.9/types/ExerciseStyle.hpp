#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {


// exerciseStyle
struct ExerciseStyle {

    static constexpr auto name = "Exercise Style";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr ExerciseStyle()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExerciseStyle(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExerciseStyle field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
