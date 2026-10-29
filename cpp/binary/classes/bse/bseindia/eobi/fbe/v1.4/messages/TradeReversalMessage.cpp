#include "TradeReversalMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

TradeReversalMessage::TradeReversalMessage(std::int64_t security_id, std::chrono::nanoseconds transact_time, std::uint32_t trd_match_id, const std::array<std::byte, 4>& pad_4, std::int64_t last_qty, Decimal last_px, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::uint8_t no_md_entries, const std::array<std::byte, 7>& pad_7, const std::array<MdTradeEntryGrp, 15>& md_trade_entry_grp)
  : security_id_(security_id), transact_time_(transact_time), trd_match_id_(trd_match_id), pad_4_(pad_4), last_qty_(last_qty), last_px_(last_px), trd_reg_ts_execution_time_(trd_reg_ts_execution_time), no_md_entries_(no_md_entries), pad_7_(pad_7), md_trade_entry_grp_(md_trade_entry_grp) {}

std::int64_t TradeReversalMessage::security_id() const { return security_id_; }
void TradeReversalMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::chrono::nanoseconds TradeReversalMessage::transact_time() const { return transact_time_; }
void TradeReversalMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::uint32_t TradeReversalMessage::trd_match_id() const { return trd_match_id_; }
void TradeReversalMessage::set_trd_match_id(std::uint32_t value) { trd_match_id_ = value; }

const std::array<std::byte, 4>& TradeReversalMessage::pad_4() const { return pad_4_; }
std::array<std::byte, 4>& TradeReversalMessage::pad_4() { return pad_4_; }
void TradeReversalMessage::set_pad_4(const std::array<std::byte, 4>& value) { pad_4_ = value; }

std::int64_t TradeReversalMessage::last_qty() const { return last_qty_; }
void TradeReversalMessage::set_last_qty(std::int64_t value) { last_qty_ = value; }

Decimal TradeReversalMessage::last_px() const { return last_px_; }
void TradeReversalMessage::set_last_px(Decimal value) { last_px_ = value; }

std::optional<std::chrono::nanoseconds> TradeReversalMessage::trd_reg_ts_execution_time() const { return trd_reg_ts_execution_time_; }
void TradeReversalMessage::set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_execution_time_ = value; }

std::uint8_t TradeReversalMessage::no_md_entries() const { return no_md_entries_; }
void TradeReversalMessage::set_no_md_entries(std::uint8_t value) { no_md_entries_ = value; }

const std::array<std::byte, 7>& TradeReversalMessage::pad_7() const { return pad_7_; }
std::array<std::byte, 7>& TradeReversalMessage::pad_7() { return pad_7_; }
void TradeReversalMessage::set_pad_7(const std::array<std::byte, 7>& value) { pad_7_ = value; }

const std::array<MdTradeEntryGrp, 15>& TradeReversalMessage::md_trade_entry_grp() const { return md_trade_entry_grp_; }
std::array<MdTradeEntryGrp, 15>& TradeReversalMessage::md_trade_entry_grp() { return md_trade_entry_grp_; }
void TradeReversalMessage::set_md_trade_entry_grp(const std::array<MdTradeEntryGrp, 15>& value) { md_trade_entry_grp_ = value; }

MessageCode TradeReversalMessage::type() const { return message_type; }

std::string_view TradeReversalMessage::name() const { return "Trade Reversal Message"; }

std::size_t TradeReversalMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReversalMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    trd_match_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    last_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    trd_reg_ts_execution_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    no_md_entries_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    for (std::size_t index = 0; index < md_trade_entry_grp_.size(); ++index) {
        offset += md_trade_entry_grp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t TradeReversalMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReversalMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trd_match_id_));
    offset += 4;

    wire::write_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_px_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_execution_time_ ? static_cast<std::uint64_t>(trd_reg_ts_execution_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_md_entries_));
    offset += 1;

    wire::write_bytes(data + offset, pad_7_.data(), 7);
    offset += 7;

    for (const auto& entry : md_trade_entry_grp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t TradeReversalMessage::encoded_size() const {
    return wire_size;
}

void TradeReversalMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeReversalMessage::clone() const {
    return std::make_unique<TradeReversalMessage>(*this);
}

void TradeReversalMessage::print(std::ostream& out) const {
    out << "TradeReversalMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", trd_match_id=";
    out << trd_match_id_;
    out << ", pad_4=";
    print::hex(out, pad_4_.data(), pad_4_.size());
    out << ", last_qty=";
    out << last_qty_;
    out << ", last_px=";
    out << last_px_;
    out << ", trd_reg_ts_execution_time=";
    print::optional_duration(out, trd_reg_ts_execution_time_);
    out << ", no_md_entries=";
    out << static_cast<int>(no_md_entries_);
    out << ", pad_7=";
    print::hex(out, pad_7_.data(), pad_7_.size());
    out << ", md_trade_entry_grp=";
    print::sequence(out, md_trade_entry_grp_);
    out << '}';
}

bool TradeReversalMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeReversalMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReversalMessage::operator==(const TradeReversalMessage& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && trd_match_id_ == other.trd_match_id_
        && pad_4_ == other.pad_4_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_
        && trd_reg_ts_execution_time_ == other.trd_reg_ts_execution_time_
        && no_md_entries_ == other.no_md_entries_
        && pad_7_ == other.pad_7_
        && md_trade_entry_grp_ == other.md_trade_entry_grp_;
}

bool TradeReversalMessage::operator!=(const TradeReversalMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
