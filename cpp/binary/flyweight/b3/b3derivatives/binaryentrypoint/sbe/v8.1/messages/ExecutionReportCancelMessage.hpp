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
#include "../enums/OrdStatus.hpp"
#include "../enums/WorkingIndicator.hpp"
#include "../enums/ExecRestatementReason.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/TimeInForce.hpp"
#include "../common/Decimal.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// ExecutionReport_CancelMessage
class ExecutionReportCancelMessage {
  public:
    static constexpr const char* name = "ExecutionReportCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionReportCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionReportCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 184;
    std::size_t encoded_size() const { return memo_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    Side side() const { return static_cast<Side>(wire::read_char(at(18))); }

    OrdStatus ord_status() const { return static_cast<OrdStatus>(wire::read_char(at(19))); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::uint64_t secondary_order_id() const { return wire::read_u64_le(at(28)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(36)); }

    std::uint64_t cum_qty() const { return wire::read_u64_le(at(44)); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(52)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t exec_id() const { return wire::read_u64_le(at(56)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(64)))); }

    std::optional<std::chrono::nanoseconds> market_segment_received_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(72)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(80)); }

    std::optional<std::uint64_t> origclordid() const { return wire::nullable(wire::read_u64_le(at(88)), static_cast<std::uint64_t>(0ULL)); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(96)); }

    WorkingIndicator working_indicator() const { return static_cast<WorkingIndicator>(wire::read_u8(at(98))); }

    std::optional<ExecRestatementReason> exec_restatement_reason() const { return wire::nullable_enum<ExecRestatementReason>(wire::read_u8(at(99)), static_cast<std::uint8_t>(0ULL)); }

    std::span<const std::byte, 4> offset_100_padding_4() const { return bytes_.subspan(100).template first<4>(); }

    std::optional<std::uint64_t> mass_action_report_id_optional() const { return wire::nullable(wire::read_u64_le(at(104)), static_cast<std::uint64_t>(0ULL)); }

    Ordtype ordtype() const { return static_cast<Ordtype>(wire::read_char(at(112))); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_char(at(113))); }

    std::optional<std::uint16_t> expire_date() const { return wire::nullable(wire::read_u16_le(at(114)), static_cast<std::uint16_t>(0ULL)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(116)); }

    std::optional<Decimal> price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(124)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> stop_px() const { return wire::nullable_decimal(wire::read_i64_le(at(132)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::uint64_t> min_qty() const { return wire::nullable(wire::read_u64_le(at(140)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> max_floor() const { return wire::nullable(wire::read_u64_le(at(148)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> received_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(156)), static_cast<std::uint64_t>(0ULL)); }

    std::span<const std::byte, 3> offset_164_padding_3() const { return bytes_.subspan(164).template first<3>(); }

    std::optional<std::uint8_t> ordtagid() const { return wire::nullable(wire::read_u8(at(167)), static_cast<std::uint8_t>(0ULL)); }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(168) }; }

    std::optional<std::int32_t> strategy_id() const { return wire::nullable(wire::read_i32_le(at(176)), static_cast<std::int32_t>(0LL)); }

    std::optional<std::uint32_t> action_requested_from_session_id() const { return wire::nullable(wire::read_u32_le(at(180)), static_cast<std::uint32_t>(0ULL)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(184) }; }

    Memo memo() const {
        wire::require("ExecutionReportCancelMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "ExecutionReportCancelMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", side=";
        out << side();
        out << ", ord_status=";
        out << ord_status();
        out << ", clordid=";
        out << clordid();
        out << ", secondary_order_id=";
        out << secondary_order_id();
        out << ", security_id=";
        out << security_id();
        out << ", cum_qty=";
        out << cum_qty();
        out << ", account=";
        print::optional(out, account());
        out << ", exec_id=";
        out << exec_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", market_segment_received_time=";
        print::optional_duration(out, market_segment_received_time());
        out << ", order_id=";
        out << order_id();
        out << ", origclordid=";
        print::optional(out, origclordid());
        out << ", trade_date=";
        out << trade_date();
        out << ", working_indicator=";
        out << working_indicator();
        out << ", exec_restatement_reason=";
        print::optional(out, exec_restatement_reason());
        out << ", offset_100_padding_4=";
        print::hex(out, offset_100_padding_4().data(), offset_100_padding_4().size());
        out << ", mass_action_report_id_optional=";
        print::optional(out, mass_action_report_id_optional());
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
        out << ", received_time=";
        print::optional_duration(out, received_time());
        out << ", offset_164_padding_3=";
        print::hex(out, offset_164_padding_3().data(), offset_164_padding_3().size());
        out << ", ordtagid=";
        print::optional(out, ordtagid());
        out << ", investor_id=";
        investor_id().print(out);
        out << ", strategy_id=";
        print::optional(out, strategy_id());
        out << ", action_requested_from_session_id=";
        print::optional(out, action_requested_from_session_id());
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 184 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionReportCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
