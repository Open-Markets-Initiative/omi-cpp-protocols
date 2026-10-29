#include "MdInstrumentEntryGrpComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

MdInstrumentEntryGrpComp::MdInstrumentEntryGrpComp(std::optional<Decimal> md_entry_px, std::optional<std::int32_t> md_entry_size, std::optional<MdEntryType> md_entry_type, std::optional<TradeCondition> trade_condition, const std::array<std::byte, 2>& pad2)
  : md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), md_entry_type_(md_entry_type), trade_condition_(trade_condition), pad2_(pad2) {}

std::optional<Decimal> MdInstrumentEntryGrpComp::md_entry_px() const { return md_entry_px_; }
void MdInstrumentEntryGrpComp::set_md_entry_px(std::optional<Decimal> value) { md_entry_px_ = value; }

std::optional<std::int32_t> MdInstrumentEntryGrpComp::md_entry_size() const { return md_entry_size_; }
void MdInstrumentEntryGrpComp::set_md_entry_size(std::optional<std::int32_t> value) { md_entry_size_ = value; }

std::optional<MdEntryType> MdInstrumentEntryGrpComp::md_entry_type() const { return md_entry_type_; }
void MdInstrumentEntryGrpComp::set_md_entry_type(std::optional<MdEntryType> value) { md_entry_type_ = value; }

std::optional<TradeCondition> MdInstrumentEntryGrpComp::trade_condition() const { return trade_condition_; }
void MdInstrumentEntryGrpComp::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

const std::array<std::byte, 2>& MdInstrumentEntryGrpComp::pad2() const { return pad2_; }
std::array<std::byte, 2>& MdInstrumentEntryGrpComp::pad2() { return pad2_; }
void MdInstrumentEntryGrpComp::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::size_t MdInstrumentEntryGrpComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MdInstrumentEntryGrpComp", wire_size, length);

    md_entry_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    md_entry_size_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    md_entry_type_ = wire::nullable_enum<MdEntryType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t MdInstrumentEntryGrpComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdInstrumentEntryGrpComp", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_ ? static_cast<std::int64_t>(md_entry_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i32_le(data + offset, md_entry_size_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, md_entry_type_ ? static_cast<std::uint8_t>(*md_entry_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, trade_condition_ ? static_cast<std::uint8_t>(*trade_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t MdInstrumentEntryGrpComp::encoded_size() const {
    return wire_size;
}

void MdInstrumentEntryGrpComp::print(std::ostream& out) const {
    out << "MdInstrumentEntryGrpComp{";
    out << "md_entry_px=";
    print::optional(out, md_entry_px_);
    out << ", md_entry_size=";
    print::optional(out, md_entry_size_);
    out << ", md_entry_type=";
    print::optional(out, md_entry_type_);
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << '}';
}

bool MdInstrumentEntryGrpComp::operator==(const MdInstrumentEntryGrpComp& other) const {
    return md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && md_entry_type_ == other.md_entry_type_
        && trade_condition_ == other.trade_condition_
        && pad2_ == other.pad2_;
}

bool MdInstrumentEntryGrpComp::operator!=(const MdInstrumentEntryGrpComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
