#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/PriorDayMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/PriorDayMessagePayload.hpp"

namespace siac::cts::output::cta::v2_9 {

class Visitor;
class PriorDayMessagePayloadVisitor;

// Prior Day Messages
class PriorDayMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::PriorDay;

    PriorDayMessage() = default;
    PriorDayMessage(const PriorDayMessage& other);
    PriorDayMessage& operator=(const PriorDayMessage& other);
    PriorDayMessage(PriorDayMessage&& other) noexcept = default;
    PriorDayMessage& operator=(PriorDayMessage&& other) noexcept = default;
    ~PriorDayMessage() = default;

    // Prior Day Message Type: Prior Day message type
    PriorDayMessageType prior_day_message_type() const;
    void set_prior_day_message_type(PriorDayMessageType value);

    // Prior Day Message Payload: Branch
    const PriorDayMessagePayload* prior_day_message_payload() const;
    PriorDayMessagePayload* prior_day_message_payload();
    void set_prior_day_message_payload(std::unique_ptr<PriorDayMessagePayload> value);

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

    bool operator==(const PriorDayMessage& other) const;
    bool operator!=(const PriorDayMessage& other) const;

  private:
    PriorDayMessageType prior_day_message_type_{};
    std::unique_ptr<PriorDayMessagePayload> prior_day_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_9
