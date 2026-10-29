#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MassActionScope.hpp"
#include "../enums/MassActionType.hpp"
#include "../enums/MassCancelRestatementReason.hpp"
#include "../enums/SideOptional.hpp"
#include "../messages/Message.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// OrderMassActionRequestMessage
class OrderMassActionRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderMassActionRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 54;

    OrderMassActionRequestMessage() = default;
    OrderMassActionRequestMessage(const InboundBusinessHeader& inbound_business_header, MassActionType mass_action_type, std::optional<MassActionScope> mass_action_scope, std::uint64_t clordid, std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason, std::optional<std::uint8_t> ordtagid, SideOptional side_optional, const std::array<std::byte, 1>& offset_31_padding_1, const std::string& asset, std::optional<std::uint64_t> security_id_optional, const InvestorId& investor_id);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // Mass Action Type: massActionType
    MassActionType mass_action_type() const;
    void set_mass_action_type(MassActionType value);

    // Mass Action Scope: massActionScope
    std::optional<MassActionScope> mass_action_scope() const;
    void set_mass_action_scope(std::optional<MassActionScope> value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Mass Cancel Restatement Reason: execRestatementReason
    std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason() const;
    void set_mass_cancel_restatement_reason(std::optional<MassCancelRestatementReason> value);

    // OrdTagId: ordTagID
    std::optional<std::uint8_t> ordtagid() const;
    void set_ordtagid(std::optional<std::uint8_t> value);

    // Side Optional: side
    SideOptional side_optional() const;
    void set_side_optional(SideOptional value);

    // Offset 31 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_31_padding_1() const;
    std::array<std::byte, 1>& offset_31_padding_1();
    void set_offset_31_padding_1(const std::array<std::byte, 1>& value);

    // Asset: asset
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Security Id Optional: securityID
    std::optional<std::uint64_t> security_id_optional() const;
    void set_security_id_optional(std::optional<std::uint64_t> value);

    // Investor Id: SimpleNewOrderMessage
    const InvestorId& investor_id() const;
    InvestorId& investor_id();
    void set_investor_id(const InvestorId& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const OrderMassActionRequestMessage& other) const;
    bool operator!=(const OrderMassActionRequestMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    MassActionType mass_action_type_{};
    std::optional<MassActionScope> mass_action_scope_{};
    std::uint64_t clordid_{};
    std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason_{};
    std::optional<std::uint8_t> ordtagid_{};
    SideOptional side_optional_{};
    std::array<std::byte, 1> offset_31_padding_1_{};
    std::string asset_{};
    std::optional<std::uint64_t> security_id_optional_{};
    InvestorId investor_id_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
