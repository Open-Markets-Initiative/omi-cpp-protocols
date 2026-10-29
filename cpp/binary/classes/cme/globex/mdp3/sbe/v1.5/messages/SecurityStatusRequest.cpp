#include "SecurityStatusRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

SecurityStatusRequest::SecurityStatusRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const SecurityStatusRequestSecurityGroups& security_status_request_security_groups, const SecurityStatusRequestRelatedSymbolGroups& security_status_request_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), security_status_request_security_groups_(security_status_request_security_groups), security_status_request_related_symbol_groups_(security_status_request_related_symbol_groups) {}

std::uint32_t SecurityStatusRequest::md_req_id() const { return md_req_id_; }
void SecurityStatusRequest::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType SecurityStatusRequest::subscription_req_type() const { return subscription_req_type_; }
void SecurityStatusRequest::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

const SecurityStatusRequestSecurityGroups& SecurityStatusRequest::security_status_request_security_groups() const { return security_status_request_security_groups_; }
SecurityStatusRequestSecurityGroups& SecurityStatusRequest::security_status_request_security_groups() { return security_status_request_security_groups_; }
void SecurityStatusRequest::set_security_status_request_security_groups(const SecurityStatusRequestSecurityGroups& value) { security_status_request_security_groups_ = value; }

const SecurityStatusRequestRelatedSymbolGroups& SecurityStatusRequest::security_status_request_related_symbol_groups() const { return security_status_request_related_symbol_groups_; }
SecurityStatusRequestRelatedSymbolGroups& SecurityStatusRequest::security_status_request_related_symbol_groups() { return security_status_request_related_symbol_groups_; }
void SecurityStatusRequest::set_security_status_request_related_symbol_groups(const SecurityStatusRequestRelatedSymbolGroups& value) { security_status_request_related_symbol_groups_ = value; }

MdpsessionmgmtPayloadCode SecurityStatusRequest::type() const { return message_type; }

std::string_view SecurityStatusRequest::name() const { return "Security Status Request"; }

std::size_t SecurityStatusRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SecurityStatusRequest", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SecurityStatusRequest", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    offset += security_status_request_security_groups_.decode(data + offset, length - offset);

    offset += security_status_request_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SecurityStatusRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatusRequest", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    offset += security_status_request_security_groups_.encode(data + offset, capacity - offset);

    offset += security_status_request_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SecurityStatusRequest::encoded_size() const {
    return 4 + 1 + security_status_request_security_groups_.encoded_size() + security_status_request_related_symbol_groups_.encoded_size();
}

void SecurityStatusRequest::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> SecurityStatusRequest::clone() const {
    return std::make_unique<SecurityStatusRequest>(*this);
}

void SecurityStatusRequest::print(std::ostream& out) const {
    out << "SecurityStatusRequest{";
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

bool SecurityStatusRequest::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const SecurityStatusRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityStatusRequest::operator==(const SecurityStatusRequest& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && security_status_request_security_groups_ == other.security_status_request_security_groups_
        && security_status_request_related_symbol_groups_ == other.security_status_request_related_symbol_groups_;
}

bool SecurityStatusRequest::operator!=(const SecurityStatusRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_5
