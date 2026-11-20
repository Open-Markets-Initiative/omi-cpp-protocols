// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCancelledMessage.cpp
#include "TradeCancelledMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

TradeCancelledMessage::TradeCancelledMessage(const std::string& symbol, std::optional<std::uint32_t> trade_number, std::optional<std::chrono::microseconds> trading_system_time_stamp)
  : symbol_(symbol), trade_number_(trade_number), trading_system_time_stamp_(trading_system_time_stamp) {}

const std::string& TradeCancelledMessage::symbol() const { return symbol_; }
std::string& TradeCancelledMessage::symbol() { return symbol_; }
void TradeCancelledMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint32_t> TradeCancelledMessage::trade_number() const { return trade_number_; }
void TradeCancelledMessage::set_trade_number(std::optional<std::uint32_t> value) { trade_number_ = value; }

std::optional<std::chrono::microseconds> TradeCancelledMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void TradeCancelledMessage::set_trading_system_time_stamp(std::optional<std::chrono::microseconds> value) { trading_system_time_stamp_ = value; }

MessageCode TradeCancelledMessage::type() const { return message_type; }

std::string_view TradeCancelledMessage::name() const { return "Trade Cancelled Message"; }

std::size_t TradeCancelledMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelledMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    trade_number_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t TradeCancelledMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelledMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u32_le(data + offset, trade_number_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t TradeCancelledMessage::encoded_size() const {
    return wire_size;
}

void TradeCancelledMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeCancelledMessage::clone() const {
    return std::make_unique<TradeCancelledMessage>(*this);
}

void TradeCancelledMessage::print(std::ostream& out) const {
    out << "TradeCancelledMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", trade_number=";
    print::optional(out, trade_number_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool TradeCancelledMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeCancelledMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelledMessage::operator==(const TradeCancelledMessage& other) const {
    return symbol_ == other.symbol_
        && trade_number_ == other.trade_number_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool TradeCancelledMessage::operator!=(const TradeCancelledMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
