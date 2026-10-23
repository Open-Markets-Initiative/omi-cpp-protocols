#include "OrderBookClearFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderBookClearFlags::OrderBookClearFlags(std::uint8_t raw) : raw_(raw) {}

std::uint8_t OrderBookClearFlags::unused_5() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint8_t>(0x1F)) >> 0); }
void OrderBookClearFlags::set_unused_5(std::uint8_t value) { raw_ = static_cast<std::uint8_t>((raw_ & ~static_cast<std::uint8_t>(0x1F)) | ((static_cast<std::uint8_t>(value) << 0) & static_cast<std::uint8_t>(0x1F))); }

bool OrderBookClearFlags::firm_quote() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void OrderBookClearFlags::set_firm_quote(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool OrderBookClearFlags::private_rfq() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void OrderBookClearFlags::set_private_rfq(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool OrderBookClearFlags::unused_1() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void OrderBookClearFlags::set_unused_1(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t OrderBookClearFlags::raw() const { return raw_; }
void OrderBookClearFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t OrderBookClearFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("OrderBookClearFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t OrderBookClearFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("OrderBookClearFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t OrderBookClearFlags::encoded_size() const {
    return wire_size;
}

void OrderBookClearFlags::print(std::ostream& out) const {
    out << "OrderBookClearFlags{";
    out << "unused_5=";
    out << static_cast<unsigned long long>(unused_5());
    out << ", firm_quote=";
    out << (firm_quote() ? "true" : "false");
    out << ", private_rfq=";
    out << (private_rfq() ? "true" : "false");
    out << ", unused_1=";
    out << (unused_1() ? "true" : "false");
    out << '}';
}

bool OrderBookClearFlags::operator==(const OrderBookClearFlags& other) const {
    return raw_ == other.raw_;
}

bool OrderBookClearFlags::operator!=(const OrderBookClearFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderBookClearFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
