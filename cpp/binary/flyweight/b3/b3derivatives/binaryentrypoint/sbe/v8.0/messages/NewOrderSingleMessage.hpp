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
#include "../enums/MmProtectionReset.hpp"
#include "../enums/SelfTradePreventionInstruction.hpp"
#include "../enums/Side.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/TimeInForce.hpp"
#include "../enums/RoutingInstruction.hpp"
#include "../common/Decimal.hpp"
#include "../structs/CustodianInfo.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// NewOrderSingleMessage
class NewOrderSingleMessage {
  public:
    static constexpr const char* name = "NewOrderSingleMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NewOrderSingleMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NewOrderSingleMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 127;
    std::size_t encoded_size() const { return memo_end(); }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::optional<std::uint8_t> ordtagid() const { return wire::nullable(wire::read_u8(at(18)), static_cast<std::uint8_t>(0ULL)); }

    MmProtectionReset mm_protection_reset() const { return static_cast<MmProtectionReset>(wire::read_u8(at(19))); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(28)), static_cast<std::uint32_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(32), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(42), 5, '\0'); }

    SelfTradePreventionInstruction self_trade_prevention_instruction() const { return static_cast<SelfTradePreventionInstruction>(wire::read_u8(at(47))); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(48)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(56))); }

    Ordtype ordtype() const { return static_cast<Ordtype>(wire::read_char(at(57))); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_char(at(58))); }

    std::optional<RoutingInstruction> routing_instruction() const { return wire::nullable_enum<RoutingInstruction>(wire::read_u8(at(59)), static_cast<std::uint8_t>(0ULL)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(60)); }

    std::optional<Decimal> price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(68)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> stop_px() const { return wire::nullable_decimal(wire::read_i64_le(at(76)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::uint64_t> min_qty() const { return wire::nullable(wire::read_u64_le(at(84)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> max_floor() const { return wire::nullable(wire::read_u64_le(at(92)), static_cast<std::uint64_t>(0ULL)); }

    std::string_view executing_trader_optional() const { return view::text(at(100), 5, '\0'); }

    std::optional<std::uint16_t> expire_date() const { return wire::nullable(wire::read_u16_le(at(105)), static_cast<std::uint16_t>(0ULL)); }

    CustodianInfo custodian_info() const { return CustodianInfo{ bytes_.subspan(107) }; }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(119) }; }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(127) }; }

    Memo memo() const {
        wire::require("NewOrderSingleMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "NewOrderSingleMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", ordtagid=";
        print::optional(out, ordtagid());
        out << ", mm_protection_reset=";
        out << mm_protection_reset();
        out << ", clordid=";
        out << clordid();
        out << ", account=";
        print::optional(out, account());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", self_trade_prevention_instruction=";
        out << self_trade_prevention_instruction();
        out << ", security_id=";
        out << security_id();
        out << ", side=";
        out << side();
        out << ", ordtype=";
        out << ordtype();
        out << ", time_in_force=";
        out << time_in_force();
        out << ", routing_instruction=";
        print::optional(out, routing_instruction());
        out << ", order_qty=";
        out << order_qty();
        out << ", price_optional=";
        print::optional(out, price_optional());
        out << ", stop_px=";
        print::optional(out, stop_px());
        out << ", min_qty=";
        print::optional(out, min_qty());
        out << ", max_floor=";
        print::optional(out, max_floor());
        out << ", executing_trader_optional=";
        print::text(out, executing_trader_optional());
        out << ", expire_date=";
        print::optional(out, expire_date());
        out << ", custodian_info=";
        custodian_info().print(out);
        out << ", investor_id=";
        investor_id().print(out);
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 127 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NewOrderSingleMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
