#include "SecurityFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

SecurityFlags::SecurityFlags(std::uint8_t raw) : raw_(raw) {}

bool SecurityFlags::piggyback() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void SecurityFlags::set_piggyback(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool SecurityFlags::caveat_emptor_warning() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void SecurityFlags::set_caveat_emptor_warning(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool SecurityFlags::qualified_institutional_buyers_only() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void SecurityFlags::set_qualified_institutional_buyers_only(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool SecurityFlags::unsolicited_only() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void SecurityFlags::set_unsolicited_only(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool SecurityFlags::bb_quoted() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void SecurityFlags::set_bb_quoted(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool SecurityFlags::otc_link_ecn_eligible() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void SecurityFlags::set_otc_link_ecn_eligible(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool SecurityFlags::otc_link_messaging_disabled() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void SecurityFlags::set_otc_link_messaging_disabled(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool SecurityFlags::saturation_eligible() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void SecurityFlags::set_saturation_eligible(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t SecurityFlags::raw() const { return raw_; }
void SecurityFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t SecurityFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("SecurityFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t SecurityFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("SecurityFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t SecurityFlags::encoded_size() const {
    return wire_size;
}

void SecurityFlags::print(std::ostream& out) const {
    out << "SecurityFlags{";
    out << "piggyback=";
    out << (piggyback() ? "true" : "false");
    out << ", caveat_emptor_warning=";
    out << (caveat_emptor_warning() ? "true" : "false");
    out << ", qualified_institutional_buyers_only=";
    out << (qualified_institutional_buyers_only() ? "true" : "false");
    out << ", unsolicited_only=";
    out << (unsolicited_only() ? "true" : "false");
    out << ", bb_quoted=";
    out << (bb_quoted() ? "true" : "false");
    out << ", otc_link_ecn_eligible=";
    out << (otc_link_ecn_eligible() ? "true" : "false");
    out << ", otc_link_messaging_disabled=";
    out << (otc_link_messaging_disabled() ? "true" : "false");
    out << ", saturation_eligible=";
    out << (saturation_eligible() ? "true" : "false");
    out << '}';
}

bool SecurityFlags::operator==(const SecurityFlags& other) const {
    return raw_ == other.raw_;
}

bool SecurityFlags::operator!=(const SecurityFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
