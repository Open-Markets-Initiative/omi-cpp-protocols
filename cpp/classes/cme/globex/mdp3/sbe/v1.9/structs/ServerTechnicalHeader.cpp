#include "ServerTechnicalHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerTechnicalHeader::ServerTechnicalHeader(std::uint16_t encoding_type, std::uint32_t message_sequence_number, std::chrono::nanoseconds tcp_sending_time, std::uint16_t tcp_message_size)
  : encoding_type_(encoding_type), message_sequence_number_(message_sequence_number), tcp_sending_time_(tcp_sending_time), tcp_message_size_(tcp_message_size) {}

std::uint16_t ServerTechnicalHeader::encoding_type() const { return encoding_type_; }
void ServerTechnicalHeader::set_encoding_type(std::uint16_t value) { encoding_type_ = value; }

std::uint32_t ServerTechnicalHeader::message_sequence_number() const { return message_sequence_number_; }
void ServerTechnicalHeader::set_message_sequence_number(std::uint32_t value) { message_sequence_number_ = value; }

std::chrono::nanoseconds ServerTechnicalHeader::tcp_sending_time() const { return tcp_sending_time_; }
void ServerTechnicalHeader::set_tcp_sending_time(std::chrono::nanoseconds value) { tcp_sending_time_ = value; }

std::uint16_t ServerTechnicalHeader::tcp_message_size() const { return tcp_message_size_; }
void ServerTechnicalHeader::set_tcp_message_size(std::uint16_t value) { tcp_message_size_ = value; }

std::size_t ServerTechnicalHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerTechnicalHeader", wire_size, length);

    encoding_type_ = wire::read_u16_le(data + offset);
    offset += 2;

    message_sequence_number_ = wire::read_u32_le(data + offset);
    offset += 4;

    tcp_sending_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    tcp_message_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t ServerTechnicalHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerTechnicalHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(encoding_type_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(message_sequence_number_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(tcp_sending_time_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(tcp_message_size_));
    offset += 2;

    return offset;
}

std::size_t ServerTechnicalHeader::encoded_size() const {
    return wire_size;
}

void ServerTechnicalHeader::print(std::ostream& out) const {
    out << "ServerTechnicalHeader{";
    out << "encoding_type=";
    out << encoding_type_;
    out << ", message_sequence_number=";
    out << message_sequence_number_;
    out << ", tcp_sending_time=";
    out << tcp_sending_time_.count();
    out << ", tcp_message_size=";
    out << tcp_message_size_;
    out << '}';
}

bool ServerTechnicalHeader::operator==(const ServerTechnicalHeader& other) const {
    return encoding_type_ == other.encoding_type_
        && message_sequence_number_ == other.message_sequence_number_
        && tcp_sending_time_ == other.tcp_sending_time_
        && tcp_message_size_ == other.tcp_message_size_;
}

bool ServerTechnicalHeader::operator!=(const ServerTechnicalHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ServerTechnicalHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
