#include "MessageHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MessageHeader::MessageHeader(std::uint16_t message_length, TemplateId template_id, char message_type, std::uint32_t msg_seq_num)
  : message_length_(message_length), template_id_(template_id), message_type_(message_type), msg_seq_num_(msg_seq_num) {}

std::uint16_t MessageHeader::message_length() const { return message_length_; }
void MessageHeader::set_message_length(std::uint16_t value) { message_length_ = value; }

TemplateId MessageHeader::template_id() const { return template_id_; }
void MessageHeader::set_template_id(TemplateId value) { template_id_ = value; }

char MessageHeader::message_type() const { return message_type_; }
void MessageHeader::set_message_type(char value) { message_type_ = value; }

std::uint32_t MessageHeader::msg_seq_num() const { return msg_seq_num_; }
void MessageHeader::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::size_t MessageHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeader", wire_size, length);

    message_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    template_id_ = static_cast<TemplateId>(wire::read_u8(data + offset));
    offset += 1;

    message_type_ = wire::read_char(data + offset);
    offset += 1;

    msg_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MessageHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(template_id_));
    offset += 1;

    wire::write_char(data + offset, message_type_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(msg_seq_num_));
    offset += 4;

    return offset;
}

std::size_t MessageHeader::encoded_size() const {
    return wire_size;
}

void MessageHeader::print(std::ostream& out) const {
    out << "MessageHeader{";
    out << "message_length=";
    out << message_length_;
    out << ", template_id=";
    out << template_id_;
    out << ", message_type=";
    print::character(out, message_type_);
    out << ", msg_seq_num=";
    out << msg_seq_num_;
    out << '}';
}

bool MessageHeader::operator==(const MessageHeader& other) const {
    return message_length_ == other.message_length_
        && template_id_ == other.template_id_
        && message_type_ == other.message_type_
        && msg_seq_num_ == other.msg_seq_num_;
}

bool MessageHeader::operator!=(const MessageHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
