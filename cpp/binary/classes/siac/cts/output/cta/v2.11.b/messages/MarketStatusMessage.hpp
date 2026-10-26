#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MarketStatusMessageType.hpp"
#include "../messages/MarketStatusMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::cts::output::cta::v2_11_b {

class Visitor;
class MarketStatusMessagePayloadVisitor;

// Market Status Category Market Status Messages Are Used To Provide Market Data Information
class MarketStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::MarketStatus;

    MarketStatusMessage() = default;
    MarketStatusMessage(const MarketStatusMessage& other);
    MarketStatusMessage& operator=(const MarketStatusMessage& other);
    MarketStatusMessage(MarketStatusMessage&& other) noexcept = default;
    MarketStatusMessage& operator=(MarketStatusMessage&& other) noexcept = default;
    ~MarketStatusMessage() = default;

    // Market Status Message Type: Identifies the type of Market Status message
    MarketStatusMessageType market_status_message_type() const;
    void set_market_status_message_type(MarketStatusMessageType value);

    // Market Status Message Payload: Branch
    const MarketStatusMessagePayload* market_status_message_payload() const;
    MarketStatusMessagePayload* market_status_message_payload();
    void set_market_status_message_payload(std::unique_ptr<MarketStatusMessagePayload> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const MarketStatusMessage& other) const;
    bool operator!=(const MarketStatusMessage& other) const;

  private:
    MarketStatusMessageType market_status_message_type_{};
    std::unique_ptr<MarketStatusMessagePayload> market_status_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_11_b
