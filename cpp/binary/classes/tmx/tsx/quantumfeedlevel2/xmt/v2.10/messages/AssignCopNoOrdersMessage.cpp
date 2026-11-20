// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/AssignCopNoOrdersMessage.cpp
#include "AssignCopNoOrdersMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

AssignCopNoOrdersMessage::AssignCopNoOrdersMessage(const std::string& symbol, std::optional<Decimal> calculated_opening_price, std::optional<std::chrono::microseconds> trading_system_time_stamp)
  : symbol_(symbol), calculated_opening_price_(calculated_opening_price), trading_system_time_stamp_(trading_system_time_stamp) {}

const std::string& AssignCopNoOrdersMessage::symbol() const { return symbol_; }
std::string& AssignCopNoOrdersMessage::symbol() { return symbol_; }
void AssignCopNoOrdersMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<Decimal> AssignCopNoOrdersMessage::calculated_opening_price() const { return calculated_opening_price_; }
void AssignCopNoOrdersMessage::set_calculated_opening_price(std::optional<Decimal> value) { calculated_opening_price_ = value; }

std::optional<std::chrono::microseconds> AssignCopNoOrdersMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void AssignCopNoOrdersMessage::set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value) { trading_system_time_stamp_ = value; }

MessageCode AssignCopNoOrdersMessage::type() const { return message_type; }

std::string_view AssignCopNoOrdersMessage::name() const { return "Assign Cop No Orders Message"; }

std::size_t AssignCopNoOrdersMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AssignCopNoOrdersMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    calculated_opening_price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t AssignCopNoOrdersMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AssignCopNoOrdersMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u64_le(data + offset, calculated_opening_price_ ? static_cast<std::uint64_t>(calculated_opening_price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t AssignCopNoOrdersMessage::encoded_size() const {
    return wire_size;
}

void AssignCopNoOrdersMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AssignCopNoOrdersMessage::clone() const {
    return std::make_unique<AssignCopNoOrdersMessage>(*this);
}

void AssignCopNoOrdersMessage::print(std::ostream& out) const {
    out << "AssignCopNoOrdersMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", calculated_opening_price=";
    print::optional(out, calculated_opening_price_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool AssignCopNoOrdersMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AssignCopNoOrdersMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AssignCopNoOrdersMessage::operator==(const AssignCopNoOrdersMessage& other) const {
    return symbol_ == other.symbol_
        && calculated_opening_price_ == other.calculated_opening_price_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool AssignCopNoOrdersMessage::operator!=(const AssignCopNoOrdersMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
