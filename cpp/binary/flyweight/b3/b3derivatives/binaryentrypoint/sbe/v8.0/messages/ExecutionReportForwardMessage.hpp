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
#include "../enums/SettlTypeOptional.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ExecutionReport_ForwardMessage
class ExecutionReportForwardMessage {
  public:
    static constexpr const char* name = "ExecutionReportForwardMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionReportForwardMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionReportForwardMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 152;
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

    std::uint32_t trade_id() const { return wire::read_u32_le(at(96)); }

    std::uint32_t contra_broker() const { return wire::read_u32_le(at(100)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(104)); }

    AggressorIndicator aggressor_indicator() const { return static_cast<AggressorIndicator>(wire::read_u8(at(112))); }

    SettlTypeOptional settl_type_optional() const { return static_cast<SettlTypeOptional>(wire::read_char(at(113))); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(114)); }

    std::optional<std::uint16_t> days_to_settlement_optional() const { return wire::nullable(wire::read_u16_le(at(116)), static_cast<std::uint16_t>(65535ULL)); }

    std::span<const std::byte, 2> offset_118_padding_2() const { return bytes_.subspan(118).template first<2>(); }

    std::optional<std::uint64_t> secondary_exec_id() const { return wire::nullable(wire::read_u64_le(at(120)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> exec_ref_id() const { return wire::nullable(wire::read_u64_le(at(128)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<Decimal> fixed_rate_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(136)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(144)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(152) }; }

    Memo memo() const {
        wire::require("ExecutionReportForwardMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "ExecutionReportForwardMessage{";
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
        out << ", trade_id=";
        out << trade_id();
        out << ", contra_broker=";
        out << contra_broker();
        out << ", order_id=";
        out << order_id();
        out << ", aggressor_indicator=";
        out << aggressor_indicator();
        out << ", settl_type_optional=";
        out << settl_type_optional();
        out << ", trade_date=";
        out << trade_date();
        out << ", days_to_settlement_optional=";
        print::optional(out, days_to_settlement_optional());
        out << ", offset_118_padding_2=";
        print::hex(out, offset_118_padding_2().data(), offset_118_padding_2().size());
        out << ", secondary_exec_id=";
        print::optional(out, secondary_exec_id());
        out << ", exec_ref_id=";
        print::optional(out, exec_ref_id());
        out << ", fixed_rate_optional=";
        print::optional(out, fixed_rate_optional());
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
    std::size_t desk_id_end() const { return 152 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionReportForwardMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
