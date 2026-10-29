#include "ExecutionReportCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

ExecutionReportCancelMessage::ExecutionReportCancelMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::uint64_t clordid, std::uint64_t secondary_order_id, std::uint64_t security_id, std::uint64_t cum_qty, std::optional<std::uint32_t> account, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::optional<std::chrono::nanoseconds> market_segment_received_time, std::uint64_t order_id, std::optional<std::uint64_t> origclordid, std::uint16_t trade_date, WorkingIndicator working_indicator, std::optional<ExecRestatementReason> exec_restatement_reason, const std::array<std::byte, 4>& offset_100_padding_4, std::optional<std::uint64_t> mass_action_report_id_optional, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, std::optional<std::chrono::nanoseconds> received_time, const std::array<std::byte, 3>& offset_164_padding_3, std::optional<std::uint8_t> ordtagid, const InvestorId& investor_id, std::optional<std::int32_t> strategy_id, std::optional<std::uint32_t> action_requested_from_session_id, const DeskId& desk_id, const Memo& memo)
  : outbound_business_header_(outbound_business_header), side_(side), ord_status_(ord_status), clordid_(clordid), secondary_order_id_(secondary_order_id), security_id_(security_id), cum_qty_(cum_qty), account_(account), exec_id_(exec_id), transact_time_(transact_time), market_segment_received_time_(market_segment_received_time), order_id_(order_id), origclordid_(origclordid), trade_date_(trade_date), working_indicator_(working_indicator), exec_restatement_reason_(exec_restatement_reason), offset_100_padding_4_(offset_100_padding_4), mass_action_report_id_optional_(mass_action_report_id_optional), ordtype_(ordtype), time_in_force_(time_in_force), expire_date_(expire_date), order_qty_(order_qty), price_optional_(price_optional), stop_px_(stop_px), min_qty_(min_qty), max_floor_(max_floor), received_time_(received_time), offset_164_padding_3_(offset_164_padding_3), ordtagid_(ordtagid), investor_id_(investor_id), strategy_id_(strategy_id), action_requested_from_session_id_(action_requested_from_session_id), desk_id_(desk_id), memo_(memo) {}

const OutboundBusinessHeader& ExecutionReportCancelMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& ExecutionReportCancelMessage::outbound_business_header() { return outbound_business_header_; }
void ExecutionReportCancelMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

Side ExecutionReportCancelMessage::side() const { return side_; }
void ExecutionReportCancelMessage::set_side(Side value) { side_ = value; }

OrdStatus ExecutionReportCancelMessage::ord_status() const { return ord_status_; }
void ExecutionReportCancelMessage::set_ord_status(OrdStatus value) { ord_status_ = value; }

std::uint64_t ExecutionReportCancelMessage::clordid() const { return clordid_; }
void ExecutionReportCancelMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::uint64_t ExecutionReportCancelMessage::secondary_order_id() const { return secondary_order_id_; }
void ExecutionReportCancelMessage::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::uint64_t ExecutionReportCancelMessage::security_id() const { return security_id_; }
void ExecutionReportCancelMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t ExecutionReportCancelMessage::cum_qty() const { return cum_qty_; }
void ExecutionReportCancelMessage::set_cum_qty(std::uint64_t value) { cum_qty_ = value; }

std::optional<std::uint32_t> ExecutionReportCancelMessage::account() const { return account_; }
void ExecutionReportCancelMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::uint64_t ExecutionReportCancelMessage::exec_id() const { return exec_id_; }
void ExecutionReportCancelMessage::set_exec_id(std::uint64_t value) { exec_id_ = value; }

std::chrono::nanoseconds ExecutionReportCancelMessage::transact_time() const { return transact_time_; }
void ExecutionReportCancelMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionReportCancelMessage::market_segment_received_time() const { return market_segment_received_time_; }
void ExecutionReportCancelMessage::set_market_segment_received_time(std::optional<std::chrono::nanoseconds> value) { market_segment_received_time_ = value; }

std::uint64_t ExecutionReportCancelMessage::order_id() const { return order_id_; }
void ExecutionReportCancelMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::optional<std::uint64_t> ExecutionReportCancelMessage::origclordid() const { return origclordid_; }
void ExecutionReportCancelMessage::set_origclordid(std::optional<std::uint64_t> value) { origclordid_ = value; }

std::uint16_t ExecutionReportCancelMessage::trade_date() const { return trade_date_; }
void ExecutionReportCancelMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

WorkingIndicator ExecutionReportCancelMessage::working_indicator() const { return working_indicator_; }
void ExecutionReportCancelMessage::set_working_indicator(WorkingIndicator value) { working_indicator_ = value; }

std::optional<ExecRestatementReason> ExecutionReportCancelMessage::exec_restatement_reason() const { return exec_restatement_reason_; }
void ExecutionReportCancelMessage::set_exec_restatement_reason(std::optional<ExecRestatementReason> value) { exec_restatement_reason_ = value; }

const std::array<std::byte, 4>& ExecutionReportCancelMessage::offset_100_padding_4() const { return offset_100_padding_4_; }
std::array<std::byte, 4>& ExecutionReportCancelMessage::offset_100_padding_4() { return offset_100_padding_4_; }
void ExecutionReportCancelMessage::set_offset_100_padding_4(const std::array<std::byte, 4>& value) { offset_100_padding_4_ = value; }

std::optional<std::uint64_t> ExecutionReportCancelMessage::mass_action_report_id_optional() const { return mass_action_report_id_optional_; }
void ExecutionReportCancelMessage::set_mass_action_report_id_optional(std::optional<std::uint64_t> value) { mass_action_report_id_optional_ = value; }

Ordtype ExecutionReportCancelMessage::ordtype() const { return ordtype_; }
void ExecutionReportCancelMessage::set_ordtype(Ordtype value) { ordtype_ = value; }

TimeInForce ExecutionReportCancelMessage::time_in_force() const { return time_in_force_; }
void ExecutionReportCancelMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

std::optional<std::uint16_t> ExecutionReportCancelMessage::expire_date() const { return expire_date_; }
void ExecutionReportCancelMessage::set_expire_date(std::optional<std::uint16_t> value) { expire_date_ = value; }

std::uint64_t ExecutionReportCancelMessage::order_qty() const { return order_qty_; }
void ExecutionReportCancelMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<Decimal> ExecutionReportCancelMessage::price_optional() const { return price_optional_; }
void ExecutionReportCancelMessage::set_price_optional(std::optional<Decimal> value) { price_optional_ = value; }

std::optional<Decimal> ExecutionReportCancelMessage::stop_px() const { return stop_px_; }
void ExecutionReportCancelMessage::set_stop_px(std::optional<Decimal> value) { stop_px_ = value; }

std::optional<std::uint64_t> ExecutionReportCancelMessage::min_qty() const { return min_qty_; }
void ExecutionReportCancelMessage::set_min_qty(std::optional<std::uint64_t> value) { min_qty_ = value; }

std::optional<std::uint64_t> ExecutionReportCancelMessage::max_floor() const { return max_floor_; }
void ExecutionReportCancelMessage::set_max_floor(std::optional<std::uint64_t> value) { max_floor_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionReportCancelMessage::received_time() const { return received_time_; }
void ExecutionReportCancelMessage::set_received_time(std::optional<std::chrono::nanoseconds> value) { received_time_ = value; }

const std::array<std::byte, 3>& ExecutionReportCancelMessage::offset_164_padding_3() const { return offset_164_padding_3_; }
std::array<std::byte, 3>& ExecutionReportCancelMessage::offset_164_padding_3() { return offset_164_padding_3_; }
void ExecutionReportCancelMessage::set_offset_164_padding_3(const std::array<std::byte, 3>& value) { offset_164_padding_3_ = value; }

std::optional<std::uint8_t> ExecutionReportCancelMessage::ordtagid() const { return ordtagid_; }
void ExecutionReportCancelMessage::set_ordtagid(std::optional<std::uint8_t> value) { ordtagid_ = value; }

const InvestorId& ExecutionReportCancelMessage::investor_id() const { return investor_id_; }
InvestorId& ExecutionReportCancelMessage::investor_id() { return investor_id_; }
void ExecutionReportCancelMessage::set_investor_id(const InvestorId& value) { investor_id_ = value; }

std::optional<std::int32_t> ExecutionReportCancelMessage::strategy_id() const { return strategy_id_; }
void ExecutionReportCancelMessage::set_strategy_id(std::optional<std::int32_t> value) { strategy_id_ = value; }

std::optional<std::uint32_t> ExecutionReportCancelMessage::action_requested_from_session_id() const { return action_requested_from_session_id_; }
void ExecutionReportCancelMessage::set_action_requested_from_session_id(std::optional<std::uint32_t> value) { action_requested_from_session_id_ = value; }

const DeskId& ExecutionReportCancelMessage::desk_id() const { return desk_id_; }
DeskId& ExecutionReportCancelMessage::desk_id() { return desk_id_; }
void ExecutionReportCancelMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& ExecutionReportCancelMessage::memo() const { return memo_; }
Memo& ExecutionReportCancelMessage::memo() { return memo_; }
void ExecutionReportCancelMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode ExecutionReportCancelMessage::type() const { return message_type; }

std::string_view ExecutionReportCancelMessage::name() const { return "Execution Report Cancel Message"; }

std::size_t ExecutionReportCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    ord_status_ = static_cast<OrdStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    cum_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    exec_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    market_segment_received_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    origclordid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 2, length);
    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    working_indicator_ = static_cast<WorkingIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    exec_restatement_reason_ = wire::nullable_enum<ExecRestatementReason>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("ExecutionReportCancelMessage", offset + 4, length);
    wire::read_bytes(data + offset, offset_100_padding_4_.data(), 4);
    offset += 4;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    mass_action_report_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    ordtype_ = static_cast<Ordtype>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    time_in_force_ = static_cast<TimeInForce>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportCancelMessage", offset + 2, length);
    expire_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    stop_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    min_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    max_floor_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 8, length);
    received_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportCancelMessage", offset + 3, length);
    wire::read_bytes(data + offset, offset_164_padding_3_.data(), 3);
    offset += 3;

    wire::require("ExecutionReportCancelMessage", offset + 1, length);
    ordtagid_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    offset += investor_id_.decode(data + offset, length - offset);

    wire::require("ExecutionReportCancelMessage", offset + 4, length);
    strategy_id_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    wire::require("ExecutionReportCancelMessage", offset + 4, length);
    action_requested_from_session_id_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExecutionReportCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionReportCancelMessage", encoded_size(), capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(ord_status_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(clordid_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(secondary_order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(cum_qty_));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(exec_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, market_segment_received_time_ ? static_cast<std::uint64_t>(market_segment_received_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, origclordid_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(working_indicator_));
    offset += 1;

    wire::write_u8(data + offset, exec_restatement_reason_ ? static_cast<std::uint8_t>(*exec_restatement_reason_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_bytes(data + offset, offset_100_padding_4_.data(), 4);
    offset += 4;

    wire::write_u64_le(data + offset, mass_action_report_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(ordtype_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(time_in_force_));
    offset += 1;

    wire::write_u16_le(data + offset, expire_date_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, price_optional_ ? static_cast<std::int64_t>(price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, stop_px_ ? static_cast<std::int64_t>(stop_px_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, min_qty_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, max_floor_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, received_time_ ? static_cast<std::uint64_t>(received_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_bytes(data + offset, offset_164_padding_3_.data(), 3);
    offset += 3;

    wire::write_u8(data + offset, ordtagid_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    offset += investor_id_.encode(data + offset, capacity - offset);

    wire::write_i32_le(data + offset, strategy_id_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    wire::write_u32_le(data + offset, action_requested_from_session_id_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExecutionReportCancelMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 8 + 4 + 8 + 8 + 8 + 8 + 8 + 2 + 1 + 1 + 4 + 8 + 1 + 1 + 2 + 8 + 8 + 8 + 8 + 8 + 8 + 3 + 1 + investor_id_.encoded_size() + 4 + 4 + desk_id_.encoded_size() + memo_.encoded_size();
}

void ExecutionReportCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionReportCancelMessage::clone() const {
    return std::make_unique<ExecutionReportCancelMessage>(*this);
}

void ExecutionReportCancelMessage::print(std::ostream& out) const {
    out << "ExecutionReportCancelMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", side=";
    out << side_;
    out << ", ord_status=";
    out << ord_status_;
    out << ", clordid=";
    out << clordid_;
    out << ", secondary_order_id=";
    out << secondary_order_id_;
    out << ", security_id=";
    out << security_id_;
    out << ", cum_qty=";
    out << cum_qty_;
    out << ", account=";
    print::optional(out, account_);
    out << ", exec_id=";
    out << exec_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", market_segment_received_time=";
    print::optional_duration(out, market_segment_received_time_);
    out << ", order_id=";
    out << order_id_;
    out << ", origclordid=";
    print::optional(out, origclordid_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", working_indicator=";
    out << working_indicator_;
    out << ", exec_restatement_reason=";
    print::optional(out, exec_restatement_reason_);
    out << ", offset_100_padding_4=";
    print::hex(out, offset_100_padding_4_.data(), offset_100_padding_4_.size());
    out << ", mass_action_report_id_optional=";
    print::optional(out, mass_action_report_id_optional_);
    out << ", ordtype=";
    out << ordtype_;
    out << ", time_in_force=";
    out << time_in_force_;
    out << ", expire_date=";
    print::optional(out, expire_date_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", price_optional=";
    print::optional(out, price_optional_);
    out << ", stop_px=";
    print::optional(out, stop_px_);
    out << ", min_qty=";
    print::optional(out, min_qty_);
    out << ", max_floor=";
    print::optional(out, max_floor_);
    out << ", received_time=";
    print::optional_duration(out, received_time_);
    out << ", offset_164_padding_3=";
    print::hex(out, offset_164_padding_3_.data(), offset_164_padding_3_.size());
    out << ", ordtagid=";
    print::optional(out, ordtagid_);
    out << ", investor_id=";
    investor_id_.print(out);
    out << ", strategy_id=";
    print::optional(out, strategy_id_);
    out << ", action_requested_from_session_id=";
    print::optional(out, action_requested_from_session_id_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool ExecutionReportCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionReportCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionReportCancelMessage::operator==(const ExecutionReportCancelMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && side_ == other.side_
        && ord_status_ == other.ord_status_
        && clordid_ == other.clordid_
        && secondary_order_id_ == other.secondary_order_id_
        && security_id_ == other.security_id_
        && cum_qty_ == other.cum_qty_
        && account_ == other.account_
        && exec_id_ == other.exec_id_
        && transact_time_ == other.transact_time_
        && market_segment_received_time_ == other.market_segment_received_time_
        && order_id_ == other.order_id_
        && origclordid_ == other.origclordid_
        && trade_date_ == other.trade_date_
        && working_indicator_ == other.working_indicator_
        && exec_restatement_reason_ == other.exec_restatement_reason_
        && offset_100_padding_4_ == other.offset_100_padding_4_
        && mass_action_report_id_optional_ == other.mass_action_report_id_optional_
        && ordtype_ == other.ordtype_
        && time_in_force_ == other.time_in_force_
        && expire_date_ == other.expire_date_
        && order_qty_ == other.order_qty_
        && price_optional_ == other.price_optional_
        && stop_px_ == other.stop_px_
        && min_qty_ == other.min_qty_
        && max_floor_ == other.max_floor_
        && received_time_ == other.received_time_
        && offset_164_padding_3_ == other.offset_164_padding_3_
        && ordtagid_ == other.ordtagid_
        && investor_id_ == other.investor_id_
        && strategy_id_ == other.strategy_id_
        && action_requested_from_session_id_ == other.action_requested_from_session_id_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool ExecutionReportCancelMessage::operator!=(const ExecutionReportCancelMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
