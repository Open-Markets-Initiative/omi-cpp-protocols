#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/IndicesMessageType.hpp"
#include "../messages/IndicesMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::cts::output::cta::v2_11_b {

class Visitor;
class IndicesMessagePayloadVisitor;

// Index Category Index Messages Are Used To Provide Index Value Information Of A Security
class IndicesMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Indices;

    IndicesMessage() = default;
    IndicesMessage(const IndicesMessage& other);
    IndicesMessage& operator=(const IndicesMessage& other);
    IndicesMessage(IndicesMessage&& other) noexcept = default;
    IndicesMessage& operator=(IndicesMessage&& other) noexcept = default;
    ~IndicesMessage() = default;

    // Indices Message Type: Identifies the type of Index message
    IndicesMessageType indices_message_type() const;
    void set_indices_message_type(IndicesMessageType value);

    // Indices Message Payload: Branch
    const IndicesMessagePayload* indices_message_payload() const;
    IndicesMessagePayload* indices_message_payload();
    void set_indices_message_payload(std::unique_ptr<IndicesMessagePayload> value);

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

    bool operator==(const IndicesMessage& other) const;
    bool operator!=(const IndicesMessage& other) const;

  private:
    IndicesMessageType indices_message_type_{};
    std::unique_ptr<IndicesMessagePayload> indices_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_11_b
