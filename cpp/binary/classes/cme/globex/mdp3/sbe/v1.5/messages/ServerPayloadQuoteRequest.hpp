#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/RelatedSymGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ServerTcpMessageVisitor;

// QuoteRequest
class ServerPayloadQuoteRequest : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::QuoteRequest;

    ServerPayloadQuoteRequest() = default;
    ServerPayloadQuoteRequest(std::chrono::nanoseconds transact_time, const std::string& quote_req_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& padding_3, const RelatedSymGroups& related_sym_groups);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Quote Req Id: Quote Request ID defined by the exchange
    const std::string& quote_req_id() const;
    std::string& quote_req_id();
    void set_quote_req_id(const std::string& value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& padding_3() const;
    std::array<std::byte, 3>& padding_3();
    void set_padding_3(const std::array<std::byte, 3>& value);

    // Related Sym Groups: NoRelatedSym Block
    const RelatedSymGroups& related_sym_groups() const;
    RelatedSymGroups& related_sym_groups();
    void set_related_sym_groups(const RelatedSymGroups& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadQuoteRequest& other) const;
    bool operator!=(const ServerPayloadQuoteRequest& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    std::string quote_req_id_{};
    MatchEventIndicator match_event_indicator_{};
    std::array<std::byte, 3> padding_3_{};
    RelatedSymGroups related_sym_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
