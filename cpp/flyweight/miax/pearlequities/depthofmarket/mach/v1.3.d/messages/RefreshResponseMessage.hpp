#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Sent by MIAX Pearl Equities over the DoM Retransmission Interface (ESeSM Unsequenced Data
// Packet) carrying one Application Message that satisfies a previous Refresh Request.
class RefreshResponseMessage {
  public:
    static constexpr const char* name = "RefreshResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint64_t sequence_number() const { return wire::read_u64_le(at(0)); }

    void print(std::ostream& out) const {
        out << "RefreshResponseMessage{";
        out << "sequence_number=";
        out << sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
