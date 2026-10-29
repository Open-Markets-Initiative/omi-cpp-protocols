#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/OrderRejectedReason.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// An Order Rejected Message may be sent in response to an Enter Order Message if the order
// cannot be accepted
class OrderRejectedMessage {
  public:
    static constexpr const char* name = "OrderRejectedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderRejectedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderRejectedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t order_token() const { return wire::read_u32_be(at(8)); }

    OrderRejectedReason order_rejected_reason() const { return static_cast<OrderRejectedReason>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "OrderRejectedMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "Asia/Tokyo");
        out << ", order_token=";
        out << order_token();
        out << ", order_rejected_reason=";
        out << order_rejected_reason();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderRejectedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
