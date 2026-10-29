#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ErrorCodes.hpp"
#include "../messages/ServerTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ServerTcpMessageVisitor;

// NegotiationReject
class ServerPayloadNegotiationReject : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::NegotiationReject;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 70;

    ServerPayloadNegotiationReject() = default;
    ServerPayloadNegotiationReject(const std::string& reason, std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, ErrorCodes error_codes, const std::array<std::byte, 5>& padding_5);

    // Reason: Reject reason details
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

    // Uuid: Session Identifier defined as type long uInt64, recommended to use timestamp as
    // number of microseconds since Unix epoch
    std::uint64_t uuid() const;
    void set_uuid(std::uint64_t value);

    // Request Timestamp: Time of request, recommended to use timestamp as number of
    // nanoseconds since Unix epoch
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Error Codes: Error code for reject reason
    ErrorCodes error_codes() const;
    void set_error_codes(ErrorCodes value);

    // Padding 5: 5 bytes padding
    const std::array<std::byte, 5>& padding_5() const;
    std::array<std::byte, 5>& padding_5();
    void set_padding_5(const std::array<std::byte, 5>& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadNegotiationReject& other) const;
    bool operator!=(const ServerPayloadNegotiationReject& other) const;

  private:
    std::string reason_{};
    std::uint64_t uuid_{};
    std::chrono::nanoseconds request_timestamp_{};
    ErrorCodes error_codes_{};
    std::array<std::byte, 5> padding_5_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
