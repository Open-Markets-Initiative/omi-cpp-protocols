#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MdReqIdStatus.hpp"
#include "../enums/SubscriptionReqType.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/RequestAckRelatedSymbolGroups.hpp"
#include "../structs/RequestAckSecurityGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ServerTcpMessageVisitor;

// RequestAck
class ServerPayloadRequestAck : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::RequestAck;

    ServerPayloadRequestAck() = default;
    ServerPayloadRequestAck(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, MdReqIdStatus md_req_id_status, const RequestAckSecurityGroups& request_ack_security_groups, const RequestAckRelatedSymbolGroups& request_ack_related_symbol_groups);

    // Md Req Id: Unique identifier for Market Data Request. Must be unique per session so it
    // can be referenced in Request Ack or Request Reject responses from the exchange
    std::uint32_t md_req_id() const;
    void set_md_req_id(std::uint32_t value);

    // Subscription Req Type: Subscription Request Type indicates to the type of response
    // expected
    SubscriptionReqType subscription_req_type() const;
    void set_subscription_req_type(SubscriptionReqType value);

    // Md Req Id Status: Status of the request acknowledgement
    MdReqIdStatus md_req_id_status() const;
    void set_md_req_id_status(MdReqIdStatus value);

    // Request Ack Security Groups: NoSecurityGroups Block
    const RequestAckSecurityGroups& request_ack_security_groups() const;
    RequestAckSecurityGroups& request_ack_security_groups();
    void set_request_ack_security_groups(const RequestAckSecurityGroups& value);

    // Request Ack Related Symbol Groups: NoRelatedSym Block
    const RequestAckRelatedSymbolGroups& request_ack_related_symbol_groups() const;
    RequestAckRelatedSymbolGroups& request_ack_related_symbol_groups();
    void set_request_ack_related_symbol_groups(const RequestAckRelatedSymbolGroups& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadRequestAck& other) const;
    bool operator!=(const ServerPayloadRequestAck& other) const;

  private:
    std::uint32_t md_req_id_{};
    SubscriptionReqType subscription_req_type_{};
    MdReqIdStatus md_req_id_status_{};
    RequestAckSecurityGroups request_ack_security_groups_{};
    RequestAckRelatedSymbolGroups request_ack_related_symbol_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
