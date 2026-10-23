#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Printable.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Sent if a displayed order is fully or partially filled at a price that is different from its
// displayed price.
class OrderExecutedWithPriceSizeMessage {
  public:
    static constexpr const char* name = "OrderExecutedWithPriceSizeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedWithPriceSizeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedWithPriceSizeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    static constexpr std::size_t fixed_size = 37;
    std::size_t encoded_size() const { return 37; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_le(at(12)); }

    std::uint32_t display_quantity() const { return wire::read_u32_le(at(16)); }

    std::uint64_t trade_match_id() const { return wire::read_u64_le(at(20)); }

    Printable printable() const { return static_cast<Printable>(wire::read_char(at(28))); }

    std::int64_t price() const { return wire::read_i64_le(at(29)); }

    void print(std::ostream& out) const {
        out << "OrderExecutedWithPriceSizeMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", order_id=";
        out << order_id();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", display_quantity=";
        out << display_quantity();
        out << ", trade_match_id=";
        out << trade_match_id();
        out << ", printable=";
        out << printable();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedWithPriceSizeMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
