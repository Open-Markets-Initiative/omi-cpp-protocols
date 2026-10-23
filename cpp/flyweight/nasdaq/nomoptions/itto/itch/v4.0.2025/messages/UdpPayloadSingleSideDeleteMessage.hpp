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

// The message is sent when an order or a side of a quote is being cancelled. All remaining
// contracts are no longer accessible so the side should be removed from the book.
class UdpPayloadSingleSideDeleteMessage {
  public:
    static constexpr const char* name = "UdpPayloadSingleSideDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadSingleSideDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadSingleSideDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t reference_number() const { return wire::read_u64_be(at(8)); }

    void print(std::ostream& out) const {
        out << "UdpPayloadSingleSideDeleteMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", reference_number=";
        out << reference_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadSingleSideDeleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
