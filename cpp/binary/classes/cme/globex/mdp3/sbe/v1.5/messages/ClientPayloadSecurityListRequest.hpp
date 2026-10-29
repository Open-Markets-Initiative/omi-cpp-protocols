#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SubscriptionReqType.hpp"
#include "../messages/ClientTcpMessage.hpp"
#include "../structs/SecurityListRequestRelatedSymbolGroups.hpp"
#include "../structs/SecurityListRequestSecurityGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ClientTcpMessageVisitor;

// SecurityListRequest
class ClientPayloadSecurityListRequest : public ClientTcpMessage {
  public:
    // The code that selects this message
    static constexpr ClientTcpMessageCode message_type = TemplateId::SecurityListRequest;

    ClientPayloadSecurityListRequest() = default;
    ClientPayloadSecurityListRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const SecurityListRequestSecurityGroups& security_list_request_security_groups, const SecurityListRequestRelatedSymbolGroups& security_list_request_related_symbol_groups);

    // Md Req Id: Unique identifier for Market Data Request. Must be unique per session so it
    // can be referenced in Request Ack or Request Reject responses from the exchange
    std::uint32_t md_req_id() const;
    void set_md_req_id(std::uint32_t value);

    // Subscription Req Type: Subscription Request Type indicates to the type of response
    // expected
    SubscriptionReqType subscription_req_type() const;
    void set_subscription_req_type(SubscriptionReqType value);

    // Security List Request Security Groups: NoSecurityGroups Block
    const SecurityListRequestSecurityGroups& security_list_request_security_groups() const;
    SecurityListRequestSecurityGroups& security_list_request_security_groups();
    void set_security_list_request_security_groups(const SecurityListRequestSecurityGroups& value);

    // Security List Request Related Symbol Groups: NoRelatedSym Block
    const SecurityListRequestRelatedSymbolGroups& security_list_request_related_symbol_groups() const;
    SecurityListRequestRelatedSymbolGroups& security_list_request_related_symbol_groups();
    void set_security_list_request_related_symbol_groups(const SecurityListRequestRelatedSymbolGroups& value);

    // ClientTcpMessage
    ClientTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ClientTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ClientTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ClientTcpMessage& other) const override;

    bool operator==(const ClientPayloadSecurityListRequest& other) const;
    bool operator!=(const ClientPayloadSecurityListRequest& other) const;

  private:
    std::uint32_t md_req_id_{};
    SubscriptionReqType subscription_req_type_{};
    SecurityListRequestSecurityGroups security_list_request_security_groups_{};
    SecurityListRequestRelatedSymbolGroups security_list_request_related_symbol_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
