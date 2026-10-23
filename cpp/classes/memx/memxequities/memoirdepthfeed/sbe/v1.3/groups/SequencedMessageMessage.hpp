#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../structs/SbeMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Message List Element
class SequencedMessageMessage {
  public:

    SequencedMessageMessage() = default;
    SequencedMessageMessage(std::uint16_t message_length, const SbeMessage& sbe_message);

    // Message Length: Number of bytes in the following message
    std::uint16_t message_length() const;
    void set_message_length(std::uint16_t value);

    // Sbe Message: Sbe Message
    const SbeMessage& sbe_message() const;
    SbeMessage& sbe_message();
    void set_sbe_message(const SbeMessage& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SequencedMessageMessage& other) const;
    bool operator!=(const SequencedMessageMessage& other) const;

  private:
    std::uint16_t message_length_{};
    SbeMessage sbe_message_{};
};

std::ostream& operator<<(std::ostream& out, const SequencedMessageMessage& value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
