#include "SbeHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

SbeHeader::SbeHeader(std::uint16_t block_length, TemplateId template_id, std::uint8_t schema_id, std::uint16_t version)
  : block_length_(block_length), template_id_(template_id), schema_id_(schema_id), version_(version) {}

std::uint16_t SbeHeader::block_length() const { return block_length_; }
void SbeHeader::set_block_length(std::uint16_t value) { block_length_ = value; }

TemplateId SbeHeader::template_id() const { return template_id_; }
void SbeHeader::set_template_id(TemplateId value) { template_id_ = value; }

std::uint8_t SbeHeader::schema_id() const { return schema_id_; }
void SbeHeader::set_schema_id(std::uint8_t value) { schema_id_ = value; }

std::uint16_t SbeHeader::version() const { return version_; }
void SbeHeader::set_version(std::uint16_t value) { version_ = value; }

std::size_t SbeHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SbeHeader", wire_size, length);

    block_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    template_id_ = static_cast<TemplateId>(wire::read_u8(data + offset));
    offset += 1;

    schema_id_ = wire::read_u8(data + offset);
    offset += 1;

    version_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t SbeHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SbeHeader", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(block_length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(template_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(schema_id_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(version_));
    offset += 2;

    return offset;
}

std::size_t SbeHeader::encoded_size() const {
    return wire_size;
}

void SbeHeader::print(std::ostream& out) const {
    out << "SbeHeader{";
    out << "block_length=";
    out << block_length_;
    out << ", template_id=";
    out << template_id_;
    out << ", schema_id=";
    out << static_cast<int>(schema_id_);
    out << ", version=";
    out << version_;
    out << '}';
}

bool SbeHeader::operator==(const SbeHeader& other) const {
    return block_length_ == other.block_length_
        && template_id_ == other.template_id_
        && schema_id_ == other.schema_id_
        && version_ == other.version_;
}

bool SbeHeader::operator!=(const SbeHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SbeHeader& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
