#include "TimeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

TimeMessage::TimeMessage(std::chrono::seconds time)
  : time_(time) {}

std::chrono::seconds TimeMessage::time() const { return time_; }
void TimeMessage::set_time(std::chrono::seconds value) { time_ = value; }

MessageCode TimeMessage::type() const { return message_type; }

std::string_view TimeMessage::name() const { return "Time Message"; }

std::size_t TimeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TimeMessage", wire_size, length);

    time_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t TimeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TimeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_.count()));
    offset += 4;

    return offset;
}

std::size_t TimeMessage::encoded_size() const {
    return wire_size;
}

void TimeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TimeMessage::clone() const {
    return std::make_unique<TimeMessage>(*this);
}

void TimeMessage::print(std::ostream& out) const {
    out << "TimeMessage{";
    out << "time=";
    out << time_.count();
    out << '}';
}

bool TimeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TimeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TimeMessage::operator==(const TimeMessage& other) const {
    return time_ == other.time_;
}

bool TimeMessage::operator!=(const TimeMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
