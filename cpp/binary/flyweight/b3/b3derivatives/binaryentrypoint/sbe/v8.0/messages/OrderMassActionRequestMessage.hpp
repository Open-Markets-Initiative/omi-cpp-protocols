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
#include "../enums/MassActionType.hpp"
#include "../enums/MassActionScope.hpp"
#include "../enums/MassCancelRestatementReason.hpp"
#include "../enums/SideOptional.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// OrderMassActionRequestMessage
class OrderMassActionRequestMessage {
  public:
    static constexpr const char* name = "OrderMassActionRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderMassActionRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderMassActionRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 54;
    static constexpr std::size_t fixed_size = 54;
    std::size_t encoded_size() const { return 54; }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    MassActionType mass_action_type() const { return static_cast<MassActionType>(wire::read_u8(at(18))); }

    std::optional<MassActionScope> mass_action_scope() const { return wire::nullable_enum<MassActionScope>(wire::read_u8(at(19)), static_cast<std::uint8_t>(0ULL)); }

    std::uint64_t clordid() const { return wire::read_u64_le(at(20)); }

    std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason() const { return wire::nullable_enum<MassCancelRestatementReason>(wire::read_u8(at(28)), static_cast<std::uint8_t>(0ULL)); }

    std::optional<std::uint8_t> ordtagid() const { return wire::nullable(wire::read_u8(at(29)), static_cast<std::uint8_t>(0ULL)); }

    SideOptional side_optional() const { return static_cast<SideOptional>(wire::read_char(at(30))); }

    std::span<const std::byte, 1> offset_31_padding_1() const { return bytes_.subspan(31).template first<1>(); }

    std::string_view asset() const { return view::text(at(32), 6, '\0'); }

    std::optional<std::uint64_t> security_id_optional() const { return wire::nullable(wire::read_u64_le(at(38)), static_cast<std::uint64_t>(0ULL)); }

    InvestorId investor_id() const { return InvestorId{ bytes_.subspan(46) }; }

    void print(std::ostream& out) const {
        out << "OrderMassActionRequestMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", mass_action_type=";
        out << mass_action_type();
        out << ", mass_action_scope=";
        print::optional(out, mass_action_scope());
        out << ", clordid=";
        out << clordid();
        out << ", mass_cancel_restatement_reason=";
        print::optional(out, mass_cancel_restatement_reason());
        out << ", ordtagid=";
        print::optional(out, ordtagid());
        out << ", side_optional=";
        out << side_optional();
        out << ", offset_31_padding_1=";
        print::hex(out, offset_31_padding_1().data(), offset_31_padding_1().size());
        out << ", asset=";
        print::text(out, asset());
        out << ", security_id_optional=";
        print::optional(out, security_id_optional());
        out << ", investor_id=";
        investor_id().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderMassActionRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
