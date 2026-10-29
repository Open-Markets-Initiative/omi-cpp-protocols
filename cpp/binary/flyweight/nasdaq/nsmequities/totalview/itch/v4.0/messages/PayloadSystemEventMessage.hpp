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

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// The system event message type is used to signal a market or data feed handler event.
class PayloadSystemEventMessage {
  public:
    static constexpr const char* name = "PayloadSystemEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadSystemEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadSystemEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    EventCode event_code() const { return static_cast<EventCode>(wire::read_char(at(4))); }

    void print(std::ostream& out) const {
        out << "PayloadSystemEventMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", event_code=";
        out << event_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadSystemEventMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
