#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/AdministrativeMessageType.hpp"
#include "../messages/AdministrativeMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::cts::output::cta::v2_9 {

class Visitor;
class AdministrativeMessagePayloadVisitor;

// Administrative Message Header
class AdministrativeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Administrative;

    AdministrativeMessage() = default;
    AdministrativeMessage(const AdministrativeMessage& other);
    AdministrativeMessage& operator=(const AdministrativeMessage& other);
    AdministrativeMessage(AdministrativeMessage&& other) noexcept = default;
    AdministrativeMessage& operator=(AdministrativeMessage&& other) noexcept = default;
    ~AdministrativeMessage() = default;

    // Administrative Message Type: Administrative message type
    AdministrativeMessageType administrative_message_type() const;
    void set_administrative_message_type(AdministrativeMessageType value);

    // Administrative Message Payload: Branch
    const AdministrativeMessagePayload* administrative_message_payload() const;
    AdministrativeMessagePayload* administrative_message_payload();
    void set_administrative_message_payload(std::unique_ptr<AdministrativeMessagePayload> value);

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

    bool operator==(const AdministrativeMessage& other) const;
    bool operator!=(const AdministrativeMessage& other) const;

  private:
    AdministrativeMessageType administrative_message_type_{};
    std::unique_ptr<AdministrativeMessagePayload> administrative_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_9
