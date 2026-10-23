#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/ServerMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

class ServerMessageVisitor;

// Debug packets are intended to provide human readable text that may aid in debugging problems
class ServerPayloadDebugPacket : public ServerMessage {
  public:
    // The code that selects this message
    static constexpr ServerMessageCode message_type = ServerPacketType::DebugPacket;

    ServerPayloadDebugPacket() = default;
    ServerPayloadDebugPacket(const std::string& debug_text);

    // Debug Text: Free form human readable text
    const std::string& debug_text() const;
    std::string& debug_text();
    void set_debug_text(const std::string& value);

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
    std::string debug_text_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
