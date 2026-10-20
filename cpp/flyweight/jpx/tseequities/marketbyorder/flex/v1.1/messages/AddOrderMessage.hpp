#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OrderCondition.hpp"
#include "../enums/ModificationFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about book registration. Delivered when a new order or modification
// order is registered.
class AddOrderMessage {
  public:
    static constexpr const char* name = "AddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::microseconds time_microseconds() const { return std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_id() const { return wire::read_u32_be(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(8))); }

    std::uint64_t quantity() const { return wire::read_u48_be(at(9)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_u64_be(at(15)), static_cast<std::uint64_t>(18446744073709551615ULL), -4); }

    OrderCondition order_condition() const { return static_cast<OrderCondition>(wire::read_u8(at(23))); }

    ModificationFlag modification_flag() const { return static_cast<ModificationFlag>(wire::read_u8(at(24))); }

    void print(std::ostream& out) const {
        out << "AddOrderMessage{";
        out << "time_microseconds=";
        out << time_microseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", quantity=";
        out << quantity();
        out << ", price=";
        print::optional(out, price());
        out << ", order_condition=";
        out << order_condition();
        out << ", modification_flag=";
        out << modification_flag();
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

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
