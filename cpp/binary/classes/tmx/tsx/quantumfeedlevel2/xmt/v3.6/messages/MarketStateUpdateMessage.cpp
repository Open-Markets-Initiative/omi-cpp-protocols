// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MarketStateUpdateMessage.cpp
#include "MarketStateUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

MarketStateUpdateMessage::MarketStateUpdateMessage(MarketState market_state, std::optional<std::uint8_t> stock_group, std::optional<std::chrono::nanoseconds> trading_system_time_stamp)
  : market_state_(market_state), stock_group_(stock_group), trading_system_time_stamp_(trading_system_time_stamp) {}

MarketState MarketStateUpdateMessage::market_state() const { return market_state_; }
void MarketStateUpdateMessage::set_market_state(MarketState value) { market_state_ = value; }

std::optional<std::uint8_t> MarketStateUpdateMessage::stock_group() const { return stock_group_; }
void MarketStateUpdateMessage::set_stock_group(std::optional<std::uint8_t> value) { stock_group_ = value; }

std::optional<std::chrono::nanoseconds> MarketStateUpdateMessage::trading_system_time_stamp() const { return trading_system_time_stamp_; }
void MarketStateUpdateMessage::set_trading_system_time_stamp(std::optional<std::chrono::nanoseconds> value) { trading_system_time_stamp_ = value; }

MessageCode MarketStateUpdateMessage::type() const { return message_type; }

std::string_view MarketStateUpdateMessage::name() const { return "Market State Update Message"; }

std::size_t MarketStateUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketStateUpdateMessage", wire_size, length);

    market_state_ = static_cast<MarketState>(wire::read_char(data + offset));
    offset += 1;

    stock_group_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    trading_system_time_stamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t MarketStateUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketStateUpdateMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(market_state_));
    offset += 1;

    wire::write_u8(data + offset, stock_group_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_u64_le(data + offset, trading_system_time_stamp_ ? static_cast<std::uint64_t>(trading_system_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t MarketStateUpdateMessage::encoded_size() const {
    return wire_size;
}

void MarketStateUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketStateUpdateMessage::clone() const {
    return std::make_unique<MarketStateUpdateMessage>(*this);
}

void MarketStateUpdateMessage::print(std::ostream& out) const {
    out << "MarketStateUpdateMessage{";
    out << "market_state=";
    out << market_state_;
    out << ", stock_group=";
    print::optional(out, stock_group_);
    out << ", trading_system_time_stamp=";
    print::optional_duration(out, trading_system_time_stamp_);
    out << '}';
}

bool MarketStateUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketStateUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketStateUpdateMessage::operator==(const MarketStateUpdateMessage& other) const {
    return market_state_ == other.market_state_
        && stock_group_ == other.stock_group_
        && trading_system_time_stamp_ == other.trading_system_time_stamp_;
}

bool MarketStateUpdateMessage::operator!=(const MarketStateUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
