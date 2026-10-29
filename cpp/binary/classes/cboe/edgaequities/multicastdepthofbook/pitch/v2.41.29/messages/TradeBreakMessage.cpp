#include "TradeBreakMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

TradeBreakMessage::TradeBreakMessage(std::chrono::nanoseconds time_offset, std::uint64_t execution_id)
  : time_offset_(time_offset), execution_id_(execution_id) {}

std::chrono::nanoseconds TradeBreakMessage::time_offset() const { return time_offset_; }
void TradeBreakMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t TradeBreakMessage::execution_id() const { return execution_id_; }
void TradeBreakMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

MessageCode TradeBreakMessage::type() const { return message_type; }

std::string_view TradeBreakMessage::name() const { return "Trade Break Message"; }

std::size_t TradeBreakMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeBreakMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeBreakMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeBreakMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    return offset;
}

std::size_t TradeBreakMessage::encoded_size() const {
    return wire_size;
}

void TradeBreakMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeBreakMessage::clone() const {
    return std::make_unique<TradeBreakMessage>(*this);
}

void TradeBreakMessage::print(std::ostream& out) const {
    out << "TradeBreakMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", execution_id=";
    out << execution_id_;
    out << '}';
}

bool TradeBreakMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeBreakMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeBreakMessage::operator==(const TradeBreakMessage& other) const {
    return time_offset_ == other.time_offset_
        && execution_id_ == other.execution_id_;
}

bool TradeBreakMessage::operator!=(const TradeBreakMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29
