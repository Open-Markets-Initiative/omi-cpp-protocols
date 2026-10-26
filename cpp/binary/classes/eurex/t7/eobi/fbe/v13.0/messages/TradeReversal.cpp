#include "TradeReversal.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

TradeReversal::TradeReversal(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<Decimal> last_qty, std::optional<Decimal> last_px, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::optional<std::uint32_t> trd_match_id, std::optional<TradeCondition> trade_condition, std::optional<MdOriginType> md_origin_type, std::optional<std::uint8_t> no_md_entries, const std::array<MdTradeEntryGrpComp, 15>& md_trade_entry_grp_comp)
  : security_id_(security_id), transact_time_(transact_time), last_qty_(last_qty), last_px_(last_px), trd_reg_ts_execution_time_(trd_reg_ts_execution_time), trd_match_id_(trd_match_id), trade_condition_(trade_condition), md_origin_type_(md_origin_type), no_md_entries_(no_md_entries), md_trade_entry_grp_comp_(md_trade_entry_grp_comp) {}

std::optional<std::int64_t> TradeReversal::security_id() const { return security_id_; }
void TradeReversal::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> TradeReversal::transact_time() const { return transact_time_; }
void TradeReversal::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<Decimal> TradeReversal::last_qty() const { return last_qty_; }
void TradeReversal::set_last_qty(std::optional<Decimal> value) { last_qty_ = value; }

std::optional<Decimal> TradeReversal::last_px() const { return last_px_; }
void TradeReversal::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

std::optional<std::chrono::nanoseconds> TradeReversal::trd_reg_ts_execution_time() const { return trd_reg_ts_execution_time_; }
void TradeReversal::set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_execution_time_ = value; }

std::optional<std::uint32_t> TradeReversal::trd_match_id() const { return trd_match_id_; }
void TradeReversal::set_trd_match_id(std::optional<std::uint32_t> value) { trd_match_id_ = value; }

std::optional<TradeCondition> TradeReversal::trade_condition() const { return trade_condition_; }
void TradeReversal::set_trade_condition(std::optional<TradeCondition> value) { trade_condition_ = value; }

std::optional<MdOriginType> TradeReversal::md_origin_type() const { return md_origin_type_; }
void TradeReversal::set_md_origin_type(std::optional<MdOriginType> value) { md_origin_type_ = value; }

std::optional<std::uint8_t> TradeReversal::no_md_entries() const { return no_md_entries_; }
void TradeReversal::set_no_md_entries(std::optional<std::uint8_t> value) { no_md_entries_ = value; }

const std::array<MdTradeEntryGrpComp, 15>& TradeReversal::md_trade_entry_grp_comp() const { return md_trade_entry_grp_comp_; }
std::array<MdTradeEntryGrpComp, 15>& TradeReversal::md_trade_entry_grp_comp() { return md_trade_entry_grp_comp_; }
void TradeReversal::set_md_trade_entry_grp_comp(const std::array<MdTradeEntryGrpComp, 15>& value) { md_trade_entry_grp_comp_ = value; }

MessageCode TradeReversal::type() const { return message_type; }

std::string_view TradeReversal::name() const { return "Trade Reversal"; }

std::size_t TradeReversal::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReversal", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    last_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -4);
    offset += 8;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    trd_reg_ts_execution_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    trd_match_id_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    trade_condition_ = wire::nullable_enum<TradeCondition>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    md_origin_type_ = wire::nullable_enum<MdOriginType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    no_md_entries_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    for (std::size_t index = 0; index < md_trade_entry_grp_comp_.size(); ++index) {
        offset += md_trade_entry_grp_comp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t TradeReversal::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReversal", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, last_qty_ ? static_cast<std::int64_t>(last_qty_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_execution_time_ ? static_cast<std::uint64_t>(trd_reg_ts_execution_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u32_le(data + offset, trd_match_id_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_u16_le(data + offset, trade_condition_ ? static_cast<std::uint16_t>(*trade_condition_) : static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::write_u8(data + offset, md_origin_type_ ? static_cast<std::uint8_t>(*md_origin_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, no_md_entries_.value_or(static_cast<std::uint8_t>(0xFFULL)));
    offset += 1;

    for (const auto& entry : md_trade_entry_grp_comp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t TradeReversal::encoded_size() const {
    return wire_size;
}

void TradeReversal::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeReversal::clone() const {
    return std::make_unique<TradeReversal>(*this);
}

void TradeReversal::print(std::ostream& out) const {
    out << "TradeReversal{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", last_px=";
    print::optional(out, last_px_);
    out << ", trd_reg_ts_execution_time=";
    print::optional_duration(out, trd_reg_ts_execution_time_);
    out << ", trd_match_id=";
    print::optional(out, trd_match_id_);
    out << ", trade_condition=";
    print::optional(out, trade_condition_);
    out << ", md_origin_type=";
    print::optional(out, md_origin_type_);
    out << ", no_md_entries=";
    print::optional(out, no_md_entries_);
    out << ", md_trade_entry_grp_comp=";
    print::sequence(out, md_trade_entry_grp_comp_);
    out << '}';
}

bool TradeReversal::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeReversal*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReversal::operator==(const TradeReversal& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_
        && trd_reg_ts_execution_time_ == other.trd_reg_ts_execution_time_
        && trd_match_id_ == other.trd_match_id_
        && trade_condition_ == other.trade_condition_
        && md_origin_type_ == other.md_origin_type_
        && no_md_entries_ == other.no_md_entries_
        && md_trade_entry_grp_comp_ == other.md_trade_entry_grp_comp_;
}

bool TradeReversal::operator!=(const TradeReversal& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
