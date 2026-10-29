#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Day.hpp"
#include "../enums/MessageType.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Message Header
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 11;

    MessageHeader() = default;
    MessageHeader(std::uint16_t message_length, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, MessageType message_type);

    // Message Length: Length of data message not including this field
    std::uint16_t message_length() const;
    void set_message_length(std::uint16_t value);

    // Tracking Number: Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Number of nanoseconds past midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Message Type: Code identifying this message type
    MessageType message_type() const;
    void set_message_type(MessageType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MessageHeader& other) const;
    bool operator!=(const MessageHeader& other) const;

  private:
    std::uint16_t message_length_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    MessageType message_type_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
