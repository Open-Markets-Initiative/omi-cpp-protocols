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

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Relays information on state changes.
class OrderBookStateMessage {
  public:
    static constexpr const char* name = "OrderBookStateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookStateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookStateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(4)); }

    std::string_view state_name() const { return view::text(at(8), 20, ' '); }

    void print(std::ostream& out) const {
        out << "OrderBookStateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", state_name=";
        print::text(out, state_name());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookStateMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
