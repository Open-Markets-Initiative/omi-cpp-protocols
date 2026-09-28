#include "EmptyBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

EmptyBookMessage::EmptyBookMessage(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& offset_9_padding_3, std::optional<std::chrono::nanoseconds> md_entry_timestamp)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), offset_9_padding_3_(offset_9_padding_3), md_entry_timestamp_(md_entry_timestamp) {}

std::uint64_t EmptyBookMessage::security_id() const { return security_id_; }
void EmptyBookMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& EmptyBookMessage::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& EmptyBookMessage::match_event_indicator() { return match_event_indicator_; }
void EmptyBookMessage::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 3>& EmptyBookMessage::offset_9_padding_3() const { return offset_9_padding_3_; }
std::array<std::byte, 3>& EmptyBookMessage::offset_9_padding_3() { return offset_9_padding_3_; }
void EmptyBookMessage::set_offset_9_padding_3(const std::array<std::byte, 3>& value) { offset_9_padding_3_ = value; }

std::optional<std::chrono::nanoseconds> EmptyBookMessage::md_entry_timestamp() const { return md_entry_timestamp_; }
void EmptyBookMessage::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

MessageCode EmptyBookMessage::type() const { return message_type; }

std::string_view EmptyBookMessage::name() const { return "Empty Book Message"; }

std::size_t EmptyBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EmptyBookMessage", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_9_padding_3_.data(), 3);
    offset += 3;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t EmptyBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EmptyBookMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_9_padding_3_.data(), 3);
    offset += 3;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t EmptyBookMessage::encoded_size() const {
    return wire_size;
}

void EmptyBookMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EmptyBookMessage::clone() const {
    return std::make_unique<EmptyBookMessage>(*this);
}

void EmptyBookMessage::print(std::ostream& out) const {
    out << "EmptyBookMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", offset_9_padding_3=";
    print::hex(out, offset_9_padding_3_.data(), offset_9_padding_3_.size());
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << '}';
}

bool EmptyBookMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EmptyBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EmptyBookMessage::operator==(const EmptyBookMessage& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && offset_9_padding_3_ == other.offset_9_padding_3_
        && md_entry_timestamp_ == other.md_entry_timestamp_;
}

bool EmptyBookMessage::operator!=(const EmptyBookMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
