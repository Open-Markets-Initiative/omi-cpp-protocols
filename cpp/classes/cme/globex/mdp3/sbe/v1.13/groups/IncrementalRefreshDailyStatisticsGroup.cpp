#include "IncrementalRefreshDailyStatisticsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshDailyStatisticsGroup::IncrementalRefreshDailyStatisticsGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::int32_t> md_entry_size_short_optional, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<std::uint16_t> trading_reference_date, const SettlPriceType& settl_price_type, MdUpdateAction md_update_action, MdEntryTypeDailyStatistics md_entry_type_daily_statistics, const std::array<std::byte, 7>& padding_7)
  : md_entry_px_optional_ex_(md_entry_px_optional_ex), md_entry_size_short_optional_(md_entry_size_short_optional), security_id_(security_id), rpt_seq_(rpt_seq), trading_reference_date_(trading_reference_date), settl_price_type_(settl_price_type), md_update_action_(md_update_action), md_entry_type_daily_statistics_(md_entry_type_daily_statistics), padding_7_(padding_7) {}

std::optional<Decimal> IncrementalRefreshDailyStatisticsGroup::md_entry_px_optional_ex() const { return md_entry_px_optional_ex_; }
void IncrementalRefreshDailyStatisticsGroup::set_md_entry_px_optional_ex(std::optional<Decimal> value) { md_entry_px_optional_ex_ = value; }

std::optional<std::int32_t> IncrementalRefreshDailyStatisticsGroup::md_entry_size_short_optional() const { return md_entry_size_short_optional_; }
void IncrementalRefreshDailyStatisticsGroup::set_md_entry_size_short_optional(std::optional<std::int32_t> value) { md_entry_size_short_optional_ = value; }

std::int32_t IncrementalRefreshDailyStatisticsGroup::security_id() const { return security_id_; }
void IncrementalRefreshDailyStatisticsGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshDailyStatisticsGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshDailyStatisticsGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::optional<std::uint16_t> IncrementalRefreshDailyStatisticsGroup::trading_reference_date() const { return trading_reference_date_; }
void IncrementalRefreshDailyStatisticsGroup::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

const SettlPriceType& IncrementalRefreshDailyStatisticsGroup::settl_price_type() const { return settl_price_type_; }
SettlPriceType& IncrementalRefreshDailyStatisticsGroup::settl_price_type() { return settl_price_type_; }
void IncrementalRefreshDailyStatisticsGroup::set_settl_price_type(const SettlPriceType& value) { settl_price_type_ = value; }

MdUpdateAction IncrementalRefreshDailyStatisticsGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshDailyStatisticsGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

MdEntryTypeDailyStatistics IncrementalRefreshDailyStatisticsGroup::md_entry_type_daily_statistics() const { return md_entry_type_daily_statistics_; }
void IncrementalRefreshDailyStatisticsGroup::set_md_entry_type_daily_statistics(MdEntryTypeDailyStatistics value) { md_entry_type_daily_statistics_ = value; }

const std::array<std::byte, 7>& IncrementalRefreshDailyStatisticsGroup::padding_7() const { return padding_7_; }
std::array<std::byte, 7>& IncrementalRefreshDailyStatisticsGroup::padding_7() { return padding_7_; }
void IncrementalRefreshDailyStatisticsGroup::set_padding_7(const std::array<std::byte, 7>& value) { padding_7_ = value; }

std::size_t IncrementalRefreshDailyStatisticsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshDailyStatisticsGroup", wire_size, length);

    md_entry_px_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    md_entry_size_short_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    offset += settl_price_type_.decode(data + offset, length - offset);

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_entry_type_daily_statistics_ = static_cast<MdEntryTypeDailyStatistics>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t IncrementalRefreshDailyStatisticsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshDailyStatisticsGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, md_entry_px_optional_ex_ ? static_cast<std::int64_t>(md_entry_px_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, md_entry_size_short_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_u16_le(data + offset, trading_reference_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    offset += settl_price_type_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_daily_statistics_));
    offset += 1;

    wire::write_bytes(data + offset, padding_7_.data(), 7);
    offset += 7;

    return offset;
}

std::size_t IncrementalRefreshDailyStatisticsGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshDailyStatisticsGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshDailyStatisticsGroup{";
    out << "md_entry_px_optional_ex=";
    print::optional(out, md_entry_px_optional_ex_);
    out << ", md_entry_size_short_optional=";
    print::optional(out, md_entry_size_short_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", trading_reference_date=";
    print::optional(out, trading_reference_date_);
    out << ", settl_price_type=";
    settl_price_type_.print(out);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_entry_type_daily_statistics=";
    out << md_entry_type_daily_statistics_;
    out << ", padding_7=";
    print::hex(out, padding_7_.data(), padding_7_.size());
    out << '}';
}

bool IncrementalRefreshDailyStatisticsGroup::operator==(const IncrementalRefreshDailyStatisticsGroup& other) const {
    return md_entry_px_optional_ex_ == other.md_entry_px_optional_ex_
        && md_entry_size_short_optional_ == other.md_entry_size_short_optional_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && trading_reference_date_ == other.trading_reference_date_
        && settl_price_type_ == other.settl_price_type_
        && md_update_action_ == other.md_update_action_
        && md_entry_type_daily_statistics_ == other.md_entry_type_daily_statistics_
        && padding_7_ == other.padding_7_;
}

bool IncrementalRefreshDailyStatisticsGroup::operator!=(const IncrementalRefreshDailyStatisticsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshDailyStatisticsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
