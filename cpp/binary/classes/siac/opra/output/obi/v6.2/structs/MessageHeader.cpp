#include "MessageHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::opra::output::obi::v6_2 {

MessageHeader::MessageHeader(ParticipantId participant_id, MessageCategory message_category)
  : participant_id_(participant_id), message_category_(message_category) {}

ParticipantId MessageHeader::participant_id() const { return participant_id_; }
void MessageHeader::set_participant_id(ParticipantId value) { participant_id_ = value; }

MessageCategory MessageHeader::message_category() const { return message_category_; }
void MessageHeader::set_message_category(MessageCategory value) { message_category_ = value; }

std::size_t MessageHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeader", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    message_category_ = static_cast<MessageCategory>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MessageHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeader", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(message_category_));
    offset += 1;

    return offset;
}

std::size_t MessageHeader::encoded_size() const {
    return wire_size;
}

void MessageHeader::print(std::ostream& out) const {
    out << "MessageHeader{";
    out << "participant_id=";
    out << participant_id_;
    out << ", message_category=";
    out << message_category_;
    out << '}';
}

bool MessageHeader::operator==(const MessageHeader& other) const {
    return participant_id_ == other.participant_id_
        && message_category_ == other.message_category_;
}

bool MessageHeader::operator!=(const MessageHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
