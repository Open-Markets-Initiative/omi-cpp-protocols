#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/OrderDeletedFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Sent to indicate that the remainder of a displayed order is cancelled.
class OrderDeletedMessage {
  public:
    static constexpr const char* name = "OrderDeletedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeletedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeletedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    OrderDeletedFlags order_deleted_flags() const { return OrderDeletedFlags{ bytes_.subspan(12) }; }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(13)); }

    void print(std::ostream& out) const {
        out << "OrderDeletedMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", order_id=";
        out << order_id();
        out << ", order_deleted_flags=";
        order_deleted_flags().print(out);
        out << ", instrument_id=";
        out << instrument_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDeletedMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
