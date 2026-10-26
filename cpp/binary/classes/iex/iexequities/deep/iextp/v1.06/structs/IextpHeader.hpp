#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace iex::iexequities::deep::iextp::v1_06 {

// IexTp packet header
class IextpHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 40;

    IextpHeader() = default;
    IextpHeader(std::uint8_t version, const std::array<std::byte, 1>& reserved, std::uint16_t message_protocol_id, std::uint32_t channel_id, std::uint32_t session_id, std::uint16_t payload_length, std::uint16_t message_count, std::uint64_t stream_offset, std::uint64_t first_message_sequence_number, std::chrono::nanoseconds send_time);

    // Version: Version of transport specification
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Reserved: Reserved byte
    const std::array<std::byte, 1>& reserved() const;
    std::array<std::byte, 1>& reserved();
    void set_reserved(const std::array<std::byte, 1>& value);

    // Message Protocol Id: Unique identifier of the higher layer protocol
    std::uint16_t message_protocol_id() const;
    void set_message_protocol_id(std::uint16_t value);

    // Channel Id: Identifies the stream of bytes sequenced messages
    std::uint32_t channel_id() const;
    void set_channel_id(std::uint32_t value);

    // Session Id: Identifies the session
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Payload Length: Byte length of the payload
    std::uint16_t payload_length() const;
    void set_payload_length(std::uint16_t value);

    // Message Count: Number of messages in the payload
    std::uint16_t message_count() const;
    void set_message_count(std::uint16_t value);

    // Stream Offset: Byte offset of the data stream
    std::uint64_t stream_offset() const;
    void set_stream_offset(std::uint64_t value);

    // First Message Sequence Number: Sequence of the first message in the segment
    std::uint64_t first_message_sequence_number() const;
    void set_first_message_sequence_number(std::uint64_t value);

    // Send Time: Send time of segment
    std::chrono::nanoseconds send_time() const;
    void set_send_time(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IextpHeader& other) const;
    bool operator!=(const IextpHeader& other) const;

  private:
    std::uint8_t version_{};
    std::array<std::byte, 1> reserved_{};
    std::uint16_t message_protocol_id_{};
    std::uint32_t channel_id_{};
    std::uint32_t session_id_{};
    std::uint16_t payload_length_{};
    std::uint16_t message_count_{};
    std::uint64_t stream_offset_{};
    std::uint64_t first_message_sequence_number_{};
    std::chrono::nanoseconds send_time_{};
};

std::ostream& operator<<(std::ostream& out, const IextpHeader& value);

} // namespace iex::iexequities::deep::iextp::v1_06
