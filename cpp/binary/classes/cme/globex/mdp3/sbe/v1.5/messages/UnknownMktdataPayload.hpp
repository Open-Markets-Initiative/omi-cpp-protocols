#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "MktdataPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class MktdataPayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownMktdataPayload : public MktdataPayload {
  public:
    UnknownMktdataPayload() = default;
    explicit UnknownMktdataPayload(MktdataPayloadCode code);
    UnknownMktdataPayload(MktdataPayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(MktdataPayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // MktdataPayload
    MktdataPayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MktdataPayloadVisitor& visitor) const override;
    std::unique_ptr<MktdataPayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MktdataPayload& other) const override;

    bool operator==(const UnknownMktdataPayload& other) const;
    bool operator!=(const UnknownMktdataPayload& other) const;

  private:
    MktdataPayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace cme::globex::mdp3::sbe::v1_5
