#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

PacketHeader::PacketHeader(std::uint8_t multicast_group_number, std::uint8_t number_of_system_reboots, std::uint32_t sequence_number, const std::string& issue_code, std::uint32_t update_number, std::uint8_t packet_number, std::uint8_t total_number_of_packets, std::uint8_t utility_flag, std::uint8_t message_count)
  : multicast_group_number_(multicast_group_number), number_of_system_reboots_(number_of_system_reboots), sequence_number_(sequence_number), issue_code_(issue_code), update_number_(update_number), packet_number_(packet_number), total_number_of_packets_(total_number_of_packets), utility_flag_(utility_flag), message_count_(message_count) {}

std::uint8_t PacketHeader::multicast_group_number() const { return multicast_group_number_; }
void PacketHeader::set_multicast_group_number(std::uint8_t value) { multicast_group_number_ = value; }

std::uint8_t PacketHeader::number_of_system_reboots() const { return number_of_system_reboots_; }
void PacketHeader::set_number_of_system_reboots(std::uint8_t value) { number_of_system_reboots_ = value; }

std::uint32_t PacketHeader::sequence_number() const { return sequence_number_; }
void PacketHeader::set_sequence_number(std::uint32_t value) { sequence_number_ = value; }

const std::string& PacketHeader::issue_code() const { return issue_code_; }
std::string& PacketHeader::issue_code() { return issue_code_; }
void PacketHeader::set_issue_code(const std::string& value) { issue_code_ = value; }

std::uint32_t PacketHeader::update_number() const { return update_number_; }
void PacketHeader::set_update_number(std::uint32_t value) { update_number_ = value; }

std::uint8_t PacketHeader::packet_number() const { return packet_number_; }
void PacketHeader::set_packet_number(std::uint8_t value) { packet_number_ = value; }

std::uint8_t PacketHeader::total_number_of_packets() const { return total_number_of_packets_; }
void PacketHeader::set_total_number_of_packets(std::uint8_t value) { total_number_of_packets_ = value; }

std::uint8_t PacketHeader::utility_flag() const { return utility_flag_; }
void PacketHeader::set_utility_flag(std::uint8_t value) { utility_flag_ = value; }

std::uint8_t PacketHeader::message_count() const { return message_count_; }
void PacketHeader::set_message_count(std::uint8_t value) { message_count_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    multicast_group_number_ = wire::read_u8(data + offset);
    offset += 1;

    number_of_system_reboots_ = wire::read_u8(data + offset);
    offset += 1;

    sequence_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    issue_code_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    update_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    packet_number_ = wire::read_u8(data + offset);
    offset += 1;

    total_number_of_packets_ = wire::read_u8(data + offset);
    offset += 1;

    utility_flag_ = wire::read_u8(data + offset);
    offset += 1;

    message_count_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(multicast_group_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_system_reboots_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(sequence_number_));
    offset += 4;

    wire::write_text(data + offset, 12, ' ', issue_code_);
    offset += 12;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(update_number_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(packet_number_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(total_number_of_packets_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(utility_flag_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_count_));
    offset += 1;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "multicast_group_number=";
    out << static_cast<int>(multicast_group_number_);
    out << ", number_of_system_reboots=";
    out << static_cast<int>(number_of_system_reboots_);
    out << ", sequence_number=";
    out << sequence_number_;
    out << ", issue_code=";
    print::text(out, issue_code_);
    out << ", update_number=";
    out << update_number_;
    out << ", packet_number=";
    out << static_cast<int>(packet_number_);
    out << ", total_number_of_packets=";
    out << static_cast<int>(total_number_of_packets_);
    out << ", utility_flag=";
    out << static_cast<int>(utility_flag_);
    out << ", message_count=";
    out << static_cast<int>(message_count_);
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return multicast_group_number_ == other.multicast_group_number_
        && number_of_system_reboots_ == other.number_of_system_reboots_
        && sequence_number_ == other.sequence_number_
        && issue_code_ == other.issue_code_
        && update_number_ == other.update_number_
        && packet_number_ == other.packet_number_
        && total_number_of_packets_ == other.total_number_of_packets_
        && utility_flag_ == other.utility_flag_
        && message_count_ == other.message_count_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
