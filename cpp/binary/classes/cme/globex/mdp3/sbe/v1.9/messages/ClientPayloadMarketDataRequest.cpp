#include "ClientPayloadMarketDataRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ClientPayloadMarketDataRequest::ClientPayloadMarketDataRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const MarketDataRequestSecurityGroups& market_data_request_security_groups, const MarketDataRequestRelatedSymbolGroups& market_data_request_related_symbol_groups)
  : md_req_id_(md_req_id), subscription_req_type_(subscription_req_type), market_data_request_security_groups_(market_data_request_security_groups), market_data_request_related_symbol_groups_(market_data_request_related_symbol_groups) {}

std::uint32_t ClientPayloadMarketDataRequest::md_req_id() const { return md_req_id_; }
void ClientPayloadMarketDataRequest::set_md_req_id(std::uint32_t value) { md_req_id_ = value; }

SubscriptionReqType ClientPayloadMarketDataRequest::subscription_req_type() const { return subscription_req_type_; }
void ClientPayloadMarketDataRequest::set_subscription_req_type(SubscriptionReqType value) { subscription_req_type_ = value; }

const MarketDataRequestSecurityGroups& ClientPayloadMarketDataRequest::market_data_request_security_groups() const { return market_data_request_security_groups_; }
MarketDataRequestSecurityGroups& ClientPayloadMarketDataRequest::market_data_request_security_groups() { return market_data_request_security_groups_; }
void ClientPayloadMarketDataRequest::set_market_data_request_security_groups(const MarketDataRequestSecurityGroups& value) { market_data_request_security_groups_ = value; }

const MarketDataRequestRelatedSymbolGroups& ClientPayloadMarketDataRequest::market_data_request_related_symbol_groups() const { return market_data_request_related_symbol_groups_; }
MarketDataRequestRelatedSymbolGroups& ClientPayloadMarketDataRequest::market_data_request_related_symbol_groups() { return market_data_request_related_symbol_groups_; }
void ClientPayloadMarketDataRequest::set_market_data_request_related_symbol_groups(const MarketDataRequestRelatedSymbolGroups& value) { market_data_request_related_symbol_groups_ = value; }

ClientTcpMessageCode ClientPayloadMarketDataRequest::type() const { return message_type; }

std::string_view ClientPayloadMarketDataRequest::name() const { return "Market Data Request"; }

std::size_t ClientPayloadMarketDataRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ClientPayloadMarketDataRequest", offset + 4, length);
    md_req_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ClientPayloadMarketDataRequest", offset + 1, length);
    subscription_req_type_ = static_cast<SubscriptionReqType>(wire::read_u8(data + offset));
    offset += 1;

    offset += market_data_request_security_groups_.decode(data + offset, length - offset);

    offset += market_data_request_related_symbol_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ClientPayloadMarketDataRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPayloadMarketDataRequest", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_req_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(subscription_req_type_));
    offset += 1;

    offset += market_data_request_security_groups_.encode(data + offset, capacity - offset);

    offset += market_data_request_related_symbol_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ClientPayloadMarketDataRequest::encoded_size() const {
    return 4 + 1 + market_data_request_security_groups_.encoded_size() + market_data_request_related_symbol_groups_.encoded_size();
}

void ClientPayloadMarketDataRequest::accept(ClientTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ClientTcpMessage> ClientPayloadMarketDataRequest::clone() const {
    return std::make_unique<ClientPayloadMarketDataRequest>(*this);
}

void ClientPayloadMarketDataRequest::print(std::ostream& out) const {
    out << "ClientPayloadMarketDataRequest{";
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

bool ClientPayloadMarketDataRequest::equals(const ClientTcpMessage& other) const {
    const auto* that = dynamic_cast<const ClientPayloadMarketDataRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool ClientPayloadMarketDataRequest::operator==(const ClientPayloadMarketDataRequest& other) const {
    return md_req_id_ == other.md_req_id_
        && subscription_req_type_ == other.subscription_req_type_
        && market_data_request_security_groups_ == other.market_data_request_security_groups_
        && market_data_request_related_symbol_groups_ == other.market_data_request_related_symbol_groups_;
}

bool ClientPayloadMarketDataRequest::operator!=(const ClientPayloadMarketDataRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
