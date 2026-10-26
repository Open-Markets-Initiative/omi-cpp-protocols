#include "ServerPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

ServerPacketHeader::ServerPacketHeader(std::uint16_t packet_length, ServerPacketType server_packet_type)
  : packet_length_(packet_length), server_packet_type_(server_packet_type) {}

std::uint16_t ServerPacketHeader::packet_length() const { return packet_length_; }
void ServerPacketHeader::set_packet_length(std::uint16_t value) { packet_length_ = value; }

ServerPacketType ServerPacketHeader::server_packet_type() const { return server_packet_type_; }
void ServerPacketHeader::set_server_packet_type(ServerPacketType value) { server_packet_type_ = value; }

std::size_t ServerPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPacketHeader", wire_size, length);

    packet_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    server_packet_type_ = static_cast<ServerPacketType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ServerPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPacketHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(packet_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(server_packet_type_));
    offset += 1;

    return offset;
}

std::size_t ServerPacketHeader::encoded_size() const {
    return wire_size;
}

void ServerPacketHeader::print(std::ostream& out) const {
    out << "ServerPacketHeader{";
    out << "packet_length=";
    out << packet_length_;
    out << ", server_packet_type=";
    out << server_packet_type_;
    out << '}';
}

bool ServerPacketHeader::operator==(const ServerPacketHeader& other) const {
    return packet_length_ == other.packet_length_
        && server_packet_type_ == other.server_packet_type_;
}

bool ServerPacketHeader::operator!=(const ServerPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ServerPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
