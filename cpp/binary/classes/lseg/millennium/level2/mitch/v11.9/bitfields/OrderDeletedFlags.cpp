#include "OrderDeletedFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderDeletedFlags::OrderDeletedFlags(std::uint8_t raw) : raw_(raw) {}

std::uint8_t OrderDeletedFlags::unused_5() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0x1F)) >> 0); }
void OrderDeletedFlags::set_unused_5(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0x1F)) | ((static_cast<std::uint8_t>(value) << 0) & static_cast<std::uint8_t>(0x1F))); }

bool OrderDeletedFlags::firm_quote() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void OrderDeletedFlags::set_firm_quote(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

std::uint8_t OrderDeletedFlags::unused_2() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xC0)) >> 6); }
void OrderDeletedFlags::set_unused_2(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xC0)) | ((static_cast<std::uint8_t>(value) << 6) & static_cast<std::uint8_t>(0xC0))); }

std::uint8_t OrderDeletedFlags::raw() const { return raw_; }
void OrderDeletedFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t OrderDeletedFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("OrderDeletedFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t OrderDeletedFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("OrderDeletedFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t OrderDeletedFlags::encoded_size() const {
    return wire_size;
}

void OrderDeletedFlags::print(std::ostream& out) const {
    out << "OrderDeletedFlags{";
    out << "unused_5=";
    out << static_cast<unsigned long long>(unused_5());
    out << ", firm_quote=";
    out << (firm_quote() ? "true" : "false");
    out << ", unused_2=";
    out << static_cast<unsigned long long>(unused_2());
    out << '}';
}

bool OrderDeletedFlags::operator==(const OrderDeletedFlags& other) const {
    return raw_ == other.raw_;
}

bool OrderDeletedFlags::operator!=(const OrderDeletedFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderDeletedFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
