#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/ServerTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// AdminLogin
class ServerPayloadAdminLogin : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::AdminLogin;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    ServerPayloadAdminLogin() = default;
    ServerPayloadAdminLogin(std::int8_t heart_bt_int);

    // Heart Bt Int: Heartbeat interval (seconds)
    std::int8_t heart_bt_int() const;
    void set_heart_bt_int(std::int8_t value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadAdminLogin& other) const;
    bool operator!=(const ServerPayloadAdminLogin& other) const;

  private:
    std::int8_t heart_bt_int_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
