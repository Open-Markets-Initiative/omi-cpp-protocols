#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// Code to represent the type of instrument attributes.
struct InstrAttribType {

    static constexpr auto name = "Instr Attrib Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr InstrAttribType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InstrAttribType(const std::uint8_t &value)
     : value{ value } {}

    // get value of InstrAttribType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
