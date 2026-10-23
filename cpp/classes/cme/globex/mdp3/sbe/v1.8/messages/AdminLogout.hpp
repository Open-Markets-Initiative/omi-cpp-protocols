#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/MktdataPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

class MktdataPayloadVisitor;

// AdminLogout
class AdminLogout : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::AdminLogout;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 100;

    AdminLogout() = default;
    AdminLogout(const std::string& text);

    // Text: Reject reason details
    const std::string& text() const;
    std::string& text();
    void set_text(const std::string& value);

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

    bool operator==(const AdminLogout& other) const;
    bool operator!=(const AdminLogout& other) const;

  private:
    std::string text_{};
};

} // namespace cme::globex::mdp3::sbe::v1_8
