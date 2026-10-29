#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/LegsGroups.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// SecurityDefinitionRequestMessage
class SecurityDefinitionRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SecurityDefinitionRequestMessage;

    SecurityDefinitionRequestMessage() = default;
    SecurityDefinitionRequestMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t security_req_id, const std::string& sender_location, const std::string& entering_trader, const LegsGroups& legs_groups);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // Security Req Id: securityReqID
    std::uint64_t security_req_id() const;
    void set_security_req_id(std::uint64_t value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Legs Groups: noLegs Block
    const LegsGroups& legs_groups() const;
    LegsGroups& legs_groups();
    void set_legs_groups(const LegsGroups& value);

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

    bool operator==(const SecurityDefinitionRequestMessage& other) const;
    bool operator!=(const SecurityDefinitionRequestMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::uint64_t security_req_id_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    LegsGroups legs_groups_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
