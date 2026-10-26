#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Tcp end of message marker terminating a retransmission or snapshot session.
class EndOfMessageMessage {
  public:
    static constexpr const char* name = "EndOfMessageMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfMessageMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfMessageMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    static constexpr std::size_t fixed_size = 6;
    std::size_t encoded_size() const { return 6; }

    std::uint8_t multicast_group_number() const { return wire::read_u8(at(0)); }

    std::uint8_t number_of_system_reboots() const { return wire::read_u8(at(1)); }

    std::uint32_t next_sequence_number() const { return wire::read_u32_be(at(2)); }

    void print(std::ostream& out) const {
        out << "EndOfMessageMessage{";
        out << "multicast_group_number=";
        out << static_cast<int>(multicast_group_number());
        out << ", number_of_system_reboots=";
        out << static_cast<int>(number_of_system_reboots());
        out << ", next_sequence_number=";
        out << next_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfMessageMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
