#include "TcpPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

TcpPacketHeader::TcpPacketHeader(std::uint16_t packet_length, PacketType packet_type)
  : packet_length_(packet_length), packet_type_(packet_type) {}

std::uint16_t TcpPacketHeader::packet_length() const { return packet_length_; }
void TcpPacketHeader::set_packet_length(std::uint16_t value) { packet_length_ = value; }

PacketType TcpPacketHeader::packet_type() const { return packet_type_; }
void TcpPacketHeader::set_packet_type(PacketType value) { packet_type_ = value; }

std::size_t TcpPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TcpPacketHeader", wire_size, length);

    packet_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    packet_type_ = static_cast<PacketType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TcpPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TcpPacketHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(packet_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(packet_type_));
    offset += 1;

    return offset;
}

std::size_t TcpPacketHeader::encoded_size() const {
    return wire_size;
}

void TcpPacketHeader::print(std::ostream& out) const {
    out << "TcpPacketHeader{";
    out << "packet_length=";
    out << packet_length_;
    out << ", packet_type=";
    out << packet_type_;
    out << '}';
}

bool TcpPacketHeader::operator==(const TcpPacketHeader& other) const {
    return packet_length_ == other.packet_length_
        && packet_type_ == other.packet_type_;
}

bool TcpPacketHeader::operator!=(const TcpPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TcpPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
