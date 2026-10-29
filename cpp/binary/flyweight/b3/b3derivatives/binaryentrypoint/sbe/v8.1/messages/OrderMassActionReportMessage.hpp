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
#include "../enums/MassActionType.hpp"
#include "../enums/MassActionScope.hpp"
#include "../enums/MassActionResponse.hpp"
#include "../enums/MassActionRejectReason.hpp"
#include "../enums/MassCancelRestatementReason.hpp"
#include "../enums/SideOptional.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// OrderMassActionReportMessage
class OrderMassActionReportMessage {
  public:
    static constexpr const char* name = "OrderMassActionReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderMassActionReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderMassActionReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 72;
    std::size_t encoded_size() const { return text_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    MassActionType mass_action_type() const { return static_cast<MassActionType>(wire::read_u8(at(18))); }

    std::optional<MassActionScope> mass_action_scope() const { return wire::nullable_enum<MassActionScope>(wire::read_u8(at(19)), static_cast<std::uint8_t>(0ULL)); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::uint64_t mass_action_report_id() const { return wire::read_u64_le(at(28)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(36)))); }

    MassActionResponse mass_action_response() const { return static_cast<MassActionResponse>(wire::read_char(at(44))); }

    std::optional<MassActionRejectReason> mass_action_reject_reason() const { return wire::nullable_enum<MassActionRejectReason>(wire::read_u8(at(45)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason() const { return wire::nullable_enum<MassCancelRestatementReason>(wire::read_u8(at(46)), static_cast<std::uint8_t>(0ULL)); }

    std::optional<std::uint8_t> ordtagid() const { return wire::nullable(wire::read_u8(at(47)), static_cast<std::uint8_t>(0ULL)); }

    SideOptional side_optional() const { return static_cast<SideOptional>(wire::read_char(at(48))); }

    std::span<const std::byte, 1> offset_49_padding_1() const { return bytes_.subspan(49).template first<1>(); }

    std::string_view asset() const { return view::text(at(50), 6, '\0'); }

    std::optional<std::uint64_t> security_id_optional() const { return wire::nullable(wire::read_u64_le(at(56)), static_cast<std::uint64_t>(0ULL)); }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(64) }; }

    Text text() const { return Text{ bytes_.subspan(72) }; }

    void print(std::ostream& out) const {
        out << "OrderMassActionReportMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", mass_action_type=";
        out << mass_action_type();
        out << ", mass_action_scope=";
        print::optional(out, mass_action_scope());
        out << ", clordid=";
        out << clordid();
        out << ", mass_action_report_id=";
        out << mass_action_report_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", mass_action_response=";
        out << mass_action_response();
        out << ", mass_action_reject_reason=";
        print::optional(out, mass_action_reject_reason());
        out << ", mass_cancel_restatement_reason=";
        print::optional(out, mass_cancel_restatement_reason());
        out << ", ordtagid=";
        print::optional(out, ordtagid());
        out << ", side_optional=";
        out << side_optional();
        out << ", offset_49_padding_1=";
        print::hex(out, offset_49_padding_1().data(), offset_49_padding_1().size());
        out << ", asset=";
        print::text(out, asset());
        out << ", security_id_optional=";
        print::optional(out, security_id_optional());
        out << ", investor_id=";
        investor_id().print(out);
        out << ", text=";
        text().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t text_end() const { return 72 + text().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderMassActionReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
