#include "ExecutionReportRejectMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

ExecutionReportRejectMessage::ExecutionReportRejectMessage(const OutboundBusinessHeader& outbound_business_header, Side side, CxlRejResponseTo cxl_rej_response_to, std::uint64_t clordid, std::optional<std::uint64_t> secondary_order_id_optional, std::uint64_t security_id, OrdRejReason ord_rej_reason, std::chrono::nanoseconds transact_time, std::uint64_t exec_id, std::optional<std::uint64_t> order_id_optional, std::optional<std::uint64_t> origclordid, std::optional<std::uint32_t> account, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, std::optional<std::uint64_t> crossid_optional, std::optional<CrossedIndicator> crossed_indicator, const DeskId& desk_id, const Memo& memo, const Text& text)
  : outbound_business_header_(outbound_business_header), side_(side), cxl_rej_response_to_(cxl_rej_response_to), clordid_(clordid), secondary_order_id_optional_(secondary_order_id_optional), security_id_(security_id), ord_rej_reason_(ord_rej_reason), transact_time_(transact_time), exec_id_(exec_id), order_id_optional_(order_id_optional), origclordid_(origclordid), account_(account), ordtype_(ordtype), time_in_force_(time_in_force), expire_date_(expire_date), order_qty_(order_qty), price_optional_(price_optional), stop_px_(stop_px), min_qty_(min_qty), max_floor_(max_floor), crossid_optional_(crossid_optional), crossed_indicator_(crossed_indicator), desk_id_(desk_id), memo_(memo), text_(text) {}

const OutboundBusinessHeader& ExecutionReportRejectMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& ExecutionReportRejectMessage::outbound_business_header() { return outbound_business_header_; }
void ExecutionReportRejectMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

Side ExecutionReportRejectMessage::side() const { return side_; }
void ExecutionReportRejectMessage::set_side(Side value) { side_ = value; }

CxlRejResponseTo ExecutionReportRejectMessage::cxl_rej_response_to() const { return cxl_rej_response_to_; }
void ExecutionReportRejectMessage::set_cxl_rej_response_to(CxlRejResponseTo value) { cxl_rej_response_to_ = value; }

std::uint64_t ExecutionReportRejectMessage::clordid() const { return clordid_; }
void ExecutionReportRejectMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::optional<std::uint64_t> ExecutionReportRejectMessage::secondary_order_id_optional() const { return secondary_order_id_optional_; }
void ExecutionReportRejectMessage::set_secondary_order_id_optional(std::optional<std::uint64_t> value) { secondary_order_id_optional_ = value; }

std::uint64_t ExecutionReportRejectMessage::security_id() const { return security_id_; }
void ExecutionReportRejectMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

OrdRejReason ExecutionReportRejectMessage::ord_rej_reason() const { return ord_rej_reason_; }
void ExecutionReportRejectMessage::set_ord_rej_reason(OrdRejReason value) { ord_rej_reason_ = value; }

std::chrono::nanoseconds ExecutionReportRejectMessage::transact_time() const { return transact_time_; }
void ExecutionReportRejectMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::uint64_t ExecutionReportRejectMessage::exec_id() const { return exec_id_; }
void ExecutionReportRejectMessage::set_exec_id(std::uint64_t value) { exec_id_ = value; }

std::optional<std::uint64_t> ExecutionReportRejectMessage::order_id_optional() const { return order_id_optional_; }
void ExecutionReportRejectMessage::set_order_id_optional(std::optional<std::uint64_t> value) { order_id_optional_ = value; }

std::optional<std::uint64_t> ExecutionReportRejectMessage::origclordid() const { return origclordid_; }
void ExecutionReportRejectMessage::set_origclordid(std::optional<std::uint64_t> value) { origclordid_ = value; }

std::optional<std::uint32_t> ExecutionReportRejectMessage::account() const { return account_; }
void ExecutionReportRejectMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

Ordtype ExecutionReportRejectMessage::ordtype() const { return ordtype_; }
void ExecutionReportRejectMessage::set_ordtype(Ordtype value) { ordtype_ = value; }

TimeInForce ExecutionReportRejectMessage::time_in_force() const { return time_in_force_; }
void ExecutionReportRejectMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

std::optional<std::uint16_t> ExecutionReportRejectMessage::expire_date() const { return expire_date_; }
void ExecutionReportRejectMessage::set_expire_date(std::optional<std::uint16_t> value) { expire_date_ = value; }

std::uint64_t ExecutionReportRejectMessage::order_qty() const { return order_qty_; }
void ExecutionReportRejectMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<Decimal> ExecutionReportRejectMessage::price_optional() const { return price_optional_; }
void ExecutionReportRejectMessage::set_price_optional(std::optional<Decimal> value) { price_optional_ = value; }

std::optional<Decimal> ExecutionReportRejectMessage::stop_px() const { return stop_px_; }
void ExecutionReportRejectMessage::set_stop_px(std::optional<Decimal> value) { stop_px_ = value; }

std::optional<std::uint64_t> ExecutionReportRejectMessage::min_qty() const { return min_qty_; }
void ExecutionReportRejectMessage::set_min_qty(std::optional<std::uint64_t> value) { min_qty_ = value; }

std::optional<std::uint64_t> ExecutionReportRejectMessage::max_floor() const { return max_floor_; }
void ExecutionReportRejectMessage::set_max_floor(std::optional<std::uint64_t> value) { max_floor_ = value; }

std::optional<std::uint64_t> ExecutionReportRejectMessage::crossid_optional() const { return crossid_optional_; }
void ExecutionReportRejectMessage::set_crossid_optional(std::optional<std::uint64_t> value) { crossid_optional_ = value; }

std::optional<CrossedIndicator> ExecutionReportRejectMessage::crossed_indicator() const { return crossed_indicator_; }
void ExecutionReportRejectMessage::set_crossed_indicator(std::optional<CrossedIndicator> value) { crossed_indicator_ = value; }

const DeskId& ExecutionReportRejectMessage::desk_id() const { return desk_id_; }
DeskId& ExecutionReportRejectMessage::desk_id() { return desk_id_; }
void ExecutionReportRejectMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& ExecutionReportRejectMessage::memo() const { return memo_; }
Memo& ExecutionReportRejectMessage::memo() { return memo_; }
void ExecutionReportRejectMessage::set_memo(const Memo& value) { memo_ = value; }

const Text& ExecutionReportRejectMessage::text() const { return text_; }
Text& ExecutionReportRejectMessage::text() { return text_; }
void ExecutionReportRejectMessage::set_text(const Text& value) { text_ = value; }

MessageCode ExecutionReportRejectMessage::type() const { return message_type; }

std::string_view ExecutionReportRejectMessage::name() const { return "Execution Report Reject Message"; }

std::size_t ExecutionReportRejectMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("ExecutionReportRejectMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportRejectMessage", offset + 1, length);
    cxl_rej_response_to_ = static_cast<CxlRejResponseTo>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    secondary_order_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 4, length);
    ord_rej_reason_ = static_cast<OrdRejReason>(wire::read_u32_le(data + offset));
    offset += 4;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    exec_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    order_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    origclordid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("ExecutionReportRejectMessage", offset + 1, length);
    ordtype_ = static_cast<Ordtype>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportRejectMessage", offset + 1, length);
    time_in_force_ = static_cast<TimeInForce>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ExecutionReportRejectMessage", offset + 2, length);
    expire_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    stop_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    min_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    max_floor_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 8, length);
    crossid_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("ExecutionReportRejectMessage", offset + 2, length);
    crossed_indicator_ = wire::nullable_enum<CrossedIndicator>(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    offset += text_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ExecutionReportRejectMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionReportRejectMessage", encoded_size(), capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(cxl_rej_response_to_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(clordid_));
    offset += 8;

    wire::write_u64_le(data + offset, secondary_order_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ord_rej_reason_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(exec_id_));
    offset += 8;

    wire::write_u64_le(data + offset, order_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, origclordid_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

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

    wire::write_u16_le(data + offset, crossed_indicator_ ? static_cast<std::uint16_t>(*crossed_indicator_) : static_cast<std::uint16_t>(0ULL));
    offset += 2;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    offset += text_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ExecutionReportRejectMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 4 + 8 + 8 + 8 + 8 + 4 + 1 + 1 + 2 + 8 + 8 + 8 + 8 + 8 + 8 + 2 + desk_id_.encoded_size() + memo_.encoded_size() + text_.encoded_size();
}

void ExecutionReportRejectMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionReportRejectMessage::clone() const {
    return std::make_unique<ExecutionReportRejectMessage>(*this);
}

void ExecutionReportRejectMessage::print(std::ostream& out) const {
    out << "ExecutionReportRejectMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", side=";
    out << side_;
    out << ", cxl_rej_response_to=";
    out << cxl_rej_response_to_;
    out << ", clordid=";
    out << clordid_;
    out << ", secondary_order_id_optional=";
    print::optional(out, secondary_order_id_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", ord_rej_reason=";
    out << ord_rej_reason_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", exec_id=";
    out << exec_id_;
    out << ", order_id_optional=";
    print::optional(out, order_id_optional_);
    out << ", origclordid=";
    print::optional(out, origclordid_);
    out << ", account=";
    print::optional(out, account_);
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
    out << ", crossed_indicator=";
    print::optional(out, crossed_indicator_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << ", text=";
    text_.print(out);
    out << '}';
}

bool ExecutionReportRejectMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionReportRejectMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionReportRejectMessage::operator==(const ExecutionReportRejectMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && side_ == other.side_
        && cxl_rej_response_to_ == other.cxl_rej_response_to_
        && clordid_ == other.clordid_
        && secondary_order_id_optional_ == other.secondary_order_id_optional_
        && security_id_ == other.security_id_
        && ord_rej_reason_ == other.ord_rej_reason_
        && transact_time_ == other.transact_time_
        && exec_id_ == other.exec_id_
        && order_id_optional_ == other.order_id_optional_
        && origclordid_ == other.origclordid_
        && account_ == other.account_
        && ordtype_ == other.ordtype_
        && time_in_force_ == other.time_in_force_
        && expire_date_ == other.expire_date_
        && order_qty_ == other.order_qty_
        && price_optional_ == other.price_optional_
        && stop_px_ == other.stop_px_
        && min_qty_ == other.min_qty_
        && max_floor_ == other.max_floor_
        && crossid_optional_ == other.crossid_optional_
        && crossed_indicator_ == other.crossed_indicator_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_
        && text_ == other.text_;
}

bool ExecutionReportRejectMessage::operator!=(const ExecutionReportRejectMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
