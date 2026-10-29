#include "ExecutionReportForwardMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

ExecutionReportForwardMessage::ExecutionReportForwardMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::optional<std::uint64_t> clordid_optional, std::uint64_t secondary_order_id, std::uint64_t security_id, std::optional<std::uint32_t> account, std::uint64_t last_qty, Decimal last_px, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::uint64_t leaves_qty, std::uint64_t cum_qty, std::uint32_t trade_id, std::uint32_t contra_broker, std::uint64_t order_id, AggressorIndicator aggressor_indicator, SettlTypeOptional settl_type_optional, std::uint16_t trade_date, std::optional<std::uint16_t> days_to_settlement_optional, const std::array<std::byte, 2>& offset_118_padding_2, std::optional<std::uint64_t> secondary_exec_id, std::optional<std::uint64_t> exec_ref_id, std::optional<Decimal> fixed_rate_percentage_8_optional, std::uint64_t order_qty, std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<SecurityTradingStatus> security_trading_status, std::optional<std::uint32_t> trading_sub_account, const DeskId& desk_id, const Memo& memo)
  : outbound_business_header_(outbound_business_header), side_(side), ord_status_(ord_status), clordid_optional_(clordid_optional), secondary_order_id_(secondary_order_id), security_id_(security_id), account_(account), last_qty_(last_qty), last_px_(last_px), exec_id_(exec_id), transact_time_(transact_time), leaves_qty_(leaves_qty), cum_qty_(cum_qty), trade_id_(trade_id), contra_broker_(contra_broker), order_id_(order_id), aggressor_indicator_(aggressor_indicator), settl_type_optional_(settl_type_optional), trade_date_(trade_date), days_to_settlement_optional_(days_to_settlement_optional), offset_118_padding_2_(offset_118_padding_2), secondary_exec_id_(secondary_exec_id), exec_ref_id_(exec_ref_id), fixed_rate_percentage_8_optional_(fixed_rate_percentage_8_optional), order_qty_(order_qty), trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), security_trading_status_(security_trading_status), trading_sub_account_(trading_sub_account), desk_id_(desk_id), memo_(memo) {}

const OutboundBusinessHeader& ExecutionReportForwardMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& ExecutionReportForwardMessage::outbound_business_header() { return outbound_business_header_; }
void ExecutionReportForwardMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

Side ExecutionReportForwardMessage::side() const { return side_; }
void ExecutionReportForwardMessage::set_side(Side value) { side_ = value; }

OrdStatus ExecutionReportForwardMessage::ord_status() const { return ord_status_; }
void ExecutionReportForwardMessage::set_ord_status(OrdStatus value) { ord_status_ = value; }

std::optional<std::uint64_t> ExecutionReportForwardMessage::clordid_optional() const { return clordid_optional_; }
void ExecutionReportForwardMessage::set_clordid_optional(std::optional<std::uint64_t> value) { clordid_optional_ = value; }

std::uint64_t ExecutionReportForwardMessage::secondary_order_id() const { return secondary_order_id_; }
void ExecutionReportForwardMessage::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::uint64_t ExecutionReportForwardMessage::security_id() const { return security_id_; }
void ExecutionReportForwardMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::optional<std::uint32_t> ExecutionReportForwardMessage::account() const { return account_; }
void ExecutionReportForwardMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::uint64_t ExecutionReportForwardMessage::last_qty() const { return last_qty_; }
void ExecutionReportForwardMessage::set_last_qty(std::uint64_t value) { last_qty_ = value; }

Decimal ExecutionReportForwardMessage::last_px() const { return last_px_; }
void ExecutionReportForwardMessage::set_last_px(Decimal value) { last_px_ = value; }

std::uint64_t ExecutionReportForwardMessage::exec_id() const { return exec_id_; }
void ExecutionReportForwardMessage::set_exec_id(std::uint64_t value) { exec_id_ = value; }

std::chrono::nanoseconds ExecutionReportForwardMessage::transact_time() const { return transact_time_; }
void ExecutionReportForwardMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::uint64_t ExecutionReportForwardMessage::leaves_qty() const { return leaves_qty_; }
void ExecutionReportForwardMessage::set_leaves_qty(std::uint64_t value) { leaves_qty_ = value; }

std::uint64_t ExecutionReportForwardMessage::cum_qty() const { return cum_qty_; }
void ExecutionReportForwardMessage::set_cum_qty(std::uint64_t value) { cum_qty_ = value; }

std::uint32_t ExecutionReportForwardMessage::trade_id() const { return trade_id_; }
void ExecutionReportForwardMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::uint32_t ExecutionReportForwardMessage::contra_broker() const { return contra_broker_; }
void ExecutionReportForwardMessage::set_contra_broker(std::uint32_t value) { contra_broker_ = value; }

std::uint64_t ExecutionReportForwardMessage::order_id() const { return order_id_; }
void ExecutionReportForwardMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

AggressorIndicator ExecutionReportForwardMessage::aggressor_indicator() const { return aggressor_indicator_; }
void ExecutionReportForwardMessage::set_aggressor_indicator(AggressorIndicator value) { aggressor_indicator_ = value; }

SettlTypeOptional ExecutionReportForwardMessage::settl_type_optional() const { return settl_type_optional_; }
void ExecutionReportForwardMessage::set_settl_type_optional(SettlTypeOptional value) { settl_type_optional_ = value; }

std::uint16_t ExecutionReportForwardMessage::trade_date() const { return trade_date_; }
void ExecutionReportForwardMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<std::uint16_t> ExecutionReportForwardMessage::days_to_settlement_optional() const { return days_to_settlement_optional_; }
void ExecutionReportForwardMessage::set_days_to_settlement_optional(std::optional<std::uint16_t> value) { days_to_settlement_optional_ = value; }

const std::array<std::byte, 2>& ExecutionReportForwardMessage::offset_118_padding_2() const { return offset_118_padding_2_; }
std::array<std::byte, 2>& ExecutionReportForwardMessage::offset_118_padding_2() { return offset_118_padding_2_; }
void ExecutionReportForwardMessage::set_offset_118_padding_2(const std::array<std::byte, 2>& value) { offset_118_padding_2_ = value; }

std::optional<std::uint64_t> ExecutionReportForwardMessage::secondary_exec_id() const { return secondary_exec_id_; }
void ExecutionReportForwardMessage::set_secondary_exec_id(std::optional<std::uint64_t> value) { secondary_exec_id_ = value; }

std::optional<std::uint64_t> ExecutionReportForwardMessage::exec_ref_id() const { return exec_ref_id_; }
void ExecutionReportForwardMessage::set_exec_ref_id(std::optional<std::uint64_t> value) { exec_ref_id_ = value; }

std::optional<Decimal> ExecutionReportForwardMessage::fixed_rate_percentage_8_optional() const { return fixed_rate_percentage_8_optional_; }
void ExecutionReportForwardMessage::set_fixed_rate_percentage_8_optional(std::optional<Decimal> value) { fixed_rate_percentage_8_optional_ = value; }

std::uint64_t ExecutionReportForwardMessage::order_qty() const { return order_qty_; }
void ExecutionReportForwardMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<TradingSessionId> ExecutionReportForwardMessage::trading_session_id() const { return trading_session_id_; }
void ExecutionReportForwardMessage::set_trading_session_id(std::optional<TradingSessionId> value) { trading_session_id_ = value; }

std::optional<TradingSessionSubId> ExecutionReportForwardMessage::trading_session_sub_id() const { return trading_session_sub_id_; }
void ExecutionReportForwardMessage::set_trading_session_sub_id(std::optional<TradingSessionSubId> value) { trading_session_sub_id_ = value; }

std::optional<SecurityTradingStatus> ExecutionReportForwardMessage::security_trading_status() const { return security_trading_status_; }
void ExecutionReportForwardMessage::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

std::optional<std::uint32_t> ExecutionReportForwardMessage::trading_sub_account() const { return trading_sub_account_; }
void ExecutionReportForwardMessage::set_trading_sub_account(std::optional<std::uint32_t> value) { trading_sub_account_ = value; }

const DeskId& ExecutionReportForwardMessage::desk_id() const { return desk_id_; }
DeskId& ExecutionReportForwardMessage::desk_id() { return desk_id_; }
void ExecutionReportForwardMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& ExecutionReportForwardMessage::memo() const { return memo_; }
Memo& ExecutionReportForwardMessage::memo() { return memo_; }
void ExecutionReportForwardMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode ExecutionReportForwardMessage::type() const { return message_type; }

std::string_view ExecutionReportForwardMessage::name() const { return "Execution Report Forward Message"; }

std::size_t ExecutionReportForwardMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    ord_status_ = static_cast<OrdStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    clordid_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    last_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    exec_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    leaves_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    cum_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 4, length);
    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ExecutionReportForwardMessage", offset + 4, length);
    contra_broker_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    aggressor_indicator_ = static_cast<AggressorIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    settl_type_optional_ = static_cast<SettlTypeOptional>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 2, length);
    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ExecutionReportForwardMessage", offset + 2, length);
    days_to_settlement_optional_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ExecutionReportForwardMessage", offset + 2, length);
    wire::read_bytes(data + offset, offset_118_padding_2_.data(), 2);
    offset += 2;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    secondary_exec_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    exec_ref_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    fixed_rate_percentage_8_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    trading_session_id_ = wire::nullable_enum<TradingSessionId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    trading_session_sub_id_ = wire::nullable_enum<TradingSessionSubId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 1, length);
    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportForwardMessage", offset + 4, length);
    trading_sub_account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExecutionReportForwardMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionReportForwardMessage", encoded_size(), capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(ord_status_));
    offset += 1;

    wire::write_u64_le(data + offset, clordid_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(secondary_order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(last_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_px_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(exec_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(leaves_qty_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(cum_qty_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(contra_broker_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(aggressor_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settl_type_optional_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u16_le(data + offset, days_to_settlement_optional_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_bytes(data + offset, offset_118_padding_2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, secondary_exec_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, exec_ref_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_i64_le(data + offset, fixed_rate_percentage_8_optional_ ? static_cast<std::int64_t>(fixed_rate_percentage_8_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_u8(data + offset, trading_session_id_ ? static_cast<std::uint8_t>(*trading_session_id_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, trading_session_sub_id_ ? static_cast<std::uint8_t>(*trading_session_sub_id_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u32_le(data + offset, trading_sub_account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExecutionReportForwardMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 4 + 8 + 8 + 8 + 8 + 8 + 8 + 4 + 4 + 8 + 1 + 1 + 2 + 2 + 2 + 8 + 8 + 8 + 8 + 1 + 1 + 1 + 4 + desk_id_.encoded_size() + memo_.encoded_size();
}

void ExecutionReportForwardMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionReportForwardMessage::clone() const {
    return std::make_unique<ExecutionReportForwardMessage>(*this);
}

void ExecutionReportForwardMessage::print(std::ostream& out) const {
    out << "ExecutionReportForwardMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", side=";
    out << side_;
    out << ", ord_status=";
    out << ord_status_;
    out << ", clordid_optional=";
    print::optional(out, clordid_optional_);
    out << ", secondary_order_id=";
    out << secondary_order_id_;
    out << ", security_id=";
    out << security_id_;
    out << ", account=";
    print::optional(out, account_);
    out << ", last_qty=";
    out << last_qty_;
    out << ", last_px=";
    out << last_px_;
    out << ", exec_id=";
    out << exec_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", leaves_qty=";
    out << leaves_qty_;
    out << ", cum_qty=";
    out << cum_qty_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", contra_broker=";
    out << contra_broker_;
    out << ", order_id=";
    out << order_id_;
    out << ", aggressor_indicator=";
    out << aggressor_indicator_;
    out << ", settl_type_optional=";
    out << settl_type_optional_;
    out << ", trade_date=";
    out << trade_date_;
    out << ", days_to_settlement_optional=";
    print::optional(out, days_to_settlement_optional_);
    out << ", offset_118_padding_2=";
    print::hex(out, offset_118_padding_2_.data(), offset_118_padding_2_.size());
    out << ", secondary_exec_id=";
    print::optional(out, secondary_exec_id_);
    out << ", exec_ref_id=";
    print::optional(out, exec_ref_id_);
    out << ", fixed_rate_percentage_8_optional=";
    print::optional(out, fixed_rate_percentage_8_optional_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", trading_session_id=";
    print::optional(out, trading_session_id_);
    out << ", trading_session_sub_id=";
    print::optional(out, trading_session_sub_id_);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", trading_sub_account=";
    print::optional(out, trading_sub_account_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool ExecutionReportForwardMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionReportForwardMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionReportForwardMessage::operator==(const ExecutionReportForwardMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && side_ == other.side_
        && ord_status_ == other.ord_status_
        && clordid_optional_ == other.clordid_optional_
        && secondary_order_id_ == other.secondary_order_id_
        && security_id_ == other.security_id_
        && account_ == other.account_
        && last_qty_ == other.last_qty_
        && last_px_ == other.last_px_
        && exec_id_ == other.exec_id_
        && transact_time_ == other.transact_time_
        && leaves_qty_ == other.leaves_qty_
        && cum_qty_ == other.cum_qty_
        && trade_id_ == other.trade_id_
        && contra_broker_ == other.contra_broker_
        && order_id_ == other.order_id_
        && aggressor_indicator_ == other.aggressor_indicator_
        && settl_type_optional_ == other.settl_type_optional_
        && trade_date_ == other.trade_date_
        && days_to_settlement_optional_ == other.days_to_settlement_optional_
        && offset_118_padding_2_ == other.offset_118_padding_2_
        && secondary_exec_id_ == other.secondary_exec_id_
        && exec_ref_id_ == other.exec_ref_id_
        && fixed_rate_percentage_8_optional_ == other.fixed_rate_percentage_8_optional_
        && order_qty_ == other.order_qty_
        && trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && security_trading_status_ == other.security_trading_status_
        && trading_sub_account_ == other.trading_sub_account_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool ExecutionReportForwardMessage::operator!=(const ExecutionReportForwardMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
