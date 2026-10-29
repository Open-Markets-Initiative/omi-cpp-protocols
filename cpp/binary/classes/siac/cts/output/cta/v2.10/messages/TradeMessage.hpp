#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/TradeMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/TradeMessagePayload.hpp"

namespace siac::cts::output::cta::v2_10 {

class Visitor;
class TradeMessagePayloadVisitor;

// Trade Messages
class TradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Trade;

    TradeMessage() = default;
    TradeMessage(const TradeMessage& other);
    TradeMessage& operator=(const TradeMessage& other);
    TradeMessage(TradeMessage&& other) noexcept = default;
    TradeMessage& operator=(TradeMessage&& other) noexcept = default;
    ~TradeMessage() = default;

    // Trade Message Type: Trade message type
    TradeMessageType trade_message_type() const;
    void set_trade_message_type(TradeMessageType value);

    // Trade Message Payload: Branch
    const TradeMessagePayload* trade_message_payload() const;
    TradeMessagePayload* trade_message_payload();
    void set_trade_message_payload(std::unique_ptr<TradeMessagePayload> value);

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

    bool operator==(const TradeMessage& other) const;
    bool operator!=(const TradeMessage& other) const;

  private:
    TradeMessageType trade_message_type_{};
    std::unique_ptr<TradeMessagePayload> trade_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_10
