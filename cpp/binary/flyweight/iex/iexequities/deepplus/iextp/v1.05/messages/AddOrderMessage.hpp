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
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

// A displayed order that has been added to the IEX Book
class AddOrderMessage {
  public:
    static constexpr const char* name = "AddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    static constexpr std::size_t fixed_size = 37;
    std::size_t encoded_size() const { return 37; }

    Side side() const { return static_cast<Side>(wire::read_char(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(17)); }

    std::uint32_t size() const { return wire::read_u32_le(at(25)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(29))), -4); }

    void print(std::ostream& out) const {
        out << "AddOrderMessage{";
        out << "side=";
        out << side();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", order_id=";
        out << order_id();
        out << ", size=";
        out << size();
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

} // namespace iex::iexequities::deepplus::iextp::v1_05
