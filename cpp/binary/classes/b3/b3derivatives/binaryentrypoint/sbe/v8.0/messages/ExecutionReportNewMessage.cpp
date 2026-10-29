#include "ExecutionReportNewMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

ExecutionReportNewMessage::ExecutionReportNewMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::uint64_t clordid, std::uint64_t secondary_order_id, std::uint64_t security_id, std::uint64_t order_id, std::optional<std::uint32_t> account, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::optional<std::chrono::nanoseconds> market_segment_received_time, std::optional<Decimal> protection_price, std::uint16_t trade_date, WorkingIndicator working_indicator, MultiLegReportingType multi_leg_reporting_type, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, std::optional<std::uint64_t> crossid_optional, const DeskId& desk_id, const Memo& memo)
  : outbound_business_header_(outbound_business_header), side_(side), ord_status_(ord_status), clordid_(clordid), secondary_order_id_(secondary_order_id), security_id_(security_id), order_id_(order_id), account_(account), exec_id_(exec_id), transact_time_(transact_time), market_segment_received_time_(market_segment_received_time), protection_price_(protection_price), trade_date_(trade_date), working_indicator_(working_indicator), multi_leg_reporting_type_(multi_leg_reporting_type), ordtype_(ordtype), time_in_force_(time_in_force), expire_date_(expire_date), order_qty_(order_qty), price_optional_(price_optional), stop_px_(stop_px), min_qty_(min_qty), max_floor_(max_floor), crossid_optional_(crossid_optional), desk_id_(desk_id), memo_(memo) {}

const OutboundBusinessHeader& ExecutionReportNewMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& ExecutionReportNewMessage::outbound_business_header() { return outbound_business_header_; }
void ExecutionReportNewMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

Side ExecutionReportNewMessage::side() const { return side_; }
void ExecutionReportNewMessage::set_side(Side value) { side_ = value; }

OrdStatus ExecutionReportNewMessage::ord_status() const { return ord_status_; }
void ExecutionReportNewMessage::set_ord_status(OrdStatus value) { ord_status_ = value; }

std::uint64_t ExecutionReportNewMessage::clordid() const { return clordid_; }
void ExecutionReportNewMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::uint64_t ExecutionReportNewMessage::secondary_order_id() const { return secondary_order_id_; }
void ExecutionReportNewMessage::set_secondary_order_id(std::uint64_t value) { secondary_order_id_ = value; }

std::uint64_t ExecutionReportNewMessage::security_id() const { return security_id_; }
void ExecutionReportNewMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t ExecutionReportNewMessage::order_id() const { return order_id_; }
void ExecutionReportNewMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::optional<std::uint32_t> ExecutionReportNewMessage::account() const { return account_; }
void ExecutionReportNewMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

std::uint64_t ExecutionReportNewMessage::exec_id() const { return exec_id_; }
void ExecutionReportNewMessage::set_exec_id(std::uint64_t value) { exec_id_ = value; }

std::chrono::nanoseconds ExecutionReportNewMessage::transact_time() const { return transact_time_; }
void ExecutionReportNewMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionReportNewMessage::market_segment_received_time() const { return market_segment_received_time_; }
void ExecutionReportNewMessage::set_market_segment_received_time(std::optional<std::chrono::nanoseconds> value) { market_segment_received_time_ = value; }

std::optional<Decimal> ExecutionReportNewMessage::protection_price() const { return protection_price_; }
void ExecutionReportNewMessage::set_protection_price(std::optional<Decimal> value) { protection_price_ = value; }

std::uint16_t ExecutionReportNewMessage::trade_date() const { return trade_date_; }
void ExecutionReportNewMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

WorkingIndicator ExecutionReportNewMessage::working_indicator() const { return working_indicator_; }
void ExecutionReportNewMessage::set_working_indicator(WorkingIndicator value) { working_indicator_ = value; }

MultiLegReportingType ExecutionReportNewMessage::multi_leg_reporting_type() const { return multi_leg_reporting_type_; }
void ExecutionReportNewMessage::set_multi_leg_reporting_type(MultiLegReportingType value) { multi_leg_reporting_type_ = value; }

Ordtype ExecutionReportNewMessage::ordtype() const { return ordtype_; }
void ExecutionReportNewMessage::set_ordtype(Ordtype value) { ordtype_ = value; }

TimeInForce ExecutionReportNewMessage::time_in_force() const { return time_in_force_; }
void ExecutionReportNewMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

std::optional<std::uint16_t> ExecutionReportNewMessage::expire_date() const { return expire_date_; }
void ExecutionReportNewMessage::set_expire_date(std::optional<std::uint16_t> value) { expire_date_ = value; }

std::uint64_t ExecutionReportNewMessage::order_qty() const { return order_qty_; }
void ExecutionReportNewMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<Decimal> ExecutionReportNewMessage::price_optional() const { return price_optional_; }
void ExecutionReportNewMessage::set_price_optional(std::optional<Decimal> value) { price_optional_ = value; }

std::optional<Decimal> ExecutionReportNewMessage::stop_px() const { return stop_px_; }
void ExecutionReportNewMessage::set_stop_px(std::optional<Decimal> value) { stop_px_ = value; }

std::optional<std::uint64_t> ExecutionReportNewMessage::min_qty() const { return min_qty_; }
void ExecutionReportNewMessage::set_min_qty(std::optional<std::uint64_t> value) { min_qty_ = value; }

std::optional<std::uint64_t> ExecutionReportNewMessage::max_floor() const { return max_floor_; }
void ExecutionReportNewMessage::set_max_floor(std::optional<std::uint64_t> value) { max_floor_ = value; }

std::optional<std::uint64_t> ExecutionReportNewMessage::crossid_optional() const { return crossid_optional_; }
void ExecutionReportNewMessage::set_crossid_optional(std::optional<std::uint64_t> value) { crossid_optional_ = value; }

const DeskId& ExecutionReportNewMessage::desk_id() const { return desk_id_; }
DeskId& ExecutionReportNewMessage::desk_id() { return desk_id_; }
void ExecutionReportNewMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& ExecutionReportNewMessage::memo() const { return memo_; }
Memo& ExecutionReportNewMessage::memo() { return memo_; }
void ExecutionReportNewMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode ExecutionReportNewMessage::type() const { return message_type; }

std::string_view ExecutionReportNewMessage::name() const { return "Execution Report New Message"; }

std::size_t ExecutionReportNewMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("ExecutionReportNewMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportNewMessage", offset + 1, length);
    ord_status_ = static_cast<OrdStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    secondary_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    exec_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    market_segment_received_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    protection_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 2, length);
    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ExecutionReportNewMessage", offset + 1, length);
    working_indicator_ = static_cast<WorkingIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExecutionReportNewMessage", offset + 1, length);
    multi_leg_reporting_type_ = static_cast<MultiLegReportingType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportNewMessage", offset + 1, length);
    ordtype_ = static_cast<Ordtype>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportNewMessage", offset + 1, length);
    time_in_force_ = static_cast<TimeInForce>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportNewMessage", offset + 2, length);
    expire_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    stop_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    min_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    max_floor_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportNewMessage", offset + 8, length);
    crossid_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExecutionReportNewMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionReportNewMessage", encoded_size(), capacity);

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

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(exec_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, market_segment_received_time_ ? static_cast<std::uint64_t>(market_segment_received_time_->count()) : static_cast<std::uint64_t>(0ULL));
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

    wire::write_u64_le(data + offset, crossid_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExecutionReportNewMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 8 + 4 + 8 + 8 + 8 + 8 + 2 + 1 + 1 + 1 + 1 + 2 + 8 + 8 + 8 + 8 + 8 + 8 + desk_id_.encoded_size() + memo_.encoded_size();
}

void ExecutionReportNewMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionReportNewMessage::clone() const {
    return std::make_unique<ExecutionReportNewMessage>(*this);
}

void ExecutionReportNewMessage::print(std::ostream& out) const {
    out << "ExecutionReportNewMessage{";
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
    out << ", order_id=";
    out << order_id_;
    out << ", account=";
    print::optional(out, account_);
    out << ", exec_id=";
    out << exec_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", market_segment_received_time=";
    print::optional_duration(out, market_segment_received_time_);
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
    out << ", crossid_optional=";
    print::optional(out, crossid_optional_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool ExecutionReportNewMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionReportNewMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionReportNewMessage::operator==(const ExecutionReportNewMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && side_ == other.side_
        && ord_status_ == other.ord_status_
        && clordid_ == other.clordid_
        && secondary_order_id_ == other.secondary_order_id_
        && security_id_ == other.security_id_
        && order_id_ == other.order_id_
        && account_ == other.account_
        && exec_id_ == other.exec_id_
        && transact_time_ == other.transact_time_
        && market_segment_received_time_ == other.market_segment_received_time_
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
        && crossid_optional_ == other.crossid_optional_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool ExecutionReportNewMessage::operator!=(const ExecutionReportNewMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
