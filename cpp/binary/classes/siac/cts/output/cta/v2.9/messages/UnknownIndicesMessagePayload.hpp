#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "IndicesMessagePayload.hpp"

namespace siac::cts::output::cta::v2_9 {

class IndicesMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownIndicesMessagePayload : public IndicesMessagePayload {
  public:
    UnknownIndicesMessagePayload() = default;
    explicit UnknownIndicesMessagePayload(IndicesMessagePayloadCode code);
    UnknownIndicesMessagePayload(IndicesMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(IndicesMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // IndicesMessagePayload
    IndicesMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(IndicesMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<IndicesMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const IndicesMessagePayload& other) const override;

    bool operator==(const UnknownIndicesMessagePayload& other) const;
    bool operator!=(const UnknownIndicesMessagePayload& other) const;

  private:
    IndicesMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::cts::output::cta::v2_9
