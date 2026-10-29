#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AccountType.hpp"
#include "../enums/ContraryInstructionIndicator.hpp"
#include "../enums/PosMaintAction.hpp"
#include "../enums/PosMaintStatus.hpp"
#include "../enums/PosTransType.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../structs/PositionsGroups.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

class Visitor;

// PositionMaintenanceReportMessage
class PositionMaintenanceReportMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::PositionMaintenanceReportMessage;

    PositionMaintenanceReportMessage() = default;
    PositionMaintenanceReportMessage(const OutboundBusinessHeader& outbound_business_header, std::optional<std::uint64_t> pos_req_id_optional, std::uint64_t security_id, std::uint64_t pos_maint_rpt_id, PosTransType pos_trans_type, PosMaintAction pos_maint_action, PosMaintStatus pos_maint_status, std::optional<std::uint32_t> trade_id_optional, std::optional<std::uint64_t> orig_pos_req_ref_id, std::optional<AccountType> account_type, std::uint16_t clearing_business_date, std::optional<Decimal> threshold_amount, std::chrono::nanoseconds transact_time, std::optional<std::uint32_t> account, const std::string& sender_location, std::optional<std::uint32_t> pos_maint_result, ContraryInstructionIndicator contrary_instruction_indicator, const PositionsGroups& positions_groups, const DeskId& desk_id, const Memo& memo, const Text& text);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Pos Req Id Optional: posReqID
    std::optional<std::uint64_t> pos_req_id_optional() const;
    void set_pos_req_id_optional(std::optional<std::uint64_t> value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Pos Maint Rpt Id: posMaintRptID
    std::uint64_t pos_maint_rpt_id() const;
    void set_pos_maint_rpt_id(std::uint64_t value);

    // Pos Trans Type: posTransType
    PosTransType pos_trans_type() const;
    void set_pos_trans_type(PosTransType value);

    // Pos Maint Action: posMaintAction
    PosMaintAction pos_maint_action() const;
    void set_pos_maint_action(PosMaintAction value);

    // Pos Maint Status: posMaintStatus
    PosMaintStatus pos_maint_status() const;
    void set_pos_maint_status(PosMaintStatus value);

    // Trade Id Optional: tradeID
    std::optional<std::uint32_t> trade_id_optional() const;
    void set_trade_id_optional(std::optional<std::uint32_t> value);

    // Orig Pos Req Ref Id: origPosReqRefID
    std::optional<std::uint64_t> orig_pos_req_ref_id() const;
    void set_orig_pos_req_ref_id(std::optional<std::uint64_t> value);

    // Account Type: accountType
    std::optional<AccountType> account_type() const;
    void set_account_type(std::optional<AccountType> value);

    // Clearing Business Date: clearingBusinessDate
    std::uint16_t clearing_business_date() const;
    void set_clearing_business_date(std::uint16_t value);

    // Threshold Amount: thresholdAmount
    std::optional<Decimal> threshold_amount() const;
    void set_threshold_amount(std::optional<Decimal> value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Pos Maint Result: posMaintResult
    std::optional<std::uint32_t> pos_maint_result() const;
    void set_pos_maint_result(std::optional<std::uint32_t> value);

    // Contrary Instruction Indicator: contraryInstructionIndicator
    ContraryInstructionIndicator contrary_instruction_indicator() const;
    void set_contrary_instruction_indicator(ContraryInstructionIndicator value);

    // Positions Groups: noPositions Block
    const PositionsGroups& positions_groups() const;
    PositionsGroups& positions_groups();
    void set_positions_groups(const PositionsGroups& value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

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

    bool operator==(const PositionMaintenanceReportMessage& other) const;
    bool operator!=(const PositionMaintenanceReportMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    std::optional<std::uint64_t> pos_req_id_optional_{};
    std::uint64_t security_id_{};
    std::uint64_t pos_maint_rpt_id_{};
    PosTransType pos_trans_type_{};
    PosMaintAction pos_maint_action_{};
    PosMaintStatus pos_maint_status_{};
    std::optional<std::uint32_t> trade_id_optional_{};
    std::optional<std::uint64_t> orig_pos_req_ref_id_{};
    std::optional<AccountType> account_type_{};
    std::uint16_t clearing_business_date_{};
    std::optional<Decimal> threshold_amount_{};
    std::chrono::nanoseconds transact_time_{};
    std::optional<std::uint32_t> account_{};
    std::string sender_location_{};
    std::optional<std::uint32_t> pos_maint_result_{};
    ContraryInstructionIndicator contrary_instruction_indicator_{};
    PositionsGroups positions_groups_{};
    DeskId desk_id_{};
    Memo memo_{};
    Text text_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
