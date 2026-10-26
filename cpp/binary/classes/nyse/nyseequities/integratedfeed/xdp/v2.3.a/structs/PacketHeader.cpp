#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

PacketHeader::PacketHeader(std::uint16_t packet_size, DeliveryFlag delivery_flag, std::uint8_t message_count, std::uint32_t sequence_number, const SendTime& send_time)
  : packet_size_(packet_size), delivery_flag_(delivery_flag), message_count_(message_count), sequence_number_(sequence_number), send_time_(send_time) {}

std::uint16_t PacketHeader::packet_size() const { return packet_size_; }
void PacketHeader::set_packet_size(std::uint16_t value) { packet_size_ = value; }

DeliveryFlag PacketHeader::delivery_flag() const { return delivery_flag_; }
void PacketHeader::set_delivery_flag(DeliveryFlag value) { delivery_flag_ = value; }

std::uint8_t PacketHeader::message_count() const { return message_count_; }
void PacketHeader::set_message_count(std::uint8_t value) { message_count_ = value; }

std::uint32_t PacketHeader::sequence_number() const { return sequence_number_; }
void PacketHeader::set_sequence_number(std::uint32_t value) { sequence_number_ = value; }

const SendTime& PacketHeader::send_time() const { return send_time_; }
SendTime& PacketHeader::send_time() { return send_time_; }
void PacketHeader::set_send_time(const SendTime& value) { send_time_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    packet_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    delivery_flag_ = static_cast<DeliveryFlag>(wire::read_u8(data + offset));
    offset += 1;

    message_count_ = wire::read_u8(data + offset);
    offset += 1;

    sequence_number_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += send_time_.decode(data + offset, length - offset);

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(packet_size_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(delivery_flag_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_count_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sequence_number_));
    offset += 4;

    offset += send_time_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "packet_size=";
    out << packet_size_;
    out << ", delivery_flag=";
    out << delivery_flag_;
    out << ", message_count=";
    out << static_cast<int>(message_count_);
    out << ", sequence_number=";
    out << sequence_number_;
    out << ", send_time=";
    send_time_.print(out);
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return packet_size_ == other.packet_size_
        && delivery_flag_ == other.delivery_flag_
        && message_count_ == other.message_count_
        && sequence_number_ == other.sequence_number_
        && send_time_ == other.send_time_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
