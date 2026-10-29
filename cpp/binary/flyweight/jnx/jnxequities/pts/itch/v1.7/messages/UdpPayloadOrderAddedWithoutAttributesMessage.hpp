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
#include "../enums/BuySellIndicator.hpp"
#include "../enums/Group.hpp"
#include "../common/Decimal.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// Order Added Message will be generated for normal orders accepted by the system.
class UdpPayloadOrderAddedWithoutAttributesMessage {
  public:
    static constexpr const char* name = "UdpPayloadOrderAddedWithoutAttributesMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UdpPayloadOrderAddedWithoutAttributesMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UdpPayloadOrderAddedWithoutAttributesMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_number() const { return wire::read_u64_be(at(4)); }

    BuySellIndicator buy_sell_indicator() const { return static_cast<BuySellIndicator>(wire::read_char(at(12))); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(13)); }

    std::uint32_t orderbook_id() const { return wire::read_u32_be(at(17)); }

    std::string_view group() const { return view::text(at(21), 4, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(25))), -1); }

    void print(std::ostream& out) const {
        out << "UdpPayloadOrderAddedWithoutAttributesMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_number=";
        out << order_number();
        out << ", buy_sell_indicator=";
        out << buy_sell_indicator();
        out << ", quantity=";
        out << quantity();
        out << ", orderbook_id=";
        out << orderbook_id();
        out << ", group=";
        print::text(out, group());
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UdpPayloadOrderAddedWithoutAttributesMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_7
