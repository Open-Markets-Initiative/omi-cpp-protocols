#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PacketHeader::PacketHeader(const std::string& session, std::uint64_t sequence_number, std::uint16_t message_count)
  : session_(session), sequence_number_(sequence_number), message_count_(message_count) {}

const std::string& PacketHeader::session() const { return session_; }
std::string& PacketHeader::session() { return session_; }
void PacketHeader::set_session(const std::string& value) { session_ = value; }

std::uint64_t PacketHeader::sequence_number() const { return sequence_number_; }
void PacketHeader::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

std::uint16_t PacketHeader::message_count() const { return message_count_; }
void PacketHeader::set_message_count(std::uint16_t value) { message_count_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    session_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    sequence_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    message_count_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_text(data + offset, 10, '\0', session_);
    offset += 10;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(sequence_number_));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_count_));
    offset += 2;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "session=";
    print::text(out, session_);
    out << ", sequence_number=";
    out << sequence_number_;
    out << ", message_count=";
    out << message_count_;
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return session_ == other.session_
        && sequence_number_ == other.sequence_number_
        && message_count_ == other.message_count_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
