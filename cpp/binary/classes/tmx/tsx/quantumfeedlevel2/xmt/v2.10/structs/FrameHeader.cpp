// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: structs/FrameHeader.cpp
#include "FrameHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

FrameHeader::FrameHeader(std::uint8_t start_of_frame, char protocol_name, char protocol_version, std::uint16_t message_length, std::uint32_t session_id, AckRequiredPossDup ack_required_poss_dup, std::uint8_t num_body)
  : start_of_frame_(start_of_frame), protocol_name_(protocol_name), protocol_version_(protocol_version), message_length_(message_length), session_id_(session_id), ack_required_poss_dup_(ack_required_poss_dup), num_body_(num_body) {}

std::uint8_t FrameHeader::start_of_frame() const { return start_of_frame_; }
void FrameHeader::set_start_of_frame(std::uint8_t value) { start_of_frame_ = value; }

char FrameHeader::protocol_name() const { return protocol_name_; }
void FrameHeader::set_protocol_name(char value) { protocol_name_ = value; }

char FrameHeader::protocol_version() const { return protocol_version_; }
void FrameHeader::set_protocol_version(char value) { protocol_version_ = value; }

std::uint16_t FrameHeader::message_length() const { return message_length_; }
void FrameHeader::set_message_length(std::uint16_t value) { message_length_ = value; }

std::uint32_t FrameHeader::session_id() const { return session_id_; }
void FrameHeader::set_session_id(std::uint32_t value) { session_id_ = value; }

AckRequiredPossDup FrameHeader::ack_required_poss_dup() const { return ack_required_poss_dup_; }
void FrameHeader::set_ack_required_poss_dup(AckRequiredPossDup value) { ack_required_poss_dup_ = value; }

std::uint8_t FrameHeader::num_body() const { return num_body_; }
void FrameHeader::set_num_body(std::uint8_t value) { num_body_ = value; }

std::size_t FrameHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FrameHeader", wire_size, length);

    start_of_frame_ = wire::read_u8(data + offset);
    offset += 1;

    protocol_name_ = wire::read_char(data + offset);
    offset += 1;

    protocol_version_ = wire::read_char(data + offset);
    offset += 1;

    message_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    ack_required_poss_dup_ = static_cast<AckRequiredPossDup>(wire::read_char(data + offset));
    offset += 1;

    num_body_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t FrameHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FrameHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(start_of_frame_));
    offset += 1;

    wire::write_char(data + offset, protocol_name_);
    offset += 1;

    wire::write_char(data + offset, protocol_version_);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(ack_required_poss_dup_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_body_));
    offset += 1;

    return offset;
}

std::size_t FrameHeader::encoded_size() const {
    return wire_size;
}

void FrameHeader::print(std::ostream& out) const {
    out << "FrameHeader{";
    out << "start_of_frame=";
    out << static_cast<int>(start_of_frame_);
    out << ", protocol_name=";
    print::character(out, protocol_name_);
    out << ", protocol_version=";
    print::character(out, protocol_version_);
    out << ", message_length=";
    out << message_length_;
    out << ", session_id=";
    out << session_id_;
    out << ", ack_required_poss_dup=";
    out << ack_required_poss_dup_;
    out << ", num_body=";
    out << static_cast<int>(num_body_);
    out << '}';
}

bool FrameHeader::operator==(const FrameHeader& other) const {
    return start_of_frame_ == other.start_of_frame_
        && protocol_name_ == other.protocol_name_
        && protocol_version_ == other.protocol_version_
        && message_length_ == other.message_length_
        && session_id_ == other.session_id_
        && ack_required_poss_dup_ == other.ack_required_poss_dup_
        && num_body_ == other.num_body_;
}

bool FrameHeader::operator!=(const FrameHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FrameHeader& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
