#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

PacketHeader::PacketHeader(std::uint16_t pkt_size, DeliveryFlag delivery_flag, std::uint8_t number_msgs, std::uint32_t seq_num, const SendTime& send_time)
  : pkt_size_(pkt_size), delivery_flag_(delivery_flag), number_msgs_(number_msgs), seq_num_(seq_num), send_time_(send_time) {}

std::uint16_t PacketHeader::pkt_size() const { return pkt_size_; }
void PacketHeader::set_pkt_size(std::uint16_t value) { pkt_size_ = value; }

DeliveryFlag PacketHeader::delivery_flag() const { return delivery_flag_; }
void PacketHeader::set_delivery_flag(DeliveryFlag value) { delivery_flag_ = value; }

std::uint8_t PacketHeader::number_msgs() const { return number_msgs_; }
void PacketHeader::set_number_msgs(std::uint8_t value) { number_msgs_ = value; }

std::uint32_t PacketHeader::seq_num() const { return seq_num_; }
void PacketHeader::set_seq_num(std::uint32_t value) { seq_num_ = value; }

const SendTime& PacketHeader::send_time() const { return send_time_; }
SendTime& PacketHeader::send_time() { return send_time_; }
void PacketHeader::set_send_time(const SendTime& value) { send_time_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    pkt_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    delivery_flag_ = static_cast<DeliveryFlag>(wire::read_u8(data + offset));
    offset += 1;

    number_msgs_ = wire::read_u8(data + offset);
    offset += 1;

    seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += send_time_.decode(data + offset, length - offset);

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(pkt_size_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(delivery_flag_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_msgs_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(seq_num_));
    offset += 4;

    offset += send_time_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "pkt_size=";
    out << pkt_size_;
    out << ", delivery_flag=";
    out << delivery_flag_;
    out << ", number_msgs=";
    out << static_cast<int>(number_msgs_);
    out << ", seq_num=";
    out << seq_num_;
    out << ", send_time=";
    send_time_.print(out);
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return pkt_size_ == other.pkt_size_
        && delivery_flag_ == other.delivery_flag_
        && number_msgs_ == other.number_msgs_
        && seq_num_ == other.seq_num_
        && send_time_ == other.send_time_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
