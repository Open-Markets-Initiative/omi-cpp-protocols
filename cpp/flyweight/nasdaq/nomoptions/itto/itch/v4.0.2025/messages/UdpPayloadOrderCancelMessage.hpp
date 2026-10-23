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

// This message is sent whenever an order on the book is modified as a result of a partial
// cancellation.
class UdpPayloadOrderCancelMessage {
  public:
    static constexpr const char* name = "UdpPayloadOrderCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadOrderCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadOrderCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(8)); }

    std::uint32_t cancelled_contracts() const { return wire::read_u32_be(at(16)); }

    void print(std::ostream& out) const {
        out << "UdpPayloadOrderCancelMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", cancelled_contracts=";
        out << cancelled_contracts();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadOrderCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
