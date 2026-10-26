#include "AddAttributedOrderFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

AddAttributedOrderFlags::AddAttributedOrderFlags(std::uint8_t raw) : raw_(raw) {}

std::uint8_t AddAttributedOrderFlags::unused_4() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xF)) >> 0); }
void AddAttributedOrderFlags::set_unused_4(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xF)) | ((static_cast<std::uint8_t>(value) << 0) & static_cast<std::uint8_t>(0xF))); }

bool AddAttributedOrderFlags::named_market_order() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void AddAttributedOrderFlags::set_named_market_order(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool AddAttributedOrderFlags::firm_quote() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void AddAttributedOrderFlags::set_firm_quote(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

std::uint8_t AddAttributedOrderFlags::unused_2() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0xC0)) >> 6); }
void AddAttributedOrderFlags::set_unused_2(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0xC0)) | ((static_cast<std::uint8_t>(value) << 6) & static_cast<std::uint8_t>(0xC0))); }

std::uint8_t AddAttributedOrderFlags::raw() const { return raw_; }
void AddAttributedOrderFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t AddAttributedOrderFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("AddAttributedOrderFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t AddAttributedOrderFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("AddAttributedOrderFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t AddAttributedOrderFlags::encoded_size() const {
    return wire_size;
}

void AddAttributedOrderFlags::print(std::ostream& out) const {
    out << "AddAttributedOrderFlags{";
    out << "unused_4=";
    out << static_cast<unsigned long long>(unused_4());
    out << ", named_market_order=";
    out << (named_market_order() ? "true" : "false");
    out << ", firm_quote=";
    out << (firm_quote() ? "true" : "false");
    out << ", unused_2=";
    out << static_cast<unsigned long long>(unused_2());
    out << '}';
}

bool AddAttributedOrderFlags::operator==(const AddAttributedOrderFlags& other) const {
    return raw_ == other.raw_;
}

bool AddAttributedOrderFlags::operator!=(const AddAttributedOrderFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const AddAttributedOrderFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
