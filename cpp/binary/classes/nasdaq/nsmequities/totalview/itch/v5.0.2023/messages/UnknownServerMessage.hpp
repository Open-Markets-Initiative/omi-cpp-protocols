#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "ServerMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class ServerMessageVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownServerMessage : public ServerMessage {
  public:
    UnknownServerMessage() = default;
    explicit UnknownServerMessage(ServerMessageCode code);
    UnknownServerMessage(ServerMessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(ServerMessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

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

    bool operator==(const UnknownServerMessage& other) const;
    bool operator!=(const UnknownServerMessage& other) const;

  private:
    ServerMessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
