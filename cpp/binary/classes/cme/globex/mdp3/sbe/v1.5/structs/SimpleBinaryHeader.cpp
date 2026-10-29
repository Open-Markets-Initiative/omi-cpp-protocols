#include "SimpleBinaryHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

SimpleBinaryHeader::SimpleBinaryHeader(std::uint16_t block_length, TemplateId template_id, SchemaId schema_id, std::uint16_t version)
  : block_length_(block_length), template_id_(template_id), schema_id_(schema_id), version_(version) {}

std::uint16_t SimpleBinaryHeader::block_length() const { return block_length_; }
void SimpleBinaryHeader::set_block_length(std::uint16_t value) { block_length_ = value; }

TemplateId SimpleBinaryHeader::template_id() const { return template_id_; }
void SimpleBinaryHeader::set_template_id(TemplateId value) { template_id_ = value; }

SchemaId SimpleBinaryHeader::schema_id() const { return schema_id_; }
void SimpleBinaryHeader::set_schema_id(SchemaId value) { schema_id_ = value; }

std::uint16_t SimpleBinaryHeader::version() const { return version_; }
void SimpleBinaryHeader::set_version(std::uint16_t value) { version_ = value; }

std::size_t SimpleBinaryHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SimpleBinaryHeader", wire_size, length);

    block_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    template_id_ = static_cast<TemplateId>(wire::read_u16_le(data + offset));
    offset += 2;

    schema_id_ = static_cast<SchemaId>(wire::read_u16_le(data + offset));
    offset += 2;

    version_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t SimpleBinaryHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleBinaryHeader", wire_size, capacity);

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

std::size_t SimpleBinaryHeader::encoded_size() const {
    return wire_size;
}

void SimpleBinaryHeader::print(std::ostream& out) const {
    out << "SimpleBinaryHeader{";
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

bool SimpleBinaryHeader::operator==(const SimpleBinaryHeader& other) const {
    return block_length_ == other.block_length_
        && template_id_ == other.template_id_
        && schema_id_ == other.schema_id_
        && version_ == other.version_;
}

bool SimpleBinaryHeader::operator!=(const SimpleBinaryHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SimpleBinaryHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
