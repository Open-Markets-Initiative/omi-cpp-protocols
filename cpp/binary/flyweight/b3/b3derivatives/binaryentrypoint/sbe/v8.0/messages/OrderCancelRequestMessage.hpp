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
#include "../enums/Side.hpp"
#include "../enums/SingleCancelRestatementReason.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// OrderCancelRequestMessage
class OrderCancelRequestMessage {
  public:
    static constexpr const char* name = "OrderCancelRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderCancelRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderCancelRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 76;
    std::size_t encoded_size() const { return memo_end(); }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::span<const std::byte, 2> offset_18_padding_2() const { return bytes_.subspan(18).template first<2>(); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(28)); }

    std::optional<std::uint64_t> order_id_optional() const { return wire::nullable(wire::read_u64_le(at(36)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> origclordid() const { return wire::nullable(wire::read_u64_le(at(44)), static_cast<std::uint64_t>(0ULL)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(52))); }

    std::optional<SingleCancelRestatementReason> single_cancel_restatement_reason() const { return wire::nullable_enum<SingleCancelRestatementReason>(wire::read_u8(at(53)), static_cast<std::uint8_t>(0ULL)); }

    std::span<const std::byte, 2> offset_54_padding_2() const { return bytes_.subspan(54).template first<2>(); }

    std::string_view sender_location() const { return view::text(at(56), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(66), 5, '\0'); }

    std::string_view executing_trader_optional() const { return view::text(at(71), 5, '\0'); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(76) }; }

    Memo memo() const {
        wire::require("OrderCancelRequestMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "OrderCancelRequestMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", offset_18_padding_2=";
        print::hex(out, offset_18_padding_2().data(), offset_18_padding_2().size());
        out << ", clordid=";
        out << clordid();
        out << ", security_id=";
        out << security_id();
        out << ", order_id_optional=";
        print::optional(out, order_id_optional());
        out << ", origclordid=";
        print::optional(out, origclordid());
        out << ", side=";
        out << side();
        out << ", single_cancel_restatement_reason=";
        print::optional(out, single_cancel_restatement_reason());
        out << ", offset_54_padding_2=";
        print::hex(out, offset_54_padding_2().data(), offset_54_padding_2().size());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", executing_trader_optional=";
        print::text(out, executing_trader_optional());
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 76 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderCancelRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
