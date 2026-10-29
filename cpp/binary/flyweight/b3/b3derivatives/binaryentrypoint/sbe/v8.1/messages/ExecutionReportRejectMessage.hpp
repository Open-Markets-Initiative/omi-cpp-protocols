#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../enums/Side.hpp"
#include "../enums/CxlRejResponseTo.hpp"
#include "../enums/OrdRejReason.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/TimeInForce.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossedIndicator.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// ExecutionReport_RejectMessage
class ExecutionReportRejectMessage {
  public:
    static constexpr const char* name = "ExecutionReportRejectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionReportRejectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionReportRejectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 162;
    std::size_t encoded_size() const { return text_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    Side side() const { return static_cast<Side>(wire::read_char(at(18))); }

    CxlRejResponseTo cxl_rej_response_to() const { return static_cast<CxlRejResponseTo>(wire::read_u8(at(19))); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::optional<std::uint64_t> secondary_order_id_optional() const { return wire::nullable(wire::read_u64_le(at(28)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(36)); }

    OrdRejReason ord_rej_reason() const { return static_cast<OrdRejReason>(wire::read_u32_le(at(44))); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(48)))); }

    std::uint64_t exec_id() const { return wire::read_u64_le(at(56)); }

    std::optional<std::uint64_t> order_id_optional() const { return wire::nullable(wire::read_u64_le(at(64)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> origclordid() const { return wire::nullable(wire::read_u64_le(at(72)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(80)), static_cast<std::uint32_t>(0ULL)); }

    Ordtype ordtype() const { return static_cast<Ordtype>(wire::read_char(at(84))); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_char(at(85))); }

    std::optional<std::uint16_t> expire_date() const { return wire::nullable(wire::read_u16_le(at(86)), static_cast<std::uint16_t>(0ULL)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(88)); }

    std::optional<Decimal> price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(96)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> stop_px() const { return wire::nullable_decimal(wire::read_i64_le(at(104)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::uint64_t> min_qty() const { return wire::nullable(wire::read_u64_le(at(112)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> max_floor() const { return wire::nullable(wire::read_u64_le(at(120)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> crossid_optional() const { return wire::nullable(wire::read_u64_le(at(128)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<CrossedIndicator> crossed_indicator() const { return wire::nullable_enum<CrossedIndicator>(wire::read_u16_le(at(136)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> received_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(138)), static_cast<std::uint64_t>(0ULL)); }

    std::span<const std::byte, 3> offset_146_padding_3() const { return bytes_.subspan(146).template first<3>(); }

    std::optional<std::uint8_t> ordtagid() const { return wire::nullable(wire::read_u8(at(149)), static_cast<std::uint8_t>(0ULL)); }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(150) }; }

    std::optional<std::int32_t> strategy_id() const { return wire::nullable(wire::read_i32_le(at(158)), static_cast<std::int32_t>(0LL)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(162) }; }

    Memo memo() const {
        wire::require("ExecutionReportRejectMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    Text text() const {
        wire::require("ExecutionReportRejectMessage", memo_end() + Text::minimum_size, bytes_.size());
        return Text{ bytes_.subspan(memo_end()) };
    }

    void print(std::ostream& out) const {
        out << "ExecutionReportRejectMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", side=";
        out << side();
        out << ", cxl_rej_response_to=";
        out << cxl_rej_response_to();
        out << ", clordid=";
        out << clordid();
        out << ", secondary_order_id_optional=";
        print::optional(out, secondary_order_id_optional());
        out << ", security_id=";
        out << security_id();
        out << ", ord_rej_reason=";
        out << ord_rej_reason();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", exec_id=";
        out << exec_id();
        out << ", order_id_optional=";
        print::optional(out, order_id_optional());
        out << ", origclordid=";
        print::optional(out, origclordid());
        out << ", account=";
        print::optional(out, account());
        out << ", ordtype=";
        out << ordtype();
        out << ", time_in_force=";
        out << time_in_force();
        out << ", expire_date=";
        print::optional(out, expire_date());
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
        out << ", crossid_optional=";
        print::optional(out, crossid_optional());
        out << ", crossed_indicator=";
        print::optional(out, crossed_indicator());
        out << ", received_time=";
        print::optional_duration(out, received_time());
        out << ", offset_146_padding_3=";
        print::hex(out, offset_146_padding_3().data(), offset_146_padding_3().size());
        out << ", ordtagid=";
        print::optional(out, ordtagid());
        out << ", investor_id=";
        investor_id().print(out);
        out << ", strategy_id=";
        print::optional(out, strategy_id());
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << ", text=";
        text().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 162 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }
    std::size_t text_end() const { return memo_end() + text().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionReportRejectMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
