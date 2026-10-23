#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownPayload : public Payload {
  public:
    UnknownPayload() = default;
    explicit UnknownPayload(PayloadCode code);
    UnknownPayload(PayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(PayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // Payload
    PayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PayloadVisitor& visitor) const override;
    std::unique_ptr<Payload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Payload& other) const override;

    bool operator==(const UnknownPayload& other) const;
    bool operator!=(const UnknownPayload& other) const;

  private:
    PayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
