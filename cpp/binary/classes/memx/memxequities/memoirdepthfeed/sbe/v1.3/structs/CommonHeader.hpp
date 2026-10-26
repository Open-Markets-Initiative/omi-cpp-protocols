#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MessageType.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Common Header
class CommonHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 18;

    CommonHeader() = default;
    CommonHeader(MessageType message_type, std::uint8_t header_length, std::uint64_t session_id, std::uint64_t sequence_number);

    // Message Type: Message Type
    MessageType message_type() const;
    void set_message_type(MessageType value);

    // Header Length: Total bytes in this header
    std::uint8_t header_length() const;
    void set_header_length(std::uint8_t value);

    // Session Id: Session identifier
    std::uint64_t session_id() const;
    void set_session_id(std::uint64_t value);

    // Sequence Number: Sequence Number
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CommonHeader& other) const;
    bool operator!=(const CommonHeader& other) const;

  private:
    MessageType message_type_{};
    std::uint8_t header_length_{};
    std::uint64_t session_id_{};
    std::uint64_t sequence_number_{};
};

std::ostream& operator<<(std::ostream& out, const CommonHeader& value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
