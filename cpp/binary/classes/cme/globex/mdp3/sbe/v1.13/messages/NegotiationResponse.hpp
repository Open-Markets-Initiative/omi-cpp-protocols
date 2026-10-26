#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/MdpsessionmgmtPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MdpsessionmgmtPayloadVisitor;

// NegotiationResponse
class NegotiationResponse : public MdpsessionmgmtPayload {
  public:
    // The code that selects this message
    static constexpr MdpsessionmgmtPayloadCode message_type = TemplateId::NegotiationResponse;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    NegotiationResponse() = default;
    NegotiationResponse(std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, std::optional<std::uint16_t> secret_key_secure_id_expiration, const std::array<std::byte, 4>& padding_4);

    // Uuid: Session Identifier defined as type long uInt64, recommended to use timestamp as
    // number of microseconds since Unix epoch
    std::uint64_t uuid() const;
    void set_uuid(std::uint64_t value);

    // Request Timestamp: Time of request, recommended to use timestamp as number of
    // nanoseconds since Unix epoch
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Secret Key Secure Id Expiration: This indicates in how many days the HMAC secret key
    // will expire
    std::optional<std::uint16_t> secret_key_secure_id_expiration() const;
    void set_secret_key_secure_id_expiration(std::optional<std::uint16_t> value);

    // Padding 4: 4 bytes padding
    const std::array<std::byte, 4>& padding_4() const;
    std::array<std::byte, 4>& padding_4();
    void set_padding_4(const std::array<std::byte, 4>& value);

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

    bool operator==(const NegotiationResponse& other) const;
    bool operator!=(const NegotiationResponse& other) const;

  private:
    std::uint64_t uuid_{};
    std::chrono::nanoseconds request_timestamp_{};
    std::optional<std::uint16_t> secret_key_secure_id_expiration_{};
    std::array<std::byte, 4> padding_4_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
