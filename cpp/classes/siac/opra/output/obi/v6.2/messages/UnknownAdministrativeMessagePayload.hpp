#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "AdministrativeMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class AdministrativeMessagePayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownAdministrativeMessagePayload : public AdministrativeMessagePayload {
  public:
    UnknownAdministrativeMessagePayload() = default;
    explicit UnknownAdministrativeMessagePayload(AdministrativeMessagePayloadCode code);
    UnknownAdministrativeMessagePayload(AdministrativeMessagePayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(AdministrativeMessagePayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // AdministrativeMessagePayload
    AdministrativeMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(AdministrativeMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<AdministrativeMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const AdministrativeMessagePayload& other) const override;

    bool operator==(const UnknownAdministrativeMessagePayload& other) const;
    bool operator!=(const UnknownAdministrativeMessagePayload& other) const;

  private:
    AdministrativeMessagePayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace siac::opra::output::obi::v6_2
