#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// This message is sent whenever an order on the book is modified as a result of a partial
// cancellation.
class PayloadOrderCancelMessage {
  public:
    static constexpr const char* name = "PayloadOrderCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadOrderCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadOrderCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(4)); }

    std::uint32_t canceled_shares() const { return wire::read_u32_be(at(12)); }

    void print(std::ostream& out) const {
        out << "PayloadOrderCancelMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", canceled_shares=";
        out << canceled_shares();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadOrderCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
