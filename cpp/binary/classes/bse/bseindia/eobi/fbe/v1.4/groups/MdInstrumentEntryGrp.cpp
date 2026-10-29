#include "MdInstrumentEntryGrp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

MdInstrumentEntryGrp::MdInstrumentEntryGrp(std::optional<Decimal> md_entry_px, std::optional<std::int64_t> md_entry_size, MdEntryType md_entry_type, const std::array<std::byte, 7>& pad_7)
  : md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), md_entry_type_(md_entry_type), pad_7_(pad_7) {}

std::optional<Decimal> MdInstrumentEntryGrp::md_entry_px() const { return md_entry_px_; }
void MdInstrumentEntryGrp::set_md_entry_px(std::optional<Decimal> value) { md_entry_px_ = value; }

std::optional<std::int64_t> MdInstrumentEntryGrp::md_entry_size() const { return md_entry_size_; }
void MdInstrumentEntryGrp::set_md_entry_size(std::optional<std::int64_t> value) { md_entry_size_ = value; }

MdEntryType MdInstrumentEntryGrp::md_entry_type() const { return md_entry_type_; }
void MdInstrumentEntryGrp::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const std::array<std::byte, 7>& MdInstrumentEntryGrp::pad_7() const { return pad_7_; }
std::array<std::byte, 7>& MdInstrumentEntryGrp::pad_7() { return pad_7_; }
void MdInstrumentEntryGrp::set_pad_7(const std::array<std::byte, 7>& value) { pad_7_ = value; }

std::size_t MdInstrumentEntryGrp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MdInstrumentEntryGrp", wire_size, length);

    md_entry_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    md_entry_size_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t MdInstrumentEntryGrp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdInstrumentEntryGrp", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_ ? static_cast<std::int64_t>(md_entry_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, md_entry_size_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_entry_type_));
    offset += 1;

    wire::write_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t MdInstrumentEntryGrp::encoded_size() const {
    return wire_size;
}

void MdInstrumentEntryGrp::print(std::ostream& out) const {
    out << "MdInstrumentEntryGrp{";
    out << "md_entry_px=";
    print::optional(out, md_entry_px_);
    out << ", md_entry_size=";
    print::optional(out, md_entry_size_);
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << ", pad_7=";
    print::hex(out, pad_7_.data(), pad_7_.size());
    out << '}';
}

bool MdInstrumentEntryGrp::operator==(const MdInstrumentEntryGrp& other) const {
    return md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && md_entry_type_ == other.md_entry_type_
        && pad_7_ == other.pad_7_;
}

bool MdInstrumentEntryGrp::operator!=(const MdInstrumentEntryGrp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrp& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
