// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BodyHeader.cpp
#include "BodyHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

BodyHeader::BodyHeader(std::uint16_t msg_length, MsgType msg_type)
  : msg_length_(msg_length), msg_type_(msg_type) {}

std::uint16_t BodyHeader::msg_length() const { return msg_length_; }
void BodyHeader::set_msg_length(std::uint16_t value) { msg_length_ = value; }

MsgType BodyHeader::msg_type() const { return msg_type_; }
void BodyHeader::set_msg_type(MsgType value) { msg_type_ = value; }

std::size_t BodyHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BodyHeader", wire_size, length);

    msg_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    msg_type_ = static_cast<MsgType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t BodyHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BodyHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(msg_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(msg_type_));
    offset += 1;

    return offset;
}

std::size_t BodyHeader::encoded_size() const {
    return wire_size;
}

void BodyHeader::print(std::ostream& out) const {
    out << "BodyHeader{";
    out << "msg_length=";
    out << msg_length_;
    out << ", msg_type=";
    out << msg_type_;
    out << '}';
}

bool BodyHeader::operator==(const BodyHeader& other) const {
    return msg_length_ == other.msg_length_
        && msg_type_ == other.msg_type_;
}

bool BodyHeader::operator!=(const BodyHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BodyHeader& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
