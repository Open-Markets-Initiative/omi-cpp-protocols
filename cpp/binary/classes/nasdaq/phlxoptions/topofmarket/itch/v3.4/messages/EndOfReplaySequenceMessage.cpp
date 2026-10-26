#include "EndOfReplaySequenceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

EndOfReplaySequenceMessage::EndOfReplaySequenceMessage(const std::string& end_of_replay_sequence_number)
  : end_of_replay_sequence_number_(end_of_replay_sequence_number) {}

const std::string& EndOfReplaySequenceMessage::end_of_replay_sequence_number() const { return end_of_replay_sequence_number_; }
std::string& EndOfReplaySequenceMessage::end_of_replay_sequence_number() { return end_of_replay_sequence_number_; }
void EndOfReplaySequenceMessage::set_end_of_replay_sequence_number(const std::string& value) { end_of_replay_sequence_number_ = value; }

SequencedMessageCode EndOfReplaySequenceMessage::type() const { return message_type; }

std::string_view EndOfReplaySequenceMessage::name() const { return "End Of Replay Sequence Message"; }

std::size_t EndOfReplaySequenceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfReplaySequenceMessage", wire_size, length);

    end_of_replay_sequence_number_ = wire::read_text(data + offset, 20, ' ');
    offset += 20;

    return offset;
}

std::size_t EndOfReplaySequenceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfReplaySequenceMessage", wire_size, capacity);

    wire::write_text(data + offset, 20, ' ', end_of_replay_sequence_number_);
    offset += 20;

    return offset;
}

std::size_t EndOfReplaySequenceMessage::encoded_size() const {
    return wire_size;
}

void EndOfReplaySequenceMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> EndOfReplaySequenceMessage::clone() const {
    return std::make_unique<EndOfReplaySequenceMessage>(*this);
}

void EndOfReplaySequenceMessage::print(std::ostream& out) const {
    out << "EndOfReplaySequenceMessage{";
    out << "end_of_replay_sequence_number=";
    print::text(out, end_of_replay_sequence_number_);
    out << '}';
}

bool EndOfReplaySequenceMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const EndOfReplaySequenceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfReplaySequenceMessage::operator==(const EndOfReplaySequenceMessage& other) const {
    return end_of_replay_sequence_number_ == other.end_of_replay_sequence_number_;
}

bool EndOfReplaySequenceMessage::operator!=(const EndOfReplaySequenceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
