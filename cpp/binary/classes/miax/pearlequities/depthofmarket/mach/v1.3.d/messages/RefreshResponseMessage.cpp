#include "RefreshResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

RefreshResponseMessage::RefreshResponseMessage(std::uint64_t sequence_number)
  : sequence_number_(sequence_number) {}

std::uint64_t RefreshResponseMessage::sequence_number() const { return sequence_number_; }
void RefreshResponseMessage::set_sequence_number(std::uint64_t value) { sequence_number_ = value; }

UnsequencedMessageCode RefreshResponseMessage::type() const { return message_type; }

std::string_view RefreshResponseMessage::name() const { return "Refresh Response Message"; }

std::size_t RefreshResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RefreshResponseMessage", wire_size, length);

    sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t RefreshResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshResponseMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sequence_number_));
    offset += 8;

    return offset;
}

std::size_t RefreshResponseMessage::encoded_size() const {
    return wire_size;
}

void RefreshResponseMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> RefreshResponseMessage::clone() const {
    return std::make_unique<RefreshResponseMessage>(*this);
}

void RefreshResponseMessage::print(std::ostream& out) const {
    out << "RefreshResponseMessage{";
    out << "sequence_number=";
    out << sequence_number_;
    out << '}';
}

bool RefreshResponseMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const RefreshResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshResponseMessage::operator==(const RefreshResponseMessage& other) const {
    return sequence_number_ == other.sequence_number_;
}

bool RefreshResponseMessage::operator!=(const RefreshResponseMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
