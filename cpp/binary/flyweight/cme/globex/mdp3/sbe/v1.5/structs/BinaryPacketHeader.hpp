#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Cme Mdp Packet Header
class BinaryPacketHeader {
  public:
    static constexpr const char* name = "BinaryPacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BinaryPacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BinaryPacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::uint32_t packet_sequence_number() const { return wire::read_u32_le(at(0)); }

    std::chrono::nanoseconds sending_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(4)))); }

    void print(std::ostream& out) const {
        out << "BinaryPacketHeader{";
        out << "packet_sequence_number=";
        out << packet_sequence_number();
        out << ", sending_time=";
        out << sending_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BinaryPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
