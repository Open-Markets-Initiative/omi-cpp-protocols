#include "RequestAck.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

RequestAck::RequestAck(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, MdReqIdStatus md_req_id_status, const RequestAckSecurityGroups& request_ack_security_groups, const RequestAckRelatedSymbolGroups& request_ack_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), md_req_id_status_(md_req_id_status), request_ack_security_groups_(request_ack_security_groups), request_ack_related_symbol_groups_(request_ack_related_symbol_groups) {}

std::uint32_t RequestAck::md_req_id() const { return md_req_id_; }
void RequestAck::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType RequestAck::subscription_req_type() const { return subscription_req_type_; }
void RequestAck::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

MdReqIdStatus RequestAck::md_req_id_status() const { return md_req_id_status_; }
void RequestAck::set_md_req_id_status(MdReqIdStatus value) { md_req_id_status_ = value; }

const RequestAckSecurityGroups& RequestAck::request_ack_security_groups() const { return request_ack_security_groups_; }
RequestAckSecurityGroups& RequestAck::request_ack_security_groups() { return request_ack_security_groups_; }
void RequestAck::set_request_ack_security_groups(const RequestAckSecurityGroups& value) { request_ack_security_groups_ = value; }

const RequestAckRelatedSymbolGroups& RequestAck::request_ack_related_symbol_groups() const { return request_ack_related_symbol_groups_; }
RequestAckRelatedSymbolGroups& RequestAck::request_ack_related_symbol_groups() { return request_ack_related_symbol_groups_; }
void RequestAck::set_request_ack_related_symbol_groups(const RequestAckRelatedSymbolGroups& value) { request_ack_related_symbol_groups_ = value; }

MdpsessionmgmtPayloadCode RequestAck::type() const { return message_type; }

std::string_view RequestAck::name() const { return "Request Ack"; }

std::size_t RequestAck::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("RequestAck", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("RequestAck", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("RequestAck", offset + 1, length);
    md_req_id_status_ = static_cast<MdReqIdStatus>(wire::read_u8(data + offset));
    offset += 1;

    offset += request_ack_security_groups_.decode(data + offset, length - offset);

    offset += request_ack_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t RequestAck::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestAck", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_req_id_status_));
    offset += 1;

    offset += request_ack_security_groups_.encode(data + offset, capacity - offset);

    offset += request_ack_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t RequestAck::encoded_size() const {
    return 4 + 1 + 1 + request_ack_security_groups_.encoded_size() + request_ack_related_symbol_groups_.encoded_size();
}

void RequestAck::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> RequestAck::clone() const {
    return std::make_unique<RequestAck>(*this);
}

void RequestAck::print(std::ostream& out) const {
    out << "RequestAck{";
    out << "md_req_id=";
    out << md_req_id_;
    out << ", subscription_req_type=";
    out << subscription_req_type_;
    out << ", md_req_id_status=";
    out << md_req_id_status_;
    out << ", request_ack_security_groups=";
    request_ack_security_groups_.print(out);
    out << ", request_ack_related_symbol_groups=";
    request_ack_related_symbol_groups_.print(out);
    out << '}';
}

bool RequestAck::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const RequestAck*>(&other);
    return that != nullptr && *this == *that;
}

bool RequestAck::operator==(const RequestAck& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && md_req_id_status_ == other.md_req_id_status_
        && request_ack_security_groups_ == other.request_ack_security_groups_
        && request_ack_related_symbol_groups_ == other.request_ack_related_symbol_groups_;
}

bool RequestAck::operator!=(const RequestAck& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
