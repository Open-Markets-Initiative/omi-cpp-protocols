#include "IncrementalRefreshSessionStatisticsLongGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshSessionStatisticsLongGroup::IncrementalRefreshSessionStatisticsLongGroup(Decimal md_entry_px_ex, std::optional<std::uint64_t> md_entry_size_optional, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<OpenCloseSettlFlag> open_close_settl_flag, MdUpdateAction md_update_action, MdEntryTypeStatistics md_entry_type_statistics, const std::array<std::byte, 5>& padding_5)
  : md_entry_px_ex_(md_entry_px_ex), md_entry_size_optional_(md_entry_size_optional), security_id_(security_id), rpt_seq_(rpt_seq), open_close_settl_flag_(open_close_settl_flag), md_update_action_(md_update_action), md_entry_type_statistics_(md_entry_type_statistics), padding_5_(padding_5) {}

Decimal IncrementalRefreshSessionStatisticsLongGroup::md_entry_px_ex() const { return md_entry_px_ex_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_md_entry_px_ex(Decimal value) { md_entry_px_ex_ = value; }

std::optional<std::uint64_t> IncrementalRefreshSessionStatisticsLongGroup::md_entry_size_optional() const { return md_entry_size_optional_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_md_entry_size_optional(std::optional<std::uint64_t> value) { md_entry_size_optional_ = value; }

std::int32_t IncrementalRefreshSessionStatisticsLongGroup::security_id() const { return security_id_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshSessionStatisticsLongGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::optional<OpenCloseSettlFlag> IncrementalRefreshSessionStatisticsLongGroup::open_close_settl_flag() const { return open_close_settl_flag_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value) { open_close_settl_flag_ = value; }

MdUpdateAction IncrementalRefreshSessionStatisticsLongGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

MdEntryTypeStatistics IncrementalRefreshSessionStatisticsLongGroup::md_entry_type_statistics() const { return md_entry_type_statistics_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_md_entry_type_statistics(MdEntryTypeStatistics value) { md_entry_type_statistics_ = value; }

const std::array<std::byte, 5>& IncrementalRefreshSessionStatisticsLongGroup::padding_5() const { return padding_5_; }
std::array<std::byte, 5>& IncrementalRefreshSessionStatisticsLongGroup::padding_5() { return padding_5_; }
void IncrementalRefreshSessionStatisticsLongGroup::set_padding_5(const std::array<std::byte, 5>& value) { padding_5_ = value; }

std::size_t IncrementalRefreshSessionStatisticsLongGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshSessionStatisticsLongGroup", wire_size, length);

    md_entry_px_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    md_entry_size_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    open_close_settl_flag_ = wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_entry_type_statistics_ = static_cast<MdEntryTypeStatistics>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_5_.data(), 5);
    offset += 5;

    return offset;
}

std::size_t IncrementalRefreshSessionStatisticsLongGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshSessionStatisticsLongGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_px_ex_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_size_optional_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_u8(data + offset, open_close_settl_flag_ ? static_cast<std::uint8_t>(*open_close_settl_flag_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_statistics_));
    offset += 1;

    wire::write_bytes(data + offset, padding_5_.data(), 5);
    offset += 5;

    return offset;
}

std::size_t IncrementalRefreshSessionStatisticsLongGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshSessionStatisticsLongGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshSessionStatisticsLongGroup{";
    out << "md_entry_px_ex=";
    out << md_entry_px_ex_;
    out << ", md_entry_size_optional=";
    print::optional(out, md_entry_size_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", open_close_settl_flag=";
    print::optional(out, open_close_settl_flag_);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_entry_type_statistics=";
    out << md_entry_type_statistics_;
    out << ", padding_5=";
    print::hex(out, padding_5_.data(), padding_5_.size());
    out << '}';
}

bool IncrementalRefreshSessionStatisticsLongGroup::operator==(const IncrementalRefreshSessionStatisticsLongGroup& other) const {
    return md_entry_px_ex_ == other.md_entry_px_ex_
        && md_entry_size_optional_ == other.md_entry_size_optional_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && md_update_action_ == other.md_update_action_
        && md_entry_type_statistics_ == other.md_entry_type_statistics_
        && padding_5_ == other.padding_5_;
}

bool IncrementalRefreshSessionStatisticsLongGroup::operator!=(const IncrementalRefreshSessionStatisticsLongGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshSessionStatisticsLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
