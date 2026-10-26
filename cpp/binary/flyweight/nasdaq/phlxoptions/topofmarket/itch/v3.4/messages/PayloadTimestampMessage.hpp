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

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The system event message type is used to signal a market or data feed handler event.
class PayloadTimestampMessage {
  public:
    static constexpr const char* name = "PayloadTimestampMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadTimestampMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadTimestampMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::chrono::seconds second() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }
    std::int64_t second_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(second().count()) * 1000000000); }

    void print(std::ostream& out) const {
        out << "PayloadTimestampMessage{";
        out << "second=";
        calendar::print(out, second().count(), 1000000000, "America/New_York");
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadTimestampMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
