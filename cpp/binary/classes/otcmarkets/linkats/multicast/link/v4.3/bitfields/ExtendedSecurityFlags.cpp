#include "ExtendedSecurityFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

ExtendedSecurityFlags::ExtendedSecurityFlags(std::uint16_t raw) : raw_(raw) {}

bool ExtendedSecurityFlags::piggyback() const { return (raw_ & static_cast<std::uint16_t>(0x1)) != 0; }
void ExtendedSecurityFlags::set_piggyback(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x1)) : (raw_ & ~static_cast<std::uint16_t>(0x1))); }

bool ExtendedSecurityFlags::caveat_emptor_warning() const { return (raw_ & static_cast<std::uint16_t>(0x2)) != 0; }
void ExtendedSecurityFlags::set_caveat_emptor_warning(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x2)) : (raw_ & ~static_cast<std::uint16_t>(0x2))); }

bool ExtendedSecurityFlags::qualified_institutional_buyers_only() const { return (raw_ & static_cast<std::uint16_t>(0x4)) != 0; }
void ExtendedSecurityFlags::set_qualified_institutional_buyers_only(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x4)) : (raw_ & ~static_cast<std::uint16_t>(0x4))); }

bool ExtendedSecurityFlags::unsolicited_only() const { return (raw_ & static_cast<std::uint16_t>(0x8)) != 0; }
void ExtendedSecurityFlags::set_unsolicited_only(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x8)) : (raw_ & ~static_cast<std::uint16_t>(0x8))); }

bool ExtendedSecurityFlags::sponsored_status() const { return (raw_ & static_cast<std::uint16_t>(0x10)) != 0; }
void ExtendedSecurityFlags::set_sponsored_status(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x10)) : (raw_ & ~static_cast<std::uint16_t>(0x10))); }

bool ExtendedSecurityFlags::otc_link_ecn_eligible() const { return (raw_ & static_cast<std::uint16_t>(0x20)) != 0; }
void ExtendedSecurityFlags::set_otc_link_ecn_eligible(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x20)) : (raw_ & ~static_cast<std::uint16_t>(0x20))); }

bool ExtendedSecurityFlags::otc_link_messaging_disabled() const { return (raw_ & static_cast<std::uint16_t>(0x40)) != 0; }
void ExtendedSecurityFlags::set_otc_link_messaging_disabled(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x40)) : (raw_ & ~static_cast<std::uint16_t>(0x40))); }

bool ExtendedSecurityFlags::saturation_eligible() const { return (raw_ & static_cast<std::uint16_t>(0x80)) != 0; }
void ExtendedSecurityFlags::set_saturation_eligible(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x80)) : (raw_ & ~static_cast<std::uint16_t>(0x80))); }

bool ExtendedSecurityFlags::investment_grade() const { return (raw_ & static_cast<std::uint16_t>(0x100)) != 0; }
void ExtendedSecurityFlags::set_investment_grade(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x100)) : (raw_ & ~static_cast<std::uint16_t>(0x100))); }

bool ExtendedSecurityFlags::trading_flat() const { return (raw_ & static_cast<std::uint16_t>(0x200)) != 0; }
void ExtendedSecurityFlags::set_trading_flat(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x200)) : (raw_ & ~static_cast<std::uint16_t>(0x200))); }

bool ExtendedSecurityFlags::callable() const { return (raw_ & static_cast<std::uint16_t>(0x400)) != 0; }
void ExtendedSecurityFlags::set_callable(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x400)) : (raw_ & ~static_cast<std::uint16_t>(0x400))); }

std::uint16_t ExtendedSecurityFlags::raw() const { return raw_; }
void ExtendedSecurityFlags::set_raw(std::uint16_t value) { raw_ = value; }

std::size_t ExtendedSecurityFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("ExtendedSecurityFlags", wire_size, length);
    raw_ = wire::read_u16_be(data);
    return wire_size;
}

std::size_t ExtendedSecurityFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("ExtendedSecurityFlags", wire_size, capacity);
    wire::write_u16_be(data, raw_);
    return wire_size;
}

std::size_t ExtendedSecurityFlags::encoded_size() const {
    return wire_size;
}

void ExtendedSecurityFlags::print(std::ostream& out) const {
    out << "ExtendedSecurityFlags{";
    out << "piggyback=";
    out << (piggyback() ? "true" : "false");
    out << ", caveat_emptor_warning=";
    out << (caveat_emptor_warning() ? "true" : "false");
    out << ", qualified_institutional_buyers_only=";
    out << (qualified_institutional_buyers_only() ? "true" : "false");
    out << ", unsolicited_only=";
    out << (unsolicited_only() ? "true" : "false");
    out << ", sponsored_status=";
    out << (sponsored_status() ? "true" : "false");
    out << ", otc_link_ecn_eligible=";
    out << (otc_link_ecn_eligible() ? "true" : "false");
    out << ", otc_link_messaging_disabled=";
    out << (otc_link_messaging_disabled() ? "true" : "false");
    out << ", saturation_eligible=";
    out << (saturation_eligible() ? "true" : "false");
    out << ", investment_grade=";
    out << (investment_grade() ? "true" : "false");
    out << ", trading_flat=";
    out << (trading_flat() ? "true" : "false");
    out << ", callable=";
    out << (callable() ? "true" : "false");
    out << '}';
}

bool ExtendedSecurityFlags::operator==(const ExtendedSecurityFlags& other) const {
    return raw_ == other.raw_;
}

bool ExtendedSecurityFlags::operator!=(const ExtendedSecurityFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ExtendedSecurityFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
