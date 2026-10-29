#include "MessageUnavailableMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

MessageUnavailableMessage::MessageUnavailableMessage(std::uint32_t begin_seq_num, std::uint32_t end_seq_num, std::uint8_t product_id, std::uint8_t channel_id)
  : begin_seq_num_(begin_seq_num), end_seq_num_(end_seq_num), product_id_(product_id), channel_id_(channel_id) {}

std::uint32_t MessageUnavailableMessage::begin_seq_num() const { return begin_seq_num_; }
void MessageUnavailableMessage::set_begin_seq_num(std::uint32_t value) { begin_seq_num_ = value; }

std::uint32_t MessageUnavailableMessage::end_seq_num() const { return end_seq_num_; }
void MessageUnavailableMessage::set_end_seq_num(std::uint32_t value) { end_seq_num_ = value; }

std::uint8_t MessageUnavailableMessage::product_id() const { return product_id_; }
void MessageUnavailableMessage::set_product_id(std::uint8_t value) { product_id_ = value; }

std::uint8_t MessageUnavailableMessage::channel_id() const { return channel_id_; }
void MessageUnavailableMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

MessageCode MessageUnavailableMessage::type() const { return message_type; }

std::string_view MessageUnavailableMessage::name() const { return "Message Unavailable Message"; }

std::size_t MessageUnavailableMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageUnavailableMessage", wire_size, length);

    begin_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    end_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    product_id_ = wire::read_u8(data + offset);
    offset += 1;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t MessageUnavailableMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageUnavailableMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(begin_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(end_seq_num_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    return offset;
}

std::size_t MessageUnavailableMessage::encoded_size() const {
    return wire_size;
}

void MessageUnavailableMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MessageUnavailableMessage::clone() const {
    return std::make_unique<MessageUnavailableMessage>(*this);
}

void MessageUnavailableMessage::print(std::ostream& out) const {
    out << "MessageUnavailableMessage{";
    out << "begin_seq_num=";
    out << begin_seq_num_;
    out << ", end_seq_num=";
    out << end_seq_num_;
    out << ", product_id=";
    out << static_cast<int>(product_id_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << '}';
}

bool MessageUnavailableMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MessageUnavailableMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MessageUnavailableMessage::operator==(const MessageUnavailableMessage& other) const {
    return begin_seq_num_ == other.begin_seq_num_
        && end_seq_num_ == other.end_seq_num_
        && product_id_ == other.product_id_
        && channel_id_ == other.channel_id_;
}

bool MessageUnavailableMessage::operator!=(const MessageUnavailableMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
