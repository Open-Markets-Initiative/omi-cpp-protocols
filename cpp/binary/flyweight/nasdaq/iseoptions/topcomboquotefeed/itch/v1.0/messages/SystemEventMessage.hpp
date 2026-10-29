#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/EventCode.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The system event message type is used to signal a market or data feed handler event.
class SystemEventMessage {
  public:
    static constexpr const char* name = "SystemEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    EventCode event_code() const { return static_cast<EventCode>(wire::read_char(at(6))); }

    std::uint16_t current_year() const { return wire::read_u16_be(at(7)); }

    std::uint8_t current_month() const { return wire::read_u8(at(9)); }

    std::uint8_t current_day() const { return wire::read_u8(at(10)); }

    std::uint8_t version() const { return wire::read_u8(at(11)); }

    std::uint8_t sub_version() const { return wire::read_u8(at(12)); }

    void print(std::ostream& out) const {
        out << "SystemEventMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", event_code=";
        out << event_code();
        out << ", current_year=";
        out << current_year();
        out << ", current_month=";
        out << static_cast<int>(current_month());
        out << ", current_day=";
        out << static_cast<int>(current_day());
        out << ", version=";
        out << static_cast<int>(version());
        out << ", sub_version=";
        out << static_cast<int>(sub_version());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SystemEventMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
