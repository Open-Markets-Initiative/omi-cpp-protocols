#include "EobiHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

EobiHeader::EobiHeader(std::uint16_t body_len, TemplateId template_id, std::uint32_t msg_seq_num)
  : body_len_(body_len), template_id_(template_id), msg_seq_num_(msg_seq_num) {}

std::uint16_t EobiHeader::body_len() const { return body_len_; }
void EobiHeader::set_body_len(std::uint16_t value) { body_len_ = value; }

TemplateId EobiHeader::template_id() const { return template_id_; }
void EobiHeader::set_template_id(TemplateId value) { template_id_ = value; }

std::uint32_t EobiHeader::msg_seq_num() const { return msg_seq_num_; }
void EobiHeader::set_msg_seq_num(std::uint32_t value) { msg_seq_num_ = value; }

std::size_t EobiHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EobiHeader", wire_size, length);

    body_len_ = wire::read_u16_le(data + offset);
    offset += 2;

    template_id_ = static_cast<TemplateId>(wire::read_u16_le(data + offset));
    offset += 2;

    msg_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t EobiHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EobiHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(body_len_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(template_id_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(msg_seq_num_));
    offset += 4;

    return offset;
}

std::size_t EobiHeader::encoded_size() const {
    return wire_size;
}

void EobiHeader::print(std::ostream& out) const {
    out << "EobiHeader{";
    out << "body_len=";
    out << body_len_;
    out << ", template_id=";
    out << template_id_;
    out << ", msg_seq_num=";
    out << msg_seq_num_;
    out << '}';
}

bool EobiHeader::operator==(const EobiHeader& other) const {
    return body_len_ == other.body_len_
        && template_id_ == other.template_id_
        && msg_seq_num_ == other.msg_seq_num_;
}

bool EobiHeader::operator!=(const EobiHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const EobiHeader& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
