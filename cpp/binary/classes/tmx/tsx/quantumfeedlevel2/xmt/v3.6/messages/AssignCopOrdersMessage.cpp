// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/AssignCopOrdersMessage.cpp
#include "AssignCopOrdersMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

AssignCopOrdersMessage::AssignCopOrdersMessage(const std::string& symbol, std::optional<Decimal> calculated_opening_price, OrderSide order_side, const std::array<CopOrder, 15>& cop_order, std::optional<std::chrono::nanoseconds> trading_system_time_stamp)
  : symbol_(symbol), calculated_opening_price_(calculated_opening_price), order_side_(order_side), cop_order_(cop_order), trading_system_time_stamp_(trading_system_time_stamp) {}

const std::string& AssignCopOrdersMessage::symbol() const { return symbol_; }
std::string& AssignCopOrdersMessage::symbol() { return symbol_; }
void AssignCopOrdersMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<Decimal> AssignCopOrdersMessage::calculated_opening_price() const { return calculated_opening_price_; }
void AssignCopOrdersMessage::set_calculated_opening_price(std::optional<Decimal> value) { calculated_opening_price_ = value; }

OrderSide AssignCopOrdersMessage::order_side() const { return order_side_; }
void AssignCopOrdersMessage::set_order_side(OrderSide value) { order_side_ = value; }

const std::array<CopOrder, 15>& AssignCopOrdersMessage::cop_order() const { return cop_order_; }
std::array<CopOrder, 15>& AssignCopOrdersMessage::cop_order() { return cop_order_; }
void AssignCopOrdersMessage::set_cop_order(const std::array<CopOrder, 15>& value) { cop_order_ = value; }

std::optional<std::chrono::nanoseconds> AssignCopOrdersMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void AssignCopOrdersMessage::set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value) { trading_system_time_stamp_ = value; }

MessageCode AssignCopOrdersMessage::type() const { return message_type; }

std::string_view AssignCopOrdersMessage::name() const { return "Assign Cop Orders Message"; }

std::size_t AssignCopOrdersMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AssignCopOrdersMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    calculated_opening_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    order_side_ = static_cast<OrderSide>(wire::read_char(data + offset));
    offset += 1;

    for (std::size_t index = 0; index < cop_order_.size(); ++index) {
        offset += cop_order_[index].decode(data + offset, length - offset);
    }

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t AssignCopOrdersMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AssignCopOrdersMessage", wire_size, capacity);

    wire::write_text(data + offset, 12, ' ', symbol_);
    offset += 12;

    wire::write_u64_le(data + offset, calculated_opening_price_ ? static_cast<std::uint64_t>(calculated_opening_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(order_side_));
    offset += 1;

    for (const auto& entry : cop_order_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t AssignCopOrdersMessage::encoded_size() const {
    return wire_size;
}

void AssignCopOrdersMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AssignCopOrdersMessage::clone() const {
    return std::make_unique<AssignCopOrdersMessage>(*this);
}

void AssignCopOrdersMessage::print(std::ostream& out) const {
    out << "AssignCopOrdersMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", calculated_opening_price=";
    print::optional(out, calculated_opening_price_);
    out << ", order_side=";
    out << order_side_;
    out << ", cop_order=";
    print::sequence(out, cop_order_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool AssignCopOrdersMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AssignCopOrdersMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AssignCopOrdersMessage::operator==(const AssignCopOrdersMessage& other) const {
    return symbol_ == other.symbol_
        && calculated_opening_price_ == other.calculated_opening_price_
        && order_side_ == other.order_side_
        && cop_order_ == other.cop_order_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool AssignCopOrdersMessage::operator!=(const AssignCopOrdersMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
