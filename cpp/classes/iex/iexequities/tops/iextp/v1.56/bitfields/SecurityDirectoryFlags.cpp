#include "SecurityDirectoryFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

SecurityDirectoryFlags::SecurityDirectoryFlags(std::uint8_t raw) : raw_(raw) {}

bool SecurityDirectoryFlags::etp() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void SecurityDirectoryFlags::set_etp(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool SecurityDirectoryFlags::when_issued() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void SecurityDirectoryFlags::set_when_issued(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool SecurityDirectoryFlags::test_security() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void SecurityDirectoryFlags::set_test_security(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t SecurityDirectoryFlags::raw() const { return raw_; }
void SecurityDirectoryFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t SecurityDirectoryFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("SecurityDirectoryFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t SecurityDirectoryFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("SecurityDirectoryFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t SecurityDirectoryFlags::encoded_size() const {
    return wire_size;
}

void SecurityDirectoryFlags::print(std::ostream& out) const {
    out << "SecurityDirectoryFlags{";
    out << "etp=";
    out << (etp() ? "true" : "false");
    out << ", when_issued=";
    out << (when_issued() ? "true" : "false");
    out << ", test_security=";
    out << (test_security() ? "true" : "false");
    out << '}';
}

bool SecurityDirectoryFlags::operator==(const SecurityDirectoryFlags& other) const {
    return raw_ == other.raw_;
}

bool SecurityDirectoryFlags::operator!=(const SecurityDirectoryFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityDirectoryFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::iextp::v1_56
