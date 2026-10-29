#include "InstrumentSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

InstrumentSummaryMessage::InstrumentSummaryMessage(std::int64_t security_id, std::chrono::nanoseconds last_update_time, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::uint32_t tot_no_orders, SecurityStatus security_status, SecurityTradingStatus security_trading_status, FastMarketIndicator fast_market_indicator, std::uint8_t no_md_entries, std::int64_t trade_volume, std::uint32_t no_of_trades, const std::array<std::byte, 4>& pad_4, const std::array<MdInstrumentEntryGrp, 15>& md_instrument_entry_grp)
  : security_id_(security_id), last_update_time_(last_update_time), trd_reg_ts_execution_time_(trd_reg_ts_execution_time), tot_no_orders_(tot_no_orders), security_status_(security_status), security_trading_status_(security_trading_status), fast_market_indicator_(fast_market_indicator), no_md_entries_(no_md_entries), trade_volume_(trade_volume), no_of_trades_(no_of_trades), pad_4_(pad_4), md_instrument_entry_grp_(md_instrument_entry_grp) {}

std::int64_t InstrumentSummaryMessage::security_id() const { return security_id_; }
void InstrumentSummaryMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::chrono::nanoseconds InstrumentSummaryMessage::last_update_time() const { return last_update_time_; }
void InstrumentSummaryMessage::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentSummaryMessage::trd_reg_ts_execution_time() const { return trd_reg_ts_execution_time_; }
void InstrumentSummaryMessage::set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_execution_time_ = value; }

std::uint32_t InstrumentSummaryMessage::tot_no_orders() const { return tot_no_orders_; }
void InstrumentSummaryMessage::set_tot_no_orders(std::uint32_t value) { tot_no_orders_ = value; }

SecurityStatus InstrumentSummaryMessage::security_status() const { return security_status_; }
void InstrumentSummaryMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

SecurityTradingStatus InstrumentSummaryMessage::security_trading_status() const { return security_trading_status_; }
void InstrumentSummaryMessage::set_security_trading_status(SecurityTradingStatus value) { security_trading_status_ = value; }

FastMarketIndicator InstrumentSummaryMessage::fast_market_indicator() const { return fast_market_indicator_; }
void InstrumentSummaryMessage::set_fast_market_indicator(FastMarketIndicator value) { fast_market_indicator_ = value; }

std::uint8_t InstrumentSummaryMessage::no_md_entries() const { return no_md_entries_; }
void InstrumentSummaryMessage::set_no_md_entries(std::uint8_t value) { no_md_entries_ = value; }

std::int64_t InstrumentSummaryMessage::trade_volume() const { return trade_volume_; }
void InstrumentSummaryMessage::set_trade_volume(std::int64_t value) { trade_volume_ = value; }

std::uint32_t InstrumentSummaryMessage::no_of_trades() const { return no_of_trades_; }
void InstrumentSummaryMessage::set_no_of_trades(std::uint32_t value) { no_of_trades_ = value; }

const std::array<std::byte, 4>& InstrumentSummaryMessage::pad_4() const { return pad_4_; }
std::array<std::byte, 4>& InstrumentSummaryMessage::pad_4() { return pad_4_; }
void InstrumentSummaryMessage::set_pad_4(const std::array<std::byte, 4>& value) { pad_4_ = value; }

const std::array<MdInstrumentEntryGrp, 15>& InstrumentSummaryMessage::md_instrument_entry_grp() const { return md_instrument_entry_grp_; }
std::array<MdInstrumentEntryGrp, 15>& InstrumentSummaryMessage::md_instrument_entry_grp() { return md_instrument_entry_grp_; }
void InstrumentSummaryMessage::set_md_instrument_entry_grp(const std::array<MdInstrumentEntryGrp, 15>& value) { md_instrument_entry_grp_ = value; }

MessageCode InstrumentSummaryMessage::type() const { return message_type; }

std::string_view InstrumentSummaryMessage::name() const { return "Instrument Summary Message"; }

std::size_t InstrumentSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentSummaryMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    trd_reg_ts_execution_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    tot_no_orders_ = wire::read_u32_le(data + offset);
    offset += 4;

    security_status_ = static_cast<SecurityStatus>(wire::read_u8(data + offset));
    offset += 1;

    security_trading_status_ = static_cast<SecurityTradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    fast_market_indicator_ = static_cast<FastMarketIndicator>(wire::read_u8(data + offset));
    offset += 1;

    no_md_entries_ = wire::read_u8(data + offset);
    offset += 1;

    trade_volume_ = wire::read_i64_le(data + offset);
    offset += 8;

    no_of_trades_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    for (std::size_t index = 0; index < md_instrument_entry_grp_.size(); ++index) {
        offset += md_instrument_entry_grp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t InstrumentSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentSummaryMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(last_update_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_execution_time_ ? static_cast<std::uint64_t>(trd_reg_ts_execution_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_no_orders_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(fast_market_indicator_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_md_entries_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(trade_volume_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(no_of_trades_));
    offset += 4;

    wire::write_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    for (const auto& entry : md_instrument_entry_grp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t InstrumentSummaryMessage::encoded_size() const {
    return wire_size;
}

void InstrumentSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentSummaryMessage::clone() const {
    return std::make_unique<InstrumentSummaryMessage>(*this);
}

void InstrumentSummaryMessage::print(std::ostream& out) const {
    out << "InstrumentSummaryMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", last_update_time=";
    out << last_update_time_.count();
    out << ", trd_reg_ts_execution_time=";
    print::optional_duration(out, trd_reg_ts_execution_time_);
    out << ", tot_no_orders=";
    out << tot_no_orders_;
    out << ", security_status=";
    out << security_status_;
    out << ", security_trading_status=";
    out << security_trading_status_;
    out << ", fast_market_indicator=";
    out << fast_market_indicator_;
    out << ", no_md_entries=";
    out << static_cast<int>(no_md_entries_);
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", no_of_trades=";
    out << no_of_trades_;
    out << ", pad_4=";
    print::hex(out, pad_4_.data(), pad_4_.size());
    out << ", md_instrument_entry_grp=";
    print::sequence(out, md_instrument_entry_grp_);
    out << '}';
}

bool InstrumentSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentSummaryMessage::operator==(const InstrumentSummaryMessage& other) const {
    return security_id_ == other.security_id_
        && last_update_time_ == other.last_update_time_
        && trd_reg_ts_execution_time_ == other.trd_reg_ts_execution_time_
        && tot_no_orders_ == other.tot_no_orders_
        && security_status_ == other.security_status_
        && security_trading_status_ == other.security_trading_status_
        && fast_market_indicator_ == other.fast_market_indicator_
        && no_md_entries_ == other.no_md_entries_
        && trade_volume_ == other.trade_volume_
        && no_of_trades_ == other.no_of_trades_
        && pad_4_ == other.pad_4_
        && md_instrument_entry_grp_ == other.md_instrument_entry_grp_;
}

bool InstrumentSummaryMessage::operator!=(const InstrumentSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
