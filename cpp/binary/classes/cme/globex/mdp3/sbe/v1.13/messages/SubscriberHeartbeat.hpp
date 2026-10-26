#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/MdpsessionmgmtPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MdpsessionmgmtPayloadVisitor;

// SubscriberHeartbeat
class SubscriberHeartbeat : public MdpsessionmgmtPayload {
  public:
    // The code that selects this message
    static constexpr MdpsessionmgmtPayloadCode message_type = TemplateId::SubscriberHeartbeat;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 0;

    SubscriberHeartbeat() = default;

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

    bool operator==(const SubscriberHeartbeat& other) const;
    bool operator!=(const SubscriberHeartbeat& other) const;

  private:
};

} // namespace cme::globex::mdp3::sbe::v1_13
