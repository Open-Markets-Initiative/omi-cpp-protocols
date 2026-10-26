#include "BinaryPacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

BinaryPacketHeader::BinaryPacketHeader(std::uint32_t packet_sequence_number, std::chrono::nanoseconds sending_time)
  : packet_sequence_number_(packet_sequence_number), sending_time_(sending_time) {}

std::uint32_t BinaryPacketHeader::packet_sequence_number() const { return packet_sequence_number_; }
void BinaryPacketHeader::set_packet_sequence_number(std::uint32_t value) { packet_sequence_number_ = value; }

std::chrono::nanoseconds BinaryPacketHeader::sending_time() const { return sending_time_; }
void BinaryPacketHeader::set_sending_time(std::chrono::nanoseconds value) { sending_time_ = value; }

std::size_t BinaryPacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BinaryPacketHeader", wire_size, length);

    packet_sequence_number_ = wire::read_u32_le(data + offset);
    offset += 4;

    sending_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t BinaryPacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BinaryPacketHeader", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(packet_sequence_number_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sending_time_.count()));
    offset += 8;

    return offset;
}

std::size_t BinaryPacketHeader::encoded_size() const {
    return wire_size;
}

void BinaryPacketHeader::print(std::ostream& out) const {
    out << "BinaryPacketHeader{";
    out << "packet_sequence_number=";
    out << packet_sequence_number_;
    out << ", sending_time=";
    out << sending_time_.count();
    out << '}';
}

bool BinaryPacketHeader::operator==(const BinaryPacketHeader& other) const {
    return packet_sequence_number_ == other.packet_sequence_number_
        && sending_time_ == other.sending_time_;
}

bool BinaryPacketHeader::operator!=(const BinaryPacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BinaryPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
