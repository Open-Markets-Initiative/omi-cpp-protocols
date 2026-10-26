#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/ServerMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class ServerMessageVisitor;

// The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login
// Request from the client
class LoginAcceptedPacket : public ServerMessage {
  public:
    // The code that selects this message
    static constexpr ServerMessageCode message_type = ServerPacketType::LoginAcceptedPacket;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    LoginAcceptedPacket() = default;
    LoginAcceptedPacket(const std::string& accepted_session, const std::string& accepted_sequence_number);

    // Accepted Session: The session ID of the session that is now logged into. Left padded
    // with spaces.
    const std::string& accepted_session() const;
    std::string& accepted_session();
    void set_accepted_session(const std::string& value);

    // Accepted Sequence Number: The sequence number in ASCII of the next Sequenced Message to
    // be sent. Left padded with spaces.
    const std::string& accepted_sequence_number() const;
    std::string& accepted_sequence_number();
    void set_accepted_sequence_number(const std::string& value);

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

    bool operator==(const LoginAcceptedPacket& other) const;
    bool operator!=(const LoginAcceptedPacket& other) const;

  private:
    std::string accepted_session_{};
    std::string accepted_sequence_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
