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

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about registered orders in case of Zaraba execution. Delivered when an
// execution occurs in Zaraba.
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 19;
    static constexpr std::size_t fixed_size = 19;
    std::size_t encoded_size() const { return 19; }

    std::chrono::microseconds time_microseconds() const { return std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_id() const { return wire::read_u32_be(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(8))); }

    std::uint64_t volume() const { return wire::read_u48_be(at(9)); }

    std::uint32_t match_id() const { return wire::read_u32_be(at(15)); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
        out << "time_microseconds=";
        out << time_microseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", volume=";
        out << volume();
        out << ", match_id=";
        out << match_id();
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

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
