#include "MessageHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

MessageHeader::MessageHeader(std::uint16_t message_length, MessageType message_type)
  : message_length_(message_length), message_type_(message_type) {}

std::uint16_t MessageHeader::message_length() const { return message_length_; }
void MessageHeader::set_message_length(std::uint16_t value) { message_length_ = value; }

MessageType MessageHeader::message_type() const { return message_type_; }
void MessageHeader::set_message_type(MessageType value) { message_type_ = value; }

std::size_t MessageHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeader", wire_size, length);

    message_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    message_type_ = static_cast<MessageType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MessageHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(message_type_));
    offset += 1;

    return offset;
}

std::size_t MessageHeader::encoded_size() const {
    return wire_size;
}

void MessageHeader::print(std::ostream& out) const {
    out << "MessageHeader{";
    out << "message_length=";
    out << message_length_;
    out << ", message_type=";
    out << message_type_;
    out << '}';
}

bool MessageHeader::operator==(const MessageHeader& other) const {
    return message_length_ == other.message_length_
        && message_type_ == other.message_type_;
}

bool MessageHeader::operator!=(const MessageHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::iextp::v1_04
