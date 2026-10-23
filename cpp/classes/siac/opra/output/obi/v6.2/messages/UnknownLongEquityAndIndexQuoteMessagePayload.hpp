#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "LongEquityAndIndexQuoteMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class LongEquityAndIndexQuoteMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownLongEquityAndIndexQuoteMessagePayload : public LongEquityAndIndexQuoteMessagePayload {
  public:
    UnknownLongEquityAndIndexQuoteMessagePayload() = default;
    explicit UnknownLongEquityAndIndexQuoteMessagePayload(LongEquityAndIndexQuoteMessagePayloadCode code);
    UnknownLongEquityAndIndexQuoteMessagePayload(LongEquityAndIndexQuoteMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(LongEquityAndIndexQuoteMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // LongEquityAndIndexQuoteMessagePayload
    LongEquityAndIndexQuoteMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(LongEquityAndIndexQuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const LongEquityAndIndexQuoteMessagePayload& other) const override;

    bool operator==(const UnknownLongEquityAndIndexQuoteMessagePayload& other) const;
    bool operator!=(const UnknownLongEquityAndIndexQuoteMessagePayload& other) const;

  private:
    LongEquityAndIndexQuoteMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::opra::output::obi::v6_2
