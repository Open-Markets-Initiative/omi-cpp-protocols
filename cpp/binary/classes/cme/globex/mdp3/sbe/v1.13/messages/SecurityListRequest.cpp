#include "SecurityListRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SecurityListRequest::SecurityListRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const SecurityListRequestSecurityGroups& security_list_request_security_groups, const SecurityListRequestRelatedSymbolGroups& security_list_request_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), security_list_request_security_groups_(security_list_request_security_groups), security_list_request_related_symbol_groups_(security_list_request_related_symbol_groups) {}

std::uint32_t SecurityListRequest::md_req_id() const { return md_req_id_; }
void SecurityListRequest::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType SecurityListRequest::subscription_req_type() const { return subscription_req_type_; }
void SecurityListRequest::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

const SecurityListRequestSecurityGroups& SecurityListRequest::security_list_request_security_groups() const { return security_list_request_security_groups_; }
SecurityListRequestSecurityGroups& SecurityListRequest::security_list_request_security_groups() { return security_list_request_security_groups_; }
void SecurityListRequest::set_security_list_request_security_groups(const SecurityListRequestSecurityGroups& value) { security_list_request_security_groups_ = value; }

const SecurityListRequestRelatedSymbolGroups& SecurityListRequest::security_list_request_related_symbol_groups() const { return security_list_request_related_symbol_groups_; }
SecurityListRequestRelatedSymbolGroups& SecurityListRequest::security_list_request_related_symbol_groups() { return security_list_request_related_symbol_groups_; }
void SecurityListRequest::set_security_list_request_related_symbol_groups(const SecurityListRequestRelatedSymbolGroups& value) { security_list_request_related_symbol_groups_ = value; }

MdpsessionmgmtPayloadCode SecurityListRequest::type() const { return message_type; }

std::string_view SecurityListRequest::name() const { return "Security List Request"; }

std::size_t SecurityListRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SecurityListRequest", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SecurityListRequest", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    offset += security_list_request_security_groups_.decode(data + offset, length - offset);

    offset += security_list_request_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SecurityListRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityListRequest", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    offset += security_list_request_security_groups_.encode(data + offset, capacity - offset);

    offset += security_list_request_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SecurityListRequest::encoded_size() const {
    return 4 + 1 + security_list_request_security_groups_.encoded_size() + security_list_request_related_symbol_groups_.encoded_size();
}

void SecurityListRequest::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> SecurityListRequest::clone() const {
    return std::make_unique<SecurityListRequest>(*this);
}

void SecurityListRequest::print(std::ostream& out) const {
    out << "SecurityListRequest{";
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

bool SecurityListRequest::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const SecurityListRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityListRequest::operator==(const SecurityListRequest& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && security_list_request_security_groups_ == other.security_list_request_security_groups_
        && security_list_request_related_symbol_groups_ == other.security_list_request_related_symbol_groups_;
}

bool SecurityListRequest::operator!=(const SecurityListRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
