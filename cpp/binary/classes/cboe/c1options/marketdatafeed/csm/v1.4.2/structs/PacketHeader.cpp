#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

PacketHeader::PacketHeader(std::uint8_t version, std::uint16_t packet_length, std::uint64_t sending_time, std::uint8_t message_count, std::uint32_t first_msg_seq_num)
  : version_(version), packet_length_(packet_length), sending_time_(sending_time), message_count_(message_count), first_msg_seq_num_(first_msg_seq_num) {}

std::uint8_t PacketHeader::version() const { return version_; }
void PacketHeader::set_version(std::uint8_t value) { version_ = value; }

std::uint16_t PacketHeader::packet_length() const { return packet_length_; }
void PacketHeader::set_packet_length(std::uint16_t value) { packet_length_ = value; }

std::uint64_t PacketHeader::sending_time() const { return sending_time_; }
void PacketHeader::set_sending_time(std::uint64_t value) { sending_time_ = value; }

std::uint8_t PacketHeader::message_count() const { return message_count_; }
void PacketHeader::set_message_count(std::uint8_t value) { message_count_ = value; }

std::uint32_t PacketHeader::first_msg_seq_num() const { return first_msg_seq_num_; }
void PacketHeader::set_first_msg_seq_num(std::uint32_t value) { first_msg_seq_num_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    version_ = wire::read_u8(data + offset);
    offset += 1;

    packet_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    sending_time_ = wire::read_u64_be(data + offset);
    offset += 8;

    message_count_ = wire::read_u8(data + offset);
    offset += 1;

    first_msg_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(version_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(packet_length_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(sending_time_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_count_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(first_msg_seq_num_));
    offset += 4;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "version=";
    out << static_cast<int>(version_);
    out << ", packet_length=";
    out << packet_length_;
    out << ", sending_time=";
    out << sending_time_;
    out << ", message_count=";
    out << static_cast<int>(message_count_);
    out << ", first_msg_seq_num=";
    out << first_msg_seq_num_;
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return version_ == other.version_
        && packet_length_ == other.packet_length_
        && sending_time_ == other.sending_time_
        && message_count_ == other.message_count_
        && first_msg_seq_num_ == other.first_msg_seq_num_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
