#pragma once

#include <chrono>
#include <cstddef>
#include <ostream>

#include "../enums/EventType.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of repeating EventType entries
class EventsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    EventsGroup() = default;
    EventsGroup(EventType event_type, std::chrono::nanoseconds event_time);

    // Event Type: Code to represent the type of event
    EventType event_type() const;
    void set_event_type(EventType value);

    // Event Time: Date and Time of instument Activation or Expiration event sent as number of
    // nanoseconds since Unix epoch
    std::chrono::nanoseconds event_time() const;
    void set_event_time(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const EventsGroup& other) const;
    bool operator!=(const EventsGroup& other) const;

  private:
    EventType event_type_{};
    std::chrono::nanoseconds event_time_{};
};

std::ostream& operator<<(std::ostream& out, const EventsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
