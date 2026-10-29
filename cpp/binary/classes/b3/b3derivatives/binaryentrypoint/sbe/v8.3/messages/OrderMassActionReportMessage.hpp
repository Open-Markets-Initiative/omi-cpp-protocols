#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MassActionRejectReason.hpp"
#include "../enums/MassActionResponse.hpp"
#include "../enums/MassActionScope.hpp"
#include "../enums/MassActionType.hpp"
#include "../enums/MassCancelRestatementReason.hpp"
#include "../enums/SideOptional.hpp"
#include "../messages/Message.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

class Visitor;

// OrderMassActionReportMessage
class OrderMassActionReportMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderMassActionReportMessage;

    OrderMassActionReportMessage() = default;
    OrderMassActionReportMessage(const OutboundBusinessHeader& outbound_business_header, MassActionType mass_action_type, std::optional<MassActionScope> mass_action_scope, std::uint64_t clordid, std::uint64_t mass_action_report_id, std::chrono::nanoseconds transact_time, MassActionResponse mass_action_response, std::optional<MassActionRejectReason> mass_action_reject_reason, std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason, std::optional<std::uint8_t> ordtagid, SideOptional side_optional, const std::array<std::byte, 1>& offset_49_padding_1, const std::string& asset, std::optional<std::uint64_t> security_id_optional, const InvestorId& investor_id, const Text& text);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Mass Action Type: massActionType
    MassActionType mass_action_type() const;
    void set_mass_action_type(MassActionType value);

    // Mass Action Scope: massActionScope
    std::optional<MassActionScope> mass_action_scope() const;
    void set_mass_action_scope(std::optional<MassActionScope> value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Mass Action Report Id: massActionReportID
    std::uint64_t mass_action_report_id() const;
    void set_mass_action_report_id(std::uint64_t value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Mass Action Response: massActionResponse
    MassActionResponse mass_action_response() const;
    void set_mass_action_response(MassActionResponse value);

    // Mass Action Reject Reason: massActionRejectReason
    std::optional<MassActionRejectReason> mass_action_reject_reason() const;
    void set_mass_action_reject_reason(std::optional<MassActionRejectReason> value);

    // Mass Cancel Restatement Reason: execRestatementReason
    std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason() const;
    void set_mass_cancel_restatement_reason(std::optional<MassCancelRestatementReason> value);

    // OrdTagId: ordTagID
    std::optional<std::uint8_t> ordtagid() const;
    void set_ordtagid(std::optional<std::uint8_t> value);

    // Side Optional: side
    SideOptional side_optional() const;
    void set_side_optional(SideOptional value);

    // Offset 49 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_49_padding_1() const;
    std::array<std::byte, 1>& offset_49_padding_1();
    void set_offset_49_padding_1(const std::array<std::byte, 1>& value);

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

    // Text: text data struct
    const Text& text() const;
    Text& text();
    void set_text(const Text& value);

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

    bool operator==(const OrderMassActionReportMessage& other) const;
    bool operator!=(const OrderMassActionReportMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    MassActionType mass_action_type_{};
    std::optional<MassActionScope> mass_action_scope_{};
    std::uint64_t clordid_{};
    std::uint64_t mass_action_report_id_{};
    std::chrono::nanoseconds transact_time_{};
    MassActionResponse mass_action_response_{};
    std::optional<MassActionRejectReason> mass_action_reject_reason_{};
    std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason_{};
    std::optional<std::uint8_t> ordtagid_{};
    SideOptional side_optional_{};
    std::array<std::byte, 1> offset_49_padding_1_{};
    std::string asset_{};
    std::optional<std::uint64_t> security_id_optional_{};
    InvestorId investor_id_{};
    Text text_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
