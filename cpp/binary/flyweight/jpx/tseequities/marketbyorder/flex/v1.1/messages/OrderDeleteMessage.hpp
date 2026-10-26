#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../enums/ModificationFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about order deletion from the order book. Delivered when an order is
// deleted via a cancel order or a modification order or when a registered order expires.
class OrderDeleteMessage {
  public:
    static constexpr const char* name = "OrderDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::chrono::microseconds time_microseconds() const { return std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_id() const { return wire::read_u32_be(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(8))); }

    ModificationFlag modification_flag() const { return static_cast<ModificationFlag>(wire::read_u8(at(9))); }

    void print(std::ostream& out) const {
        out << "OrderDeleteMessage{";
        out << "time_microseconds=";
        out << time_microseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", modification_flag=";
        out << modification_flag();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDeleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
