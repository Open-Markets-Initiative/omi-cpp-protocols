#include "MarketDataRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

MarketDataRequest::MarketDataRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const MarketDataRequestSecurityGroups& market_data_request_security_groups, const MarketDataRequestRelatedSymbolGroups& market_data_request_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), market_data_request_security_groups_(market_data_request_security_groups), market_data_request_related_symbol_groups_(market_data_request_related_symbol_groups) {}

std::uint32_t MarketDataRequest::md_req_id() const { return md_req_id_; }
void MarketDataRequest::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType MarketDataRequest::subscription_req_type() const { return subscription_req_type_; }
void MarketDataRequest::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

const MarketDataRequestSecurityGroups& MarketDataRequest::market_data_request_security_groups() const { return market_data_request_security_groups_; }
MarketDataRequestSecurityGroups& MarketDataRequest::market_data_request_security_groups() { return market_data_request_security_groups_; }
void MarketDataRequest::set_market_data_request_security_groups(const MarketDataRequestSecurityGroups& value) { market_data_request_security_groups_ = value; }

const MarketDataRequestRelatedSymbolGroups& MarketDataRequest::market_data_request_related_symbol_groups() const { return market_data_request_related_symbol_groups_; }
MarketDataRequestRelatedSymbolGroups& MarketDataRequest::market_data_request_related_symbol_groups() { return market_data_request_related_symbol_groups_; }
void MarketDataRequest::set_market_data_request_related_symbol_groups(const MarketDataRequestRelatedSymbolGroups& value) { market_data_request_related_symbol_groups_ = value; }

MdpsessionmgmtPayloadCode MarketDataRequest::type() const { return message_type; }

std::string_view MarketDataRequest::name() const { return "Market Data Request"; }

std::size_t MarketDataRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("MarketDataRequest", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("MarketDataRequest", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    offset += market_data_request_security_groups_.decode(data + offset, length - offset);

    offset += market_data_request_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MarketDataRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketDataRequest", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    offset += market_data_request_security_groups_.encode(data + offset, capacity - offset);

    offset += market_data_request_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MarketDataRequest::encoded_size() const {
    return 4 + 1 + market_data_request_security_groups_.encoded_size() + market_data_request_related_symbol_groups_.encoded_size();
}

void MarketDataRequest::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> MarketDataRequest::clone() const {
    return std::make_unique<MarketDataRequest>(*this);
}

void MarketDataRequest::print(std::ostream& out) const {
    out << "MarketDataRequest{";
    out << "md_req_id=";
    out << md_req_id_;
    out << ", subscription_req_type=";
    out << subscription_req_type_;
    out << ", market_data_request_security_groups=";
    market_data_request_security_groups_.print(out);
    out << ", market_data_request_related_symbol_groups=";
    market_data_request_related_symbol_groups_.print(out);
    out << '}';
}

bool MarketDataRequest::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const MarketDataRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketDataRequest::operator==(const MarketDataRequest& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && market_data_request_security_groups_ == other.market_data_request_security_groups_
        && market_data_request_related_symbol_groups_ == other.market_data_request_related_symbol_groups_;
}

bool MarketDataRequest::operator!=(const MarketDataRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
