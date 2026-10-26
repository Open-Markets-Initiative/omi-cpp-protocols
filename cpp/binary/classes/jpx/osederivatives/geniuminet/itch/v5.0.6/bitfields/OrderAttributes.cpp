#include "OrderAttributes.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

OrderAttributes::OrderAttributes(std::uint16_t raw) : raw_(raw) {}

bool OrderAttributes::force() const { return (raw_ & static_cast<std::uint16_t>(0x1)) != 0; }
void OrderAttributes::set_force(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x1)) : (raw_ & ~static_cast<std::uint16_t>(0x1))); }

bool OrderAttributes::short_sell() const { return (raw_ & static_cast<std::uint16_t>(0x2)) != 0; }
void OrderAttributes::set_short_sell(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x2)) : (raw_ & ~static_cast<std::uint16_t>(0x2))); }

bool OrderAttributes::market_bid() const { return (raw_ & static_cast<std::uint16_t>(0x4)) != 0; }
void OrderAttributes::set_market_bid(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x4)) : (raw_ & ~static_cast<std::uint16_t>(0x4))); }

bool OrderAttributes::price_stabilization() const { return (raw_ & static_cast<std::uint16_t>(0x8)) != 0; }
void OrderAttributes::set_price_stabilization(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x8)) : (raw_ & ~static_cast<std::uint16_t>(0x8))); }

bool OrderAttributes::override_crossing() const { return (raw_ & static_cast<std::uint16_t>(0x10)) != 0; }
void OrderAttributes::set_override_crossing(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x10)) : (raw_ & ~static_cast<std::uint16_t>(0x10))); }

bool OrderAttributes::undisclosed() const { return (raw_ & static_cast<std::uint16_t>(0x20)) != 0; }
void OrderAttributes::set_undisclosed(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x20)) : (raw_ & ~static_cast<std::uint16_t>(0x20))); }

std::uint16_t OrderAttributes::raw() const { return raw_; }
void OrderAttributes::set_raw(std::uint16_t value) { raw_ = value; }

std::size_t OrderAttributes::decode(const std::byte* data, std::size_t length) {
    wire::require("OrderAttributes", wire_size, length);
    raw_ = wire::read_u16_be(data);
    return wire_size;
}

std::size_t OrderAttributes::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("OrderAttributes", wire_size, capacity);
    wire::write_u16_be(data, raw_);
    return wire_size;
}

std::size_t OrderAttributes::encoded_size() const {
    return wire_size;
}

void OrderAttributes::print(std::ostream& out) const {
    out << "OrderAttributes{";
    out << "force=";
    out << (force() ? "true" : "false");
    out << ", short_sell=";
    out << (short_sell() ? "true" : "false");
    out << ", market_bid=";
    out << (market_bid() ? "true" : "false");
    out << ", price_stabilization=";
    out << (price_stabilization() ? "true" : "false");
    out << ", override_crossing=";
    out << (override_crossing() ? "true" : "false");
    out << ", undisclosed=";
    out << (undisclosed() ? "true" : "false");
    out << '}';
}

bool OrderAttributes::operator==(const OrderAttributes& other) const {
    return raw_ == other.raw_;
}

bool OrderAttributes::operator!=(const OrderAttributes& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderAttributes& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
