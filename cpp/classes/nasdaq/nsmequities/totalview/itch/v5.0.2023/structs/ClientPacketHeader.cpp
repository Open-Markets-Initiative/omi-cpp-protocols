#include "ClientPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

ClientPacketHeader::ClientPacketHeader(std::uint16_t packet_length, ClientPacketType client_packet_type)
  : packet_length_(packet_length), client_packet_type_(client_packet_type) {}

std::uint16_t ClientPacketHeader::packet_length() const { return packet_length_; }
void ClientPacketHeader::set_packet_length(std::uint16_t value) { packet_length_ = value; }

ClientPacketType ClientPacketHeader::client_packet_type() const { return client_packet_type_; }
void ClientPacketHeader::set_client_packet_type(ClientPacketType value) { client_packet_type_ = value; }

std::size_t ClientPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ClientPacketHeader", wire_size, length);

    packet_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    client_packet_type_ = static_cast<ClientPacketType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ClientPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPacketHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(packet_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(client_packet_type_));
    offset += 1;

    return offset;
}

std::size_t ClientPacketHeader::encoded_size() const {
    return wire_size;
}

void ClientPacketHeader::print(std::ostream& out) const {
    out << "ClientPacketHeader{";
    out << "packet_length=";
    out << packet_length_;
    out << ", client_packet_type=";
    out << client_packet_type_;
    out << '}';
}

bool ClientPacketHeader::operator==(const ClientPacketHeader& other) const {
    return packet_length_ == other.packet_length_
        && client_packet_type_ == other.client_packet_type_;
}

bool ClientPacketHeader::operator!=(const ClientPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ClientPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
