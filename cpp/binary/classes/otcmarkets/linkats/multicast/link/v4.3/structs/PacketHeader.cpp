#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

PacketHeader::PacketHeader(std::uint16_t packet_size, std::uint32_t seq_num, const PacketFlag& packet_flag, std::uint8_t message_count, std::chrono::milliseconds packet_milli)
  : packet_size_(packet_size), seq_num_(seq_num), packet_flag_(packet_flag), message_count_(message_count), packet_milli_(packet_milli) {}

std::uint16_t PacketHeader::packet_size() const { return packet_size_; }
void PacketHeader::set_packet_size(std::uint16_t value) { packet_size_ = value; }

std::uint32_t PacketHeader::seq_num() const { return seq_num_; }
void PacketHeader::set_seq_num(std::uint32_t value) { seq_num_ = value; }

const PacketFlag& PacketHeader::packet_flag() const { return packet_flag_; }
PacketFlag& PacketHeader::packet_flag() { return packet_flag_; }
void PacketHeader::set_packet_flag(const PacketFlag& value) { packet_flag_ = value; }

std::uint8_t PacketHeader::message_count() const { return message_count_; }
void PacketHeader::set_message_count(std::uint8_t value) { message_count_ = value; }

std::chrono::milliseconds PacketHeader::packet_milli() const { return packet_milli_; }
void PacketHeader::set_packet_milli(std::chrono::milliseconds value) { packet_milli_ = value; }
std::int64_t PacketHeader::packet_milli_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(packet_milli_.count()) * 1000000); }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    packet_size_ = wire::read_u16_be(data + offset);
    offset += 2;

    seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += packet_flag_.decode(data + offset, length - offset);

    message_count_ = wire::read_u8(data + offset);
    offset += 1;

    packet_milli_ = std::chrono::milliseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(packet_size_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seq_num_));
    offset += 4;

    offset += packet_flag_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_count_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(packet_milli_.count()));
    offset += 4;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "packet_size=";
    out << packet_size_;
    out << ", seq_num=";
    out << seq_num_;
    out << ", packet_flag=";
    packet_flag_.print(out);
    out << ", message_count=";
    out << static_cast<int>(message_count_);
    out << ", packet_milli=";
    calendar::print(out, packet_milli_.count(), 1000000, "America/New_York");
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return packet_size_ == other.packet_size_
        && seq_num_ == other.seq_num_
        && packet_flag_ == other.packet_flag_
        && message_count_ == other.message_count_
        && packet_milli_ == other.packet_milli_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
