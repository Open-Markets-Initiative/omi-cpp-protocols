#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/NegotiationRejectCode.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// NegotiateRejectMessage
class NegotiateRejectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::NegotiateRejectMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    NegotiateRejectMessage() = default;
    NegotiateRejectMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, std::optional<std::uint32_t> entering_firm_optional, NegotiationRejectCode negotiation_reject_code, const std::array<std::byte, 3>& offset_25_padding_3, std::optional<std::uint64_t> current_session_ver_id);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Request Timestamp: requestTimestamp
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Entering Firm Optional: enteringFirm
    std::optional<std::uint32_t> entering_firm_optional() const;
    void set_entering_firm_optional(std::optional<std::uint32_t> value);

    // Negotiation Reject Code: negotiationRejectCode
    NegotiationRejectCode negotiation_reject_code() const;
    void set_negotiation_reject_code(NegotiationRejectCode value);

    // Offset 25 Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& offset_25_padding_3() const;
    std::array<std::byte, 3>& offset_25_padding_3();
    void set_offset_25_padding_3(const std::array<std::byte, 3>& value);

    // Current Session Ver Id: currentSessionVerID
    std::optional<std::uint64_t> current_session_ver_id() const;
    void set_current_session_ver_id(std::optional<std::uint64_t> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const NegotiateRejectMessage& other) const;
    bool operator!=(const NegotiateRejectMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    std::chrono::nanoseconds request_timestamp_{};
    std::optional<std::uint32_t> entering_firm_optional_{};
    NegotiationRejectCode negotiation_reject_code_{};
    std::array<std::byte, 3> offset_25_padding_3_{};
    std::optional<std::uint64_t> current_session_ver_id_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
