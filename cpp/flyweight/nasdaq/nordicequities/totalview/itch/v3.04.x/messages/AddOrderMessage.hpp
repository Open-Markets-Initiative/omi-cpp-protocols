#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/BuySellIndicator.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// An order added to the book without Mpid attribution
class AddOrderMessage {
  public:
    static constexpr const char* name = "AddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 31;
    static constexpr std::size_t fixed_size = 31;
    std::size_t encoded_size() const { return 31; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(10)); }

    BuySellIndicator buy_sell_indicator() const { return static_cast<BuySellIndicator>(wire::read_char(at(18))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(19)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(23)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(27))), -4); }

    void print(std::ostream& out) const {
        out << "AddOrderMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", buy_sell_indicator=";
        out << buy_sell_indicator();
        out << ", quantity=";
        out << quantity();
        out << ", order_book=";
        out << order_book();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
