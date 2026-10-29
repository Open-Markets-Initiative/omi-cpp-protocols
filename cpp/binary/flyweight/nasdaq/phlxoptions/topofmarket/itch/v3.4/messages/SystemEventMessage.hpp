#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/EventCode.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The system event message type is used to signal a market or data feed handler event.
class SystemEventMessage {
  public:
    static constexpr const char* name = "SystemEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 7;
    static constexpr std::size_t fixed_size = 7;
    std::size_t encoded_size() const { return 7; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    EventCode event_code() const { return static_cast<EventCode>(wire::read_char(at(4))); }

    std::uint8_t version() const { return wire::read_u8(at(5)); }

    std::uint8_t sub_version() const { return wire::read_u8(at(6)); }

    void print(std::ostream& out) const {
        out << "SystemEventMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", event_code=";
        out << event_code();
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

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
