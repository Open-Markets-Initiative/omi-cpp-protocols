// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/AssignLimitMessage.cpp
#include "AssignLimitMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

AssignLimitMessage::AssignLimitMessage(const std::string& symbol, std::optional<Decimal> calculated_opening_price, OrderSide order_side, const std::array<CopLimit, 15>& cop_limit, std::optional<std::chrono::microseconds> trading_system_time_stamp)
  : symbol_(symbol), calculated_opening_price_(calculated_opening_price), order_side_(order_side), cop_limit_(cop_limit), trading_system_time_stamp_(trading_system_time_stamp) {}

const std::string& AssignLimitMessage::symbol() const { return symbol_; }
std::string& AssignLimitMessage::symbol() { return symbol_; }
void AssignLimitMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<Decimal> AssignLimitMessage::calculated_opening_price() const { return calculated_opening_price_; }
void AssignLimitMessage::set_calculated_opening_price(std::optional<Decimal> value) { calculated_opening_price_ = value; }

OrderSide AssignLimitMessage::order_side() const { return order_side_; }
void AssignLimitMessage::set_order_side(OrderSide value) { order_side_ = value; }

const std::array<CopLimit, 15>& AssignLimitMessage::cop_limit() const { return cop_limit_; }
std::array<CopLimit, 15>& AssignLimitMessage::cop_limit() { return cop_limit_; }
void AssignLimitMessage::set_cop_limit(const std::array<CopLimit, 15>& value) { cop_limit_ = value; }

std::optional<std::chrono::microseconds> AssignLimitMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void AssignLimitMessage::set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value) { trading_system_time_stamp_ = value; }

MessageCode AssignLimitMessage::type() const { return message_type; }

std::string_view AssignLimitMessage::name() const { return "Assign Limit Message"; }

std::size_t AssignLimitMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AssignLimitMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    calculated_opening_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    order_side_ = static_cast<OrderSide>(wire::read_char(data + offset));
    offset += 1;

    for (std::size_t index = 0; index < cop_limit_.size(); ++index) {
        offset += cop_limit_[index].decode(data + offset, length - offset);
    }

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t AssignLimitMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AssignLimitMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u64_le(data + offset, calculated_opening_price_ ? static_cast<std::uint64_t>(calculated_opening_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(order_side_));
    offset += 1;

    for (const auto& entry : cop_limit_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t AssignLimitMessage::encoded_size() const {
    return wire_size;
}

void AssignLimitMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AssignLimitMessage::clone() const {
    return std::make_unique<AssignLimitMessage>(*this);
}

void AssignLimitMessage::print(std::ostream& out) const {
    out << "AssignLimitMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", calculated_opening_price=";
    print::optional(out, calculated_opening_price_);
    out << ", order_side=";
    out << order_side_;
    out << ", cop_limit=";
    print::sequence(out, cop_limit_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool AssignLimitMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AssignLimitMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AssignLimitMessage::operator==(const AssignLimitMessage& other) const {
    return symbol_ == other.symbol_
        && calculated_opening_price_ == other.calculated_opening_price_
        && order_side_ == other.order_side_
        && cop_limit_ == other.cop_limit_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool AssignLimitMessage::operator!=(const AssignLimitMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
