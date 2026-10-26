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

// A Time message is immediately generated and sent when there is a PITCH event for a given
// clock second.
class TimeMessage {
  public:
    static constexpr const char* name = "TimeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TimeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TimeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::chrono::seconds time_reference() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }
    std::int64_t time_reference_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/Chicago").utc(static_cast<std::int64_t>(time_reference().count()) * 1000000000); }

    std::uint32_t epoch_time() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "TimeMessage{";
        out << "time_reference=";
        calendar::print(out, time_reference().count(), 1000000000, "America/Chicago");
        out << ", epoch_time=";
        out << epoch_time();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TimeMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
