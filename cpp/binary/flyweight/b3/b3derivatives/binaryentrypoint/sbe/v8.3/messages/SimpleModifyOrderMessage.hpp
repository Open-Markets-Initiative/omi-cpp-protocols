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
#include "../enums/SimpleOrdtype.hpp"
#include "../enums/TimeInForceSimple.hpp"
#include "../enums/RoutingInstruction.hpp"
#include "../common/Decimal.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// SimpleModifyOrderMessage
class SimpleModifyOrderMessage {
  public:
    static constexpr const char* name = "SimpleModifyOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleModifyOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleModifyOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 100;
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

    SimpleOrdtype simple_ordtype() const { return static_cast<SimpleOrdtype>(wire::read_char(at(57))); }

    TimeInForceSimple time_in_force_simple() const { return static_cast<TimeInForceSimple>(wire::read_char(at(58))); }

    std::optional<RoutingInstruction> routing_instruction() const { return wire::nullable_enum<RoutingInstruction>(wire::read_u8(at(59)), static_cast<std::uint8_t>(0ULL)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(60)); }

    std::optional<Decimal> price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(68)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::uint64_t> order_id_optional() const { return wire::nullable(wire::read_u64_le(at(76)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> origclordid() const { return wire::nullable(wire::read_u64_le(at(84)), static_cast<std::uint64_t>(0ULL)); }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(92) }; }

    Memo memo() const { return Memo{ bytes_.subspan(100) }; }

    void print(std::ostream& out) const {
        out << "SimpleModifyOrderMessage{";
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
        out << ", simple_ordtype=";
        out << simple_ordtype();
        out << ", time_in_force_simple=";
        out << time_in_force_simple();
        out << ", routing_instruction=";
        print::optional(out, routing_instruction());
        out << ", order_qty=";
        out << order_qty();
        out << ", price_optional=";
        print::optional(out, price_optional());
        out << ", order_id_optional=";
        print::optional(out, order_id_optional());
        out << ", origclordid=";
        print::optional(out, origclordid());
        out << ", investor_id=";
        investor_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t memo_end() const { return 100 + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleModifyOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
