#include "RetransmissionRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

RetransmissionRequestMessage::RetransmissionRequestMessage(std::uint32_t begin_seq_num, std::uint32_t end_seq_num, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id)
  : begin_seq_num_(begin_seq_num), end_seq_num_(end_seq_num), source_id_(source_id), product_id_(product_id), channel_id_(channel_id) {}

std::uint32_t RetransmissionRequestMessage::begin_seq_num() const { return begin_seq_num_; }
void RetransmissionRequestMessage::set_begin_seq_num(std::uint32_t value) { begin_seq_num_ = value; }

std::uint32_t RetransmissionRequestMessage::end_seq_num() const { return end_seq_num_; }
void RetransmissionRequestMessage::set_end_seq_num(std::uint32_t value) { end_seq_num_ = value; }

const std::string& RetransmissionRequestMessage::source_id() const { return source_id_; }
std::string& RetransmissionRequestMessage::source_id() { return source_id_; }
void RetransmissionRequestMessage::set_source_id(const std::string& value) { source_id_ = value; }

std::uint8_t RetransmissionRequestMessage::product_id() const { return product_id_; }
void RetransmissionRequestMessage::set_product_id(std::uint8_t value) { product_id_ = value; }

std::uint8_t RetransmissionRequestMessage::channel_id() const { return channel_id_; }
void RetransmissionRequestMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

MessageCode RetransmissionRequestMessage::type() const { return message_type; }

std::string_view RetransmissionRequestMessage::name() const { return "Retransmission Request Message"; }

std::size_t RetransmissionRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetransmissionRequestMessage", wire_size, length);

    begin_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    end_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_id_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    product_id_ = wire::read_u8(data + offset);
    offset += 1;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t RetransmissionRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetransmissionRequestMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(begin_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(end_seq_num_));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', source_id_);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    return offset;
}

std::size_t RetransmissionRequestMessage::encoded_size() const {
    return wire_size;
}

void RetransmissionRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetransmissionRequestMessage::clone() const {
    return std::make_unique<RetransmissionRequestMessage>(*this);
}

void RetransmissionRequestMessage::print(std::ostream& out) const {
    out << "RetransmissionRequestMessage{";
    out << "begin_seq_num=";
    out << begin_seq_num_;
    out << ", end_seq_num=";
    out << end_seq_num_;
    out << ", source_id=";
    print::text(out, source_id_);
    out << ", product_id=";
    out << static_cast<int>(product_id_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << '}';
}

bool RetransmissionRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetransmissionRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetransmissionRequestMessage::operator==(const RetransmissionRequestMessage& other) const {
    return begin_seq_num_ == other.begin_seq_num_
        && end_seq_num_ == other.end_seq_num_
        && source_id_ == other.source_id_
        && product_id_ == other.product_id_
        && channel_id_ == other.channel_id_;
}

bool RetransmissionRequestMessage::operator!=(const RetransmissionRequestMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
