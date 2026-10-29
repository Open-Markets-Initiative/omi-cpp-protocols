#include "SequenceNumberResetMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

SequenceNumberResetMessage::SequenceNumberResetMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint8_t product_id, std::uint8_t channel_id)
  : source_time_(source_time), source_time_ns_(source_time_ns), product_id_(product_id), channel_id_(channel_id) {}

std::uint32_t SequenceNumberResetMessage::source_time() const { return source_time_; }
void SequenceNumberResetMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t SequenceNumberResetMessage::source_time_ns() const { return source_time_ns_; }
void SequenceNumberResetMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint8_t SequenceNumberResetMessage::product_id() const { return product_id_; }
void SequenceNumberResetMessage::set_product_id(std::uint8_t value) { product_id_ = value; }

std::uint8_t SequenceNumberResetMessage::channel_id() const { return channel_id_; }
void SequenceNumberResetMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

MessageCode SequenceNumberResetMessage::type() const { return message_type; }

std::string_view SequenceNumberResetMessage::name() const { return "Sequence Number Reset Message"; }

std::size_t SequenceNumberResetMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SequenceNumberResetMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    product_id_ = wire::read_u8(data + offset);
    offset += 1;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SequenceNumberResetMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SequenceNumberResetMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    return offset;
}

std::size_t SequenceNumberResetMessage::encoded_size() const {
    return wire_size;
}

void SequenceNumberResetMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SequenceNumberResetMessage::clone() const {
    return std::make_unique<SequenceNumberResetMessage>(*this);
}

void SequenceNumberResetMessage::print(std::ostream& out) const {
    out << "SequenceNumberResetMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", product_id=";
    out << static_cast<int>(product_id_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << '}';
}

bool SequenceNumberResetMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SequenceNumberResetMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SequenceNumberResetMessage::operator==(const SequenceNumberResetMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && product_id_ == other.product_id_
        && channel_id_ == other.channel_id_;
}

bool SequenceNumberResetMessage::operator!=(const SequenceNumberResetMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
