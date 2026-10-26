#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "QuoteMessagePayload.hpp"

namespace siac::cqs::output::cta::v2_10_a {

class QuoteMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownQuoteMessagePayload : public QuoteMessagePayload {
  public:
    UnknownQuoteMessagePayload() = default;
    explicit UnknownQuoteMessagePayload(QuoteMessagePayloadCode code);
    UnknownQuoteMessagePayload(QuoteMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(QuoteMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // QuoteMessagePayload
    QuoteMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(QuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<QuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const QuoteMessagePayload& other) const override;

    bool operator==(const UnknownQuoteMessagePayload& other) const;
    bool operator!=(const UnknownQuoteMessagePayload& other) const;

  private:
    QuoteMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::cqs::output::cta::v2_10_a
