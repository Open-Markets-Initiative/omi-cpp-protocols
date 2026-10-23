#include "ClientPayloadSecurityStatusRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ClientPayloadSecurityStatusRequest::ClientPayloadSecurityStatusRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const SecurityStatusRequestSecurityGroups& security_status_request_security_groups, const SecurityStatusRequestRelatedSymbolGroups& security_status_request_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), security_status_request_security_groups_(security_status_request_security_groups), security_status_request_related_symbol_groups_(security_status_request_related_symbol_groups) {}

std::uint32_t ClientPayloadSecurityStatusRequest::md_req_id() const { return md_req_id_; }
void ClientPayloadSecurityStatusRequest::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType ClientPayloadSecurityStatusRequest::subscription_req_type() const { return subscription_req_type_; }
void ClientPayloadSecurityStatusRequest::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

const SecurityStatusRequestSecurityGroups& ClientPayloadSecurityStatusRequest::security_status_request_security_groups() const { return security_status_request_security_groups_; }
SecurityStatusRequestSecurityGroups& ClientPayloadSecurityStatusRequest::security_status_request_security_groups() { return security_status_request_security_groups_; }
void ClientPayloadSecurityStatusRequest::set_security_status_request_security_groups(const SecurityStatusRequestSecurityGroups& value) { security_status_request_security_groups_ = value; }

const SecurityStatusRequestRelatedSymbolGroups& ClientPayloadSecurityStatusRequest::security_status_request_related_symbol_groups() const { return security_status_request_related_symbol_groups_; }
SecurityStatusRequestRelatedSymbolGroups& ClientPayloadSecurityStatusRequest::security_status_request_related_symbol_groups() { return security_status_request_related_symbol_groups_; }
void ClientPayloadSecurityStatusRequest::set_security_status_request_related_symbol_groups(const SecurityStatusRequestRelatedSymbolGroups& value) { security_status_request_related_symbol_groups_ = value; }

ClientTcpMessageCode ClientPayloadSecurityStatusRequest::type() const { return message_type; }

std::string_view ClientPayloadSecurityStatusRequest::name() const { return "Security Status Request"; }

std::size_t ClientPayloadSecurityStatusRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ClientPayloadSecurityStatusRequest", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ClientPayloadSecurityStatusRequest", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    offset += security_status_request_security_groups_.decode(data + offset, length - offset);

    offset += security_status_request_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ClientPayloadSecurityStatusRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPayloadSecurityStatusRequest", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    offset += security_status_request_security_groups_.encode(data + offset, capacity - offset);

    offset += security_status_request_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ClientPayloadSecurityStatusRequest::encoded_size() const {
    return 4 + 1 + security_status_request_security_groups_.encoded_size() + security_status_request_related_symbol_groups_.encoded_size();
}

void ClientPayloadSecurityStatusRequest::accept(ClientTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ClientTcpMessage> ClientPayloadSecurityStatusRequest::clone() const {
    return std::make_unique<ClientPayloadSecurityStatusRequest>(*this);
}

void ClientPayloadSecurityStatusRequest::print(std::ostream& out) const {
    out << "ClientPayloadSecurityStatusRequest{";
    out << "md_req_id=";
    out << md_req_id_;
    out << ", subscription_req_type=";
    out << subscription_req_type_;
    out << ", security_status_request_security_groups=";
    security_status_request_security_groups_.print(out);
    out << ", security_status_request_related_symbol_groups=";
    security_status_request_related_symbol_groups_.print(out);
    out << '}';
}

bool ClientPayloadSecurityStatusRequest::equals(const ClientTcpMessage& other) const {
    const auto* that = dynamic_cast<const ClientPayloadSecurityStatusRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool ClientPayloadSecurityStatusRequest::operator==(const ClientPayloadSecurityStatusRequest& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && security_status_request_security_groups_ == other.security_status_request_security_groups_
        && security_status_request_related_symbol_groups_ == other.security_status_request_related_symbol_groups_;
}

bool ClientPayloadSecurityStatusRequest::operator!=(const ClientPayloadSecurityStatusRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
