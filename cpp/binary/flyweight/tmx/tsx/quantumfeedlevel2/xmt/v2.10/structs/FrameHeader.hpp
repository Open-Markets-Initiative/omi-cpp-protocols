// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: structs/FrameHeader.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AckRequiredPossDup.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Xmt Udp Packet Frame Header
class FrameHeader {
  public:
    static constexpr const char* name = "FrameHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FrameHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FrameHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::uint8_t start_of_frame() const { return wire::read_u8(at(0)); }

    char protocol_name() const { return wire::read_char(at(1)); }

    char protocol_version() const { return wire::read_char(at(2)); }

    std::uint16_t message_length() const { return wire::read_u16_le(at(3)); }

    std::uint32_t session_id() const { return wire::read_u32_le(at(5)); }

    AckRequiredPossDup ack_required_poss_dup() const { return static_cast<AckRequiredPossDup>(wire::read_char(at(9))); }

    std::uint8_t num_body() const { return wire::read_u8(at(10)); }

    void print(std::ostream& out) const {
        out << "FrameHeader{";
        out << "start_of_frame=";
        out << static_cast<int>(start_of_frame());
        out << ", protocol_name=";
        print::character(out, protocol_name());
        out << ", protocol_version=";
        print::character(out, protocol_version());
        out << ", message_length=";
        out << message_length();
        out << ", session_id=";
        out << session_id();
        out << ", ack_required_poss_dup=";
        out << ack_required_poss_dup();
        out << ", num_body=";
        out << static_cast<int>(num_body());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FrameHeader& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
