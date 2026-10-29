#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/UnsequencedMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/UnsequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class Visitor;
class UnsequencedMessageVisitor;

// The Unsequenced Data Packets act as an envelope to carry the actual data messages that are
// transferred from the client to the server
class UnsequencedDataPacket : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = ClientPacketType::UnsequencedDataPacket;

    UnsequencedDataPacket() = default;
    UnsequencedDataPacket(const UnsequencedDataPacket& other);
    UnsequencedDataPacket& operator=(const UnsequencedDataPacket& other);
    UnsequencedDataPacket(UnsequencedDataPacket&& other) noexcept = default;
    UnsequencedDataPacket& operator=(UnsequencedDataPacket&& other) noexcept = default;
    ~UnsequencedDataPacket() = default;

    // Unsequenced Message Type: Value identifying unsequenced message type
    UnsequencedMessageType unsequenced_message_type() const;
    void set_unsequenced_message_type(UnsequencedMessageType value);

    // Unsequenced Message: The unsequenced (client to server) message carried by the packet,
    // opaque bytes unless an application source dispatches it
    const UnsequencedMessage* unsequenced_message() const;
    UnsequencedMessage* unsequenced_message();
    void set_unsequenced_message(std::unique_ptr<UnsequencedMessage> value);

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

    bool operator==(const UnsequencedDataPacket& other) const;
    bool operator!=(const UnsequencedDataPacket& other) const;

  private:
    UnsequencedMessageType unsequenced_message_type_{};
    std::unique_ptr<UnsequencedMessage> unsequenced_message_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
