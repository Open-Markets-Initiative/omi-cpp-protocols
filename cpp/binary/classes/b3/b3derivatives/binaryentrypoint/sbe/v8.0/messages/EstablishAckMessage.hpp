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

// EstablishAckMessage
class EstablishAckMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::EstablishAckMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    EstablishAckMessage() = default;
    EstablishAckMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, std::uint64_t keep_alive_interval, std::uint32_t next_seq_no, std::uint32_t last_incoming_seq_no);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Request Timestamp: requestTimestamp
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Keep Alive Interval: keepAliveInterval
    std::uint64_t keep_alive_interval() const;
    void set_keep_alive_interval(std::uint64_t value);

    // Next Seq No: nextSeqNo
    std::uint32_t next_seq_no() const;
    void set_next_seq_no(std::uint32_t value);

    // Last Incoming Seq No: lastIncomingSeqNo
    std::uint32_t last_incoming_seq_no() const;
    void set_last_incoming_seq_no(std::uint32_t value);

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

    bool operator==(const EstablishAckMessage& other) const;
    bool operator!=(const EstablishAckMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    std::chrono::nanoseconds request_timestamp_{};
    std::uint64_t keep_alive_interval_{};
    std::uint32_t next_seq_no_{};
    std::uint32_t last_incoming_seq_no_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
