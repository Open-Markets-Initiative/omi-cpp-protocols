#include "MdTradeEntryGrpComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

MdTradeEntryGrpComp::MdTradeEntryGrpComp(std::optional<Decimal> md_entry_px, std::optional<std::int32_t> md_entry_size, std::optional<MdEntryType> md_entry_type, const std::array<std::byte, 3>& pad3)
  : md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), md_entry_type_(md_entry_type), pad3_(pad3) {}

std::optional<Decimal> MdTradeEntryGrpComp::md_entry_px() const { return md_entry_px_; }
void MdTradeEntryGrpComp::set_md_entry_px(std::optional<Decimal> value) { md_entry_px_ = value; }

std::optional<std::int32_t> MdTradeEntryGrpComp::md_entry_size() const { return md_entry_size_; }
void MdTradeEntryGrpComp::set_md_entry_size(std::optional<std::int32_t> value) { md_entry_size_ = value; }

std::optional<MdEntryType> MdTradeEntryGrpComp::md_entry_type() const { return md_entry_type_; }
void MdTradeEntryGrpComp::set_md_entry_type(std::optional<MdEntryType> value) { md_entry_type_ = value; }

const std::array<std::byte, 3>& MdTradeEntryGrpComp::pad3() const { return pad3_; }
std::array<std::byte, 3>& MdTradeEntryGrpComp::pad3() { return pad3_; }
void MdTradeEntryGrpComp::set_pad3(const std::array<std::byte, 3>& value) { pad3_ = value; }

std::size_t MdTradeEntryGrpComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MdTradeEntryGrpComp", wire_size, length);

    md_entry_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    md_entry_size_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    md_entry_type_ = wire::nullable_enum<MdEntryType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t MdTradeEntryGrpComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdTradeEntryGrpComp", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_ ? static_cast<std::int64_t>(md_entry_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i32_le(data + offset, md_entry_size_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, md_entry_type_ ? static_cast<std::uint8_t>(*md_entry_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t MdTradeEntryGrpComp::encoded_size() const {
    return wire_size;
}

void MdTradeEntryGrpComp::print(std::ostream& out) const {
    out << "MdTradeEntryGrpComp{";
    out << "md_entry_px=";
    print::optional(out, md_entry_px_);
    out << ", md_entry_size=";
    print::optional(out, md_entry_size_);
    out << ", md_entry_type=";
    print::optional(out, md_entry_type_);
    out << ", pad3=";
    print::hex(out, pad3_.data(), pad3_.size());
    out << '}';
}

bool MdTradeEntryGrpComp::operator==(const MdTradeEntryGrpComp& other) const {
    return md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && md_entry_type_ == other.md_entry_type_
        && pad3_ == other.pad3_;
}

bool MdTradeEntryGrpComp::operator!=(const MdTradeEntryGrpComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MdTradeEntryGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v3_0
