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

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// An order on the book has been cancel replaced
class OrderReplaceMessage {
  public:
    static constexpr const char* name = "OrderReplaceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderReplaceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderReplaceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t original_order_reference_number() const { return wire::read_u64_be(at(10)); }

    std::uint64_t new_order_reference_number() const { return wire::read_u64_be(at(18)); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(26)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(30))), -4); }

    void print(std::ostream& out) const {
        out << "OrderReplaceMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", original_order_reference_number=";
        out << original_order_reference_number();
        out << ", new_order_reference_number=";
        out << new_order_reference_number();
        out << ", quantity=";
        out << quantity();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderReplaceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
