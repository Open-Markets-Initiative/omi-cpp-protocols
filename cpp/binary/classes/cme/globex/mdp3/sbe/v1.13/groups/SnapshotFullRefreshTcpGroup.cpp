#include "SnapshotFullRefreshTcpGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotFullRefreshTcpGroup::SnapshotFullRefreshTcpGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::int32_t> md_entry_size_short_optional, std::optional<std::int32_t> tradeable_size, std::optional<std::int32_t> number_of_orders_optional, std::optional<std::int8_t> md_price_level_optional, std::optional<OpenCloseSettlFlag> open_close_settl_flag, MdEntryType md_entry_type, std::optional<std::uint16_t> trading_reference_date, const SettlPriceType& settl_price_type)
  : md_entry_px_optional_ex_(md_entry_px_optional_ex), md_entry_size_short_optional_(md_entry_size_short_optional), tradeable_size_(tradeable_size), number_of_orders_optional_(number_of_orders_optional), md_price_level_optional_(md_price_level_optional), open_close_settl_flag_(open_close_settl_flag), md_entry_type_(md_entry_type), trading_reference_date_(trading_reference_date), settl_price_type_(settl_price_type) {}

std::optional<Decimal> SnapshotFullRefreshTcpGroup::md_entry_px_optional_ex() const { return md_entry_px_optional_ex_; }
void SnapshotFullRefreshTcpGroup::set_md_entry_px_optional_ex(std::optional<Decimal> value) { md_entry_px_optional_ex_ = value; }

std::optional<std::int32_t> SnapshotFullRefreshTcpGroup::md_entry_size_short_optional() const { return md_entry_size_short_optional_; }
void SnapshotFullRefreshTcpGroup::set_md_entry_size_short_optional(std::optional<std::int32_t> value) { md_entry_size_short_optional_ = value; }

std::optional<std::int32_t> SnapshotFullRefreshTcpGroup::tradeable_size() const { return tradeable_size_; }
void SnapshotFullRefreshTcpGroup::set_tradeable_size(std::optional<std::int32_t> value) { tradeable_size_ = value; }

std::optional<std::int32_t> SnapshotFullRefreshTcpGroup::number_of_orders_optional() const { return number_of_orders_optional_; }
void SnapshotFullRefreshTcpGroup::set_number_of_orders_optional(std::optional<std::int32_t> value) { number_of_orders_optional_ = value; }

std::optional<std::int8_t> SnapshotFullRefreshTcpGroup::md_price_level_optional() const { return md_price_level_optional_; }
void SnapshotFullRefreshTcpGroup::set_md_price_level_optional(std::optional<std::int8_t> value) { md_price_level_optional_ = value; }

std::optional<OpenCloseSettlFlag> SnapshotFullRefreshTcpGroup::open_close_settl_flag() const { return open_close_settl_flag_; }
void SnapshotFullRefreshTcpGroup::set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value) { open_close_settl_flag_ = value; }

MdEntryType SnapshotFullRefreshTcpGroup::md_entry_type() const { return md_entry_type_; }
void SnapshotFullRefreshTcpGroup::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

std::optional<std::uint16_t> SnapshotFullRefreshTcpGroup::trading_reference_date() const { return trading_reference_date_; }
void SnapshotFullRefreshTcpGroup::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

const SettlPriceType& SnapshotFullRefreshTcpGroup::settl_price_type() const { return settl_price_type_; }
SettlPriceType& SnapshotFullRefreshTcpGroup::settl_price_type() { return settl_price_type_; }
void SnapshotFullRefreshTcpGroup::set_settl_price_type(const SettlPriceType& value) { settl_price_type_ = value; }

std::size_t SnapshotFullRefreshTcpGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotFullRefreshTcpGroup", wire_size, length);

    md_entry_px_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    md_entry_size_short_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    tradeable_size_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    number_of_orders_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    md_price_level_optional_ = wire::nullable(wire::read_i8(data + offset), static_cast<std::int8_t>(127LL));
    offset += 1;

    open_close_settl_flag_ = wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    offset += settl_price_type_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotFullRefreshTcpGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshTcpGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_optional_ex_ ? static_cast<std::int64_t>(md_entry_px_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, md_entry_size_short_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, tradeable_size_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, number_of_orders_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i8(data + offset, md_price_level_optional_.value_or(static_cast<std::int8_t>(127LL)));
    offset += 1;

    wire::write_u8(data + offset, open_close_settl_flag_ ? static_cast<std::uint8_t>(*open_close_settl_flag_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    wire::write_u16_le(data + offset, trading_reference_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    offset += settl_price_type_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotFullRefreshTcpGroup::encoded_size() const {
    return wire_size;
}

void SnapshotFullRefreshTcpGroup::print(std::ostream& out) const {
    out << "SnapshotFullRefreshTcpGroup{";
    out << "md_entry_px_optional_ex=";
    print::optional(out, md_entry_px_optional_ex_);
    out << ", md_entry_size_short_optional=";
    print::optional(out, md_entry_size_short_optional_);
    out << ", tradeable_size=";
    print::optional(out, tradeable_size_);
    out << ", number_of_orders_optional=";
    print::optional(out, number_of_orders_optional_);
    out << ", md_price_level_optional=";
    print::optional(out, md_price_level_optional_);
    out << ", open_close_settl_flag=";
    print::optional(out, open_close_settl_flag_);
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << ", trading_reference_date=";
    print::optional(out, trading_reference_date_);
    out << ", settl_price_type=";
    settl_price_type_.print(out);
    out << '}';
}

bool SnapshotFullRefreshTcpGroup::operator==(const SnapshotFullRefreshTcpGroup& other) const {
    return md_entry_px_optional_ex_ == other.md_entry_px_optional_ex_
        && md_entry_size_short_optional_ == other.md_entry_size_short_optional_
        && tradeable_size_ == other.tradeable_size_
        && number_of_orders_optional_ == other.number_of_orders_optional_
        && md_price_level_optional_ == other.md_price_level_optional_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && md_entry_type_ == other.md_entry_type_
        && trading_reference_date_ == other.trading_reference_date_
        && settl_price_type_ == other.settl_price_type_;
}

bool SnapshotFullRefreshTcpGroup::operator!=(const SnapshotFullRefreshTcpGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshTcpGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
