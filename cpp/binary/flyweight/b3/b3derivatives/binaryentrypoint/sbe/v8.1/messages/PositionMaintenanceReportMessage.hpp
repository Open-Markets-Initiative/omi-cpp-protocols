#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../enums/PosTransType.hpp"
#include "../enums/PosMaintAction.hpp"
#include "../enums/PosMaintStatus.hpp"
#include "../enums/AccountType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ContraryInstructionIndicator.hpp"
#include "../structs/PositionsGroups.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// PositionMaintenanceReportMessage
class PositionMaintenanceReportMessage {
  public:
    static constexpr const char* name = "PositionMaintenanceReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PositionMaintenanceReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PositionMaintenanceReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 95;
    std::size_t encoded_size() const { return text_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    std::optional<std::uint64_t> pos_req_id_optional() const { return wire::nullable(wire::read_u64_le(at(18)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(26)); }

    std::uint64_t pos_maint_rpt_id() const { return wire::read_u64_le(at(34)); }

    PosTransType pos_trans_type() const { return static_cast<PosTransType>(wire::read_u8(at(42))); }

    PosMaintAction pos_maint_action() const { return static_cast<PosMaintAction>(wire::read_char(at(43))); }

    PosMaintStatus pos_maint_status() const { return static_cast<PosMaintStatus>(wire::read_char(at(44))); }

    std::optional<std::uint32_t> trade_id_optional() const { return wire::nullable(wire::read_u32_le(at(45)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint64_t> orig_pos_req_ref_id() const { return wire::nullable(wire::read_u64_le(at(49)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<AccountType> account_type() const { return wire::nullable_enum<AccountType>(wire::read_u8(at(57)), static_cast<std::uint8_t>(0ULL)); }

    std::uint16_t clearing_business_date() const { return wire::read_u16_le(at(58)); }

    std::optional<Decimal> threshold_amount() const { return wire::nullable_decimal(wire::read_i64_le(at(60)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(68)))); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(76)), static_cast<std::uint32_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(80), 10, '\0'); }

    std::optional<std::uint32_t> pos_maint_result() const { return wire::nullable(wire::read_u32_le(at(90)), static_cast<std::uint32_t>(0ULL)); }

    ContraryInstructionIndicator contrary_instruction_indicator() const { return static_cast<ContraryInstructionIndicator>(wire::read_u8(at(94))); }

    PositionsGroups positions_groups() const { return PositionsGroups{ bytes_.subspan(95) }; }

    DeskId desk_id() const {
        wire::require("PositionMaintenanceReportMessage", positions_groups_end() + DeskId::minimum_size, bytes_.size());
        return DeskId{ bytes_.subspan(positions_groups_end()) };
    }

    Memo memo() const {
        wire::require("PositionMaintenanceReportMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    Text text() const {
        wire::require("PositionMaintenanceReportMessage", memo_end() + Text::minimum_size, bytes_.size());
        return Text{ bytes_.subspan(memo_end()) };
    }

    void print(std::ostream& out) const {
        out << "PositionMaintenanceReportMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", pos_req_id_optional=";
        print::optional(out, pos_req_id_optional());
        out << ", security_id=";
        out << security_id();
        out << ", pos_maint_rpt_id=";
        out << pos_maint_rpt_id();
        out << ", pos_trans_type=";
        out << pos_trans_type();
        out << ", pos_maint_action=";
        out << pos_maint_action();
        out << ", pos_maint_status=";
        out << pos_maint_status();
        out << ", trade_id_optional=";
        print::optional(out, trade_id_optional());
        out << ", orig_pos_req_ref_id=";
        print::optional(out, orig_pos_req_ref_id());
        out << ", account_type=";
        print::optional(out, account_type());
        out << ", clearing_business_date=";
        out << clearing_business_date();
        out << ", threshold_amount=";
        print::optional(out, threshold_amount());
        out << ", transact_time=";
        out << transact_time().count();
        out << ", account=";
        print::optional(out, account());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", pos_maint_result=";
        print::optional(out, pos_maint_result());
        out << ", contrary_instruction_indicator=";
        out << contrary_instruction_indicator();
        out << ", positions_groups=";
        positions_groups().print(out);
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
    std::size_t positions_groups_end() const { return 95 + positions_groups().encoded_size(); }
    std::size_t desk_id_end() const { return positions_groups_end() + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }
    std::size_t text_end() const { return memo_end() + text().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PositionMaintenanceReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
