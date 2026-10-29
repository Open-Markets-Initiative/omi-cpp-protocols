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
#include "../enums/Group.hpp"
#include "../common/Decimal.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// Orderbook Directory Messages provide information about orderbooks available in the Japannext
// PTS execution system.
class UdpPayloadOrderbookDirectoryMessage {
  public:
    static constexpr const char* name = "UdpPayloadOrderbookDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadOrderbookDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadOrderbookDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t orderbook_id() const { return wire::read_u32_be(at(4)); }

    std::string_view orderbook_code() const { return view::text(at(8), 12, ' '); }

    std::string_view group() const { return view::text(at(20), 4, ' '); }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(24)); }

    std::uint32_t price_tick_size_table_id() const { return wire::read_u32_be(at(28)); }

    std::uint32_t price_decimals() const { return wire::read_u32_be(at(32)); }

    Decimal upper_price_limit() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(36))), -1); }

    Decimal lower_price_limit() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(40))), -1); }

    void print(std::ostream& out) const {
        out << "UdpPayloadOrderbookDirectoryMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", orderbook_id=";
        out << orderbook_id();
        out << ", orderbook_code=";
        print::text(out, orderbook_code());
        out << ", group=";
        print::text(out, group());
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", price_tick_size_table_id=";
        out << price_tick_size_table_id();
        out << ", price_decimals=";
        out << price_decimals();
        out << ", upper_price_limit=";
        out << upper_price_limit();
        out << ", lower_price_limit=";
        out << lower_price_limit();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadOrderbookDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_7
