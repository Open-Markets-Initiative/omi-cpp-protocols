#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// RetransmitRequestMessage
class RetransmitRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::RetransmitRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    RetransmitRequestMessage() = default;
    RetransmitRequestMessage(std::uint32_t session_id, std::chrono::nanoseconds timestamp, std::uint32_t from_seq_no, std::uint32_t count);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Timestamp: timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // From Seq No: fromSeqNo
    std::uint32_t from_seq_no() const;
    void set_from_seq_no(std::uint32_t value);

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

    bool operator==(const RetransmitRequestMessage& other) const;
    bool operator!=(const RetransmitRequestMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t from_seq_no_{};
    std::uint32_t count_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
