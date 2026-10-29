#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// RetransmissionMessage
class RetransmissionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::RetransmissionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    RetransmissionMessage() = default;
    RetransmissionMessage(std::uint32_t session_id, std::chrono::nanoseconds request_timestamp, std::uint32_t next_seq_no, std::uint32_t count);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Request Timestamp: requestTimestamp
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Next Seq No: nextSeqNo
    std::uint32_t next_seq_no() const;
    void set_next_seq_no(std::uint32_t value);

    // Count: count
    std::uint32_t count() const;
    void set_count(std::uint32_t value);

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

    bool operator==(const RetransmissionMessage& other) const;
    bool operator!=(const RetransmissionMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::chrono::nanoseconds request_timestamp_{};
    std::uint32_t next_seq_no_{};
    std::uint32_t count_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
