#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

// First message of a Snapshot Response sent from the Deep Plus Snap server when a Snapshot
// Request is successful
class SnapshotStartMessage {
  public:
    static constexpr const char* name = "SnapshotStartMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotStartMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotStartMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint64_t snapshot_length() const { return wire::read_u64_le(at(0)); }

    void print(std::ostream& out) const {
        out << "SnapshotStartMessage{";
        out << "snapshot_length=";
        out << snapshot_length();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotStartMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::snap::v1_06
