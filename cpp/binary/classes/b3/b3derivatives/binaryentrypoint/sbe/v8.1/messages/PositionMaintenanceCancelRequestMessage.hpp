#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/InboundBusinessHeader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// PositionMaintenanceCancelRequestMessage
class PositionMaintenanceCancelRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::PositionMaintenanceCancelRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 65;

    PositionMaintenanceCancelRequestMessage() = default;
    PositionMaintenanceCancelRequestMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t pos_req_id, std::uint64_t security_id, std::optional<std::uint64_t> orig_pos_req_ref_id, std::optional<std::uint64_t> pos_maint_rpt_ref_id, const std::string& sender_location, const std::string& entering_trader);

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

    // Orig Pos Req Ref Id: origPosReqRefID
    std::optional<std::uint64_t> orig_pos_req_ref_id() const;
    void set_orig_pos_req_ref_id(std::optional<std::uint64_t> value);

    // Pos Maint Rpt Ref Id: posMaintRptRefID
    std::optional<std::uint64_t> pos_maint_rpt_ref_id() const;
    void set_pos_maint_rpt_ref_id(std::optional<std::uint64_t> value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

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

    bool operator==(const PositionMaintenanceCancelRequestMessage& other) const;
    bool operator!=(const PositionMaintenanceCancelRequestMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::uint64_t pos_req_id_{};
    std::uint64_t security_id_{};
    std::optional<std::uint64_t> orig_pos_req_ref_id_{};
    std::optional<std::uint64_t> pos_maint_rpt_ref_id_{};
    std::string sender_location_{};
    std::string entering_trader_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
