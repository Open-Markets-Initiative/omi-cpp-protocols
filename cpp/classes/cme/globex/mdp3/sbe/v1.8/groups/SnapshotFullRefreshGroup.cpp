#include "SnapshotFullRefreshGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

SnapshotFullRefreshGroup::SnapshotFullRefreshGroup(std::optional<Decimal> md_entry_px_optional, std::optional<std::int32_t> md_entry_size_optional, std::optional<std::int32_t> number_of_orders, std::optional<std::int8_t> md_price_level_optional, std::optional<std::uint16_t> trading_reference_date, std::optional<OpenCloseSettlFlag> open_close_settl_flag, const SettlPriceType& settl_price_type, MdEntryType md_entry_type)
  : md_entry_px_optional_(md_entry_px_optional), md_entry_size_optional_(md_entry_size_optional), number_of_orders_(number_of_orders), md_price_level_optional_(md_price_level_optional), trading_reference_date_(trading_reference_date), open_close_settl_flag_(open_close_settl_flag), settl_price_type_(settl_price_type), md_entry_type_(md_entry_type) {}

std::optional<Decimal> SnapshotFullRefreshGroup::md_entry_px_optional() const { return md_entry_px_optional_; }
void SnapshotFullRefreshGroup::set_md_entry_px_optional(std::optional<Decimal> value) { md_entry_px_optional_ = value; }

std::optional<std::int32_t> SnapshotFullRefreshGroup::md_entry_size_optional() const { return md_entry_size_optional_; }
void SnapshotFullRefreshGroup::set_md_entry_size_optional(std::optional<std::int32_t> value) { md_entry_size_optional_ = value; }

std::optional<std::int32_t> SnapshotFullRefreshGroup::number_of_orders() const { return number_of_orders_; }
void SnapshotFullRefreshGroup::set_number_of_orders(std::optional<std::int32_t> value) { number_of_orders_ = value; }

std::optional<std::int8_t> SnapshotFullRefreshGroup::md_price_level_optional() const { return md_price_level_optional_; }
void SnapshotFullRefreshGroup::set_md_price_level_optional(std::optional<std::int8_t> value) { md_price_level_optional_ = value; }

std::optional<std::uint16_t> SnapshotFullRefreshGroup::trading_reference_date() const { return trading_reference_date_; }
void SnapshotFullRefreshGroup::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

std::optional<OpenCloseSettlFlag> SnapshotFullRefreshGroup::open_close_settl_flag() const { return open_close_settl_flag_; }
void SnapshotFullRefreshGroup::set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value) { open_close_settl_flag_ = value; }

const SettlPriceType& SnapshotFullRefreshGroup::settl_price_type() const { return settl_price_type_; }
SettlPriceType& SnapshotFullRefreshGroup::settl_price_type() { return settl_price_type_; }
void SnapshotFullRefreshGroup::set_settl_price_type(const SettlPriceType& value) { settl_price_type_ = value; }

MdEntryType SnapshotFullRefreshGroup::md_entry_type() const { return md_entry_type_; }
void SnapshotFullRefreshGroup::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

std::size_t SnapshotFullRefreshGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotFullRefreshGroup", wire_size, length);

    md_entry_px_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    md_entry_size_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    number_of_orders_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    md_price_level_optional_ = wire::nullable(wire::read_i8(data + offset), static_cast<std::int8_t>(127LL));
    offset += 1;

    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    open_close_settl_flag_ = wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    offset += settl_price_type_.decode(data + offset, length - offset);

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SnapshotFullRefreshGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_optional_ ? static_cast<std::int64_t>(md_entry_px_optional_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, md_entry_size_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, number_of_orders_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i8(data + offset, md_price_level_optional_.value_or(static_cast<std::int8_t>(127LL)));
    offset += 1;

    wire::write_u16_le(data + offset, trading_reference_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u8(data + offset, open_close_settl_flag_ ? static_cast<std::uint8_t>(*open_close_settl_flag_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    offset += settl_price_type_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    return offset;
}

std::size_t SnapshotFullRefreshGroup::encoded_size() const {
    return wire_size;
}

void SnapshotFullRefreshGroup::print(std::ostream& out) const {
    out << "SnapshotFullRefreshGroup{";
    out << "md_entry_px_optional=";
    print::optional(out, md_entry_px_optional_);
    out << ", md_entry_size_optional=";
    print::optional(out, md_entry_size_optional_);
    out << ", number_of_orders=";
    print::optional(out, number_of_orders_);
    out << ", md_price_level_optional=";
    print::optional(out, md_price_level_optional_);
    out << ", trading_reference_date=";
    print::optional(out, trading_reference_date_);
    out << ", open_close_settl_flag=";
    print::optional(out, open_close_settl_flag_);
    out << ", settl_price_type=";
    settl_price_type_.print(out);
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << '}';
}

bool SnapshotFullRefreshGroup::operator==(const SnapshotFullRefreshGroup& other) const {
    return md_entry_px_optional_ == other.md_entry_px_optional_
        && md_entry_size_optional_ == other.md_entry_size_optional_
        && number_of_orders_ == other.number_of_orders_
        && md_price_level_optional_ == other.md_price_level_optional_
        && trading_reference_date_ == other.trading_reference_date_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && settl_price_type_ == other.settl_price_type_
        && md_entry_type_ == other.md_entry_type_;
}

bool SnapshotFullRefreshGroup::operator!=(const SnapshotFullRefreshGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
