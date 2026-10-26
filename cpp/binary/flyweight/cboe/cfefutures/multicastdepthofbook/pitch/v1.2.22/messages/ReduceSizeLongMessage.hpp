#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Reduce Size messages are sent when a visible order on the CFE book is partially reduced.
class ReduceSizeLongMessage {
  public:
    static constexpr const char* name = "ReduceSizeLongMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ReduceSizeLongMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ReduceSizeLongMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint32_t canceled_quantity_long() const { return wire::read_u32_le(at(12)); }

    void print(std::ostream& out) const {
        out << "ReduceSizeLongMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", canceled_quantity_long=";
        out << canceled_quantity_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ReduceSizeLongMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
