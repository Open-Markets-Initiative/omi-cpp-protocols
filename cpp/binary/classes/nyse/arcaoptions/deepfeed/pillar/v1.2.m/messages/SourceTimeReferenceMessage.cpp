#include "SourceTimeReferenceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

SourceTimeReferenceMessage::SourceTimeReferenceMessage(std::uint32_t id, std::uint32_t symbol_seq_num, std::uint32_t source_time)
  : id_(id), symbol_seq_num_(symbol_seq_num), source_time_(source_time) {}

std::uint32_t SourceTimeReferenceMessage::id() const { return id_; }
void SourceTimeReferenceMessage::set_id(std::uint32_t value) { id_ = value; }

std::uint32_t SourceTimeReferenceMessage::symbol_seq_num() const { return symbol_seq_num_; }
void SourceTimeReferenceMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t SourceTimeReferenceMessage::source_time() const { return source_time_; }
void SourceTimeReferenceMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

MessageCode SourceTimeReferenceMessage::type() const { return message_type; }

std::string_view SourceTimeReferenceMessage::name() const { return "Source Time Reference Message"; }

std::size_t SourceTimeReferenceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SourceTimeReferenceMessage", wire_size, length);

    id_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SourceTimeReferenceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SourceTimeReferenceMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    return offset;
}

std::size_t SourceTimeReferenceMessage::encoded_size() const {
    return wire_size;
}

void SourceTimeReferenceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SourceTimeReferenceMessage::clone() const {
    return std::make_unique<SourceTimeReferenceMessage>(*this);
}

void SourceTimeReferenceMessage::print(std::ostream& out) const {
    out << "SourceTimeReferenceMessage{";
    out << "id=";
    out << id_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", source_time=";
    out << source_time_;
    out << '}';
}

bool SourceTimeReferenceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SourceTimeReferenceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SourceTimeReferenceMessage::operator==(const SourceTimeReferenceMessage& other) const {
    return id_ == other.id_
        && symbol_seq_num_ == other.symbol_seq_num_
        && source_time_ == other.source_time_;
}

bool SourceTimeReferenceMessage::operator!=(const SourceTimeReferenceMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
