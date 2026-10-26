#include "SequencedDataPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SequencedDataPacket::SequencedDataPacket(std::uint64_t sequence_number, std::uint8_t matching_engine_id, char sequenced_message_type, const std::array<std::byte, 0>& sequenced_message)
  : sequence_number_(sequence_number), matching_engine_id_(matching_engine_id), sequenced_message_type_(sequenced_message_type), sequenced_message_(sequenced_message) {}

std::uint64_t SequencedDataPacket::sequence_number() const { return sequence_number_; }
void SequencedDataPacket::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

std::uint8_t SequencedDataPacket::matching_engine_id() const { return matching_engine_id_; }
void SequencedDataPacket::set_matching_engine_id(std::uint8_t value) { matching_engine_id_ = value; }

char SequencedDataPacket::sequenced_message_type() const { return sequenced_message_type_; }
void SequencedDataPacket::set_sequenced_message_type(char value) { sequenced_message_type_ = value; }

const std::array<std::byte, 0>& SequencedDataPacket::sequenced_message() const { return sequenced_message_; }
std::array<std::byte, 0>& SequencedDataPacket::sequenced_message() { return sequenced_message_; }
void SequencedDataPacket::set_sequenced_message(const std::array<std::byte, 0>& value) { sequenced_message_ = value; }

TcpMessageCode SequencedDataPacket::type() const { return message_type; }

std::string_view SequencedDataPacket::name() const { return "Sequenced Data Packet"; }

std::size_t SequencedDataPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SequencedDataPacket", wire_size, length);

    sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    matching_engine_id_ = wire::read_u8(data + offset);
    offset += 1;

    sequenced_message_type_ = wire::read_char(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, sequenced_message_.data(), 0);
    offset += 0;

    return offset;
}

std::size_t SequencedDataPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SequencedDataPacket", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sequence_number_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(matching_engine_id_));
    offset += 1;

    wire::write_char(data + offset, sequenced_message_type_);
    offset += 1;

    wire::write_bytes(data + offset, sequenced_message_.data(), 0);
    offset += 0;

    return offset;
}

std::size_t SequencedDataPacket::encoded_size() const {
    return wire_size;
}

void SequencedDataPacket::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> SequencedDataPacket::clone() const {
    return std::make_unique<SequencedDataPacket>(*this);
}

void SequencedDataPacket::print(std::ostream& out) const {
    out << "SequencedDataPacket{";
    out << "sequence_number=";
    out << sequence_number_;
    out << ", matching_engine_id=";
    out << static_cast<int>(matching_engine_id_);
    out << ", sequenced_message_type=";
    print::character(out, sequenced_message_type_);
    out << ", sequenced_message=";
    print::hex(out, sequenced_message_.data(), sequenced_message_.size());
    out << '}';
}

bool SequencedDataPacket::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const SequencedDataPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool SequencedDataPacket::operator==(const SequencedDataPacket& other) const {
    return sequence_number_ == other.sequence_number_
        && matching_engine_id_ == other.matching_engine_id_
        && sequenced_message_type_ == other.sequenced_message_type_
        && sequenced_message_ == other.sequenced_message_;
}

bool SequencedDataPacket::operator!=(const SequencedDataPacket& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
