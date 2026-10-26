#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "Message.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

class Visitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownMessage : public Message {
  public:
    UnknownMessage() = default;
    explicit UnknownMessage(MessageCode code);
    UnknownMessage(MessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(MessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const UnknownMessage& other) const;
    bool operator!=(const UnknownMessage& other) const;

  private:
    MessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace iex::iexequities::deepplus::iextp::v1_05
