#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/OrderModifiedFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates that the displayed quantity or price of a displayed order has been updated.
class OrderModifiedMessage {
  public:
    static constexpr const char* name = "OrderModifiedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderModifiedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderModifiedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint32_t new_quantity() const { return wire::read_u32_le(at(12)); }

    std::int64_t new_price() const { return wire::read_i64_le(at(16)); }

    OrderModifiedFlags order_modified_flags() const { return OrderModifiedFlags{ bytes_.subspan(24) }; }

    void print(std::ostream& out) const {
        out << "OrderModifiedMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", order_id=";
        out << order_id();
        out << ", new_quantity=";
        out << new_quantity();
        out << ", new_price=";
        out << new_price();
        out << ", order_modified_flags=";
        order_modified_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderModifiedMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
