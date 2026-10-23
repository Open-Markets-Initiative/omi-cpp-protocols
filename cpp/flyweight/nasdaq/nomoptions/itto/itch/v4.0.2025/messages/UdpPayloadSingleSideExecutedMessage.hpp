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

// This message is sent whenever a Side order is executed in whole or in part. It is possible
// to receive several Single Side Executed Messages for the same Side order if that Side order
// is executed in several parts. The multiple Single Side Executed Messages on the same order
// are cumulative. By combining the executions received separately via two types of Single Side
// Executed Messages and Trade Messages, it is possible to build a complete view of all
// non-auction executions that happen on NASDAQ. Auction execution information is available in
// one bulk print via the Auction Trade Message.
class UdpPayloadSingleSideExecutedMessage {
  public:
    static constexpr const char* name = "UdpPayloadSingleSideExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadSingleSideExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadSingleSideExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t reference_number() const { return wire::read_u64_be(at(8)); }

    std::uint32_t executed_contracts() const { return wire::read_u32_be(at(16)); }

    std::uint32_t cross_number() const { return wire::read_u32_be(at(20)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(24)); }

    void print(std::ostream& out) const {
        out << "UdpPayloadSingleSideExecutedMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", reference_number=";
        out << reference_number();
        out << ", executed_contracts=";
        out << executed_contracts();
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

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadSingleSideExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
