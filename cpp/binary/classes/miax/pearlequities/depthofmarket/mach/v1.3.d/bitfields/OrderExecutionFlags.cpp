#include "OrderExecutionFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

OrderExecutionFlags::OrderExecutionFlags(std::uint8_t raw) : raw_(raw) {}

bool OrderExecutionFlags::sip_reporting() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void OrderExecutionFlags::set_sip_reporting(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool OrderExecutionFlags::traded_against_retail() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void OrderExecutionFlags::set_traded_against_retail(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

std::uint8_t OrderExecutionFlags::raw() const { return raw_; }
void OrderExecutionFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t OrderExecutionFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("OrderExecutionFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t OrderExecutionFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("OrderExecutionFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t OrderExecutionFlags::encoded_size() const {
    return wire_size;
}

void OrderExecutionFlags::print(std::ostream& out) const {
    out << "OrderExecutionFlags{";
    out << "sip_reporting=";
    out << (sip_reporting() ? "true" : "false");
    out << ", traded_against_retail=";
    out << (traded_against_retail() ? "true" : "false");
    out << '}';
}

bool OrderExecutionFlags::operator==(const OrderExecutionFlags& other) const {
    return raw_ == other.raw_;
}

bool OrderExecutionFlags::operator!=(const OrderExecutionFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OrderExecutionFlags& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
