#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "EquityAndIndexLastSaleMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class EquityAndIndexLastSaleMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownEquityAndIndexLastSaleMessagePayload : public EquityAndIndexLastSaleMessagePayload {
  public:
    UnknownEquityAndIndexLastSaleMessagePayload() = default;
    explicit UnknownEquityAndIndexLastSaleMessagePayload(EquityAndIndexLastSaleMessagePayloadCode code);
    UnknownEquityAndIndexLastSaleMessagePayload(EquityAndIndexLastSaleMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(EquityAndIndexLastSaleMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // EquityAndIndexLastSaleMessagePayload
    EquityAndIndexLastSaleMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(EquityAndIndexLastSaleMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<EquityAndIndexLastSaleMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const EquityAndIndexLastSaleMessagePayload& other) const override;

    bool operator==(const UnknownEquityAndIndexLastSaleMessagePayload& other) const;
    bool operator!=(const UnknownEquityAndIndexLastSaleMessagePayload& other) const;

  private:
    EquityAndIndexLastSaleMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::opra::output::obi::v6_2
