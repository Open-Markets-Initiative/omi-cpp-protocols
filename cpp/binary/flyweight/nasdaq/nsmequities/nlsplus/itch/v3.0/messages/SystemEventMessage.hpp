#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/EventCode.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// System Event Messages is used to signal key market or data feed control events.
class SystemEventMessage {
  public:
    static constexpr const char* name = "SystemEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    EventCode event_code() const { return static_cast<EventCode>(wire::read_char(at(0))); }

    void print(std::ostream& out) const {
        out << "SystemEventMessage{";
        out << "event_code=";
        out << event_code();
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

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
