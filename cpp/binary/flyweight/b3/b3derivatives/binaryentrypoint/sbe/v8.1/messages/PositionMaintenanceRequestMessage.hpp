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
#include "../enums/PosTransType.hpp"
#include "../enums/ContraryInstructionIndicator.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// PositionMaintenanceRequestMessage
class PositionMaintenanceRequestMessage {
  public:
    static constexpr const char* name = "PositionMaintenanceRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PositionMaintenanceRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PositionMaintenanceRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 73;
    std::size_t encoded_size() const { return memo_end(); }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t pos_req_id() const { return wire::read_u64_le(at(18)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(26)); }

    std::optional<Decimal> threshold_amount() const { return wire::nullable_decimal(wire::read_i64_le(at(34)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(42)), static_cast<std::uint32_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(46), 10, '\0'); }

    PosTransType pos_trans_type() const { return static_cast<PosTransType>(wire::read_u8(at(56))); }

    std::uint16_t clearing_business_date() const { return wire::read_u16_le(at(57)); }

    ContraryInstructionIndicator contrary_instruction_indicator() const { return static_cast<ContraryInstructionIndicator>(wire::read_u8(at(59))); }

    std::string_view entering_trader() const { return view::text(at(60), 5, '\0'); }

    std::uint64_t long_qty() const { return wire::read_u64_le(at(65)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(73) }; }

    Memo memo() const {
        wire::require("PositionMaintenanceRequestMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "PositionMaintenanceRequestMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", pos_req_id=";
        out << pos_req_id();
        out << ", security_id=";
        out << security_id();
        out << ", threshold_amount=";
        print::optional(out, threshold_amount());
        out << ", account=";
        print::optional(out, account());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", pos_trans_type=";
        out << pos_trans_type();
        out << ", clearing_business_date=";
        out << clearing_business_date();
        out << ", contrary_instruction_indicator=";
        out << contrary_instruction_indicator();
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", long_qty=";
        out << long_qty();
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 73 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PositionMaintenanceRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
