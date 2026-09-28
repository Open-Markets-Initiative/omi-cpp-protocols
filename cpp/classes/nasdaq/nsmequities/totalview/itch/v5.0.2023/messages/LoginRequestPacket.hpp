#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new
// TCP/IP socket connection to the server
class LoginRequestPacket : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = ClientPacketType::LoginRequestPacket;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 46;

    LoginRequestPacket() = default;
    LoginRequestPacket(const std::string& username, const std::string& password, const std::string& requested_session, const std::string& requested_sequence_number);

    // Username: Session username
    const std::string& username() const;
    std::string& username();
    void set_username(const std::string& value);

    // Password: Login password
    const std::string& password() const;
    std::string& password();
    void set_password(const std::string& value);

    // Requested Session: Specifies the session the client would like to log into, or all
    // blanks to log into the currently active session.
    const std::string& requested_session() const;
    std::string& requested_session();
    void set_requested_session(const std::string& value);

    // Requested Sequence Number: Specifies the next sequence number in ASCII the client wants
    // to receive upon connection, or 0 to start receiving the most recently generated message.
    const std::string& requested_sequence_number() const;
    std::string& requested_sequence_number();
    void set_requested_sequence_number(const std::string& value);

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

    bool operator==(const LoginRequestPacket& other) const;
    bool operator!=(const LoginRequestPacket& other) const;

  private:
    std::string username_{};
    std::string password_{};
    std::string requested_session_{};
    std::string requested_sequence_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
