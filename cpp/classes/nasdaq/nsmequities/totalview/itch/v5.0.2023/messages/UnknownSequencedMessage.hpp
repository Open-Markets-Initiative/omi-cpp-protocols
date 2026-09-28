#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class SequencedMessageVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownSequencedMessage : public SequencedMessage {
  public:
    UnknownSequencedMessage() = default;
    explicit UnknownSequencedMessage(SequencedMessageCode code);
    UnknownSequencedMessage(SequencedMessageCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(SequencedMessageCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const UnknownSequencedMessage& other) const;
    bool operator!=(const UnknownSequencedMessage& other) const;

  private:
    SequencedMessageCode type_{};
    std::vector<std::byte> body_;
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
