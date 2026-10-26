#include "MdInstrumentEntryGrpComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

MdInstrumentEntryGrpComp::MdInstrumentEntryGrpComp(std::optional<Decimal> md_entry_px, std::optional<Decimal> md_entry_size, std::optional<MdOriginType> md_origin_type, std::optional<MdEntryType> md_entry_type, std::optional<TradeCondition> trade_condition, std::optional<TrdType> trd_type, std::optional<MultiLegReportingType> multi_leg_reporting_type, std::optional<MultiLegPriceModel> multi_leg_price_model, std::optional<Decimal> non_disclosed_trade_volume)
  : md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), md_origin_type_(md_origin_type), md_entry_type_(md_entry_type), trade_condition_(trade_condition), trd_type_(trd_type), multi_leg_reporting_type_(multi_leg_reporting_type), multi_leg_price_model_(multi_leg_price_model), non_disclosed_trade_volume_(non_disclosed_trade_volume) {}

std::optional<Decimal> MdInstrumentEntryGrpComp::md_entry_px() const { return md_entry_px_; }
void MdInstrumentEntryGrpComp::set_md_entry_px(std::optional<Decimal> value) { md_entry_px_ = value; }

std::optional<Decimal> MdInstrumentEntryGrpComp::md_entry_size() const { return md_entry_size_; }
void MdInstrumentEntryGrpComp::set_md_entry_size(std::optional<Decimal> value) { md_entry_size_ = value; }

std::optional<MdOriginType> MdInstrumentEntryGrpComp::md_origin_type() const { return md_origin_type_; }
void MdInstrumentEntryGrpComp::set_md_origin_type(std::optional<MdOriginType> value) { md_origin_type_ = value; }

std::optional<MdEntryType> MdInstrumentEntryGrpComp::md_entry_type() const { return md_entry_type_; }
void MdInstrumentEntryGrpComp::set_md_entry_type(std::optional<MdEntryType> value) { md_entry_type_ = value; }

std::optional<TradeCondition> MdInstrumentEntryGrpComp::trade_condition() const { return trade_condition_; }
void MdInstrumentEntryGrpComp::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

std::optional<TrdType> MdInstrumentEntryGrpComp::trd_type() const { return trd_type_; }
void MdInstrumentEntryGrpComp::set_trd_type(std::optional<TrdType> value) { trd_type_ = value; }

std::optional<MultiLegReportingType> MdInstrumentEntryGrpComp::multi_leg_reporting_type() const { return multi_leg_reporting_type_; }
void MdInstrumentEntryGrpComp::set_multi_leg_reporting_type(std::optional<MultiLegReportingType> value) { multi_leg_reporting_type_ = value; }

std::optional<MultiLegPriceModel> MdInstrumentEntryGrpComp::multi_leg_price_model() const { return multi_leg_price_model_; }
void MdInstrumentEntryGrpComp::set_multi_leg_price_model(std::optional<MultiLegPriceModel> value) { multi_leg_price_model_ = value; }

std::optional<Decimal> MdInstrumentEntryGrpComp::non_disclosed_trade_volume() const { return non_disclosed_trade_volume_; }
void MdInstrumentEntryGrpComp::set_non_disclosed_trade_volume(std::optional<Decimal> value) { non_disclosed_trade_volume_ = value; }

std::size_t MdInstrumentEntryGrpComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MdInstrumentEntryGrpComp", wire_size, length);

    md_entry_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    md_entry_size_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    md_origin_type_ = wire::nullable_enum<MdOriginType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    md_entry_type_ = wire::nullable_enum<MdEntryType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    trd_type_ = wire::nullable_enum<TrdType>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    multi_leg_reporting_type_ = wire::nullable_enum<MultiLegReportingType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    multi_leg_price_model_ = wire::nullable_enum<MultiLegPriceModel>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    non_disclosed_trade_volume_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    return offset;
}

std::size_t MdInstrumentEntryGrpComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdInstrumentEntryGrpComp", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_ ? static_cast<std::int64_t>(md_entry_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, md_entry_size_ ? static_cast<std::int64_t>(md_entry_size_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u8(data + offset, md_origin_type_ ? static_cast<std::uint8_t>(*md_origin_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, md_entry_type_ ? static_cast<std::uint8_t>(*md_entry_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u16_le(data + offset, trade_condition_ ? static_cast<std::uint16_t>(*trade_condition_) : static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::write_u16_le(data + offset, trd_type_ ? static_cast<std::uint16_t>(*trd_type_) : static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::write_u8(data + offset, multi_leg_reporting_type_ ? static_cast<std::uint8_t>(*multi_leg_reporting_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, multi_leg_price_model_ ? static_cast<std::uint8_t>(*multi_leg_price_model_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_i64_le(data + offset, non_disclosed_trade_volume_ ? static_cast<std::int64_t>(non_disclosed_trade_volume_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

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
    out << ", md_origin_type=";
    print::optional(out, md_origin_type_);
    out << ", md_entry_type=";
    print::optional(out, md_entry_type_);
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", trd_type=";
    print::optional(out, trd_type_);
    out << ", multi_leg_reporting_type=";
    print::optional(out, multi_leg_reporting_type_);
    out << ", multi_leg_price_model=";
    print::optional(out, multi_leg_price_model_);
    out << ", non_disclosed_trade_volume=";
    print::optional(out, non_disclosed_trade_volume_);
    out << '}';
}

bool MdInstrumentEntryGrpComp::operator==(const MdInstrumentEntryGrpComp& other) const {
    return md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && md_origin_type_ == other.md_origin_type_
        && md_entry_type_ == other.md_entry_type_
        && trade_condition_ == other.trade_condition_
        && trd_type_ == other.trd_type_
        && multi_leg_reporting_type_ == other.multi_leg_reporting_type_
        && multi_leg_price_model_ == other.multi_leg_price_model_
        && non_disclosed_trade_volume_ == other.non_disclosed_trade_volume_;
}

bool MdInstrumentEntryGrpComp::operator!=(const MdInstrumentEntryGrpComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
