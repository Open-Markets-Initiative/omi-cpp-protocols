#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "ClientTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

class ClientTcpMessageVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownClientTcpMessage : public ClientTcpMessage {
  public:
    UnknownClientTcpMessage() = default;
    explicit UnknownClientTcpMessage(ClientTcpMessageCode code);
    UnknownClientTcpMessage(ClientTcpMessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(ClientTcpMessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // ClientTcpMessage
    ClientTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ClientTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ClientTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ClientTcpMessage& other) const override;

    bool operator==(const UnknownClientTcpMessage& other) const;
    bool operator!=(const UnknownClientTcpMessage& other) const;

  private:
    ClientTcpMessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace cme::globex::mdp3::sbe::v1_8
