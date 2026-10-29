#include "ExecutionReportModifyMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

ExecutionReportModifyMessage::ExecutionReportModifyMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::uint64_t clordid, std::uint64_t secondary_order_id, std::uint64_t security_id, std::uint64_t leaves_qty, std::optional<std::uint32_t> account, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::uint64_t cum_qty, std::optional<std::chrono::nanoseconds> market_segment_received_time, std::uint64_t order_id, std::optional<std::uint64_t> origclordid, std::optional<Decimal> protection_price, std::uint16_t trade_date, WorkingIndicator working_indicator, MultiLegReportingType multi_leg_reporting_type, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, const DeskId& desk_id, const Memo& memo)
  : outbound_business_header_(outbound_business_header), side_(side), ord_status_(ord_status), clordid_(clordid), secondary_order_id_(secondary_order_id), security_id_(security_id), leaves_qty_(leaves_qty), account_(account), exec_id_(exec_id), transact_time_(transact_time), cum_qty_(cum_qty), market_segment_received_time_(market_segment_received_time), order_id_(order_id), origclordid_(origclordid), protection_price_(protection_price), trade_date_(trade_date), working_indicator_(working_indicator), multi_leg_reporting_type_(multi_leg_reporting_type), ordtype_(ordtype), time_in_force_(time_in_force), expire_date_(expire_date), order_qty_(order_qty), price_optional_(price_optional), stop_px_(stop_px), min_qty_(min_qty), max_floor_(max_floor), desk_id_(desk_id), memo_(memo) {}

const OutboundBusinessHeader& ExecutionReportModifyMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& ExecutionReportModifyMessage::outbound_business_header() { return outbound_business_header_; }
void ExecutionReportModifyMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

Side ExecutionReportModifyMessage::side() const { return side_; }
void ExecutionReportModifyMessage::set_side(Side value) { side_ = value; }

OrdStatus ExecutionReportModifyMessage::ord_status() const { return ord_status_; }
void ExecutionReportModifyMessage::set_ord_status(OrdStatus value) { ord_status_ = value; }

std::uint64_t ExecutionReportModifyMessage::clordid() const { return clordid_; }
void ExecutionReportModifyMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::uint64_t ExecutionReportModifyMessage::secondary_order_id() const { return secondary_order_id_; }
void ExecutionReportModifyMessage::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::uint64_t ExecutionReportModifyMessage::security_id() const { return security_id_; }
void ExecutionReportModifyMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t ExecutionReportModifyMessage::leaves_qty() const { return leaves_qty_; }
void ExecutionReportModifyMessage::set_leaves_qty(std::uint64_t value) { leaves_qty_ = value; }

std::optional<std::uint32_t> ExecutionReportModifyMessage::account() const { return account_; }
void ExecutionReportModifyMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::uint64_t ExecutionReportModifyMessage::exec_id() const { return exec_id_; }
void ExecutionReportModifyMessage::set_exec_id(std::uint64_t value) { exec_id_ = value; }

std::chrono::nanoseconds ExecutionReportModifyMessage::transact_time() const { return transact_time_; }
void ExecutionReportModifyMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::uint64_t ExecutionReportModifyMessage::cum_qty() const { return cum_qty_; }
void ExecutionReportModifyMessage::set_cum_qty(std::uint64_t value) { cum_qty_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionReportModifyMessage::market_segment_received_time() const { return market_segment_received_time_; }
void ExecutionReportModifyMessage::set_market_segment_received_time(std::optional<std::chrono::nanoseconds> value) { market_segment_received_time_ = value; }

std::uint64_t ExecutionReportModifyMessage::order_id() const { return order_id_; }
void ExecutionReportModifyMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::optional<std::uint64_t> ExecutionReportModifyMessage::origclordid() const { return origclordid_; }
void ExecutionReportModifyMessage::set_origclordid(std::optional<std::uint64_t> value) { origclordid_ = value; }

std::optional<Decimal> ExecutionReportModifyMessage::protection_price() const { return protection_price_; }
void ExecutionReportModifyMessage::set_protection_price(std::optional<Decimal> value) { protection_price_ = value; }

std::uint16_t ExecutionReportModifyMessage::trade_date() const { return trade_date_; }
void ExecutionReportModifyMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

WorkingIndicator ExecutionReportModifyMessage::working_indicator() const { return working_indicator_; }
void ExecutionReportModifyMessage::set_working_indicator(WorkingIndicator value) { working_indicator_ = value; }

MultiLegReportingType ExecutionReportModifyMessage::multi_leg_reporting_type() const { return multi_leg_reporting_type_; }
void ExecutionReportModifyMessage::set_multi_leg_reporting_type(MultiLegReportingType value) { multi_leg_reporting_type_ = value; }

Ordtype ExecutionReportModifyMessage::ordtype() const { return ordtype_; }
void ExecutionReportModifyMessage::set_ordtype(Ordtype value) { ordtype_ = value; }

TimeInForce ExecutionReportModifyMessage::time_in_force() const { return time_in_force_; }
void ExecutionReportModifyMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

std::optional<std::uint16_t> ExecutionReportModifyMessage::expire_date() const { return expire_date_; }
void ExecutionReportModifyMessage::set_expire_date(std::optional<std::uint16_t> value) { expire_date_ = value; }

std::uint64_t ExecutionReportModifyMessage::order_qty() const { return order_qty_; }
void ExecutionReportModifyMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<Decimal> ExecutionReportModifyMessage::price_optional() const { return price_optional_; }
void ExecutionReportModifyMessage::set_price_optional(std::optional<Decimal> value) { price_optional_ = value; }

std::optional<Decimal> ExecutionReportModifyMessage::stop_px() const { return stop_px_; }
void ExecutionReportModifyMessage::set_stop_px(std::optional<Decimal> value) { stop_px_ = value; }

std::optional<std::uint64_t> ExecutionReportModifyMessage::min_qty() const { return min_qty_; }
void ExecutionReportModifyMessage::set_min_qty(std::optional<std::uint64_t> value) { min_qty_ = value; }

std::optional<std::uint64_t> ExecutionReportModifyMessage::max_floor() const { return max_floor_; }
void ExecutionReportModifyMessage::set_max_floor(std::optional<std::uint64_t> value) { max_floor_ = value; }

const DeskId& ExecutionReportModifyMessage::desk_id() const { return desk_id_; }
DeskId& ExecutionReportModifyMessage::desk_id() { return desk_id_; }
void ExecutionReportModifyMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& ExecutionReportModifyMessage::memo() const { return memo_; }
Memo& ExecutionReportModifyMessage::memo() { return memo_; }
void ExecutionReportModifyMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode ExecutionReportModifyMessage::type() const { return message_type; }

std::string_view ExecutionReportModifyMessage::name() const { return "Execution Report Modify Message"; }

std::size_t ExecutionReportModifyMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("ExecutionReportModifyMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportModifyMessage", offset + 1, length);
    ord_status_ = static_cast<OrdStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    leaves_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    exec_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    cum_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    market_segment_received_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    origclordid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    protection_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 2, length);
    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ExecutionReportModifyMessage", offset + 1, length);
    working_indicator_ = static_cast<WorkingIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExecutionReportModifyMessage", offset + 1, length);
    multi_leg_reporting_type_ = static_cast<MultiLegReportingType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportModifyMessage", offset + 1, length);
    ordtype_ = static_cast<Ordtype>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportModifyMessage", offset + 1, length);
    time_in_force_ = static_cast<TimeInForce>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportModifyMessage", offset + 2, length);
    expire_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    stop_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    min_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportModifyMessage", offset + 8, length);
    max_floor_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExecutionReportModifyMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionReportModifyMessage", encoded_size(), capacity);

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

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(leaves_qty_));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(exec_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(cum_qty_));
    offset += 8;

    wire::write_u64_le(data + offset, market_segment_received_time_ ? static_cast<std::uint64_t>(market_segment_received_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, origclordid_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_i64_le(data + offset, protection_price_ ? static_cast<std::int64_t>(protection_price_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(working_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(multi_leg_reporting_type_));
    offset += 1;

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

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExecutionReportModifyMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 8 + 4 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 2 + 1 + 1 + 1 + 1 + 2 + 8 + 8 + 8 + 8 + 8 + desk_id_.encoded_size() + memo_.encoded_size();
}

void ExecutionReportModifyMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionReportModifyMessage::clone() const {
    return std::make_unique<ExecutionReportModifyMessage>(*this);
}

void ExecutionReportModifyMessage::print(std::ostream& out) const {
    out << "ExecutionReportModifyMessage{";
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
    out << ", leaves_qty=";
    out << leaves_qty_;
    out << ", account=";
    print::optional(out, account_);
    out << ", exec_id=";
    out << exec_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", cum_qty=";
    out << cum_qty_;
    out << ", market_segment_received_time=";
    print::optional_duration(out, market_segment_received_time_);
    out << ", order_id=";
    out << order_id_;
    out << ", origclordid=";
    print::optional(out, origclordid_);
    out << ", protection_price=";
    print::optional(out, protection_price_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", working_indicator=";
    out << working_indicator_;
    out << ", multi_leg_reporting_type=";
    out << multi_leg_reporting_type_;
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
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool ExecutionReportModifyMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionReportModifyMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionReportModifyMessage::operator==(const ExecutionReportModifyMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && side_ == other.side_
        && ord_status_ == other.ord_status_
        && clordid_ == other.clordid_
        && secondary_order_id_ == other.secondary_order_id_
        && security_id_ == other.security_id_
        && leaves_qty_ == other.leaves_qty_
        && account_ == other.account_
        && exec_id_ == other.exec_id_
        && transact_time_ == other.transact_time_
        && cum_qty_ == other.cum_qty_
        && market_segment_received_time_ == other.market_segment_received_time_
        && order_id_ == other.order_id_
        && origclordid_ == other.origclordid_
        && protection_price_ == other.protection_price_
        && trade_date_ == other.trade_date_
        && working_indicator_ == other.working_indicator_
        && multi_leg_reporting_type_ == other.multi_leg_reporting_type_
        && ordtype_ == other.ordtype_
        && time_in_force_ == other.time_in_force_
        && expire_date_ == other.expire_date_
        && order_qty_ == other.order_qty_
        && price_optional_ == other.price_optional_
        && stop_px_ == other.stop_px_
        && min_qty_ == other.min_qty_
        && max_floor_ == other.max_floor_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool ExecutionReportModifyMessage::operator!=(const ExecutionReportModifyMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
