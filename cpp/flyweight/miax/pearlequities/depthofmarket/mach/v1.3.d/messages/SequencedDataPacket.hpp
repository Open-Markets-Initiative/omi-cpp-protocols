#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The ESesM server uses Sequenced data packets to send all messages that must be recoverable
// by the client in case of a connection loss
class SequencedDataPacket {
  public:
    static constexpr const char* name = "SequencedDataPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SequencedDataPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SequencedDataPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::uint64_t sequence_number() const { return wire::read_u64_le(at(0)); }

    std::uint8_t matching_engine_id() const { return wire::read_u8(at(8)); }

    std::uint8_t sequenced_message_type() const { return wire::read_u8(at(9)); }

    std::span<const std::byte, 0> sequenced_message() const { return bytes_.subspan(10).template first<0>(); }

    void print(std::ostream& out) const {
        out << "SequencedDataPacket{";
        out << "sequence_number=";
        out << sequence_number();
        out << ", matching_engine_id=";
        out << static_cast<int>(matching_engine_id());
        out << ", sequenced_message_type=";
        out << static_cast<int>(sequenced_message_type());
        out << ", sequenced_message=";
        print::hex(out, sequenced_message().data(), sequenced_message().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SequencedDataPacket& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
