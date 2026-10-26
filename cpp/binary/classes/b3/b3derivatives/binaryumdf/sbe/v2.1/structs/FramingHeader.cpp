#include "FramingHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

FramingHeader::FramingHeader(std::uint16_t message_length, std::uint16_t encoding_type)
  : message_length_(message_length), encoding_type_(encoding_type) {}

std::uint16_t FramingHeader::message_length() const { return message_length_; }
void FramingHeader::set_message_length(std::uint16_t value) { message_length_ = value; }

std::uint16_t FramingHeader::encoding_type() const { return encoding_type_; }
void FramingHeader::set_encoding_type(std::uint16_t value) { encoding_type_ = value; }

std::size_t FramingHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FramingHeader", wire_size, length);

    message_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    encoding_type_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t FramingHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FramingHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(encoding_type_));
    offset += 2;

    return offset;
}

std::size_t FramingHeader::encoded_size() const {
    return wire_size;
}

void FramingHeader::print(std::ostream& out) const {
    out << "FramingHeader{";
    out << "message_length=";
    out << message_length_;
    out << ", encoding_type=";
    out << encoding_type_;
    out << '}';
}

bool FramingHeader::operator==(const FramingHeader& other) const {
    return message_length_ == other.message_length_
        && encoding_type_ == other.encoding_type_;
}

bool FramingHeader::operator!=(const FramingHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FramingHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
