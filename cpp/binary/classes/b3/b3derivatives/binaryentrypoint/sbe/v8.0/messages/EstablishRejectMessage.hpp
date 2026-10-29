#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/EstablishmentRejectCode.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// EstablishRejectMessage
class EstablishRejectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::EstablishRejectMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 26;

    EstablishRejectMessage() = default;
    EstablishRejectMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, EstablishmentRejectCode establishment_reject_code, const std::array<std::byte, 1>& offset_21_padding_1, std::optional<std::uint32_t> last_incoming_seq_no_optional);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Request Timestamp: requestTimestamp
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Establishment Reject Code: establishmentRejectCode
    EstablishmentRejectCode establishment_reject_code() const;
    void set_establishment_reject_code(EstablishmentRejectCode value);

    // Offset 21 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_21_padding_1() const;
    std::array<std::byte, 1>& offset_21_padding_1();
    void set_offset_21_padding_1(const std::array<std::byte, 1>& value);

    // Last Incoming Seq No Optional: lastIncomingSeqNo
    std::optional<std::uint32_t> last_incoming_seq_no_optional() const;
    void set_last_incoming_seq_no_optional(std::optional<std::uint32_t> value);

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

    bool operator==(const EstablishRejectMessage& other) const;
    bool operator!=(const EstablishRejectMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    std::chrono::nanoseconds request_timestamp_{};
    EstablishmentRejectCode establishment_reject_code_{};
    std::array<std::byte, 1> offset_21_padding_1_{};
    std::optional<std::uint32_t> last_incoming_seq_no_optional_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
