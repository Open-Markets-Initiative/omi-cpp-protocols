#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/RejectReasonCode.hpp"
#include "../messages/ServerMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class ServerMessageVisitor;

// The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from
// the client
class LoginRejectedPacket : public ServerMessage {
  public:
    // The code that selects this message
    static constexpr ServerMessageCode message_type = ServerPacketType::LoginRejectedPacket;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    LoginRejectedPacket() = default;
    LoginRejectedPacket(RejectReasonCode reject_reason_code);

    // Reject Reason Code: Login Reject Codes
    RejectReasonCode reject_reason_code() const;
    void set_reject_reason_code(RejectReasonCode value);

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

    bool operator==(const LoginRejectedPacket& other) const;
    bool operator!=(const LoginRejectedPacket& other) const;

  private:
    RejectReasonCode reject_reason_code_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
