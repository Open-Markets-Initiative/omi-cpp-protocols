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

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Part of a resting order is canceled
class OrderPartialCancelMessage {
  public:
    static constexpr const char* name = "OrderPartialCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderPartialCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderPartialCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(8)); }

    Decimal quantity_canceled() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(16))), -6); }

    void print(std::ostream& out) const {
        out << "OrderPartialCancelMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", order_id=";
        out << order_id();
        out << ", quantity_canceled=";
        out << quantity_canceled();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderPartialCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
