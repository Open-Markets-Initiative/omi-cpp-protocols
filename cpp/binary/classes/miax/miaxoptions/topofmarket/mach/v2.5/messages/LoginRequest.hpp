#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class TcpMessageVisitor;

// The SesM client must send a Login request packet immediately upon establishing a new TCP/IP
// socket connection to the server
class LoginRequest : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = SesmPacketType::LoginRequest;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 35;

    LoginRequest() = default;
    LoginRequest(const std::string& sesm_version, const std::string& username, const std::string& computer_id, const std::string& application_protocol, std::uint8_t requested_trading_session_id, std::uint64_t requested_sequence_number);

    // Sesm Version: Protocol version
    const std::string& sesm_version() const;
    std::string& sesm_version();
    void set_sesm_version(const std::string& value);

    // Username: issued by MIAX during initial setup
    const std::string& username() const;
    std::string& username();
    void set_username(const std::string& value);

    // Computer Id: issued by MIAX Futures Exchange during initial setup
    const std::string& computer_id() const;
    std::string& computer_id();
    void set_computer_id(const std::string& value);

    // Application Protocol: Miax Application Protocol
    const std::string& application_protocol() const;
    std::string& application_protocol();
    void set_application_protocol(const std::string& value);

    // Requested Trading Session Id: Specifies the session the client would like to log into,
    // or zero to log into the currently active session
    std::uint8_t requested_trading_session_id() const;
    void set_requested_trading_session_id(std::uint8_t value);

    // Requested Sequence Number: Specifies client requested sequence number
    std::uint64_t requested_sequence_number() const;
    void set_requested_sequence_number(std::uint64_t value);

    // TcpMessage
    TcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TcpMessageVisitor& visitor) const override;
    std::unique_ptr<TcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TcpMessage& other) const override;

    bool operator==(const LoginRequest& other) const;
    bool operator!=(const LoginRequest& other) const;

  private:
    std::string sesm_version_{};
    std::string username_{};
    std::string computer_id_{};
    std::string application_protocol_{};
    std::uint8_t requested_trading_session_id_{};
    std::uint64_t requested_sequence_number_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
