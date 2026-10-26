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

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The Time Reference message is used to provide a midnight reference point for recipients of
// the feed. It is sent whenever the system starts up and when the system crosses a midnight
// boundary.
class TimeReferenceMessage {
  public:
    static constexpr const char* name = "TimeReferenceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TimeReferenceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TimeReferenceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::seconds midnight_reference() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::chrono::seconds time_reference() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(at(4)))); }
    std::int64_t time_reference_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/Chicago").utc(static_cast<std::int64_t>(time_reference().count()) * 1000000000); }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(8)))); }

    std::uint32_t trade_date() const { return wire::read_u32_le(at(12)); }

    void print(std::ostream& out) const {
        out << "TimeReferenceMessage{";
        out << "midnight_reference=";
        out << midnight_reference().count();
        out << ", time_reference=";
        calendar::print(out, time_reference().count(), 1000000000, "America/Chicago");
        out << ", time_offset=";
        out << time_offset().count();
        out << ", trade_date=";
        out << trade_date();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TimeReferenceMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
