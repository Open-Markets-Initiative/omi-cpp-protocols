#include "SequencedMessageMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

SequencedMessageMessage::SequencedMessageMessage(std::uint16_t message_length, const SbeMessage& sbe_message)
  : message_length_(message_length), sbe_message_(sbe_message) {}

std::uint16_t SequencedMessageMessage::message_length() const { return message_length_; }
void SequencedMessageMessage::set_message_length(std::uint16_t value) { message_length_ = value; }

const SbeMessage& SequencedMessageMessage::sbe_message() const { return sbe_message_; }
SbeMessage& SequencedMessageMessage::sbe_message() { return sbe_message_; }
void SequencedMessageMessage::set_sbe_message(const SbeMessage& value) { sbe_message_ = value; }

std::size_t SequencedMessageMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SequencedMessageMessage", offset + 2, length);
    message_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    offset += sbe_message_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SequencedMessageMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SequencedMessageMessage", encoded_size(), capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    offset += sbe_message_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SequencedMessageMessage::encoded_size() const {
    return 2 + sbe_message_.encoded_size();
}

void SequencedMessageMessage::print(std::ostream& out) const {
    out << "SequencedMessageMessage{";
    out << "message_length=";
    out << message_length_;
    out << ", sbe_message=";
    sbe_message_.print(out);
    out << '}';
}

bool SequencedMessageMessage::operator==(const SequencedMessageMessage& other) const {
    return message_length_ == other.message_length_
        && sbe_message_ == other.sbe_message_;
}

bool SequencedMessageMessage::operator!=(const SequencedMessageMessage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SequencedMessageMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
