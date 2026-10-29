#include "EventsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

EventsGroups::EventsGroups(const GroupSize& group_size, const std::vector<EventsGroup>& events_group)
  : group_size_(group_size), events_group_(events_group) {}

const GroupSize& EventsGroups::group_size() const { return group_size_; }
GroupSize& EventsGroups::group_size() { return group_size_; }
void EventsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<EventsGroup>& EventsGroups::events_group() const { return events_group_; }
std::vector<EventsGroup>& EventsGroups::events_group() { return events_group_; }
void EventsGroups::set_events_group(const std::vector<EventsGroup>& value) { events_group_ = value; }

std::size_t EventsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        events_group_.clear();
        events_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            EventsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("EventsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            events_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t EventsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EventsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(events_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(EventsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : events_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t EventsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(events_group_);
}

void EventsGroups::print(std::ostream& out) const {
    out << "EventsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", events_group=";
    print::sequence(out, events_group_);
    out << '}';
}

bool EventsGroups::operator==(const EventsGroups& other) const {
    return group_size_ == other.group_size_
        && events_group_ == other.events_group_;
}

bool EventsGroups::operator!=(const EventsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const EventsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
