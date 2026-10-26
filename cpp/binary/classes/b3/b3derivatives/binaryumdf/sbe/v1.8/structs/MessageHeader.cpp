#include "MessageHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

MessageHeader::MessageHeader(std::uint16_t block_length, TemplateId template_id, std::uint16_t schema_id, std::uint16_t version)
  : block_length_(block_length), template_id_(template_id), schema_id_(schema_id), version_(version) {}

std::uint16_t MessageHeader::block_length() const { return block_length_; }
void MessageHeader::set_block_length(std::uint16_t value) { block_length_ = value; }

TemplateId MessageHeader::template_id() const { return template_id_; }
void MessageHeader::set_template_id(TemplateId value) { template_id_ = value; }

std::uint16_t MessageHeader::schema_id() const { return schema_id_; }
void MessageHeader::set_schema_id(std::uint16_t value) { schema_id_ = value; }

std::uint16_t MessageHeader::version() const { return version_; }
void MessageHeader::set_version(std::uint16_t value) { version_ = value; }

std::size_t MessageHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageHeader", wire_size, length);

    block_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    template_id_ = static_cast<TemplateId>(wire::read_u16_le(data + offset));
    offset += 2;

    schema_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    version_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t MessageHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageHeader", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(block_length_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(template_id_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(schema_id_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(version_));
    offset += 2;

    return offset;
}

std::size_t MessageHeader::encoded_size() const {
    return wire_size;
}

void MessageHeader::print(std::ostream& out) const {
    out << "MessageHeader{";
    out << "block_length=";
    out << block_length_;
    out << ", template_id=";
    out << template_id_;
    out << ", schema_id=";
    out << schema_id_;
    out << ", version=";
    out << version_;
    out << '}';
}

bool MessageHeader::operator==(const MessageHeader& other) const {
    return block_length_ == other.block_length_
        && template_id_ == other.template_id_
        && schema_id_ == other.schema_id_
        && version_ == other.version_;
}

bool MessageHeader::operator!=(const MessageHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MessageHeader& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
