#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// The Unsequenced Data Packets act as an envelope to carry the actual data messages that are
// transferred from the client to the server
class UnsequencedDataPacket : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = ClientPacketType::UnsequencedDataPacket;

    UnsequencedDataPacket() = default;
    UnsequencedDataPacket(char unsequenced_message_type, const std::vector<std::byte>& unsequenced_message);

    // Unsequenced Message Type: Value identifying unsequenced message type
    char unsequenced_message_type() const;
    void set_unsequenced_message_type(char value);

    // Unsequenced Message: The unsequenced (client to server) message carried by the packet,
    // opaque bytes unless an application source dispatches it
    const std::vector<std::byte>& unsequenced_message() const;
    std::vector<std::byte>& unsequenced_message();
    void set_unsequenced_message(const std::vector<std::byte>& value);

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
    char unsequenced_message_type_{};
    std::vector<std::byte> unsequenced_message_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
