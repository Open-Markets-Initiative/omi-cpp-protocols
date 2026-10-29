#include "StrategyTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

StrategyTradingActionMessage::StrategyTradingActionMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, CurrentTradingState current_trading_state)
  : timestamp_(timestamp), strategy_id_(strategy_id), current_trading_state_(current_trading_state) {}

std::chrono::nanoseconds StrategyTradingActionMessage::timestamp() const { return timestamp_; }
void StrategyTradingActionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t StrategyTradingActionMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t StrategyTradingActionMessage::strategy_id() const { return strategy_id_; }
void StrategyTradingActionMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

CurrentTradingState StrategyTradingActionMessage::current_trading_state() const { return current_trading_state_; }
void StrategyTradingActionMessage::set_current_trading_state(CurrentTradingState value) { current_trading_state_ = value; }

MessageCode StrategyTradingActionMessage::type() const { return message_type; }

std::string_view StrategyTradingActionMessage::name() const { return "Strategy Trading Action Message"; }

std::size_t StrategyTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StrategyTradingActionMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    current_trading_state_ = static_cast<CurrentTradingState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t StrategyTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StrategyTradingActionMessage", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(current_trading_state_));
    offset += 1;

    return offset;
}

std::size_t StrategyTradingActionMessage::encoded_size() const {
    return wire_size;
}

void StrategyTradingActionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StrategyTradingActionMessage::clone() const {
    return std::make_unique<StrategyTradingActionMessage>(*this);
}

void StrategyTradingActionMessage::print(std::ostream& out) const {
    out << "StrategyTradingActionMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", current_trading_state=";
    out << current_trading_state_;
    out << '}';
}

bool StrategyTradingActionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StrategyTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StrategyTradingActionMessage::operator==(const StrategyTradingActionMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && current_trading_state_ == other.current_trading_state_;
}

bool StrategyTradingActionMessage::operator!=(const StrategyTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
