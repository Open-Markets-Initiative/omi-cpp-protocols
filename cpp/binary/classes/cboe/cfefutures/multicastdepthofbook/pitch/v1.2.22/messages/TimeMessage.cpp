#include "TimeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

TimeMessage::TimeMessage(std::chrono::seconds time_reference, std::uint32_t epoch_time)
  : time_reference_(time_reference), epoch_time_(epoch_time) {}

std::chrono::seconds TimeMessage::time_reference() const { return time_reference_; }
void TimeMessage::set_time_reference(std::chrono::seconds value) { time_reference_ = value; }
std::int64_t TimeMessage::time_reference_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/Chicago").utc(static_cast<std::int64_t>(time_reference_.count()) * 1000000000); }

std::uint32_t TimeMessage::epoch_time() const { return epoch_time_; }
void TimeMessage::set_epoch_time(std::uint32_t value) { epoch_time_ = value; }

MessageCode TimeMessage::type() const { return message_type; }

std::string_view TimeMessage::name() const { return "Time Message"; }

std::size_t TimeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TimeMessage", wire_size, length);

    time_reference_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    epoch_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TimeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TimeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_reference_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(epoch_time_));
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
    out << "time_reference=";
    calendar::print(out, time_reference_.count(), 1000000000, "America/Chicago");
    out << ", epoch_time=";
    out << epoch_time_;
    out << '}';
}

bool TimeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TimeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TimeMessage::operator==(const TimeMessage& other) const {
    return time_reference_ == other.time_reference_
        && epoch_time_ == other.epoch_time_;
}

bool TimeMessage::operator!=(const TimeMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
