#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "TcpMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class TcpMessageVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownTcpMessage : public TcpMessage {
  public:
    UnknownTcpMessage() = default;
    explicit UnknownTcpMessage(TcpMessageCode code);
    UnknownTcpMessage(TcpMessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(TcpMessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

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

    bool operator==(const UnknownTcpMessage& other) const;
    bool operator!=(const UnknownTcpMessage& other) const;

  private:
    TcpMessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
