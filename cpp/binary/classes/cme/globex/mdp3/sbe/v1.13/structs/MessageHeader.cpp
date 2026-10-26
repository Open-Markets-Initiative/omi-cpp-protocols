#include "MessageHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MessageHeader::MessageHeader(std::uint16_t message_size, const SimpleBinaryHeader& simple_binary_header)
  : message_size_(message_size), simple_binary_header_(simple_binary_header) {}

std::uint16_t MessageHeader::message_size() const { return message_size_; }
void MessageHeader::set_message_size(std::uint16_t value) { message_size_ = value; }

const SimpleBinaryHeader& MessageHeader::simple_binary_header() const { return simple_binary_header_; }
SimpleBinaryHeader& MessageHeader::simple_binary_header() { return simple_binary_header_; }
void MessageHeader::set_simple_binary_header(const SimpleBinaryHeader& value) { simple_binary_header_ = value; }

std::size_t MessageHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeader", wire_size, length);

    message_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    offset += simple_binary_header_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MessageHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(message_size_));
    offset += 2;

    offset += simple_binary_header_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MessageHeader::encoded_size() const {
    return wire_size;
}

void MessageHeader::print(std::ostream& out) const {
    out << "MessageHeader{";
    out << "message_size=";
    out << message_size_;
    out << ", simple_binary_header=";
    simple_binary_header_.print(out);
    out << '}';
}

bool MessageHeader::operator==(const MessageHeader& other) const {
    return message_size_ == other.message_size_
        && simple_binary_header_ == other.simple_binary_header_;
}

bool MessageHeader::operator!=(const MessageHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
