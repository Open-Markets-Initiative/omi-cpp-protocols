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

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message will be sent as the last message for a Business Trade Date to signal no further
// messages will be disseminated for that date.
class EndOfBusinessTradeDateMessage {
  public:
    static constexpr const char* name = "EndOfBusinessTradeDateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfBusinessTradeDateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfBusinessTradeDateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 7;
    static constexpr std::size_t fixed_size = 7;
    std::size_t encoded_size() const { return 7; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    EventCode event_code() const { return static_cast<EventCode>(wire::read_char(at(6))); }

    void print(std::ostream& out) const {
        out << "EndOfBusinessTradeDateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", event_code=";
        out << event_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfBusinessTradeDateMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
