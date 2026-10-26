#include "SnapshotEndMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

SnapshotEndMessage::SnapshotEndMessage(std::uint64_t snapshot_sequence_number)
  : snapshot_sequence_number_(snapshot_sequence_number) {}

std::uint64_t SnapshotEndMessage::snapshot_sequence_number() const { return snapshot_sequence_number_; }
void SnapshotEndMessage::set_snapshot_sequence_number(std::uint64_t value) { snapshot_sequence_number_ = value; }

MessageCode SnapshotEndMessage::type() const { return message_type; }

std::string_view SnapshotEndMessage::name() const { return "Snapshot End Message"; }

std::size_t SnapshotEndMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotEndMessage", wire_size, length);

    snapshot_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t SnapshotEndMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotEndMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(snapshot_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t SnapshotEndMessage::encoded_size() const {
    return wire_size;
}

void SnapshotEndMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotEndMessage::clone() const {
    return std::make_unique<SnapshotEndMessage>(*this);
}

void SnapshotEndMessage::print(std::ostream& out) const {
    out << "SnapshotEndMessage{";
    out << "snapshot_sequence_number=";
    out << snapshot_sequence_number_;
    out << '}';
}

bool SnapshotEndMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotEndMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotEndMessage::operator==(const SnapshotEndMessage& other) const {
    return snapshot_sequence_number_ == other.snapshot_sequence_number_;
}

bool SnapshotEndMessage::operator!=(const SnapshotEndMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::tops::snap::v1_6
