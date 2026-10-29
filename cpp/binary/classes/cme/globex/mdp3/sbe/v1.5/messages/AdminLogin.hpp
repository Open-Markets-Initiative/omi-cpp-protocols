#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/MktdataPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class MktdataPayloadVisitor;

// AdminLogin
class AdminLogin : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::AdminLogin;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    AdminLogin() = default;
    AdminLogin(std::int8_t heart_bt_int);

    // Heart Bt Int: Heartbeat interval (seconds)
    std::int8_t heart_bt_int() const;
    void set_heart_bt_int(std::int8_t value);

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

    bool operator==(const AdminLogin& other) const;
    bool operator!=(const AdminLogin& other) const;

  private:
    std::int8_t heart_bt_int_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
