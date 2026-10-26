#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/OrderSide.hpp"
#include "../common/Decimal.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This is the message format that will be used when a displayed order is received and added to
// MIAX Pearl Equities book. It includes an Order ID that is unique to the order across the
// exchange and across trading days.
class AddOrderMessage {
  public:
    static constexpr const char* name = "AddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    static constexpr std::size_t fixed_size = 33;
    std::size_t encoded_size() const { return 33; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_id() const { return wire::read_u32_le(at(4)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(8)); }

    OrderSide order_side() const { return static_cast<OrderSide>(wire::read_char(at(16))); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(17))), -6); }

    std::uint32_t size() const { return wire::read_u32_le(at(25)); }

    std::string_view attributable_id() const { return view::text(at(29), 4, ' '); }

    void print(std::ostream& out) const {
        out << "AddOrderMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", order_id=";
        out << order_id();
        out << ", order_side=";
        out << order_side();
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << ", attributable_id=";
        print::text(out, attributable_id());
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

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
