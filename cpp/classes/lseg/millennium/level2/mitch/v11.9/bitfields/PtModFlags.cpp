#include "PtModFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

PtModFlags::PtModFlags(std::uint8_t raw) : raw_(raw) {}

bool PtModFlags::canc() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void PtModFlags::set_canc(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool PtModFlags::amnd() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void PtModFlags::set_amnd(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

std::uint8_t PtModFlags::unused_6() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xFC)) >> 2); }
void PtModFlags::set_unused_6(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xFC)) | ((static_cast<std::uint8_t>(value) << 2) & static_cast<std::uint8_t>(0xFC))); }

std::uint8_t PtModFlags::raw() const { return raw_; }
void PtModFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t PtModFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("PtModFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t PtModFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("PtModFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t PtModFlags::encoded_size() const {
    return wire_size;
}

void PtModFlags::print(std::ostream& out) const {
    out << "PtModFlags{";
    out << "canc=";
    out << (canc() ? "true" : "false");
    out << ", amnd=";
    out << (amnd() ? "true" : "false");
    out << ", unused_6=";
    out << static_cast<unsigned long long>(unused_6());
    out << '}';
}

bool PtModFlags::operator==(const PtModFlags& other) const {
    return raw_ == other.raw_;
}

bool PtModFlags::operator!=(const PtModFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PtModFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
