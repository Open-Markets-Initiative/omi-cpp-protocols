#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/SequencedMessage.hpp"
#include "../messages/ServerMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class ServerMessageVisitor;
class SequencedMessageVisitor;

// The Sequenced Data Packets act as an envelope to carry the actual sequenced data messages
// that are transferred from the server to the client. Each Sequenced Data Packet carries one
// message from the higher-lever protocol
class SequencedDataPacket : public ServerMessage {
  public:
    // The code that selects this message
    static constexpr ServerMessageCode message_type = ServerPacketType::SequencedDataPacket;

    SequencedDataPacket() = default;
    SequencedDataPacket(const SequencedDataPacket& other);
    SequencedDataPacket& operator=(const SequencedDataPacket& other);
    SequencedDataPacket(SequencedDataPacket&& other) noexcept = default;
    SequencedDataPacket& operator=(SequencedDataPacket&& other) noexcept = default;
    ~SequencedDataPacket() = default;

    // Sequenced Message Type: Value identifying sequenced message type
    char sequenced_message_type() const;
    void set_sequenced_message_type(char value);

    // Sequenced Message: Branch
    const SequencedMessage* sequenced_message() const;
    SequencedMessage* sequenced_message();
    void set_sequenced_message(std::unique_ptr<SequencedMessage> value);

    // ServerMessage
    ServerMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerMessageVisitor& visitor) const override;
    std::unique_ptr<ServerMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerMessage& other) const override;

    bool operator==(const SequencedDataPacket& other) const;
    bool operator!=(const SequencedDataPacket& other) const;

  private:
    char sequenced_message_type_{};
    std::unique_ptr<SequencedMessage> sequenced_message_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
