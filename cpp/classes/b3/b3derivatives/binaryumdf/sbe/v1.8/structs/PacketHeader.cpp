#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

PacketHeader::PacketHeader(std::uint8_t channel_id, std::uint8_t packet_reserved, std::uint16_t sequence_version, std::uint32_t sequence_number, std::chrono::nanoseconds sending_time)
  : channel_id_(channel_id), packet_reserved_(packet_reserved), sequence_version_(sequence_version), sequence_number_(sequence_number), sending_time_(sending_time) {}

std::uint8_t PacketHeader::channel_id() const { return channel_id_; }
void PacketHeader::set_channel_id(std::uint8_t value) { channel_id_ = value; }

std::uint8_t PacketHeader::packet_reserved() const { return packet_reserved_; }
void PacketHeader::set_packet_reserved(std::uint8_t value) { packet_reserved_ = value; }

std::uint16_t PacketHeader::sequence_version() const { return sequence_version_; }
void PacketHeader::set_sequence_version(std::uint16_t value) { sequence_version_ = value; }

std::uint32_t PacketHeader::sequence_number() const { return sequence_number_; }
void PacketHeader::set_sequence_number(std::uint32_t value) { sequence_number_ = value; }

std::chrono::nanoseconds PacketHeader::sending_time() const { return sending_time_; }
void PacketHeader::set_sending_time(std::chrono::nanoseconds value) { sending_time_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    packet_reserved_ = wire::read_u8(data + offset);
    offset += 1;

    sequence_version_ = wire::read_u16_le(data + offset);
    offset += 2;

    sequence_number_ = wire::read_u32_le(data + offset);
    offset += 4;

    sending_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(packet_reserved_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(sequence_version_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_number_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sending_time_.count()));
    offset += 8;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", packet_reserved=";
    out << static_cast<int>(packet_reserved_);
    out << ", sequence_version=";
    out << sequence_version_;
    out << ", sequence_number=";
    out << sequence_number_;
    out << ", sending_time=";
    out << sending_time_.count();
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return channel_id_ == other.channel_id_
        && packet_reserved_ == other.packet_reserved_
        && sequence_version_ == other.sequence_version_
        && sequence_number_ == other.sequence_number_
        && sending_time_ == other.sending_time_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
