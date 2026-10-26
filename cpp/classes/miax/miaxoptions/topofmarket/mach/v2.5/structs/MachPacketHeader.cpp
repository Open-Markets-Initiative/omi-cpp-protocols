#include "MachPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

MachPacketHeader::MachPacketHeader(std::uint64_t sequence_number, std::uint16_t packet_length, PacketType packet_type, std::uint8_t session_number)
  : sequence_number_(sequence_number), packet_length_(packet_length), packet_type_(packet_type), session_number_(session_number) {}

std::uint64_t MachPacketHeader::sequence_number() const { return sequence_number_; }
void MachPacketHeader::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

std::uint16_t MachPacketHeader::packet_length() const { return packet_length_; }
void MachPacketHeader::set_packet_length(std::uint16_t value) { packet_length_ = value; }

PacketType MachPacketHeader::packet_type() const { return packet_type_; }
void MachPacketHeader::set_packet_type(PacketType value) { packet_type_ = value; }

std::uint8_t MachPacketHeader::session_number() const { return session_number_; }
void MachPacketHeader::set_session_number(std::uint8_t value) { session_number_ = value; }

std::size_t MachPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MachPacketHeader", wire_size, length);

    sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    packet_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    packet_type_ = static_cast<PacketType>(wire::read_u8(data + offset));
    offset += 1;

    session_number_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t MachPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MachPacketHeader", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sequence_number_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(packet_length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(packet_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(session_number_));
    offset += 1;

    return offset;
}

std::size_t MachPacketHeader::encoded_size() const {
    return wire_size;
}

void MachPacketHeader::print(std::ostream& out) const {
    out << "MachPacketHeader{";
    out << "sequence_number=";
    out << sequence_number_;
    out << ", packet_length=";
    out << packet_length_;
    out << ", packet_type=";
    out << packet_type_;
    out << ", session_number=";
    out << static_cast<int>(session_number_);
    out << '}';
}

bool MachPacketHeader::operator==(const MachPacketHeader& other) const {
    return sequence_number_ == other.sequence_number_
        && packet_length_ == other.packet_length_
        && packet_type_ == other.packet_type_
        && session_number_ == other.session_number_;
}

bool MachPacketHeader::operator!=(const MachPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MachPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
