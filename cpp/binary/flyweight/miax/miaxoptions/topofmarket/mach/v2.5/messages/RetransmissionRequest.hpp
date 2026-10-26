#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// The SesM client uses this packet to request a retransmission server to retransmit a range of
// packets
class RetransmissionRequest {
  public:
    static constexpr const char* name = "RetransmissionRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RetransmissionRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RetransmissionRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint64_t start_sequence_number() const { return wire::read_u64_le(at(0)); }

    std::uint64_t end_sequence_number() const { return wire::read_u64_le(at(8)); }

    void print(std::ostream& out) const {
        out << "RetransmissionRequest{";
        out << "start_sequence_number=";
        out << start_sequence_number();
        out << ", end_sequence_number=";
        out << end_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RetransmissionRequest& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
