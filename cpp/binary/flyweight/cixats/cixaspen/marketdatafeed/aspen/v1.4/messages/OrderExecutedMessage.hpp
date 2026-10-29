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
#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Sent when an order is executed
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 47;
    static constexpr std::size_t fixed_size = 47;
    std::size_t encoded_size() const { return 47; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(8)); }

    Decimal quantity() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(16))), -6); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(24)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(32))); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(33))), -6); }

    std::string_view broker() const { return view::text(at(41), 3, ' '); }

    std::string_view contra_broker() const { return view::text(at(44), 3, ' '); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", order_id=";
        out << order_id();
        out << ", quantity=";
        out << quantity();
        out << ", execution_id=";
        out << execution_id();
        out << ", side=";
        out << side();
        out << ", price=";
        out << price();
        out << ", broker=";
        print::text(out, broker());
        out << ", contra_broker=";
        print::text(out, contra_broker());
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

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
