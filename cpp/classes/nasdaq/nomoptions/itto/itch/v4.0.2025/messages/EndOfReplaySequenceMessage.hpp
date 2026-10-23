#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// The End of replay Sequence message reflects the sequence number at the time replay of
// existing messages is complete. The firms can then use this sequence number to resume on the
// real time Mold channel.
class EndOfReplaySequenceMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::EndOfReplaySequenceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    EndOfReplaySequenceMessage() = default;
    EndOfReplaySequenceMessage(const std::string& end_of_replay_sequence_number);

    // End Of Replay Sequence Number: Use this sequence number to resume on the real time Mold
    // channel.
    const std::string& end_of_replay_sequence_number() const;
    std::string& end_of_replay_sequence_number();
    void set_end_of_replay_sequence_number(const std::string& value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const EndOfReplaySequenceMessage& other) const;
    bool operator!=(const EndOfReplaySequenceMessage& other) const;

  private:
    std::string end_of_replay_sequence_number_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
