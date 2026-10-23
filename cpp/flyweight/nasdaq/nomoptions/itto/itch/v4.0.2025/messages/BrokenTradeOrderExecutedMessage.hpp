#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken. An execution may
// be broken if it is found to be “clearly erroneous” pursuant to NASDAQ’s Clearly Erroneous
// Policy. A trade break is final; once a trade is broken, it cannot be reinstated.
class BrokenTradeOrderExecutedMessage {
  public:
    static constexpr const char* name = "BrokenTradeOrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BrokenTradeOrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BrokenTradeOrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint32_t cross_number() const { return wire::read_u32_be(at(8)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(12)); }

    void print(std::ostream& out) const {
        out << "BrokenTradeOrderExecutedMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", cross_number=";
        out << cross_number();
        out << ", match_number=";
        out << match_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BrokenTradeOrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
