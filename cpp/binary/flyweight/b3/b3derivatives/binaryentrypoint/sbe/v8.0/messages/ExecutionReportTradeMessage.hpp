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
#include "../enums/AggressorIndicator.hpp"
#include "../enums/ExecType.hpp"
#include "../enums/OrderCategory.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/CrossedIndicator.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ExecutionReport_TradeMessage
class ExecutionReportTradeMessage {
  public:
    static constexpr const char* name = "ExecutionReportTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionReportTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionReportTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 154;
    std::size_t encoded_size() const { return memo_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    Side side() const { return static_cast<Side>(wire::read_char(at(18))); }

    OrdStatus ord_status() const { return static_cast<OrdStatus>(wire::read_char(at(19))); }

    std::optional<std::uint64_t> clordid_optional() const { return wire::nullable(wire::read_u64_le(at(20)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t secondary_order_id() const { return wire::read_u64_le(at(28)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(36)); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(44)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t last_qty() const { return wire::read_u64_le(at(48)); }

    Decimal last_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(56))), -4); }

    std::uint64_t exec_id() const { return wire::read_u64_le(at(64)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(72)))); }

    std::uint64_t leaves_qty() const { return wire::read_u64_le(at(80)); }

    std::uint64_t cum_qty() const { return wire::read_u64_le(at(88)); }

    AggressorIndicator aggressor_indicator() const { return static_cast<AggressorIndicator>(wire::read_u8(at(96))); }

    ExecType exec_type() const { return static_cast<ExecType>(wire::read_char(at(97))); }

    OrderCategory order_category() const { return static_cast<OrderCategory>(wire::read_char(at(98))); }

    MultiLegReportingType multi_leg_reporting_type() const { return static_cast<MultiLegReportingType>(wire::read_char(at(99))); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(100)); }

    std::uint32_t contra_broker() const { return wire::read_u32_le(at(104)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(108)); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(116)); }

    std::optional<std::uint8_t> tot_no_related_sym() const { return wire::nullable(wire::read_u8(at(118)), static_cast<std::uint8_t>(0ULL)); }

    std::span<const std::byte, 1> offset_119_padding_1() const { return bytes_.subspan(119).template first<1>(); }

    std::optional<std::uint64_t> secondary_exec_id() const { return wire::nullable(wire::read_u64_le(at(120)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> exec_ref_id() const { return wire::nullable(wire::read_u64_le(at(128)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> crossid_optional() const { return wire::nullable(wire::read_u64_le(at(136)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<CrossedIndicator> crossed_indicator() const { return wire::nullable_enum<CrossedIndicator>(wire::read_u16_le(at(144)), static_cast<std::uint16_t>(0ULL)); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(146)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(154) }; }

    Memo memo() const {
        wire::require("ExecutionReportTradeMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "ExecutionReportTradeMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", side=";
        out << side();
        out << ", ord_status=";
        out << ord_status();
        out << ", clordid_optional=";
        print::optional(out, clordid_optional());
        out << ", secondary_order_id=";
        out << secondary_order_id();
        out << ", security_id=";
        out << security_id();
        out << ", account=";
        print::optional(out, account());
        out << ", last_qty=";
        out << last_qty();
        out << ", last_px=";
        out << last_px();
        out << ", exec_id=";
        out << exec_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", leaves_qty=";
        out << leaves_qty();
        out << ", cum_qty=";
        out << cum_qty();
        out << ", aggressor_indicator=";
        out << aggressor_indicator();
        out << ", exec_type=";
        out << exec_type();
        out << ", order_category=";
        out << order_category();
        out << ", multi_leg_reporting_type=";
        out << multi_leg_reporting_type();
        out << ", trade_id=";
        out << trade_id();
        out << ", contra_broker=";
        out << contra_broker();
        out << ", order_id=";
        out << order_id();
        out << ", trade_date=";
        out << trade_date();
        out << ", tot_no_related_sym=";
        print::optional(out, tot_no_related_sym());
        out << ", offset_119_padding_1=";
        print::hex(out, offset_119_padding_1().data(), offset_119_padding_1().size());
        out << ", secondary_exec_id=";
        print::optional(out, secondary_exec_id());
        out << ", exec_ref_id=";
        print::optional(out, exec_ref_id());
        out << ", crossid_optional=";
        print::optional(out, crossid_optional());
        out << ", crossed_indicator=";
        print::optional(out, crossed_indicator());
        out << ", order_qty=";
        out << order_qty();
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 154 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionReportTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
