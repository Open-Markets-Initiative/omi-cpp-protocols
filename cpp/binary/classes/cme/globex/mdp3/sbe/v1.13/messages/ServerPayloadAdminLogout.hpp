#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/ServerTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// AdminLogout
class ServerPayloadAdminLogout : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::AdminLogout;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 180;

    ServerPayloadAdminLogout() = default;
    ServerPayloadAdminLogout(const std::string& logout_text);

    // Logout Text: Free format text string. May include logout confirmation or reason for
    // logout
    const std::string& logout_text() const;
    std::string& logout_text();
    void set_logout_text(const std::string& value);

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

    bool operator==(const ServerPayloadAdminLogout& other) const;
    bool operator!=(const ServerPayloadAdminLogout& other) const;

  private:
    std::string logout_text_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
