#include "ClientPayloadSecurityListRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ClientPayloadSecurityListRequest::ClientPayloadSecurityListRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const SecurityListRequestSecurityGroups& security_list_request_security_groups, const SecurityListRequestRelatedSymbolGroups& security_list_request_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), security_list_request_security_groups_(security_list_request_security_groups), security_list_request_related_symbol_groups_(security_list_request_related_symbol_groups) {}

std::uint32_t ClientPayloadSecurityListRequest::md_req_id() const { return md_req_id_; }
void ClientPayloadSecurityListRequest::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType ClientPayloadSecurityListRequest::subscription_req_type() const { return subscription_req_type_; }
void ClientPayloadSecurityListRequest::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

const SecurityListRequestSecurityGroups& ClientPayloadSecurityListRequest::security_list_request_security_groups() const { return security_list_request_security_groups_; }
SecurityListRequestSecurityGroups& ClientPayloadSecurityListRequest::security_list_request_security_groups() { return security_list_request_security_groups_; }
void ClientPayloadSecurityListRequest::set_security_list_request_security_groups(const SecurityListRequestSecurityGroups& value) { security_list_request_security_groups_ = value; }

const SecurityListRequestRelatedSymbolGroups& ClientPayloadSecurityListRequest::security_list_request_related_symbol_groups() const { return security_list_request_related_symbol_groups_; }
SecurityListRequestRelatedSymbolGroups& ClientPayloadSecurityListRequest::security_list_request_related_symbol_groups() { return security_list_request_related_symbol_groups_; }
void ClientPayloadSecurityListRequest::set_security_list_request_related_symbol_groups(const SecurityListRequestRelatedSymbolGroups& value) { security_list_request_related_symbol_groups_ = value; }

ClientTcpMessageCode ClientPayloadSecurityListRequest::type() const { return message_type; }

std::string_view ClientPayloadSecurityListRequest::name() const { return "Security List Request"; }

std::size_t ClientPayloadSecurityListRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ClientPayloadSecurityListRequest", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ClientPayloadSecurityListRequest", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    offset += security_list_request_security_groups_.decode(data + offset, length - offset);

    offset += security_list_request_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ClientPayloadSecurityListRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPayloadSecurityListRequest", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    offset += security_list_request_security_groups_.encode(data + offset, capacity - offset);

    offset += security_list_request_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ClientPayloadSecurityListRequest::encoded_size() const {
    return 4 + 1 + security_list_request_security_groups_.encoded_size() + security_list_request_related_symbol_groups_.encoded_size();
}

void ClientPayloadSecurityListRequest::accept(ClientTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ClientTcpMessage> ClientPayloadSecurityListRequest::clone() const {
    return std::make_unique<ClientPayloadSecurityListRequest>(*this);
}

void ClientPayloadSecurityListRequest::print(std::ostream& out) const {
    out << "ClientPayloadSecurityListRequest{";
    out << "md_req_id=";
    out << md_req_id_;
    out << ", subscription_req_type=";
    out << subscription_req_type_;
    out << ", security_list_request_security_groups=";
    security_list_request_security_groups_.print(out);
    out << ", security_list_request_related_symbol_groups=";
    security_list_request_related_symbol_groups_.print(out);
    out << '}';
}

bool ClientPayloadSecurityListRequest::equals(const ClientTcpMessage& other) const {
    const auto* that = dynamic_cast<const ClientPayloadSecurityListRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool ClientPayloadSecurityListRequest::operator==(const ClientPayloadSecurityListRequest& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && security_list_request_security_groups_ == other.security_list_request_security_groups_
        && security_list_request_related_symbol_groups_ == other.security_list_request_related_symbol_groups_;
}

bool ClientPayloadSecurityListRequest::operator!=(const ClientPayloadSecurityListRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
