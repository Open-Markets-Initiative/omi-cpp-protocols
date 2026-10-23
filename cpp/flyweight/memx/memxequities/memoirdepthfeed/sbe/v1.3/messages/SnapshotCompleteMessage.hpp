#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// SnapshotCompleteMessage
class SnapshotCompleteMessage {
  public:
    static constexpr const char* name = "SnapshotCompleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotCompleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotCompleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint64_t as_of_sequence_number() const { return wire::read_u64_be(at(8)); }

    void print(std::ostream& out) const {
        out << "SnapshotCompleteMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", as_of_sequence_number=";
        out << as_of_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotCompleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
