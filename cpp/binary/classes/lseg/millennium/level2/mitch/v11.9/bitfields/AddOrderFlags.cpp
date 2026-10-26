#include "AddOrderFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

AddOrderFlags::AddOrderFlags(std::uint8_t raw) : raw_(raw) {}

std::uint8_t AddOrderFlags::unused_4() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xF)) >> 0); }
void AddOrderFlags::set_unused_4(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xF)) | ((static_cast<std::uint8_t>(value) << 0) & static_cast<std::uint8_t>(0xF))); }

bool AddOrderFlags::market_order() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void AddOrderFlags::set_market_order(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool AddOrderFlags::unused_1() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void AddOrderFlags::set_unused_1(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool AddOrderFlags::private_rfq() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void AddOrderFlags::set_private_rfq(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool AddOrderFlags::second_unused_1() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void AddOrderFlags::set_second_unused_1(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

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
    out << "unused_4=";
    out << static_cast<unsigned long long>(unused_4());
    out << ", market_order=";
    out << (market_order() ? "true" : "false");
    out << ", unused_1=";
    out << (unused_1() ? "true" : "false");
    out << ", private_rfq=";
    out << (private_rfq() ? "true" : "false");
    out << ", second_unused_1=";
    out << (second_unused_1() ? "true" : "false");
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

} // namespace lseg::millennium::level2::mitch::v11_9
