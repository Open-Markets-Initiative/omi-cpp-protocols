#include "ModifyFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

ModifyFlags::ModifyFlags(std::uint8_t raw) : raw_(raw) {}

bool ModifyFlags::priority() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void ModifyFlags::set_priority(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t ModifyFlags::raw() const { return raw_; }
void ModifyFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t ModifyFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("ModifyFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t ModifyFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("ModifyFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t ModifyFlags::encoded_size() const {
    return wire_size;
}

void ModifyFlags::print(std::ostream& out) const {
    out << "ModifyFlags{";
    out << "priority=";
    out << (priority() ? "true" : "false");
    out << '}';
}

bool ModifyFlags::operator==(const ModifyFlags& other) const {
    return raw_ == other.raw_;
}

bool ModifyFlags::operator!=(const ModifyFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ModifyFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::iextp::v1_01
