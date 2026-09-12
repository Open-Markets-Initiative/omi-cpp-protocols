#include "SnapshotStartMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

SnapshotStartMessage::SnapshotStartMessage(std::uint64_t snapshot_length)
  : snapshot_length_(snapshot_length) {}

std::uint64_t SnapshotStartMessage::snapshot_length() const { return snapshot_length_; }
void SnapshotStartMessage::set_snapshot_length(std::uint64_t value) { snapshot_length_ = value; }

MessageCode SnapshotStartMessage::type() const { return message_type; }

std::string_view SnapshotStartMessage::name() const { return "Snapshot Start Message"; }

std::size_t SnapshotStartMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotStartMessage", wire_size, length);

    snapshot_length_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t SnapshotStartMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotStartMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(snapshot_length_));
    offset += 8;

    return offset;
}

std::size_t SnapshotStartMessage::encoded_size() const {
    return wire_size;
}

void SnapshotStartMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotStartMessage::clone() const {
    return std::make_unique<SnapshotStartMessage>(*this);
}

void SnapshotStartMessage::print(std::ostream& out) const {
    out << "SnapshotStartMessage{";
    out << "snapshot_length=";
    out << snapshot_length_;
    out << '}';
}

bool SnapshotStartMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotStartMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotStartMessage::operator==(const SnapshotStartMessage& other) const {
    return snapshot_length_ == other.snapshot_length_;
}

bool SnapshotStartMessage::operator!=(const SnapshotStartMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::snap::v1_05
