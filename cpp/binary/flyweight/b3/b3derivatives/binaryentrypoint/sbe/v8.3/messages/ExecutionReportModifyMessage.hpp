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
#include "../common/Decimal.hpp"
#include "../enums/WorkingIndicator.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/TimeInForce.hpp"
#include "../structs/InvestorId.hpp"
#include "../enums/MmProtectionResetOptional.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// ExecutionReport_ModifyMessage
class ExecutionReportModifyMessage {
  public:
    static constexpr const char* name = "ExecutionReportModifyMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionReportModifyMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionReportModifyMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 190;
    std::size_t encoded_size() const { return memo_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    Side side() const { return static_cast<Side>(wire::read_char(at(18))); }

    OrdStatus ord_status() const { return static_cast<OrdStatus>(wire::read_char(at(19))); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::uint64_t secondary_order_id() const { return wire::read_u64_le(at(28)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(36)); }

    std::uint64_t leaves_qty() const { return wire::read_u64_le(at(44)); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(52)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t exec_id() const { return wire::read_u64_le(at(56)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(64)))); }

    std::uint64_t cum_qty() const { return wire::read_u64_le(at(72)); }

    std::optional<std::chrono::nanoseconds> market_segment_received_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(80)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(88)); }

    std::optional<std::uint64_t> origclordid() const { return wire::nullable(wire::read_u64_le(at(96)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<Decimal> protection_price() const { return wire::nullable_decimal(wire::read_i64_le(at(104)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(112)); }

    WorkingIndicator working_indicator() const { return static_cast<WorkingIndicator>(wire::read_u8(at(114))); }

    MultiLegReportingType multi_leg_reporting_type() const { return static_cast<MultiLegReportingType>(wire::read_char(at(115))); }

    Ordtype ordtype() const { return static_cast<Ordtype>(wire::read_char(at(116))); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_char(at(117))); }

    std::optional<std::uint16_t> expire_date() const { return wire::nullable(wire::read_u16_le(at(118)), static_cast<std::uint16_t>(0ULL)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(120)); }

    std::optional<Decimal> price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(128)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> stop_px() const { return wire::nullable_decimal(wire::read_i64_le(at(136)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::uint64_t> min_qty() const { return wire::nullable(wire::read_u64_le(at(144)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> max_floor() const { return wire::nullable(wire::read_u64_le(at(152)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> received_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(160)), static_cast<std::uint64_t>(0ULL)); }

    std::span<const std::byte, 3> offset_168_padding_3() const { return bytes_.subspan(168).template first<3>(); }

    std::optional<std::uint8_t> ordtagid() const { return wire::nullable(wire::read_u8(at(171)), static_cast<std::uint8_t>(0ULL)); }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(172) }; }

    std::optional<MmProtectionResetOptional> mm_protection_reset_optional() const { return wire::nullable_enum<MmProtectionResetOptional>(wire::read_u8(at(180)), static_cast<std::uint8_t>(255ULL)); }

    std::span<const std::byte, 1> offset_181_padding_1() const { return bytes_.subspan(181).template first<1>(); }

    std::optional<std::int32_t> strategy_id() const { return wire::nullable(wire::read_i32_le(at(182)), static_cast<std::int32_t>(0LL)); }

    std::optional<std::uint32_t> trading_sub_account() const { return wire::nullable(wire::read_u32_le(at(186)), static_cast<std::uint32_t>(0ULL)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(190) }; }

    Memo memo() const {
        wire::require("ExecutionReportModifyMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "ExecutionReportModifyMessage{";
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
        out << ", leaves_qty=";
        out << leaves_qty();
        out << ", account=";
        print::optional(out, account());
        out << ", exec_id=";
        out << exec_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", cum_qty=";
        out << cum_qty();
        out << ", market_segment_received_time=";
        print::optional_duration(out, market_segment_received_time());
        out << ", order_id=";
        out << order_id();
        out << ", origclordid=";
        print::optional(out, origclordid());
        out << ", protection_price=";
        print::optional(out, protection_price());
        out << ", trade_date=";
        out << trade_date();
        out << ", working_indicator=";
        out << working_indicator();
        out << ", multi_leg_reporting_type=";
        out << multi_leg_reporting_type();
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
        out << ", offset_168_padding_3=";
        print::hex(out, offset_168_padding_3().data(), offset_168_padding_3().size());
        out << ", ordtagid=";
        print::optional(out, ordtagid());
        out << ", investor_id=";
        investor_id().print(out);
        out << ", mm_protection_reset_optional=";
        print::optional(out, mm_protection_reset_optional());
        out << ", offset_181_padding_1=";
        print::hex(out, offset_181_padding_1().data(), offset_181_padding_1().size());
        out << ", strategy_id=";
        print::optional(out, strategy_id());
        out << ", trading_sub_account=";
        print::optional(out, trading_sub_account());
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 190 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionReportModifyMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
