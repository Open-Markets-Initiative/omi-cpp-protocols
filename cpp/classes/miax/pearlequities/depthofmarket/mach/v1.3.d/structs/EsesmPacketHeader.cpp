#include "EsesmPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

EsesmPacketHeader::EsesmPacketHeader(std::uint16_t esesm_packet_length, EsesmPacketType esesm_packet_type)
  : esesm_packet_length_(esesm_packet_length), esesm_packet_type_(esesm_packet_type) {}

std::uint16_t EsesmPacketHeader::esesm_packet_length() const { return esesm_packet_length_; }
void EsesmPacketHeader::set_esesm_packet_length(std::uint16_t value) { esesm_packet_length_ = value; }

EsesmPacketType EsesmPacketHeader::esesm_packet_type() const { return esesm_packet_type_; }
void EsesmPacketHeader::set_esesm_packet_type(EsesmPacketType value) { esesm_packet_type_ = value; }

std::size_t EsesmPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EsesmPacketHeader", wire_size, length);

    esesm_packet_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    esesm_packet_type_ = static_cast<EsesmPacketType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t EsesmPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EsesmPacketHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(esesm_packet_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(esesm_packet_type_));
    offset += 1;

    return offset;
}

std::size_t EsesmPacketHeader::encoded_size() const {
    return wire_size;
}

void EsesmPacketHeader::print(std::ostream& out) const {
    out << "EsesmPacketHeader{";
    out << "esesm_packet_length=";
    out << esesm_packet_length_;
    out << ", esesm_packet_type=";
    out << esesm_packet_type_;
    out << '}';
}

bool EsesmPacketHeader::operator==(const EsesmPacketHeader& other) const {
    return esesm_packet_length_ == other.esesm_packet_length_
        && esesm_packet_type_ == other.esesm_packet_type_;
}

bool EsesmPacketHeader::operator!=(const EsesmPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const EsesmPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
