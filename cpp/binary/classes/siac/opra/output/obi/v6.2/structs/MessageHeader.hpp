#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/MessageCategory.hpp"
#include "../enums/ParticipantId.hpp"

namespace siac::opra::output::obi::v6_2 {

// Opra Message Header first level dispatch
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 2;

    MessageHeader() = default;
    MessageHeader(ParticipantId participant_id, MessageCategory message_category);

    // Participant Id: ASCII character that identifies the Participant or Processor that
    // initiated the message.
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Message Category: Message identifier
    MessageCategory message_category() const;
    void set_message_category(MessageCategory value);

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
    ParticipantId participant_id_{};
    MessageCategory message_category_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace siac::opra::output::obi::v6_2
