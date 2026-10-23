#include "OrderModifiedFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderModifiedFlags::OrderModifiedFlags(std::uint8_t raw) : raw_(raw) {}

bool OrderModifiedFlags::priority_flag() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void OrderModifiedFlags::set_priority_flag(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

std::uint8_t OrderModifiedFlags::unused_4() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0x1E)) >> 1); }
void OrderModifiedFlags::set_unused_4(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0x1E)) | ((static_cast<std::uint8_t>(value) << 1) & static_cast<std::uint8_t>(0x1E))); }

bool OrderModifiedFlags::firm_quote() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void OrderModifiedFlags::set_firm_quote(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

std::uint8_t OrderModifiedFlags::unused_2() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xC0)) >> 6); }
void OrderModifiedFlags::set_unused_2(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xC0)) | ((static_cast<std::uint8_t>(value) << 6) & static_cast<std::uint8_t>(0xC0))); }

std::uint8_t OrderModifiedFlags::raw() const { return raw_; }
void OrderModifiedFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t OrderModifiedFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("OrderModifiedFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t OrderModifiedFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("OrderModifiedFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t OrderModifiedFlags::encoded_size() const {
    return wire_size;
}

void OrderModifiedFlags::print(std::ostream& out) const {
    out << "OrderModifiedFlags{";
    out << "priority_flag=";
    out << (priority_flag() ? "true" : "false");
    out << ", unused_4=";
    out << static_cast<unsigned long long>(unused_4());
    out << ", firm_quote=";
    out << (firm_quote() ? "true" : "false");
    out << ", unused_2=";
    out << static_cast<unsigned long long>(unused_2());
    out << '}';
}

bool OrderModifiedFlags::operator==(const OrderModifiedFlags& other) const {
    return raw_ == other.raw_;
}

bool OrderModifiedFlags::operator!=(const OrderModifiedFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderModifiedFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
