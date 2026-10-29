#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/QuoteMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/QuoteMessagePayload.hpp"

namespace siac::cqs::output::cta::v1_91 {

class Visitor;
class QuoteMessagePayloadVisitor;

// Quote Messages
class QuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Quote;

    QuoteMessage() = default;
    QuoteMessage(const QuoteMessage& other);
    QuoteMessage& operator=(const QuoteMessage& other);
    QuoteMessage(QuoteMessage&& other) noexcept = default;
    QuoteMessage& operator=(QuoteMessage&& other) noexcept = default;
    ~QuoteMessage() = default;

    // Quote Message Type: Quote message type
    QuoteMessageType quote_message_type() const;
    void set_quote_message_type(QuoteMessageType value);

    // Quote Message Payload: Branch
    const QuoteMessagePayload* quote_message_payload() const;
    QuoteMessagePayload* quote_message_payload();
    void set_quote_message_payload(std::unique_ptr<QuoteMessagePayload> value);

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

    bool operator==(const QuoteMessage& other) const;
    bool operator!=(const QuoteMessage& other) const;

  private:
    QuoteMessageType quote_message_type_{};
    std::unique_ptr<QuoteMessagePayload> quote_message_payload_{};
};

} // namespace siac::cqs::output::cta::v1_91
