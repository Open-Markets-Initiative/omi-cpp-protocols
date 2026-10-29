#include "MessageHeaderComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

MessageHeaderComp::MessageHeaderComp(std::uint16_t body_len, TemplateId template_id, std::uint32_t msg_seq_num)
  : body_len_(body_len), template_id_(template_id), msg_seq_num_(msg_seq_num) {}

std::uint16_t MessageHeaderComp::body_len() const { return body_len_; }
void MessageHeaderComp::set_body_len(std::uint16_t value) { body_len_ = value; }

TemplateId MessageHeaderComp::template_id() const { return template_id_; }
void MessageHeaderComp::set_template_id(TemplateId value) { template_id_ = value; }

std::uint32_t MessageHeaderComp::msg_seq_num() const { return msg_seq_num_; }
void MessageHeaderComp::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::size_t MessageHeaderComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeaderComp", wire_size, length);

    body_len_ = wire::read_u16_le(data + offset);
    offset += 2;

    template_id_ = static_cast<TemplateId>(wire::read_u16_le(data + offset));
    offset += 2;

    msg_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t MessageHeaderComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeaderComp", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(body_len_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(template_id_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(msg_seq_num_));
    offset += 4;

    return offset;
}

std::size_t MessageHeaderComp::encoded_size() const {
    return wire_size;
}

void MessageHeaderComp::print(std::ostream& out) const {
    out << "MessageHeaderComp{";
    out << "body_len=";
    out << body_len_;
    out << ", template_id=";
    out << template_id_;
    out << ", msg_seq_num=";
    out << msg_seq_num_;
    out << '}';
}

bool MessageHeaderComp::operator==(const MessageHeaderComp& other) const {
    return body_len_ == other.body_len_
        && template_id_ == other.template_id_
        && msg_seq_num_ == other.msg_seq_num_;
}

bool MessageHeaderComp::operator!=(const MessageHeaderComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeaderComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
