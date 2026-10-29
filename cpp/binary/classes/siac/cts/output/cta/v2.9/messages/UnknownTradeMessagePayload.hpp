#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "TradeMessagePayload.hpp"

namespace siac::cts::output::cta::v2_9 {

class TradeMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownTradeMessagePayload : public TradeMessagePayload {
  public:
    UnknownTradeMessagePayload() = default;
    explicit UnknownTradeMessagePayload(TradeMessagePayloadCode code);
    UnknownTradeMessagePayload(TradeMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(TradeMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // TradeMessagePayload
    TradeMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TradeMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<TradeMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TradeMessagePayload& other) const override;

    bool operator==(const UnknownTradeMessagePayload& other) const;
    bool operator!=(const UnknownTradeMessagePayload& other) const;

  private:
    TradeMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::cts::output::cta::v2_9
