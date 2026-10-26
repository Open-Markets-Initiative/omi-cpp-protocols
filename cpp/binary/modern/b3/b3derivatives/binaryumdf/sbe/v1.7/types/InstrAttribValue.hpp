#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// Attribute value appropriate to the InstrAttribType (871) field.
struct InstrAttribValue {

    static constexpr auto name = "Instr Attrib Value";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr InstrAttribValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrAttribValue(const std::uint8_t &value)
     : value{ value } {}

    // get value of InstrAttribValue field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
