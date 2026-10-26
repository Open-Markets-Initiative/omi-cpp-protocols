#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "MdpsessionmgmtPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

class MdpsessionmgmtPayloadVisitor;

// A message whose code the specification does not list. It keeps its bytes as they
// came, so a packet holding one still encodes back to what was received, and a feed
// that has grown a message since its specification was written still decodes.
class UnknownMdpsessionmgmtPayload : public MdpsessionmgmtPayload {
  public:
    UnknownMdpsessionmgmtPayload() = default;
    explicit UnknownMdpsessionmgmtPayload(MdpsessionmgmtPayloadCode code);
    UnknownMdpsessionmgmtPayload(MdpsessionmgmtPayloadCode code, const std::vector<std::byte>& body);

    // The code that selected this message
    void set_type(MdpsessionmgmtPayloadCode code);

    // The bytes of the message body as they were on the wire
    const std::vector<std::byte>& body() const;
    std::vector<std::byte>& body();
    void set_body(const std::vector<std::byte>& value);

    // MdpsessionmgmtPayload
    MdpsessionmgmtPayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MdpsessionmgmtPayloadVisitor& visitor) const override;
    std::unique_ptr<MdpsessionmgmtPayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MdpsessionmgmtPayload& other) const override;

    bool operator==(const UnknownMdpsessionmgmtPayload& other) const;
    bool operator!=(const UnknownMdpsessionmgmtPayload& other) const;

  private:
    MdpsessionmgmtPayloadCode type_{};
    std::vector<std::byte> body_;
};

} // namespace cme::globex::mdp3::sbe::v1_9
