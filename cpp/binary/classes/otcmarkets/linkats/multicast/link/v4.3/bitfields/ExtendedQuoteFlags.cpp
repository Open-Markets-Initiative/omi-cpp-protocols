#include "ExtendedQuoteFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

ExtendedQuoteFlags::ExtendedQuoteFlags(std::uint8_t raw) : raw_(raw) {}

bool ExtendedQuoteFlags::quote_saturated() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void ExtendedQuoteFlags::set_quote_saturated(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool ExtendedQuoteFlags::bid_auto_ex() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void ExtendedQuoteFlags::set_bid_auto_ex(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool ExtendedQuoteFlags::offer_auto_ex() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void ExtendedQuoteFlags::set_offer_auto_ex(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool ExtendedQuoteFlags::nms_conditional_quote() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void ExtendedQuoteFlags::set_nms_conditional_quote(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

std::uint8_t ExtendedQuoteFlags::raw() const { return raw_; }
void ExtendedQuoteFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t ExtendedQuoteFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("ExtendedQuoteFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t ExtendedQuoteFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("ExtendedQuoteFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t ExtendedQuoteFlags::encoded_size() const {
    return wire_size;
}

void ExtendedQuoteFlags::print(std::ostream& out) const {
    out << "ExtendedQuoteFlags{";
    out << "quote_saturated=";
    out << (quote_saturated() ? "true" : "false");
    out << ", bid_auto_ex=";
    out << (bid_auto_ex() ? "true" : "false");
    out << ", offer_auto_ex=";
    out << (offer_auto_ex() ? "true" : "false");
    out << ", nms_conditional_quote=";
    out << (nms_conditional_quote() ? "true" : "false");
    out << '}';
}

bool ExtendedQuoteFlags::operator==(const ExtendedQuoteFlags& other) const {
    return raw_ == other.raw_;
}

bool ExtendedQuoteFlags::operator!=(const ExtendedQuoteFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ExtendedQuoteFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
