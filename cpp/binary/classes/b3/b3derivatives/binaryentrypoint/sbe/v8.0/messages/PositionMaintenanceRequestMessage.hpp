#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ContraryInstructionIndicator.hpp"
#include "../enums/PosTransType.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// PositionMaintenanceRequestMessage
class PositionMaintenanceRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::PositionMaintenanceRequestMessage;

    PositionMaintenanceRequestMessage() = default;
    PositionMaintenanceRequestMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t pos_req_id, std::uint64_t security_id, std::optional<Decimal> threshold_amount, std::optional<std::uint32_t> account, const std::string& sender_location, PosTransType pos_trans_type, std::uint16_t clearing_business_date, ContraryInstructionIndicator contrary_instruction_indicator, const std::string& entering_trader, std::uint64_t long_qty, const DeskId& desk_id, const Memo& memo);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // Pos Req Id: posReqID
    std::uint64_t pos_req_id() const;
    void set_pos_req_id(std::uint64_t value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Threshold Amount: thresholdAmount
    std::optional<Decimal> threshold_amount() const;
    void set_threshold_amount(std::optional<Decimal> value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Pos Trans Type: posTransType
    PosTransType pos_trans_type() const;
    void set_pos_trans_type(PosTransType value);

    // Clearing Business Date: clearingBusinessDate
    std::uint16_t clearing_business_date() const;
    void set_clearing_business_date(std::uint16_t value);

    // Contrary Instruction Indicator: contraryInstructionIndicator
    ContraryInstructionIndicator contrary_instruction_indicator() const;
    void set_contrary_instruction_indicator(ContraryInstructionIndicator value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Long Qty: longQty
    std::uint64_t long_qty() const;
    void set_long_qty(std::uint64_t value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

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

    bool operator==(const PositionMaintenanceRequestMessage& other) const;
    bool operator!=(const PositionMaintenanceRequestMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::uint64_t pos_req_id_{};
    std::uint64_t security_id_{};
    std::optional<Decimal> threshold_amount_{};
    std::optional<std::uint32_t> account_{};
    std::string sender_location_{};
    PosTransType pos_trans_type_{};
    std::uint16_t clearing_business_date_{};
    ContraryInstructionIndicator contrary_instruction_indicator_{};
    std::string entering_trader_{};
    std::uint64_t long_qty_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
