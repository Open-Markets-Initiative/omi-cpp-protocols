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
#include "../enums/SourceVenue.hpp"
#include "../enums/OrderBookType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Indicates the first order of a given side of an MBO snapshot.
class AddOrderMboMessage {
  public:
    static constexpr const char* name = "AddOrderMboMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMboMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMboMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(8)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    Decimal size() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(17))), -8); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(25)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(33))), -8); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(41).template first<8>(); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(49))); }

    OrderBookType order_book_type() const { return static_cast<OrderBookType>(wire::read_u8(at(51))); }

    std::string_view participant() const { return view::text(at(52), 11, ' '); }

    std::uint8_t depth() const { return wire::read_u8(at(63)); }

    void print(std::ostream& out) const {
        out << "AddOrderMboMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", size=";
        out << size();
        out << ", instrument=";
        out << instrument();
        out << ", price=";
        out << price();
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << ", source_venue=";
        out << source_venue();
        out << ", order_book_type=";
        out << order_book_type();
        out << ", participant=";
        print::text(out, participant());
        out << ", depth=";
        out << static_cast<int>(depth());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderMboMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
