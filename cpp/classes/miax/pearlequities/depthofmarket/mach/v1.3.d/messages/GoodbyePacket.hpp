#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/LogoutReason.hpp"
#include "../messages/TcpMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class TcpMessageVisitor;

// The server may send a GoodBye packet to inform the client a reason for termination of the
// connection just before it terminates the connection
class GoodbyePacket : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = EsesmPacketType::GoodbyePacket;

    GoodbyePacket() = default;
    GoodbyePacket(LogoutReason logout_reason, const std::string& logout_text);

    // Logout Reason: Logout Request Reason
    LogoutReason logout_reason() const;
    void set_logout_reason(LogoutReason value);

    // Logout Text: Free form human readable text
    const std::string& logout_text() const;
    std::string& logout_text();
    void set_logout_text(const std::string& value);

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

    bool operator==(const GoodbyePacket& other) const;
    bool operator!=(const GoodbyePacket& other) const;

  private:
    LogoutReason logout_reason_{};
    std::string logout_text_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
