#include "InstAttribGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

InstAttribGroup::InstAttribGroup(const InstAttribValue& inst_attrib_value)
  : inst_attrib_value_(inst_attrib_value) {}

const InstAttribValue& InstAttribGroup::inst_attrib_value() const { return inst_attrib_value_; }
InstAttribValue& InstAttribGroup::inst_attrib_value() { return inst_attrib_value_; }
void InstAttribGroup::set_inst_attrib_value(const InstAttribValue& value) { inst_attrib_value_ = value; }

std::size_t InstAttribGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstAttribGroup", wire_size, length);

    offset += inst_attrib_value_.decode(data + offset, length - offset);

    return offset;
}

std::size_t InstAttribGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstAttribGroup", wire_size, capacity);

    offset += inst_attrib_value_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t InstAttribGroup::encoded_size() const {
    return wire_size;
}

void InstAttribGroup::print(std::ostream& out) const {
    out << "InstAttribGroup{";
    out << "inst_attrib_value=";
    inst_attrib_value_.print(out);
    out << '}';
}

bool InstAttribGroup::operator==(const InstAttribGroup& other) const {
    return inst_attrib_value_ == other.inst_attrib_value_;
}

bool InstAttribGroup::operator!=(const InstAttribGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstAttribGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
