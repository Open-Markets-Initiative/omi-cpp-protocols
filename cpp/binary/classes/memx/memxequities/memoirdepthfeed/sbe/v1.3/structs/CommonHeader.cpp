#include "CommonHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

CommonHeader::CommonHeader(MessageType message_type, std::uint8_t header_length, std::uint64_t session_id, std::uint64_t sequence_number)
  : message_type_(message_type), header_length_(header_length), session_id_(session_id), sequence_number_(sequence_number) {}

MessageType CommonHeader::message_type() const { return message_type_; }
void CommonHeader::set_message_type(MessageType value) { message_type_ = value; }

std::uint8_t CommonHeader::header_length() const { return header_length_; }
void CommonHeader::set_header_length(std::uint8_t value) { header_length_ = value; }

std::uint64_t CommonHeader::session_id() const { return session_id_; }
void CommonHeader::set_session_id(std::uint64_t value) { session_id_ = value; }

std::uint64_t CommonHeader::sequence_number() const { return sequence_number_; }
void CommonHeader::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

std::size_t CommonHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CommonHeader", wire_size, length);

    message_type_ = static_cast<MessageType>(wire::read_u8(data + offset));
    offset += 1;

    header_length_ = wire::read_u8(data + offset);
    offset += 1;

    session_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    sequence_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t CommonHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CommonHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(header_length_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(session_id_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(sequence_number_));
    offset += 8;

    return offset;
}

std::size_t CommonHeader::encoded_size() const {
    return wire_size;
}

void CommonHeader::print(std::ostream& out) const {
    out << "CommonHeader{";
    out << "message_type=";
    out << message_type_;
    out << ", header_length=";
    out << static_cast<int>(header_length_);
    out << ", session_id=";
    out << session_id_;
    out << ", sequence_number=";
    out << sequence_number_;
    out << '}';
}

bool CommonHeader::operator==(const CommonHeader& other) const {
    return message_type_ == other.message_type_
        && header_length_ == other.header_length_
        && session_id_ == other.session_id_
        && sequence_number_ == other.sequence_number_;
}

bool CommonHeader::operator!=(const CommonHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CommonHeader& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
