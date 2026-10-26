#include "SaleConditionFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

SaleConditionFlags::SaleConditionFlags(std::uint8_t raw) : raw_(raw) {}

bool SaleConditionFlags::singleprice_cross_trade() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void SaleConditionFlags::set_singleprice_cross_trade(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool SaleConditionFlags::trade_through_exempt() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void SaleConditionFlags::set_trade_through_exempt(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool SaleConditionFlags::odd_lot() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void SaleConditionFlags::set_odd_lot(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool SaleConditionFlags::extended_hours() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void SaleConditionFlags::set_extended_hours(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool SaleConditionFlags::intermarket_sweep() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void SaleConditionFlags::set_intermarket_sweep(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t SaleConditionFlags::raw() const { return raw_; }
void SaleConditionFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t SaleConditionFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("SaleConditionFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t SaleConditionFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("SaleConditionFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t SaleConditionFlags::encoded_size() const {
    return wire_size;
}

void SaleConditionFlags::print(std::ostream& out) const {
    out << "SaleConditionFlags{";
    out << "singleprice_cross_trade=";
    out << (singleprice_cross_trade() ? "true" : "false");
    out << ", trade_through_exempt=";
    out << (trade_through_exempt() ? "true" : "false");
    out << ", odd_lot=";
    out << (odd_lot() ? "true" : "false");
    out << ", extended_hours=";
    out << (extended_hours() ? "true" : "false");
    out << ", intermarket_sweep=";
    out << (intermarket_sweep() ? "true" : "false");
    out << '}';
}

bool SaleConditionFlags::operator==(const SaleConditionFlags& other) const {
    return raw_ == other.raw_;
}

bool SaleConditionFlags::operator!=(const SaleConditionFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SaleConditionFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deep::iextp::v1_06
