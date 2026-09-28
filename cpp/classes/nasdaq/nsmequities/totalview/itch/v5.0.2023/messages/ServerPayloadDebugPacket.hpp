#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/ServerMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class ServerMessageVisitor;

// Debug packets are intended to provide human readable text that may aid in debugging problems
class ServerPayloadDebugPacket : public ServerMessage {
  public:
    // The code that selects this message
    static constexpr ServerMessageCode message_type = ServerPacketType::DebugPacket;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    ServerPayloadDebugPacket() = default;
    ServerPayloadDebugPacket(char debug_text);

    // Debug Text: Free form human readable text
    char debug_text() const;
    void set_debug_text(char value);

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

    bool operator==(const ServerPayloadDebugPacket& other) const;
    bool operator!=(const ServerPayloadDebugPacket& other) const;

  private:
    char debug_text_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
