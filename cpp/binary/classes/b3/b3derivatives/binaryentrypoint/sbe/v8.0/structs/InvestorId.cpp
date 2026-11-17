// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.0: structs/InvestorId.cpp
#include "InvestorId.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

InvestorId::InvestorId(std::optional<std::uint16_t> prefix, const std::array<std::byte, 2>& offset_2_padding_2, std::optional<std::uint32_t> document)
  : prefix_(prefix), offset_2_padding_2_(offset_2_padding_2), document_(document) {}

std::optional<std::uint16_t> InvestorId::prefix() const { return prefix_; }
void InvestorId::set_prefix(std::optional<std::uint16_t> value) { prefix_ = value; }

const std::array<std::byte, 2>& InvestorId::offset_2_padding_2() const { return offset_2_padding_2_; }
std::array<std::byte, 2>& InvestorId::offset_2_padding_2() { return offset_2_padding_2_; }
void InvestorId::set_offset_2_padding_2(const std::array<std::byte, 2>& value) { offset_2_padding_2_ = value; }

std::optional<std::uint32_t> InvestorId::document() const { return document_; }
void InvestorId::set_document(std::optional<std::uint32_t> value) { document_ = value; }

std::size_t InvestorId::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InvestorId", wire_size, length);

    prefix_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::read_bytes(data + offset, offset_2_padding_2_.data(), 2);
    offset += 2;

    document_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t InvestorId::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InvestorId", wire_size, capacity);

    wire::write_u16_le(data + offset, prefix_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_bytes(data + offset, offset_2_padding_2_.data(), 2);
    offset += 2;

    wire::write_u32_le(data + offset, document_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t InvestorId::encoded_size() const {
    return wire_size;
}

void InvestorId::print(std::ostream& out) const {
    out << "InvestorId{";
    out << "prefix=";
    print::optional(out, prefix_);
    out << ", offset_2_padding_2=";
    print::hex(out, offset_2_padding_2_.data(), offset_2_padding_2_.size());
    out << ", document=";
    print::optional(out, document_);
    out << '}';
}

bool InvestorId::operator==(const InvestorId& other) const {
    return prefix_ == other.prefix_
        && offset_2_padding_2_ == other.offset_2_padding_2_
        && document_ == other.document_;
}

bool InvestorId::operator!=(const InvestorId& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InvestorId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
