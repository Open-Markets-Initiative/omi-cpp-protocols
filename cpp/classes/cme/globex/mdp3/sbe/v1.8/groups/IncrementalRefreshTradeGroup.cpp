#include "IncrementalRefreshTradeGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

IncrementalRefreshTradeGroup::IncrementalRefreshTradeGroup(Decimal md_entry_px, std::int32_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<std::int32_t> number_of_orders, std::int32_t trade_id, std::optional<AggressorSide> aggressor_side, MdUpdateAction md_update_action, const std::array<std::byte, 2>& padding_2)
  : md_entry_px_(md_entry_px), md_entry_size_(md_entry_size), security_id_(security_id), rpt_seq_(rpt_seq), number_of_orders_(number_of_orders), trade_id_(trade_id), aggressor_side_(aggressor_side), md_update_action_(md_update_action), padding_2_(padding_2) {}

Decimal IncrementalRefreshTradeGroup::md_entry_px() const { return md_entry_px_; }
void IncrementalRefreshTradeGroup::set_md_entry_px(Decimal value) { md_entry_px_ = value; }

std::int32_t IncrementalRefreshTradeGroup::md_entry_size() const { return md_entry_size_; }
void IncrementalRefreshTradeGroup::set_md_entry_size(std::int32_t value) { md_entry_size_ = value; }

std::int32_t IncrementalRefreshTradeGroup::security_id() const { return security_id_; }
void IncrementalRefreshTradeGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshTradeGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshTradeGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::optional<std::int32_t> IncrementalRefreshTradeGroup::number_of_orders() const { return number_of_orders_; }
void IncrementalRefreshTradeGroup::set_number_of_orders(std::optional<std::int32_t> value) { number_of_orders_ = value; }

std::int32_t IncrementalRefreshTradeGroup::trade_id() const { return trade_id_; }
void IncrementalRefreshTradeGroup::set_trade_id(std::int32_t value) { trade_id_ = value; }

std::optional<AggressorSide> IncrementalRefreshTradeGroup::aggressor_side() const { return aggressor_side_; }
void IncrementalRefreshTradeGroup::set_aggressor_side(std::optional<AggressorSide> value) { aggressor_side_ = value; }

MdUpdateAction IncrementalRefreshTradeGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshTradeGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

const std::array<std::byte, 2>& IncrementalRefreshTradeGroup::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& IncrementalRefreshTradeGroup::padding_2() { return padding_2_; }
void IncrementalRefreshTradeGroup::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

std::size_t IncrementalRefreshTradeGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshTradeGroup", wire_size, length);

    md_entry_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -7);
    offset += 8;

    md_entry_size_ = wire::read_i32_le(data + offset);
    offset += 4;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    number_of_orders_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    trade_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    aggressor_side_ = wire::nullable_enum<AggressorSide>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t IncrementalRefreshTradeGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshTradeGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_px_.mantissa()));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(md_entry_size_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_i32_le(data + offset, number_of_orders_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(trade_id_));
    offset += 4;

    wire::write_u8(data + offset, aggressor_side_ ? static_cast<std::uint8_t>(*aggressor_side_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t IncrementalRefreshTradeGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshTradeGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshTradeGroup{";
    out << "md_entry_px=";
    out << md_entry_px_;
    out << ", md_entry_size=";
    out << md_entry_size_;
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", number_of_orders=";
    print::optional(out, number_of_orders_);
    out << ", trade_id=";
    out << trade_id_;
    out << ", aggressor_side=";
    print::optional(out, aggressor_side_);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << '}';
}

bool IncrementalRefreshTradeGroup::operator==(const IncrementalRefreshTradeGroup& other) const {
    return md_entry_px_ == other.md_entry_px_
        && md_entry_size_ == other.md_entry_size_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && number_of_orders_ == other.number_of_orders_
        && trade_id_ == other.trade_id_
        && aggressor_side_ == other.aggressor_side_
        && md_update_action_ == other.md_update_action_
        && padding_2_ == other.padding_2_;
}

bool IncrementalRefreshTradeGroup::operator!=(const IncrementalRefreshTradeGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
