#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "ShortEquityAndIndexQuoteMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class ShortEquityAndIndexQuoteMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownShortEquityAndIndexQuoteMessagePayload : public ShortEquityAndIndexQuoteMessagePayload {
  public:
    UnknownShortEquityAndIndexQuoteMessagePayload() = default;
    explicit UnknownShortEquityAndIndexQuoteMessagePayload(ShortEquityAndIndexQuoteMessagePayloadCode code);
    UnknownShortEquityAndIndexQuoteMessagePayload(ShortEquityAndIndexQuoteMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(ShortEquityAndIndexQuoteMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // ShortEquityAndIndexQuoteMessagePayload
    ShortEquityAndIndexQuoteMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ShortEquityAndIndexQuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ShortEquityAndIndexQuoteMessagePayload& other) const override;

    bool operator==(const UnknownShortEquityAndIndexQuoteMessagePayload& other) const;
    bool operator!=(const UnknownShortEquityAndIndexQuoteMessagePayload& other) const;

  private:
    ShortEquityAndIndexQuoteMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::opra::output::obi::v6_2
