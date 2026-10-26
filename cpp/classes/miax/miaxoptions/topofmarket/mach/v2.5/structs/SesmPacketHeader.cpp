#include "SesmPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SesmPacketHeader::SesmPacketHeader(std::uint16_t sesm_packet_length, SesmPacketType sesm_packet_type)
  : sesm_packet_length_(sesm_packet_length), sesm_packet_type_(sesm_packet_type) {}

std::uint16_t SesmPacketHeader::sesm_packet_length() const { return sesm_packet_length_; }
void SesmPacketHeader::set_sesm_packet_length(std::uint16_t value) { sesm_packet_length_ = value; }

SesmPacketType SesmPacketHeader::sesm_packet_type() const { return sesm_packet_type_; }
void SesmPacketHeader::set_sesm_packet_type(SesmPacketType value) { sesm_packet_type_ = value; }

std::size_t SesmPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SesmPacketHeader", wire_size, length);

    sesm_packet_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    sesm_packet_type_ = static_cast<SesmPacketType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SesmPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SesmPacketHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(sesm_packet_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(sesm_packet_type_));
    offset += 1;

    return offset;
}

std::size_t SesmPacketHeader::encoded_size() const {
    return wire_size;
}

void SesmPacketHeader::print(std::ostream& out) const {
    out << "SesmPacketHeader{";
    out << "sesm_packet_length=";
    out << sesm_packet_length_;
    out << ", sesm_packet_type=";
    out << sesm_packet_type_;
    out << '}';
}

bool SesmPacketHeader::operator==(const SesmPacketHeader& other) const {
    return sesm_packet_length_ == other.sesm_packet_length_
        && sesm_packet_type_ == other.sesm_packet_type_;
}

bool SesmPacketHeader::operator!=(const SesmPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SesmPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
