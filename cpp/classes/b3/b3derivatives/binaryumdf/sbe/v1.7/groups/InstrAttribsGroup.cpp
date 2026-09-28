#include "InstrAttribsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

InstrAttribsGroup::InstrAttribsGroup(InstrAttribType instr_attrib_type, InstrAttribValue instr_attrib_value)
  : instr_attrib_type_(instr_attrib_type), instr_attrib_value_(instr_attrib_value) {}

InstrAttribType InstrAttribsGroup::instr_attrib_type() const { return instr_attrib_type_; }
void InstrAttribsGroup::set_instr_attrib_type(InstrAttribType value) { instr_attrib_type_ = value; }

InstrAttribValue InstrAttribsGroup::instr_attrib_value() const { return instr_attrib_value_; }
void InstrAttribsGroup::set_instr_attrib_value(InstrAttribValue value) { instr_attrib_value_ = value; }

std::size_t InstrAttribsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrAttribsGroup", wire_size, length);

    instr_attrib_type_ = static_cast<InstrAttribType>(wire::read_u8(data + offset));
    offset += 1;

    instr_attrib_value_ = static_cast<InstrAttribValue>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t InstrAttribsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrAttribsGroup", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(instr_attrib_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(instr_attrib_value_));
    offset += 1;

    return offset;
}

std::size_t InstrAttribsGroup::encoded_size() const {
    return wire_size;
}

void InstrAttribsGroup::print(std::ostream& out) const {
    out << "InstrAttribsGroup{";
    out << "instr_attrib_type=";
    out << instr_attrib_type_;
    out << ", instr_attrib_value=";
    out << instr_attrib_value_;
    out << '}';
}

bool InstrAttribsGroup::operator==(const InstrAttribsGroup& other) const {
    return instr_attrib_type_ == other.instr_attrib_type_
        && instr_attrib_value_ == other.instr_attrib_value_;
}

bool InstrAttribsGroup::operator!=(const InstrAttribsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstrAttribsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
