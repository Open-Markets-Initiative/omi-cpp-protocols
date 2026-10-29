#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/RetransmitRejectCode.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// RetransmitRejectMessage
class RetransmitRejectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::RetransmitRejectMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    RetransmitRejectMessage() = default;
    RetransmitRejectMessage(std::uint32_t session_id, std::chrono::nanoseconds request_timestamp, RetransmitRejectCode retransmit_reject_code);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Request Timestamp: requestTimestamp
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Retransmit Reject Code: retransmitRejectCode
    RetransmitRejectCode retransmit_reject_code() const;
    void set_retransmit_reject_code(RetransmitRejectCode value);

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

    bool operator==(const RetransmitRejectMessage& other) const;
    bool operator!=(const RetransmitRejectMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::chrono::nanoseconds request_timestamp_{};
    RetransmitRejectCode retransmit_reject_code_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
