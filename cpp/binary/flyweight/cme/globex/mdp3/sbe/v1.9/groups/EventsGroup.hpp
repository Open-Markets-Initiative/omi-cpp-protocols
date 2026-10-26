#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/EventType.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of repeating EventType entries
class EventsGroup {
  public:
    static constexpr const char* name = "EventsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EventsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EventsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    EventType event_type() const { return static_cast<EventType>(wire::read_u8(at(0))); }

    std::chrono::nanoseconds event_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(1)))); }

    void print(std::ostream& out) const {
        out << "EventsGroup{";
        out << "event_type=";
        out << event_type();
        out << ", event_time=";
        out << event_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EventsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
