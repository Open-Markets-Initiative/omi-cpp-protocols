#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// This message is sent to reset the Message Sequence Number at start of day, or in response to
// failures.
class SequenceNumberResetMessage {
  public:
    static constexpr const char* name = "SequenceNumberResetMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SequenceNumberResetMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SequenceNumberResetMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint8_t product_id() const { return wire::read_u8(at(8)); }

    std::uint8_t channel_id() const { return wire::read_u8(at(9)); }

    void print(std::ostream& out) const {
        out << "SequenceNumberResetMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", product_id=";
        out << static_cast<int>(product_id());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SequenceNumberResetMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
