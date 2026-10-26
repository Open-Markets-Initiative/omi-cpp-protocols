#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/LoginStatus.hpp"
#include "../messages/TcpMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class TcpMessageVisitor;

// The SesM server sends a Login response packet in response a Login request packet from the
// client
class LoginResponse : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = SesmPacketType::LoginResponse;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    LoginResponse() = default;
    LoginResponse(std::uint8_t number_of_matching_engines, LoginStatus login_status, std::uint8_t trading_session_id, std::uint64_t highest_sequence_number);

    // Number Of Matching Engines: Count of all Matching Engines for the exchange
    std::uint8_t number_of_matching_engines() const;
    void set_number_of_matching_engines(std::uint8_t value);

    // Login Status: Login Status
    LoginStatus login_status() const;
    void set_login_status(LoginStatus value);

    // Trading Session Id: The current trading session ID of the corresponding Matching Engine
    std::uint8_t trading_session_id() const;
    void set_trading_session_id(std::uint8_t value);

    // Highest Sequence Number: the highest sequence number that the server currently has for
    // the client
    std::uint64_t highest_sequence_number() const;
    void set_highest_sequence_number(std::uint64_t value);

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

    bool operator==(const LoginResponse& other) const;
    bool operator!=(const LoginResponse& other) const;

  private:
    std::uint8_t number_of_matching_engines_{};
    LoginStatus login_status_{};
    std::uint8_t trading_session_id_{};
    std::uint64_t highest_sequence_number_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
