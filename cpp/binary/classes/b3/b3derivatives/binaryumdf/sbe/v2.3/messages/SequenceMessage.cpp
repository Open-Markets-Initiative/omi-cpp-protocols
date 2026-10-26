#include "SequenceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

SequenceMessage::SequenceMessage(std::uint32_t next_seq_no)
  : next_seq_no_(next_seq_no) {}

std::uint32_t SequenceMessage::next_seq_no() const { return next_seq_no_; }
void SequenceMessage::set_next_seq_no(std::uint32_t value) { next_seq_no_ = value; }

MessageCode SequenceMessage::type() const { return message_type; }

std::string_view SequenceMessage::name() const { return "Sequence Message"; }

std::size_t SequenceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SequenceMessage", wire_size, length);

    next_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SequenceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SequenceMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(next_seq_no_));
    offset += 4;

    return offset;
}

std::size_t SequenceMessage::encoded_size() const {
    return wire_size;
}

void SequenceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SequenceMessage::clone() const {
    return std::make_unique<SequenceMessage>(*this);
}

void SequenceMessage::print(std::ostream& out) const {
    out << "SequenceMessage{";
    out << "next_seq_no=";
    out << next_seq_no_;
    out << '}';
}

bool SequenceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SequenceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SequenceMessage::operator==(const SequenceMessage& other) const {
    return next_seq_no_ == other.next_seq_no_;
}

bool SequenceMessage::operator!=(const SequenceMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
