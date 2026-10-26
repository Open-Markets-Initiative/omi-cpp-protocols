#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/MktdataPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

class MktdataPayloadVisitor;

// AdminHeartbeat
class AdminHeartbeat : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::AdminHeartbeat;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 0;

    AdminHeartbeat() = default;

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

    bool operator==(const AdminHeartbeat& other) const;
    bool operator!=(const AdminHeartbeat& other) const;

  private:
};

} // namespace cme::globex::mdp3::sbe::v1_8
