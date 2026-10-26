#include "IextpHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

IextpHeader::IextpHeader(std::uint8_t version, const std::array<std::byte, 1>& reserved, std::uint16_t message_protocol_id, std::uint32_t channel_id, std::uint32_t session_id, std::uint16_t payload_length, std::uint16_t message_count, std::uint64_t stream_offset, std::uint64_t first_message_sequence_number, std::chrono::nanoseconds send_time)
  : version_(version), reserved_(reserved), message_protocol_id_(message_protocol_id), channel_id_(channel_id), session_id_(session_id), payload_length_(payload_length), message_count_(message_count), stream_offset_(stream_offset), first_message_sequence_number_(first_message_sequence_number), send_time_(send_time) {}

std::uint8_t IextpHeader::version() const { return version_; }
void IextpHeader::set_version(std::uint8_t value) { version_ = value; }

const std::array<std::byte, 1>& IextpHeader::reserved() const { return reserved_; }
std::array<std::byte, 1>& IextpHeader::reserved() { return reserved_; }
void IextpHeader::set_reserved(const std::array<std::byte, 1>& value) { reserved_ = value; }

std::uint16_t IextpHeader::message_protocol_id() const { return message_protocol_id_; }
void IextpHeader::set_message_protocol_id(std::uint16_t value) { message_protocol_id_ = value; }

std::uint32_t IextpHeader::channel_id() const { return channel_id_; }
void IextpHeader::set_channel_id(std::uint32_t value) { channel_id_ = value; }

std::uint32_t IextpHeader::session_id() const { return session_id_; }
void IextpHeader::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint16_t IextpHeader::payload_length() const { return payload_length_; }
void IextpHeader::set_payload_length(std::uint16_t value) { payload_length_ = value; }

std::uint16_t IextpHeader::message_count() const { return message_count_; }
void IextpHeader::set_message_count(std::uint16_t value) { message_count_ = value; }

std::uint64_t IextpHeader::stream_offset() const { return stream_offset_; }
void IextpHeader::set_stream_offset(std::uint64_t value) { stream_offset_ = value; }

std::uint64_t IextpHeader::first_message_sequence_number() const { return first_message_sequence_number_; }
void IextpHeader::set_first_message_sequence_number(std::uint64_t value) { first_message_sequence_number_ = value; }

std::chrono::nanoseconds IextpHeader::send_time() const { return send_time_; }
void IextpHeader::set_send_time(std::chrono::nanoseconds value) { send_time_ = value; }

std::size_t IextpHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IextpHeader", wire_size, length);

    version_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_.data(), 1);
    offset += 1;

    message_protocol_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    channel_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    payload_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    message_count_ = wire::read_u16_le(data + offset);
    offset += 2;

    stream_offset_ = wire::read_u64_le(data + offset);
    offset += 8;

    first_message_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    send_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t IextpHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IextpHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(version_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(message_protocol_id_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(channel_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(payload_length_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(message_count_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(stream_offset_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(first_message_sequence_number_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(send_time_.count()));
    offset += 8;

    return offset;
}

std::size_t IextpHeader::encoded_size() const {
    return wire_size;
}

void IextpHeader::print(std::ostream& out) const {
    out << "IextpHeader{";
    out << "version=";
    out << static_cast<int>(version_);
    out << ", reserved=";
    print::hex(out, reserved_.data(), reserved_.size());
    out << ", message_protocol_id=";
    out << message_protocol_id_;
    out << ", channel_id=";
    out << channel_id_;
    out << ", session_id=";
    out << session_id_;
    out << ", payload_length=";
    out << payload_length_;
    out << ", message_count=";
    out << message_count_;
    out << ", stream_offset=";
    out << stream_offset_;
    out << ", first_message_sequence_number=";
    out << first_message_sequence_number_;
    out << ", send_time=";
    out << send_time_.count();
    out << '}';
}

bool IextpHeader::operator==(const IextpHeader& other) const {
    return version_ == other.version_
        && reserved_ == other.reserved_
        && message_protocol_id_ == other.message_protocol_id_
        && channel_id_ == other.channel_id_
        && session_id_ == other.session_id_
        && payload_length_ == other.payload_length_
        && message_count_ == other.message_count_
        && stream_offset_ == other.stream_offset_
        && first_message_sequence_number_ == other.first_message_sequence_number_
        && send_time_ == other.send_time_;
}

bool IextpHeader::operator!=(const IextpHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IextpHeader& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::iextp::v1_64
