#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

PacketHeader::PacketHeader(std::uint16_t length, std::uint8_t message_count, std::uint8_t unit, std::uint32_t sequence)
  : length_(length), message_count_(message_count), unit_(unit), sequence_(sequence) {}

std::uint16_t PacketHeader::length() const { return length_; }
void PacketHeader::set_length(std::uint16_t value) { length_ = value; }

std::uint8_t PacketHeader::message_count() const { return message_count_; }
void PacketHeader::set_message_count(std::uint8_t value) { message_count_ = value; }

std::uint8_t PacketHeader::unit() const { return unit_; }
void PacketHeader::set_unit(std::uint8_t value) { unit_ = value; }

std::uint32_t PacketHeader::sequence() const { return sequence_; }
void PacketHeader::set_sequence(std::uint32_t value) { sequence_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    length_ = wire::read_u16_le(data + offset);
    offset += 2;

    message_count_ = wire::read_u8(data + offset);
    offset += 1;

    unit_ = wire::read_u8(data + offset);
    offset += 1;

    sequence_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_count_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(unit_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_));
    offset += 4;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "length=";
    out << length_;
    out << ", message_count=";
    out << static_cast<int>(message_count_);
    out << ", unit=";
    out << static_cast<int>(unit_);
    out << ", sequence=";
    out << sequence_;
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return length_ == other.length_
        && message_count_ == other.message_count_
        && unit_ == other.unit_
        && sequence_ == other.sequence_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
