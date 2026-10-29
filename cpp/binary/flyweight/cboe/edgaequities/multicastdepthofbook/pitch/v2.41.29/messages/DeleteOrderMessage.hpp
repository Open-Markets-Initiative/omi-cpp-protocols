#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// The Delete Order message is sent whenever an open order is completely canceled. The Order Id
// refers to the Order Id of the original Add Order message.
class DeleteOrderMessage {
  public:
    static constexpr const char* name = "DeleteOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeleteOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeleteOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    void print(std::ostream& out) const {
        out << "DeleteOrderMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeleteOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29
