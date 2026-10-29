#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "PriorDayMessagePayload.hpp"

namespace siac::cts::output::cta::v2_10 {

class PriorDayMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownPriorDayMessagePayload : public PriorDayMessagePayload {
  public:
    UnknownPriorDayMessagePayload() = default;
    explicit UnknownPriorDayMessagePayload(PriorDayMessagePayloadCode code);
    UnknownPriorDayMessagePayload(PriorDayMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(PriorDayMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // PriorDayMessagePayload
    PriorDayMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PriorDayMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<PriorDayMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PriorDayMessagePayload& other) const override;

    bool operator==(const UnknownPriorDayMessagePayload& other) const;
    bool operator!=(const UnknownPriorDayMessagePayload& other) const;

  private:
    PriorDayMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::cts::output::cta::v2_10
