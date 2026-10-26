#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates that the displayed portion of an order is fully or partially filled at its
// displayed price.
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_le(at(12)); }

    std::uint64_t trade_match_id() const { return wire::read_u64_le(at(16)); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", order_id=";
        out << order_id();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", trade_match_id=";
        out << trade_match_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
