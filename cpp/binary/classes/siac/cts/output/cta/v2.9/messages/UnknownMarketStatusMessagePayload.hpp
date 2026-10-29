#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "MarketStatusMessagePayload.hpp"

namespace siac::cts::output::cta::v2_9 {

class MarketStatusMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownMarketStatusMessagePayload : public MarketStatusMessagePayload {
  public:
    UnknownMarketStatusMessagePayload() = default;
    explicit UnknownMarketStatusMessagePayload(MarketStatusMessagePayloadCode code);
    UnknownMarketStatusMessagePayload(MarketStatusMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(MarketStatusMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // MarketStatusMessagePayload
    MarketStatusMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MarketStatusMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<MarketStatusMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MarketStatusMessagePayload& other) const override;

    bool operator==(const UnknownMarketStatusMessagePayload& other) const;
    bool operator!=(const UnknownMarketStatusMessagePayload& other) const;

  private:
    MarketStatusMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::cts::output::cta::v2_9
