#include "SettlPriceType.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SettlPriceType::SettlPriceType(std::uint8_t raw) : raw_(raw) {}

bool SettlPriceType::final_daily() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void SettlPriceType::set_final_daily(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool SettlPriceType::actual() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void SettlPriceType::set_actual(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool SettlPriceType::rounded() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void SettlPriceType::set_rounded(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool SettlPriceType::intraday() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void SettlPriceType::set_intraday(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool SettlPriceType::reserved_bits() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void SettlPriceType::set_reserved_bits(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool SettlPriceType::unused_settl_price_type_5() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void SettlPriceType::set_unused_settl_price_type_5(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool SettlPriceType::unused_settl_price_type_6() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void SettlPriceType::set_unused_settl_price_type_6(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool SettlPriceType::null_value() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void SettlPriceType::set_null_value(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t SettlPriceType::raw() const { return raw_; }
void SettlPriceType::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t SettlPriceType::decode(const std::byte* data, std::size_t length) {
    wire::require("SettlPriceType", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t SettlPriceType::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("SettlPriceType", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t SettlPriceType::encoded_size() const {
    return wire_size;
}

void SettlPriceType::print(std::ostream& out) const {
    out << "SettlPriceType{";
    out << "final_daily=";
    out << (final_daily() ? "true" : "false");
    out << ", actual=";
    out << (actual() ? "true" : "false");
    out << ", rounded=";
    out << (rounded() ? "true" : "false");
    out << ", intraday=";
    out << (intraday() ? "true" : "false");
    out << ", reserved_bits=";
    out << (reserved_bits() ? "true" : "false");
    out << ", unused_settl_price_type_5=";
    out << (unused_settl_price_type_5() ? "true" : "false");
    out << ", unused_settl_price_type_6=";
    out << (unused_settl_price_type_6() ? "true" : "false");
    out << ", null_value=";
    out << (null_value() ? "true" : "false");
    out << '}';
}

bool SettlPriceType::operator==(const SettlPriceType& other) const {
    return raw_ == other.raw_;
}

bool SettlPriceType::operator!=(const SettlPriceType& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SettlPriceType& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
