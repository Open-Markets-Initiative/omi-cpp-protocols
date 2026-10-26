#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SubscriptionReqType.hpp"
#include "../messages/MdpsessionmgmtPayload.hpp"
#include "../structs/SecurityStatusRequestRelatedSymbolGroups.hpp"
#include "../structs/SecurityStatusRequestSecurityGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MdpsessionmgmtPayloadVisitor;

// SecurityStatusRequest
class SecurityStatusRequest : public MdpsessionmgmtPayload {
  public:
    // The code that selects this message
    static constexpr MdpsessionmgmtPayloadCode message_type = TemplateId::SecurityStatusRequest;

    SecurityStatusRequest() = default;
    SecurityStatusRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const SecurityStatusRequestSecurityGroups& security_status_request_security_groups, const SecurityStatusRequestRelatedSymbolGroups& security_status_request_related_symbol_groups);

    // Md Req Id: Unique identifier for Market Data Request. Must be unique per session so it
    // can be referenced in Request Ack or Request Reject responses from the exchange
    std::uint32_t md_req_id() const;
    void set_md_req_id(std::uint32_t value);

    // Subscription Req Type: Subscription Request Type indicates to the type of response
    // expected
    SubscriptionReqType subscription_req_type() const;
    void set_subscription_req_type(SubscriptionReqType value);

    // Security Status Request Security Groups: NoSecurityGroups Block
    const SecurityStatusRequestSecurityGroups& security_status_request_security_groups() const;
    SecurityStatusRequestSecurityGroups& security_status_request_security_groups();
    void set_security_status_request_security_groups(const SecurityStatusRequestSecurityGroups& value);

    // Security Status Request Related Symbol Groups: NoRelatedSym Block
    const SecurityStatusRequestRelatedSymbolGroups& security_status_request_related_symbol_groups() const;
    SecurityStatusRequestRelatedSymbolGroups& security_status_request_related_symbol_groups();
    void set_security_status_request_related_symbol_groups(const SecurityStatusRequestRelatedSymbolGroups& value);

    // MdpsessionmgmtPayload
    MdpsessionmgmtPayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MdpsessionmgmtPayloadVisitor& visitor) const override;
    std::unique_ptr<MdpsessionmgmtPayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MdpsessionmgmtPayload& other) const override;

    bool operator==(const SecurityStatusRequest& other) const;
    bool operator!=(const SecurityStatusRequest& other) const;

  private:
    std::uint32_t md_req_id_{};
    SubscriptionReqType subscription_req_type_{};
    SecurityStatusRequestSecurityGroups security_status_request_security_groups_{};
    SecurityStatusRequestRelatedSymbolGroups security_status_request_related_symbol_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
