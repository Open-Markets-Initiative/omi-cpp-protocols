#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class GatewayMessageVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownGatewayMessage : public GatewayMessage {
  public:
    UnknownGatewayMessage() = default;
    explicit UnknownGatewayMessage(GatewayMessageCode code);
    UnknownGatewayMessage(GatewayMessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(GatewayMessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // GatewayMessage
    GatewayMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(GatewayMessageVisitor& visitor) const override;
    std::unique_ptr<GatewayMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const GatewayMessage& other) const override;

    bool operator==(const UnknownGatewayMessage& other) const;
    bool operator!=(const UnknownGatewayMessage& other) const;

  private:
    GatewayMessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace databento::marketdata::normalized::dbn::v1
