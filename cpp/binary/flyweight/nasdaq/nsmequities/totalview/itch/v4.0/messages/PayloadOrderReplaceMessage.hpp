#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// This message is sent whenever an order on the book has been cancel-replaced. All remaining
// shares from the original order are no longer accessible, and must be removed. The new order
// details are provided for the replacement, along with a new order reference number which will
// be used henceforth.
class PayloadOrderReplaceMessage {
  public:
    static constexpr const char* name = "PayloadOrderReplaceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadOrderReplaceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadOrderReplaceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t original_order_reference_number() const { return wire::read_u64_be(at(4)); }

    std::uint64_t new_order_reference_number() const { return wire::read_u64_be(at(12)); }

    std::uint32_t shares() const { return wire::read_u32_be(at(20)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(24))), -4); }

    void print(std::ostream& out) const {
        out << "PayloadOrderReplaceMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", original_order_reference_number=";
        out << original_order_reference_number();
        out << ", new_order_reference_number=";
        out << new_order_reference_number();
        out << ", shares=";
        out << shares();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadOrderReplaceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
