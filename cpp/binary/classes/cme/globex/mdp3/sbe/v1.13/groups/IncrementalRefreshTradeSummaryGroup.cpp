#include "IncrementalRefreshTradeSummaryGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshTradeSummaryGroup::IncrementalRefreshTradeSummaryGroup(Decimal md_entry_px_ex, std::int32_t md_entry_size_short, std::int32_t security_id, std::uint32_t rpt_seq, std::int32_t number_of_orders, std::optional<AggressorSide> aggressor_side, MdUpdateAction md_update_action, std::optional<std::uint32_t> md_trade_entry_optional, const std::array<std::byte, 2>& padding_2)
  : md_entry_px_ex_(md_entry_px_ex), md_entry_size_short_(md_entry_size_short), security_id_(security_id), rpt_seq_(rpt_seq), number_of_orders_(number_of_orders), aggressor_side_(aggressor_side), md_update_action_(md_update_action), md_trade_entry_optional_(md_trade_entry_optional), padding_2_(padding_2) {}

Decimal IncrementalRefreshTradeSummaryGroup::md_entry_px_ex() const { return md_entry_px_ex_; }
void IncrementalRefreshTradeSummaryGroup::set_md_entry_px_ex(Decimal value) { md_entry_px_ex_ = value; }

std::int32_t IncrementalRefreshTradeSummaryGroup::md_entry_size_short() const { return md_entry_size_short_; }
void IncrementalRefreshTradeSummaryGroup::set_md_entry_size_short(std::int32_t value) { md_entry_size_short_ = value; }

std::int32_t IncrementalRefreshTradeSummaryGroup::security_id() const { return security_id_; }
void IncrementalRefreshTradeSummaryGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshTradeSummaryGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshTradeSummaryGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::int32_t IncrementalRefreshTradeSummaryGroup::number_of_orders() const { return number_of_orders_; }
void IncrementalRefreshTradeSummaryGroup::set_number_of_orders(std::int32_t value) { number_of_orders_ = value; }

std::optional<AggressorSide> IncrementalRefreshTradeSummaryGroup::aggressor_side() const { return aggressor_side_; }
void IncrementalRefreshTradeSummaryGroup::set_aggressor_side(std::optional<AggressorSide> value) { aggressor_side_ = value; }

MdUpdateAction IncrementalRefreshTradeSummaryGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshTradeSummaryGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

std::optional<std::uint32_t> IncrementalRefreshTradeSummaryGroup::md_trade_entry_optional() const { return md_trade_entry_optional_; }
void IncrementalRefreshTradeSummaryGroup::set_md_trade_entry_optional(std::optional<std::uint32_t> value) { md_trade_entry_optional_ = value; }

const std::array<std::byte, 2>& IncrementalRefreshTradeSummaryGroup::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& IncrementalRefreshTradeSummaryGroup::padding_2() { return padding_2_; }
void IncrementalRefreshTradeSummaryGroup::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

std::size_t IncrementalRefreshTradeSummaryGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshTradeSummaryGroup", wire_size, length);

    md_entry_px_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    md_entry_size_short_ = wire::read_i32_le(data + offset);
    offset += 4;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    number_of_orders_ = wire::read_i32_le(data + offset);
    offset += 4;

    aggressor_side_ = wire::nullable_enum<AggressorSide>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_trade_entry_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshTradeSummaryGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_px_ex_.mantissa()));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(md_entry_size_short_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(number_of_orders_));
    offset += 4;

    wire::write_u8(data + offset, aggressor_side_ ? static_cast<std::uint8_t>(*aggressor_side_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_u32_le(data + offset, md_trade_entry_optional_.value_or(static_cast<std::uint32_t>(4294967295ULL)));
    offset += 4;

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshTradeSummaryGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshTradeSummaryGroup{";
    out << "md_entry_px_ex=";
    out << md_entry_px_ex_;
    out << ", md_entry_size_short=";
    out << md_entry_size_short_;
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", number_of_orders=";
    out << number_of_orders_;
    out << ", aggressor_side=";
    print::optional(out, aggressor_side_);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_trade_entry_optional=";
    print::optional(out, md_trade_entry_optional_);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << '}';
}

bool IncrementalRefreshTradeSummaryGroup::operator==(const IncrementalRefreshTradeSummaryGroup& other) const {
    return md_entry_px_ex_ == other.md_entry_px_ex_
        && md_entry_size_short_ == other.md_entry_size_short_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && number_of_orders_ == other.number_of_orders_
        && aggressor_side_ == other.aggressor_side_
        && md_update_action_ == other.md_update_action_
        && md_trade_entry_optional_ == other.md_trade_entry_optional_
        && padding_2_ == other.padding_2_;
}

bool IncrementalRefreshTradeSummaryGroup::operator!=(const IncrementalRefreshTradeSummaryGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
