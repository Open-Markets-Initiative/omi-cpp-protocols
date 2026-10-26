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
#include "../enums/SourceVenue.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Sent to indicate the start and end of the day.
class SystemEventMessage {
  public:
    static constexpr const char* name = "SystemEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    EventCode event_code() const { return static_cast<EventCode>(wire::read_char(at(8))); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(9))); }

    void print(std::ostream& out) const {
        out << "SystemEventMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", event_code=";
        out << event_code();
        out << ", source_venue=";
        out << source_venue();
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

} // namespace lseg::lse::level2mbo::gtp::v26_2
