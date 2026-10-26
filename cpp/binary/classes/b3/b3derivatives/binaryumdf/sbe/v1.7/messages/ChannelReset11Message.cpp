#include "ChannelReset11Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

ChannelReset11Message::ChannelReset11Message(const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& offset_1_padding_3, std::optional<std::chrono::nanoseconds> md_entry_timestamp)
  : match_event_indicator_(match_event_indicator), offset_1_padding_3_(offset_1_padding_3), md_entry_timestamp_(md_entry_timestamp) {}

const MatchEventIndicator& ChannelReset11Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ChannelReset11Message::match_event_indicator() { return match_event_indicator_; }
void ChannelReset11Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 3>& ChannelReset11Message::offset_1_padding_3() const { return offset_1_padding_3_; }
std::array<std::byte, 3>& ChannelReset11Message::offset_1_padding_3() { return offset_1_padding_3_; }
void ChannelReset11Message::set_offset_1_padding_3(const std::array<std::byte, 3>& value) { offset_1_padding_3_ = value; }

std::optional<std::chrono::nanoseconds> ChannelReset11Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void ChannelReset11Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

MessageCode ChannelReset11Message::type() const { return message_type; }

std::string_view ChannelReset11Message::name() const { return "Channel Reset 11 Message"; }

std::size_t ChannelReset11Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ChannelReset11Message", wire_size, length);

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_1_padding_3_.data(), 3);
    offset += 3;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t ChannelReset11Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ChannelReset11Message", wire_size, capacity);

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_1_padding_3_.data(), 3);
    offset += 3;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t ChannelReset11Message::encoded_size() const {
    return wire_size;
}

void ChannelReset11Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ChannelReset11Message::clone() const {
    return std::make_unique<ChannelReset11Message>(*this);
}

void ChannelReset11Message::print(std::ostream& out) const {
    out << "ChannelReset11Message{";
    out << "match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", offset_1_padding_3=";
    print::hex(out, offset_1_padding_3_.data(), offset_1_padding_3_.size());
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << '}';
}

bool ChannelReset11Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ChannelReset11Message*>(&other);
    return that != nullptr && *this == *that;
}

bool ChannelReset11Message::operator==(const ChannelReset11Message& other) const {
    return match_event_indicator_ == other.match_event_indicator_
        && offset_1_padding_3_ == other.offset_1_padding_3_
        && md_entry_timestamp_ == other.md_entry_timestamp_;
}

bool ChannelReset11Message::operator!=(const ChannelReset11Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
