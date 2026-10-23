#include "EventsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

EventsGroup::EventsGroup(EventType event_type, std::chrono::nanoseconds event_time)
  : event_type_(event_type), event_time_(event_time) {}

EventType EventsGroup::event_type() const { return event_type_; }
void EventsGroup::set_event_type(EventType value) { event_type_ = value; }

std::chrono::nanoseconds EventsGroup::event_time() const { return event_time_; }
void EventsGroup::set_event_time(std::chrono::nanoseconds value) { event_time_ = value; }

std::size_t EventsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EventsGroup", wire_size, length);

    event_type_ = static_cast<EventType>(wire::read_u8(data + offset));
    offset += 1;

    event_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t EventsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EventsGroup", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(event_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(event_time_.count()));
    offset += 8;

    return offset;
}

std::size_t EventsGroup::encoded_size() const {
    return wire_size;
}

void EventsGroup::print(std::ostream& out) const {
    out << "EventsGroup{";
    out << "event_type=";
    out << event_type_;
    out << ", event_time=";
    out << event_time_.count();
    out << '}';
}

bool EventsGroup::operator==(const EventsGroup& other) const {
    return event_type_ == other.event_type_
        && event_time_ == other.event_time_;
}

bool EventsGroup::operator!=(const EventsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const EventsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
