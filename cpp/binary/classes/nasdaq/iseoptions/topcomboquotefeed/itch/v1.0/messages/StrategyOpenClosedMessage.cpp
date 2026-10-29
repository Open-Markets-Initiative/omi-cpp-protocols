#include "StrategyOpenClosedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

StrategyOpenClosedMessage::StrategyOpenClosedMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, OpenState open_state)
  : timestamp_(timestamp), strategy_id_(strategy_id), open_state_(open_state) {}

std::chrono::nanoseconds StrategyOpenClosedMessage::timestamp() const { return timestamp_; }
void StrategyOpenClosedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t StrategyOpenClosedMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t StrategyOpenClosedMessage::strategy_id() const { return strategy_id_; }
void StrategyOpenClosedMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

OpenState StrategyOpenClosedMessage::open_state() const { return open_state_; }
void StrategyOpenClosedMessage::set_open_state(OpenState value) { open_state_ = value; }

MessageCode StrategyOpenClosedMessage::type() const { return message_type; }

std::string_view StrategyOpenClosedMessage::name() const { return "Strategy Open Closed Message"; }

std::size_t StrategyOpenClosedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StrategyOpenClosedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    open_state_ = static_cast<OpenState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t StrategyOpenClosedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StrategyOpenClosedMessage", wire_size, capacity);

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(open_state_));
    offset += 1;

    return offset;
}

std::size_t StrategyOpenClosedMessage::encoded_size() const {
    return wire_size;
}

void StrategyOpenClosedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StrategyOpenClosedMessage::clone() const {
    return std::make_unique<StrategyOpenClosedMessage>(*this);
}

void StrategyOpenClosedMessage::print(std::ostream& out) const {
    out << "StrategyOpenClosedMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", open_state=";
    out << open_state_;
    out << '}';
}

bool StrategyOpenClosedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StrategyOpenClosedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StrategyOpenClosedMessage::operator==(const StrategyOpenClosedMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && open_state_ == other.open_state_;
}

bool StrategyOpenClosedMessage::operator!=(const StrategyOpenClosedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
