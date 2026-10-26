#include "AllowedBookTypes.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

AllowedBookTypes::AllowedBookTypes(std::uint8_t raw) : raw_(raw) {}

bool AllowedBookTypes::firm_quote_book() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void AllowedBookTypes::set_firm_quote_book(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool AllowedBookTypes::offbook() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void AllowedBookTypes::set_offbook(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool AllowedBookTypes::electronic_order_book() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void AllowedBookTypes::set_electronic_order_book(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool AllowedBookTypes::private_rfq() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void AllowedBookTypes::set_private_rfq(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

std::uint8_t AllowedBookTypes::raw() const { return raw_; }
void AllowedBookTypes::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t AllowedBookTypes::decode(const std::byte* data, std::size_t length) {
    wire::require("AllowedBookTypes", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t AllowedBookTypes::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("AllowedBookTypes", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t AllowedBookTypes::encoded_size() const {
    return wire_size;
}

void AllowedBookTypes::print(std::ostream& out) const {
    out << "AllowedBookTypes{";
    out << "firm_quote_book=";
    out << (firm_quote_book() ? "true" : "false");
    out << ", offbook=";
    out << (offbook() ? "true" : "false");
    out << ", electronic_order_book=";
    out << (electronic_order_book() ? "true" : "false");
    out << ", private_rfq=";
    out << (private_rfq() ? "true" : "false");
    out << '}';
}

bool AllowedBookTypes::operator==(const AllowedBookTypes& other) const {
    return raw_ == other.raw_;
}

bool AllowedBookTypes::operator!=(const AllowedBookTypes& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const AllowedBookTypes& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
