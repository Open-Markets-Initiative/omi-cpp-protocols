#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ResultCode.hpp"
#include "../messages/TcpMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class TcpMessageVisitor;

// Tcp login response. Packet Type A indicates accepted and J indicates rejected.
class LoginResultMessage : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = PacketType::LoginResultMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 2;

    LoginResultMessage() = default;
    LoginResultMessage(std::uint8_t multicast_group_number, ResultCode result_code);

    // Multicast Group Number: Multicast Group Number for the request target
    std::uint8_t multicast_group_number() const;
    void set_multicast_group_number(std::uint8_t value);

    // Result Code: Set to the result code of the login request
    ResultCode result_code() const;
    void set_result_code(ResultCode value);

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

    bool operator==(const LoginResultMessage& other) const;
    bool operator!=(const LoginResultMessage& other) const;

  private:
    std::uint8_t multicast_group_number_{};
    ResultCode result_code_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
