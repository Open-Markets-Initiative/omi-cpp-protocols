#include "AddFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

AddFlags::AddFlags(std::uint8_t raw) : raw_(raw) {}

bool AddFlags::display() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void AddFlags::set_display(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

std::uint8_t AddFlags::raw() const { return raw_; }
void AddFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t AddFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("AddFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t AddFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("AddFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t AddFlags::encoded_size() const {
    return wire_size;
}

void AddFlags::print(std::ostream& out) const {
    out << "AddFlags{";
    out << "display=";
    out << (display() ? "true" : "false");
    out << '}';
}

bool AddFlags::operator==(const AddFlags& other) const {
    return raw_ == other.raw_;
}

bool AddFlags::operator!=(const AddFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const AddFlags& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
