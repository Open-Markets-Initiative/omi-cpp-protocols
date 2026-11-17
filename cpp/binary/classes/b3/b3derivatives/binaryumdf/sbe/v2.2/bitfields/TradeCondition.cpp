// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: bitfields/TradeCondition.cpp
#include "TradeCondition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

TradeCondition::TradeCondition(std::uint16_t raw) : raw_(raw) {}

bool TradeCondition::opening_price() const { return (raw_ & static_cast<std::uint16_t>(0x1)) != 0; }
void TradeCondition::set_opening_price(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x1)) : (raw_ & ~static_cast<std::uint16_t>(0x1))); }

bool TradeCondition::crossed() const { return (raw_ & static_cast<std::uint16_t>(0x2)) != 0; }
void TradeCondition::set_crossed(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x2)) : (raw_ & ~static_cast<std::uint16_t>(0x2))); }

bool TradeCondition::last_trade_at_the_same_price() const { return (raw_ & static_cast<std::uint16_t>(0x4)) != 0; }
void TradeCondition::set_last_trade_at_the_same_price(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x4)) : (raw_ & ~static_cast<std::uint16_t>(0x4))); }

bool TradeCondition::out_of_sequence() const { return (raw_ & static_cast<std::uint16_t>(0x8)) != 0; }
void TradeCondition::set_out_of_sequence(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x8)) : (raw_ & ~static_cast<std::uint16_t>(0x8))); }

bool TradeCondition::trade_on_behalf() const { return (raw_ & static_cast<std::uint16_t>(0x40)) != 0; }
void TradeCondition::set_trade_on_behalf(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x40)) : (raw_ & ~static_cast<std::uint16_t>(0x40))); }

bool TradeCondition::regular_trade() const { return (raw_ & static_cast<std::uint16_t>(0x2000)) != 0; }
void TradeCondition::set_regular_trade(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x2000)) : (raw_ & ~static_cast<std::uint16_t>(0x2000))); }

bool TradeCondition::block_trade() const { return (raw_ & static_cast<std::uint16_t>(0x4000)) != 0; }
void TradeCondition::set_block_trade(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x4000)) : (raw_ & ~static_cast<std::uint16_t>(0x4000))); }

std::uint16_t TradeCondition::raw() const { return raw_; }
void TradeCondition::set_raw(std::uint16_t value) { raw_ = value; }

std::size_t TradeCondition::decode(const std::byte* data, std::size_t length) {
    wire::require("TradeCondition", wire_size, length);
    raw_ = wire::read_u16_le(data);
    return wire_size;
}

std::size_t TradeCondition::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("TradeCondition", wire_size, capacity);
    wire::write_u16_le(data, raw_);
    return wire_size;
}

std::size_t TradeCondition::encoded_size() const {
    return wire_size;
}

void TradeCondition::print(std::ostream& out) const {
    out << "TradeCondition{";
    out << "opening_price=";
    out << (opening_price() ? "true" : "false");
    out << ", crossed=";
    out << (crossed() ? "true" : "false");
    out << ", last_trade_at_the_same_price=";
    out << (last_trade_at_the_same_price() ? "true" : "false");
    out << ", out_of_sequence=";
    out << (out_of_sequence() ? "true" : "false");
    out << ", trade_on_behalf=";
    out << (trade_on_behalf() ? "true" : "false");
    out << ", regular_trade=";
    out << (regular_trade() ? "true" : "false");
    out << ", block_trade=";
    out << (block_trade() ? "true" : "false");
    out << '}';
}

bool TradeCondition::operator==(const TradeCondition& other) const {
    return raw_ == other.raw_;
}

bool TradeCondition::operator!=(const TradeCondition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradeCondition& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
