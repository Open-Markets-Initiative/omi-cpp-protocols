#include "IncrementalRefreshTradeSummaryLongGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshTradeSummaryLongGroup::IncrementalRefreshTradeSummaryLongGroup(Decimal md_entry_px_ex, std::uint64_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, std::int32_t number_of_orders, std::uint32_t md_trade_entry, std::optional<AggressorSide> aggressor_side, MdUpdateAction md_update_action, const std::array<std::byte, 6>& padding_6)
  : md_entry_px_ex_(md_entry_px_ex), md_entry_size_(md_entry_size), security_id_(security_id), rpt_seq_(rpt_seq), number_of_orders_(number_of_orders), md_trade_entry_(md_trade_entry), aggressor_side_(aggressor_side), md_update_action_(md_update_action), padding_6_(padding_6) {}

Decimal IncrementalRefreshTradeSummaryLongGroup::md_entry_px_ex() const { return md_entry_px_ex_; }
void IncrementalRefreshTradeSummaryLongGroup::set_md_entry_px_ex(Decimal value) { md_entry_px_ex_ = value; }

std::uint64_t IncrementalRefreshTradeSummaryLongGroup::md_entry_size() const { return md_entry_size_; }
void IncrementalRefreshTradeSummaryLongGroup::set_md_entry_size(std::uint64_t value) { md_entry_size_ = value; }

std::int32_t IncrementalRefreshTradeSummaryLongGroup::security_id() const { return security_id_; }
void IncrementalRefreshTradeSummaryLongGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t IncrementalRefreshTradeSummaryLongGroup::rpt_seq() const { return rpt_seq_; }
void IncrementalRefreshTradeSummaryLongGroup::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::int32_t IncrementalRefreshTradeSummaryLongGroup::number_of_orders() const { return number_of_orders_; }
void IncrementalRefreshTradeSummaryLongGroup::set_number_of_orders(std::int32_t value) { number_of_orders_ = value; }

std::uint32_t IncrementalRefreshTradeSummaryLongGroup::md_trade_entry() const { return md_trade_entry_; }
void IncrementalRefreshTradeSummaryLongGroup::set_md_trade_entry(std::uint32_t value) { md_trade_entry_ = value; }

std::optional<AggressorSide> IncrementalRefreshTradeSummaryLongGroup::aggressor_side() const { return aggressor_side_; }
void IncrementalRefreshTradeSummaryLongGroup::set_aggressor_side(std::optional<AggressorSide> value) { aggressor_side_ = value; }

MdUpdateAction IncrementalRefreshTradeSummaryLongGroup::md_update_action() const { return md_update_action_; }
void IncrementalRefreshTradeSummaryLongGroup::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

const std::array<std::byte, 6>& IncrementalRefreshTradeSummaryLongGroup::padding_6() const { return padding_6_; }
std::array<std::byte, 6>& IncrementalRefreshTradeSummaryLongGroup::padding_6() { return padding_6_; }
void IncrementalRefreshTradeSummaryLongGroup::set_padding_6(const std::array<std::byte, 6>& value) { padding_6_ = value; }

std::size_t IncrementalRefreshTradeSummaryLongGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IncrementalRefreshTradeSummaryLongGroup", wire_size, length);

    md_entry_px_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    md_entry_size_ = wire::read_u64_le(data + offset);
    offset += 8;

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    number_of_orders_ = wire::read_i32_le(data + offset);
    offset += 4;

    md_trade_entry_ = wire::read_u32_le(data + offset);
    offset += 4;

    aggressor_side_ = wire::nullable_enum<AggressorSide>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, padding_6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryLongGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshTradeSummaryLongGroup", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_px_ex_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(md_entry_size_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(number_of_orders_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_trade_entry_));
    offset += 4;

    wire::write_u8(data + offset, aggressor_side_ ? static_cast<std::uint8_t>(*aggressor_side_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_bytes(data + offset, padding_6_.data(), 6);
    offset += 6;

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryLongGroup::encoded_size() const {
    return wire_size;
}

void IncrementalRefreshTradeSummaryLongGroup::print(std::ostream& out) const {
    out << "IncrementalRefreshTradeSummaryLongGroup{";
    out << "md_entry_px_ex=";
    out << md_entry_px_ex_;
    out << ", md_entry_size=";
    out << md_entry_size_;
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", number_of_orders=";
    out << number_of_orders_;
    out << ", md_trade_entry=";
    out << md_trade_entry_;
    out << ", aggressor_side=";
    print::optional(out, aggressor_side_);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", padding_6=";
    print::hex(out, padding_6_.data(), padding_6_.size());
    out << '}';
}

bool IncrementalRefreshTradeSummaryLongGroup::operator==(const IncrementalRefreshTradeSummaryLongGroup& other) const {
    return md_entry_px_ex_ == other.md_entry_px_ex_
        && md_entry_size_ == other.md_entry_size_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && number_of_orders_ == other.number_of_orders_
        && md_trade_entry_ == other.md_trade_entry_
        && aggressor_side_ == other.aggressor_side_
        && md_update_action_ == other.md_update_action_
        && padding_6_ == other.padding_6_;
}

bool IncrementalRefreshTradeSummaryLongGroup::operator!=(const IncrementalRefreshTradeSummaryLongGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
