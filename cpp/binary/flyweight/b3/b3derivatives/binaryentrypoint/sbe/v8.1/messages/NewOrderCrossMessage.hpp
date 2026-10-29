#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossedIndicator.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/CrossPrioritization.hpp"
#include "../structs/CrossSidesGroups.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// NewOrderCrossMessage
class NewOrderCrossMessage {
  public:
    static constexpr const char* name = "NewOrderCrossMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NewOrderCrossMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NewOrderCrossMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 84;
    std::size_t encoded_size() const { return memo_end(); }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::span<const std::byte, 2> offset_18_padding_2() const { return bytes_.subspan(18).template first<2>(); }

    std::uint64_t crossid() const { return wire::read_u64_le(at(20)); }

    std::string_view sender_location() const { return view::text(at(28), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(38), 5, '\0'); }

    std::string_view executing_trader_optional() const { return view::text(at(43), 5, '\0'); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(48)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(56)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(64))), -4); }

    std::optional<CrossedIndicator> crossed_indicator() const { return wire::nullable_enum<CrossedIndicator>(wire::read_u16_le(at(72)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<CrossType> cross_type() const { return wire::nullable_enum<CrossType>(wire::read_u8(at(74)), static_cast<std::uint8_t>(0ULL)); }

    std::optional<CrossPrioritization> cross_prioritization() const { return wire::nullable_enum<CrossPrioritization>(wire::read_u8(at(75)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint64_t> max_sweep_qty() const { return wire::nullable(wire::read_u64_le(at(76)), static_cast<std::uint64_t>(0ULL)); }

    CrossSidesGroups cross_sides_groups() const { return CrossSidesGroups{ bytes_.subspan(84) }; }

    DeskId desk_id() const {
        wire::require("NewOrderCrossMessage", cross_sides_groups_end() + DeskId::minimum_size, bytes_.size());
        return DeskId{ bytes_.subspan(cross_sides_groups_end()) };
    }

    Memo memo() const {
        wire::require("NewOrderCrossMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "NewOrderCrossMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", offset_18_padding_2=";
        print::hex(out, offset_18_padding_2().data(), offset_18_padding_2().size());
        out << ", crossid=";
        out << crossid();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", executing_trader_optional=";
        print::text(out, executing_trader_optional());
        out << ", security_id=";
        out << security_id();
        out << ", order_qty=";
        out << order_qty();
        out << ", price=";
        out << price();
        out << ", crossed_indicator=";
        print::optional(out, crossed_indicator());
        out << ", cross_type=";
        print::optional(out, cross_type());
        out << ", cross_prioritization=";
        print::optional(out, cross_prioritization());
        out << ", max_sweep_qty=";
        print::optional(out, max_sweep_qty());
        out << ", cross_sides_groups=";
        cross_sides_groups().print(out);
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t cross_sides_groups_end() const { return 84 + cross_sides_groups().encoded_size(); }
    std::size_t desk_id_end() const { return cross_sides_groups_end() + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NewOrderCrossMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
