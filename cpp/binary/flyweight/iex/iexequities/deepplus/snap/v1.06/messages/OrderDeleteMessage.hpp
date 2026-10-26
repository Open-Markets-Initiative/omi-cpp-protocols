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

namespace iex::iexequities::deepplus::snap::v1_06 {

// A displayed order that was removed from the IEX Book
class OrderDeleteMessage {
  public:
    static constexpr const char* name = "OrderDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    char reserved_1() const { return wire::read_char(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint64_t order_id_reference() const { return wire::read_u64_le(at(17)); }

    void print(std::ostream& out) const {
        out << "OrderDeleteMessage{";
        out << "reserved_1=";
        print::character(out, reserved_1());
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", order_id_reference=";
        out << order_id_reference();
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

} // namespace iex::iexequities::deepplus::snap::v1_06
