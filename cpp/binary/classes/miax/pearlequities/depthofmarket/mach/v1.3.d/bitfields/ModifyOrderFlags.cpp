#include "ModifyOrderFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

ModifyOrderFlags::ModifyOrderFlags(std::uint8_t raw) : raw_(raw) {}

bool ModifyOrderFlags::order_position() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void ModifyOrderFlags::set_order_position(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

std::uint8_t ModifyOrderFlags::raw() const { return raw_; }
void ModifyOrderFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t ModifyOrderFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("ModifyOrderFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t ModifyOrderFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("ModifyOrderFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t ModifyOrderFlags::encoded_size() const {
    return wire_size;
}

void ModifyOrderFlags::print(std::ostream& out) const {
    out << "ModifyOrderFlags{";
    out << "order_position=";
    out << (order_position() ? "true" : "false");
    out << '}';
}

bool ModifyOrderFlags::operator==(const ModifyOrderFlags& other) const {
    return raw_ == other.raw_;
}

bool ModifyOrderFlags::operator!=(const ModifyOrderFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ModifyOrderFlags& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
