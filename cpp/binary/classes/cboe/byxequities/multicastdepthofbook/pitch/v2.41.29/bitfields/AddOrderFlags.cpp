#include "AddOrderFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

AddOrderFlags::AddOrderFlags(std::uint8_t raw) : raw_(raw) {}

bool AddOrderFlags::display() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void AddOrderFlags::set_display(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

std::uint8_t AddOrderFlags::raw() const { return raw_; }
void AddOrderFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t AddOrderFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("AddOrderFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t AddOrderFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("AddOrderFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t AddOrderFlags::encoded_size() const {
    return wire_size;
}

void AddOrderFlags::print(std::ostream& out) const {
    out << "AddOrderFlags{";
    out << "display=";
    out << (display() ? "true" : "false");
    out << '}';
}

bool AddOrderFlags::operator==(const AddOrderFlags& other) const {
    return raw_ == other.raw_;
}

bool AddOrderFlags::operator!=(const AddOrderFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const AddOrderFlags& value) {
    value.print(out);
    return out;
}

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
