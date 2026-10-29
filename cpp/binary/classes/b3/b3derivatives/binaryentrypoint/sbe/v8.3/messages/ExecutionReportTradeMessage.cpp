#include "ExecutionReportTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

ExecutionReportTradeMessage::ExecutionReportTradeMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::optional<std::uint64_t> clordid_optional, std::uint64_t secondary_order_id, std::uint64_t security_id, std::optional<std::uint32_t> account, std::uint64_t last_qty, Decimal last_px, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::uint64_t leaves_qty, std::uint64_t cum_qty, AggressorIndicator aggressor_indicator, ExecType exec_type, OrderCategory order_category, MultiLegReportingType multi_leg_reporting_type, std::uint32_t trade_id, std::uint32_t contra_broker, std::uint64_t order_id, std::uint16_t trade_date, std::optional<std::uint8_t> tot_no_related_sym, const std::array<std::byte, 1>& offset_119_padding_1, std::optional<std::uint64_t> secondary_exec_id, std::optional<std::uint64_t> exec_ref_id, std::optional<std::uint64_t> crossid_optional, std::optional<CrossedIndicator> crossed_indicator, std::uint64_t order_qty, std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<SecurityTradingStatus> security_trading_status, std::optional<CrossType> cross_type, std::optional<CrossPrioritization> cross_prioritization, const std::array<std::byte, 1>& offset_159_padding_1, std::optional<std::int32_t> strategy_id, const ImpliedEventId& implied_event_id, std::optional<std::uint32_t> trading_sub_account, const DeskId& desk_id, const Memo& memo)
  : outbound_business_header_(outbound_business_header), side_(side), ord_status_(ord_status), clordid_optional_(clordid_optional), secondary_order_id_(secondary_order_id), security_id_(security_id), account_(account), last_qty_(last_qty), last_px_(last_px), exec_id_(exec_id), transact_time_(transact_time), leaves_qty_(leaves_qty), cum_qty_(cum_qty), aggressor_indicator_(aggressor_indicator), exec_type_(exec_type), order_category_(order_category), multi_leg_reporting_type_(multi_leg_reporting_type), trade_id_(trade_id), contra_broker_(contra_broker), order_id_(order_id), trade_date_(trade_date), tot_no_related_sym_(tot_no_related_sym), offset_119_padding_1_(offset_119_padding_1), secondary_exec_id_(secondary_exec_id), exec_ref_id_(exec_ref_id), crossid_optional_(crossid_optional), crossed_indicator_(crossed_indicator), order_qty_(order_qty), trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), security_trading_status_(security_trading_status), cross_type_(cross_type), cross_prioritization_(cross_prioritization), offset_159_padding_1_(offset_159_padding_1), strategy_id_(strategy_id), implied_event_id_(implied_event_id), trading_sub_account_(trading_sub_account), desk_id_(desk_id), memo_(memo) {}

const OutboundBusinessHeader& ExecutionReportTradeMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& ExecutionReportTradeMessage::outbound_business_header() { return outbound_business_header_; }
void ExecutionReportTradeMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

Side ExecutionReportTradeMessage::side() const { return side_; }
void ExecutionReportTradeMessage::set_side(Side value) { side_ = value; }

OrdStatus ExecutionReportTradeMessage::ord_status() const { return ord_status_; }
void ExecutionReportTradeMessage::set_ord_status(OrdStatus value) { ord_status_ = value; }

std::optional<std::uint64_t> ExecutionReportTradeMessage::clordid_optional() const { return clordid_optional_; }
void ExecutionReportTradeMessage::set_clordid_optional(std::optional<std::uint64_t> value) { clordid_optional_ = value; }

std::uint64_t ExecutionReportTradeMessage::secondary_order_id() const { return secondary_order_id_; }
void ExecutionReportTradeMessage::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::uint64_t ExecutionReportTradeMessage::security_id() const { return security_id_; }
void ExecutionReportTradeMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::optional<std::uint32_t> ExecutionReportTradeMessage::account() const { return account_; }
void ExecutionReportTradeMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::uint64_t ExecutionReportTradeMessage::last_qty() const { return last_qty_; }
void ExecutionReportTradeMessage::set_last_qty(std::uint64_t value) { last_qty_ = value; }

Decimal ExecutionReportTradeMessage::last_px() const { return last_px_; }
void ExecutionReportTradeMessage::set_last_px(Decimal value) { last_px_ = value; }

std::uint64_t ExecutionReportTradeMessage::exec_id() const { return exec_id_; }
void ExecutionReportTradeMessage::set_exec_id(std::uint64_t value) { exec_id_ = value; }

std::chrono::nanoseconds ExecutionReportTradeMessage::transact_time() const { return transact_time_; }
void ExecutionReportTradeMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::uint64_t ExecutionReportTradeMessage::leaves_qty() const { return leaves_qty_; }
void ExecutionReportTradeMessage::set_leaves_qty(std::uint64_t value) { leaves_qty_ = value; }

std::uint64_t ExecutionReportTradeMessage::cum_qty() const { return cum_qty_; }
void ExecutionReportTradeMessage::set_cum_qty(std::uint64_t value) { cum_qty_ = value; }

AggressorIndicator ExecutionReportTradeMessage::aggressor_indicator() const { return aggressor_indicator_; }
void ExecutionReportTradeMessage::set_aggressor_indicator(AggressorIndicator value) { aggressor_indicator_ = value; }

ExecType ExecutionReportTradeMessage::exec_type() const { return exec_type_; }
void ExecutionReportTradeMessage::set_exec_type(ExecType value) { exec_type_ = value; }

OrderCategory ExecutionReportTradeMessage::order_category() const { return order_category_; }
void ExecutionReportTradeMessage::set_order_category(OrderCategory value) { order_category_ = value; }

MultiLegReportingType ExecutionReportTradeMessage::multi_leg_reporting_type() const { return multi_leg_reporting_type_; }
void ExecutionReportTradeMessage::set_multi_leg_reporting_type(MultiLegReportingType value) { multi_leg_reporting_type_ = value; }

std::uint32_t ExecutionReportTradeMessage::trade_id() const { return trade_id_; }
void ExecutionReportTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::uint32_t ExecutionReportTradeMessage::contra_broker() const { return contra_broker_; }
void ExecutionReportTradeMessage::set_contra_broker(std::uint32_t value) { contra_broker_ = value; }

std::uint64_t ExecutionReportTradeMessage::order_id() const { return order_id_; }
void ExecutionReportTradeMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint16_t ExecutionReportTradeMessage::trade_date() const { return trade_date_; }
void ExecutionReportTradeMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<std::uint8_t> ExecutionReportTradeMessage::tot_no_related_sym() const { return tot_no_related_sym_; }
void ExecutionReportTradeMessage::set_tot_no_related_sym(std::optional<std::uint8_t> value) { tot_no_related_sym_ = value; }

const std::array<std::byte, 1>& ExecutionReportTradeMessage::offset_119_padding_1() const { return offset_119_padding_1_; }
std::array<std::byte, 1>& ExecutionReportTradeMessage::offset_119_padding_1() { return offset_119_padding_1_; }
void ExecutionReportTradeMessage::set_offset_119_padding_1(const std::array<std::byte, 1>& value) { offset_119_padding_1_ = value; }

std::optional<std::uint64_t> ExecutionReportTradeMessage::secondary_exec_id() const { return secondary_exec_id_; }
void ExecutionReportTradeMessage::set_secondary_exec_id(std::optional<std::uint64_t> value) { secondary_exec_id_ = value; }

std::optional<std::uint64_t> ExecutionReportTradeMessage::exec_ref_id() const { return exec_ref_id_; }
void ExecutionReportTradeMessage::set_exec_ref_id(std::optional<std::uint64_t> value) { exec_ref_id_ = value; }

std::optional<std::uint64_t> ExecutionReportTradeMessage::crossid_optional() const { return crossid_optional_; }
void ExecutionReportTradeMessage::set_crossid_optional(std::optional<std::uint64_t> value) { crossid_optional_ = value; }

std::optional<CrossedIndicator> ExecutionReportTradeMessage::crossed_indicator() const { return crossed_indicator_; }
void ExecutionReportTradeMessage::set_crossed_indicator(std::optional<CrossedIndicator> value) { crossed_indicator_ = value; }

std::uint64_t ExecutionReportTradeMessage::order_qty() const { return order_qty_; }
void ExecutionReportTradeMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<TradingSessionId> ExecutionReportTradeMessage::trading_session_id() const { return trading_session_id_; }
void ExecutionReportTradeMessage::set_trading_session_id(std::optional<TradingSessionId> value) { trading_session_id_ = value; }

std::optional<TradingSessionSubId> ExecutionReportTradeMessage::trading_session_sub_id() const { return trading_session_sub_id_; }
void ExecutionReportTradeMessage::set_trading_session_sub_id(std::optional<TradingSessionSubId> value) { trading_session_sub_id_ = value; }

std::optional<SecurityTradingStatus> ExecutionReportTradeMessage::security_trading_status() const { return security_trading_status_; }
void ExecutionReportTradeMessage::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

std::optional<CrossType> ExecutionReportTradeMessage::cross_type() const { return cross_type_; }
void ExecutionReportTradeMessage::set_cross_type(std::optional<CrossType> value) { cross_type_ = value; }

std::optional<CrossPrioritization> ExecutionReportTradeMessage::cross_prioritization() const { return cross_prioritization_; }
void ExecutionReportTradeMessage::set_cross_prioritization(std::optional<CrossPrioritization> value) { cross_prioritization_ = value; }

const std::array<std::byte, 1>& ExecutionReportTradeMessage::offset_159_padding_1() const { return offset_159_padding_1_; }
std::array<std::byte, 1>& ExecutionReportTradeMessage::offset_159_padding_1() { return offset_159_padding_1_; }
void ExecutionReportTradeMessage::set_offset_159_padding_1(const std::array<std::byte, 1>& value) { offset_159_padding_1_ = value; }

std::optional<std::int32_t> ExecutionReportTradeMessage::strategy_id() const { return strategy_id_; }
void ExecutionReportTradeMessage::set_strategy_id(std::optional<std::int32_t> value) { strategy_id_ = value; }

const ImpliedEventId& ExecutionReportTradeMessage::implied_event_id() const { return implied_event_id_; }
ImpliedEventId& ExecutionReportTradeMessage::implied_event_id() { return implied_event_id_; }
void ExecutionReportTradeMessage::set_implied_event_id(const ImpliedEventId& value) { implied_event_id_ = value; }

std::optional<std::uint32_t> ExecutionReportTradeMessage::trading_sub_account() const { return trading_sub_account_; }
void ExecutionReportTradeMessage::set_trading_sub_account(std::optional<std::uint32_t> value) { trading_sub_account_ = value; }

const DeskId& ExecutionReportTradeMessage::desk_id() const { return desk_id_; }
DeskId& ExecutionReportTradeMessage::desk_id() { return desk_id_; }
void ExecutionReportTradeMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& ExecutionReportTradeMessage::memo() const { return memo_; }
Memo& ExecutionReportTradeMessage::memo() { return memo_; }
void ExecutionReportTradeMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode ExecutionReportTradeMessage::type() const { return message_type; }

std::string_view ExecutionReportTradeMessage::name() const { return "Execution Report Trade Message"; }

std::size_t ExecutionReportTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    ord_status_ = static_cast<OrdStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    clordid_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    last_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    exec_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    leaves_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    cum_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    aggressor_indicator_ = static_cast<AggressorIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    exec_type_ = static_cast<ExecType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    order_category_ = static_cast<OrderCategory>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    multi_leg_reporting_type_ = static_cast<MultiLegReportingType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 4, length);
    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ExecutionReportTradeMessage", offset + 4, length);
    contra_broker_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 2, length);
    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    tot_no_related_sym_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    wire::read_bytes(data + offset, offset_119_padding_1_.data(), 1);
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    secondary_exec_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    exec_ref_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    crossid_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 2, length);
    crossed_indicator_ = wire::nullable_enum<CrossedIndicator>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("ExecutionReportTradeMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    trading_session_id_ = wire::nullable_enum<TradingSessionId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    trading_session_sub_id_ = wire::nullable_enum<TradingSessionSubId>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    cross_type_ = wire::nullable_enum<CrossType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    cross_prioritization_ = wire::nullable_enum<CrossPrioritization>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 1, length);
    wire::read_bytes(data + offset, offset_159_padding_1_.data(), 1);
    offset += 1;

    wire::require("ExecutionReportTradeMessage", offset + 4, length);
    strategy_id_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    offset += implied_event_id_.decode(data + offset, length - offset);

    wire::require("ExecutionReportTradeMessage", offset + 4, length);
    trading_sub_account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExecutionReportTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionReportTradeMessage", encoded_size(), capacity);

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

    wire::write_u8(data + offset, static_cast<std::uint8_t>(aggressor_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(exec_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(order_category_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(multi_leg_reporting_type_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(contra_broker_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u8(data + offset, tot_no_related_sym_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_bytes(data + offset, offset_119_padding_1_.data(), 1);
    offset += 1;

    wire::write_u64_le(data + offset, secondary_exec_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, exec_ref_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, crossid_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u16_le(data + offset, crossed_indicator_ ? static_cast<std::uint16_t>(*crossed_indicator_) : static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_u8(data + offset, trading_session_id_ ? static_cast<std::uint8_t>(*trading_session_id_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, trading_session_sub_id_ ? static_cast<std::uint8_t>(*trading_session_sub_id_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, cross_type_ ? static_cast<std::uint8_t>(*cross_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, cross_prioritization_ ? static_cast<std::uint8_t>(*cross_prioritization_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_bytes(data + offset, offset_159_padding_1_.data(), 1);
    offset += 1;

    wire::write_i32_le(data + offset, strategy_id_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    offset += implied_event_id_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, trading_sub_account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExecutionReportTradeMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 4 + 8 + 8 + 8 + 8 + 8 + 8 + 1 + 1 + 1 + 1 + 4 + 4 + 8 + 2 + 1 + 1 + 8 + 8 + 8 + 2 + 8 + 1 + 1 + 1 + 1 + 1 + 1 + 4 + implied_event_id_.encoded_size() + 4 + desk_id_.encoded_size() + memo_.encoded_size();
}

void ExecutionReportTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionReportTradeMessage::clone() const {
    return std::make_unique<ExecutionReportTradeMessage>(*this);
}

void ExecutionReportTradeMessage::print(std::ostream& out) const {
    out << "ExecutionReportTradeMessage{";
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
    out << ", aggressor_indicator=";
    out << aggressor_indicator_;
    out << ", exec_type=";
    out << exec_type_;
    out << ", order_category=";
    out << order_category_;
    out << ", multi_leg_reporting_type=";
    out << multi_leg_reporting_type_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", contra_broker=";
    out << contra_broker_;
    out << ", order_id=";
    out << order_id_;
    out << ", trade_date=";
    out << trade_date_;
    out << ", tot_no_related_sym=";
    print::optional(out, tot_no_related_sym_);
    out << ", offset_119_padding_1=";
    print::hex(out, offset_119_padding_1_.data(), offset_119_padding_1_.size());
    out << ", secondary_exec_id=";
    print::optional(out, secondary_exec_id_);
    out << ", exec_ref_id=";
    print::optional(out, exec_ref_id_);
    out << ", crossid_optional=";
    print::optional(out, crossid_optional_);
    out << ", crossed_indicator=";
    print::optional(out, crossed_indicator_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", trading_session_id=";
    print::optional(out, trading_session_id_);
    out << ", trading_session_sub_id=";
    print::optional(out, trading_session_sub_id_);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", cross_type=";
    print::optional(out, cross_type_);
    out << ", cross_prioritization=";
    print::optional(out, cross_prioritization_);
    out << ", offset_159_padding_1=";
    print::hex(out, offset_159_padding_1_.data(), offset_159_padding_1_.size());
    out << ", strategy_id=";
    print::optional(out, strategy_id_);
    out << ", implied_event_id=";
    implied_event_id_.print(out);
    out << ", trading_sub_account=";
    print::optional(out, trading_sub_account_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool ExecutionReportTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionReportTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionReportTradeMessage::operator==(const ExecutionReportTradeMessage& other) const {
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
        && aggressor_indicator_ == other.aggressor_indicator_
        && exec_type_ == other.exec_type_
        && order_category_ == other.order_category_
        && multi_leg_reporting_type_ == other.multi_leg_reporting_type_
        && trade_id_ == other.trade_id_
        && contra_broker_ == other.contra_broker_
        && order_id_ == other.order_id_
        && trade_date_ == other.trade_date_
        && tot_no_related_sym_ == other.tot_no_related_sym_
        && offset_119_padding_1_ == other.offset_119_padding_1_
        && secondary_exec_id_ == other.secondary_exec_id_
        && exec_ref_id_ == other.exec_ref_id_
        && crossid_optional_ == other.crossid_optional_
        && crossed_indicator_ == other.crossed_indicator_
        && order_qty_ == other.order_qty_
        && trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && security_trading_status_ == other.security_trading_status_
        && cross_type_ == other.cross_type_
        && cross_prioritization_ == other.cross_prioritization_
        && offset_159_padding_1_ == other.offset_159_padding_1_
        && strategy_id_ == other.strategy_id_
        && implied_event_id_ == other.implied_event_id_
        && trading_sub_account_ == other.trading_sub_account_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool ExecutionReportTradeMessage::operator!=(const ExecutionReportTradeMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
