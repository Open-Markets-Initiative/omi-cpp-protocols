#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SubscriptionReqType.hpp"
#include "../messages/ClientTcpMessage.hpp"
#include "../structs/MarketDataRequestRelatedSymbolGroups.hpp"
#include "../structs/MarketDataRequestSecurityGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ClientTcpMessageVisitor;

// MarketDataRequest
class ClientPayloadMarketDataRequest : public ClientTcpMessage {
  public:
    // The code that selects this message
    static constexpr ClientTcpMessageCode message_type = TemplateId::MarketDataRequest;

    ClientPayloadMarketDataRequest() = default;
    ClientPayloadMarketDataRequest(std::uint32_t md_req_id, SubscriptionReqType subscription_req_type, const MarketDataRequestSecurityGroups& market_data_request_security_groups, const MarketDataRequestRelatedSymbolGroups& market_data_request_related_symbol_groups);

    // Md Req Id: Unique identifier for Market Data Request. Must be unique per session so it
    // can be referenced in Request Ack or Request Reject responses from the exchange
    std::uint32_t md_req_id() const;
    void set_md_req_id(std::uint32_t value);

    // Subscription Req Type: Subscription Request Type indicates to the type of response
    // expected
    SubscriptionReqType subscription_req_type() const;
    void set_subscription_req_type(SubscriptionReqType value);

    // Market Data Request Security Groups: NoSecurityGroups Block
    const MarketDataRequestSecurityGroups& market_data_request_security_groups() const;
    MarketDataRequestSecurityGroups& market_data_request_security_groups();
    void set_market_data_request_security_groups(const MarketDataRequestSecurityGroups& value);

    // Market Data Request Related Symbol Groups: NoRelatedSym Block
    const MarketDataRequestRelatedSymbolGroups& market_data_request_related_symbol_groups() const;
    MarketDataRequestRelatedSymbolGroups& market_data_request_related_symbol_groups();
    void set_market_data_request_related_symbol_groups(const MarketDataRequestRelatedSymbolGroups& value);

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

    bool operator==(const ClientPayloadMarketDataRequest& other) const;
    bool operator!=(const ClientPayloadMarketDataRequest& other) const;

  private:
    std::uint32_t md_req_id_{};
    SubscriptionReqType subscription_req_type_{};
    MarketDataRequestSecurityGroups market_data_request_security_groups_{};
    MarketDataRequestRelatedSymbolGroups market_data_request_related_symbol_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
