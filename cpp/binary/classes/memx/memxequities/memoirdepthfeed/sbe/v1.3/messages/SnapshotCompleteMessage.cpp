#include "SnapshotCompleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

SnapshotCompleteMessage::SnapshotCompleteMessage(std::chrono::nanoseconds timestamp, std::uint64_t as_of_sequence_number)
  : timestamp_(timestamp), as_of_sequence_number_(as_of_sequence_number) {}

std::chrono::nanoseconds SnapshotCompleteMessage::timestamp() const { return timestamp_; }
void SnapshotCompleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t SnapshotCompleteMessage::as_of_sequence_number() const { return as_of_sequence_number_; }
void SnapshotCompleteMessage::set_as_of_sequence_number(std::uint64_t value) { as_of_sequence_number_ = value; }

PayloadCode SnapshotCompleteMessage::type() const { return message_type; }

std::string_view SnapshotCompleteMessage::name() const { return "Snapshot Complete Message"; }

std::size_t SnapshotCompleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotCompleteMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    as_of_sequence_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t SnapshotCompleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotCompleteMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(as_of_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t SnapshotCompleteMessage::encoded_size() const {
    return wire_size;
}

void SnapshotCompleteMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> SnapshotCompleteMessage::clone() const {
    return std::make_unique<SnapshotCompleteMessage>(*this);
}

void SnapshotCompleteMessage::print(std::ostream& out) const {
    out << "SnapshotCompleteMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", as_of_sequence_number=";
    out << as_of_sequence_number_;
    out << '}';
}

bool SnapshotCompleteMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const SnapshotCompleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotCompleteMessage::operator==(const SnapshotCompleteMessage& other) const {
    return timestamp_ == other.timestamp_
        && as_of_sequence_number_ == other.as_of_sequence_number_;
}

bool SnapshotCompleteMessage::operator!=(const SnapshotCompleteMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
