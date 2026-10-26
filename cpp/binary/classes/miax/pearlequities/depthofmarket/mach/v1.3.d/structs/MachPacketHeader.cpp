#include "MachPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

MachPacketHeader::MachPacketHeader(std::uint64_t sequence_number, std::uint16_t mach_packet_length, MachPacketType mach_packet_type, std::uint8_t session_number)
  : sequence_number_(sequence_number), mach_packet_length_(mach_packet_length), mach_packet_type_(mach_packet_type), session_number_(session_number) {}

std::uint64_t MachPacketHeader::sequence_number() const { return sequence_number_; }
void MachPacketHeader::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

std::uint16_t MachPacketHeader::mach_packet_length() const { return mach_packet_length_; }
void MachPacketHeader::set_mach_packet_length(std::uint16_t value) { mach_packet_length_ = value; }

MachPacketType MachPacketHeader::mach_packet_type() const { return mach_packet_type_; }
void MachPacketHeader::set_mach_packet_type(MachPacketType value) { mach_packet_type_ = value; }

std::uint8_t MachPacketHeader::session_number() const { return session_number_; }
void MachPacketHeader::set_session_number(std::uint8_t value) { session_number_ = value; }

std::size_t MachPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MachPacketHeader", wire_size, length);

    sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    mach_packet_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    mach_packet_type_ = static_cast<MachPacketType>(wire::read_u8(data + offset));
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

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(mach_packet_length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(mach_packet_type_));
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
    out << ", mach_packet_length=";
    out << mach_packet_length_;
    out << ", mach_packet_type=";
    out << mach_packet_type_;
    out << ", session_number=";
    out << static_cast<int>(session_number_);
    out << '}';
}

bool MachPacketHeader::operator==(const MachPacketHeader& other) const {
    return sequence_number_ == other.sequence_number_
        && mach_packet_length_ == other.mach_packet_length_
        && mach_packet_type_ == other.mach_packet_type_
        && session_number_ == other.session_number_;
}

bool MachPacketHeader::operator!=(const MachPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MachPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
