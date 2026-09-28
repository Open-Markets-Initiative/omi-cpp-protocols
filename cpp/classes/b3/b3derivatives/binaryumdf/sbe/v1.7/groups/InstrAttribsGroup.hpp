#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/InstrAttribType.hpp"
#include "../enums/InstrAttribValue.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// noInstrAttribs
class InstrAttribsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 2;

    InstrAttribsGroup() = default;
    InstrAttribsGroup(InstrAttribType instr_attrib_type, InstrAttribValue instr_attrib_value);

    // Instr Attrib Type: Code to represent the type of instrument attributes.
    InstrAttribType instr_attrib_type() const;
    void set_instr_attrib_type(InstrAttribType value);

    // Instr Attrib Value: Attribute value appropriate to the InstrAttribType (871) field.
    InstrAttribValue instr_attrib_value() const;
    void set_instr_attrib_value(InstrAttribValue value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstrAttribsGroup& other) const;
    bool operator!=(const InstrAttribsGroup& other) const;

  private:
    InstrAttribType instr_attrib_type_{};
    InstrAttribValue instr_attrib_value_{};
};

std::ostream& operator<<(std::ostream& out, const InstrAttribsGroup& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
