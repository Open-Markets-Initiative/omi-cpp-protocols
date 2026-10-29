#include "NotAppliedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

NotAppliedMessage::NotAppliedMessage(std::uint32_t from_seq_no, std::uint32_t count)
  : from_seq_no_(from_seq_no), count_(count) {}

std::uint32_t NotAppliedMessage::from_seq_no() const { return from_seq_no_; }
void NotAppliedMessage::set_from_seq_no(std::uint32_t value) { from_seq_no_ = value; }

std::uint32_t NotAppliedMessage::count() const { return count_; }
void NotAppliedMessage::set_count(std::uint32_t value) { count_ = value; }

MessageCode NotAppliedMessage::type() const { return message_type; }

std::string_view NotAppliedMessage::name() const { return "Not Applied Message"; }

std::size_t NotAppliedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NotAppliedMessage", wire_size, length);

    from_seq_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    count_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t NotAppliedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NotAppliedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(from_seq_no_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(count_));
    offset += 4;

    return offset;
}

std::size_t NotAppliedMessage::encoded_size() const {
    return wire_size;
}

void NotAppliedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NotAppliedMessage::clone() const {
    return std::make_unique<NotAppliedMessage>(*this);
}

void NotAppliedMessage::print(std::ostream& out) const {
    out << "NotAppliedMessage{";
    out << "from_seq_no=";
    out << from_seq_no_;
    out << ", count=";
    out << count_;
    out << '}';
}

bool NotAppliedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NotAppliedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NotAppliedMessage::operator==(const NotAppliedMessage& other) const {
    return from_seq_no_ == other.from_seq_no_
        && count_ == other.count_;
}

bool NotAppliedMessage::operator!=(const NotAppliedMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
