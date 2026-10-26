#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

// Final message of a Snapshot Response, carries the sequence number at which the snapshot was
// created
class SnapshotEndMessage {
  public:
    static constexpr const char* name = "SnapshotEndMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotEndMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotEndMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint64_t snapshot_sequence_number() const { return wire::read_u64_le(at(0)); }

    void print(std::ostream& out) const {
        out << "SnapshotEndMessage{";
        out << "snapshot_sequence_number=";
        out << snapshot_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotEndMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::snap::v1_06
