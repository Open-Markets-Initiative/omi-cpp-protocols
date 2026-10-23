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

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class UdpPayloadAddQuoteMessageLongFormMessage {
  public:
    static constexpr const char* name = "UdpPayloadAddQuoteMessageLongFormMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadAddQuoteMessageLongFormMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadAddQuoteMessageLongFormMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::uint64_t bid_reference_number() const { return wire::read_u64_be(at(8)); }

    std::uint64_t ask_reference_number() const { return wire::read_u64_be(at(16)); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(24)); }

    std::uint32_t bid() const { return wire::read_u32_be(at(28)); }

    std::uint32_t bid_size_long() const { return wire::read_u32_be(at(32)); }

    std::uint32_t ask() const { return wire::read_u32_be(at(36)); }

    std::uint32_t ask_size_long() const { return wire::read_u32_be(at(40)); }

    void print(std::ostream& out) const {
        out << "UdpPayloadAddQuoteMessageLongFormMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", bid_reference_number=";
        out << bid_reference_number();
        out << ", ask_reference_number=";
        out << ask_reference_number();
        out << ", option_id=";
        out << option_id();
        out << ", bid=";
        out << bid();
        out << ", bid_size_long=";
        out << bid_size_long();
        out << ", ask=";
        out << ask();
        out << ", ask_size_long=";
        out << ask_size_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadAddQuoteMessageLongFormMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
