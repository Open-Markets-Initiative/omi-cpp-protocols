#include "QuoteStatusReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

QuoteStatusReportMessage::QuoteStatusReportMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::optional<QuoteRejectReason> quote_reject_reason, std::uint64_t security_id, std::uint64_t quote_req_id, std::uint64_t quote_id, std::optional<std::uint32_t> trade_id_optional, std::uint32_t contra_broker, std::chrono::nanoseconds transact_time, QuoteStatus quote_status, QuoteStatusResponseTo quote_status_response_to, std::optional<std::uint32_t> account, SideOptional side_optional, SettlTypeOptional settl_type_optional, std::optional<Decimal> price_8_optional, std::uint64_t order_qty, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, std::optional<Decimal> fixed_rate_percentage_8_optional, ExecuteUnderlyingTrade execute_underlying_trade, std::optional<std::uint16_t> days_to_settlement_optional, const DeskId& desk_id, const Memo& memo, const Text& text)
  : bidirectional_business_header_(bidirectional_business_header), quote_reject_reason_(quote_reject_reason), security_id_(security_id), quote_req_id_(quote_req_id), quote_id_(quote_id), trade_id_optional_(trade_id_optional), contra_broker_(contra_broker), transact_time_(transact_time), quote_status_(quote_status), quote_status_response_to_(quote_status_response_to), account_(account), side_optional_(side_optional), settl_type_optional_(settl_type_optional), price_8_optional_(price_8_optional), order_qty_(order_qty), sender_location_(sender_location), entering_trader_(entering_trader), executing_trader_(executing_trader), fixed_rate_percentage_8_optional_(fixed_rate_percentage_8_optional), execute_underlying_trade_(execute_underlying_trade), days_to_settlement_optional_(days_to_settlement_optional), desk_id_(desk_id), memo_(memo), text_(text) {}

const BidirectionalBusinessHeader& QuoteStatusReportMessage::bidirectional_business_header() const { return bidirectional_business_header_; }
BidirectionalBusinessHeader& QuoteStatusReportMessage::bidirectional_business_header() { return bidirectional_business_header_; }
void QuoteStatusReportMessage::set_bidirectional_business_header(const BidirectionalBusinessHeader& value) { bidirectional_business_header_ = value; }

std::optional<QuoteRejectReason> QuoteStatusReportMessage::quote_reject_reason() const { return quote_reject_reason_; }
void QuoteStatusReportMessage::set_quote_reject_reason(std::optional<QuoteRejectReason> value) { quote_reject_reason_ = value; }

std::uint64_t QuoteStatusReportMessage::security_id() const { return security_id_; }
void QuoteStatusReportMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t QuoteStatusReportMessage::quote_req_id() const { return quote_req_id_; }
void QuoteStatusReportMessage::set_quote_req_id(std::uint64_t value) { quote_req_id_ = value; }

std::uint64_t QuoteStatusReportMessage::quote_id() const { return quote_id_; }
void QuoteStatusReportMessage::set_quote_id(std::uint64_t value) { quote_id_ = value; }

std::optional<std::uint32_t> QuoteStatusReportMessage::trade_id_optional() const { return trade_id_optional_; }
void QuoteStatusReportMessage::set_trade_id_optional(std::optional<std::uint32_t> value) { trade_id_optional_ = value; }

std::uint32_t QuoteStatusReportMessage::contra_broker() const { return contra_broker_; }
void QuoteStatusReportMessage::set_contra_broker(std::uint32_t value) { contra_broker_ = value; }

std::chrono::nanoseconds QuoteStatusReportMessage::transact_time() const { return transact_time_; }
void QuoteStatusReportMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

QuoteStatus QuoteStatusReportMessage::quote_status() const { return quote_status_; }
void QuoteStatusReportMessage::set_quote_status(QuoteStatus value) { quote_status_ = value; }

QuoteStatusResponseTo QuoteStatusReportMessage::quote_status_response_to() const { return quote_status_response_to_; }
void QuoteStatusReportMessage::set_quote_status_response_to(QuoteStatusResponseTo value) { quote_status_response_to_ = value; }

std::optional<std::uint32_t> QuoteStatusReportMessage::account() const { return account_; }
void QuoteStatusReportMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

SideOptional QuoteStatusReportMessage::side_optional() const { return side_optional_; }
void QuoteStatusReportMessage::set_side_optional(SideOptional value) { side_optional_ = value; }

SettlTypeOptional QuoteStatusReportMessage::settl_type_optional() const { return settl_type_optional_; }
void QuoteStatusReportMessage::set_settl_type_optional(SettlTypeOptional value) { settl_type_optional_ = value; }

std::optional<Decimal> QuoteStatusReportMessage::price_8_optional() const { return price_8_optional_; }
void QuoteStatusReportMessage::set_price_8_optional(std::optional<Decimal> value) { price_8_optional_ = value; }

std::uint64_t QuoteStatusReportMessage::order_qty() const { return order_qty_; }
void QuoteStatusReportMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

const std::string& QuoteStatusReportMessage::sender_location() const { return sender_location_; }
std::string& QuoteStatusReportMessage::sender_location() { return sender_location_; }
void QuoteStatusReportMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& QuoteStatusReportMessage::entering_trader() const { return entering_trader_; }
std::string& QuoteStatusReportMessage::entering_trader() { return entering_trader_; }
void QuoteStatusReportMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const std::string& QuoteStatusReportMessage::executing_trader() const { return executing_trader_; }
std::string& QuoteStatusReportMessage::executing_trader() { return executing_trader_; }
void QuoteStatusReportMessage::set_executing_trader(const std::string& value) { executing_trader_ = value; }

std::optional<Decimal> QuoteStatusReportMessage::fixed_rate_percentage_8_optional() const { return fixed_rate_percentage_8_optional_; }
void QuoteStatusReportMessage::set_fixed_rate_percentage_8_optional(std::optional<Decimal> value) { fixed_rate_percentage_8_optional_ = value; }

ExecuteUnderlyingTrade QuoteStatusReportMessage::execute_underlying_trade() const { return execute_underlying_trade_; }
void QuoteStatusReportMessage::set_execute_underlying_trade(ExecuteUnderlyingTrade value) { execute_underlying_trade_ = value; }

std::optional<std::uint16_t> QuoteStatusReportMessage::days_to_settlement_optional() const { return days_to_settlement_optional_; }
void QuoteStatusReportMessage::set_days_to_settlement_optional(std::optional<std::uint16_t> value) { days_to_settlement_optional_ = value; }

const DeskId& QuoteStatusReportMessage::desk_id() const { return desk_id_; }
DeskId& QuoteStatusReportMessage::desk_id() { return desk_id_; }
void QuoteStatusReportMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& QuoteStatusReportMessage::memo() const { return memo_; }
Memo& QuoteStatusReportMessage::memo() { return memo_; }
void QuoteStatusReportMessage::set_memo(const Memo& value) { memo_ = value; }

const Text& QuoteStatusReportMessage::text() const { return text_; }
Text& QuoteStatusReportMessage::text() { return text_; }
void QuoteStatusReportMessage::set_text(const Text& value) { text_ = value; }

MessageCode QuoteStatusReportMessage::type() const { return message_type; }

std::string_view QuoteStatusReportMessage::name() const { return "Quote Status Report Message"; }

std::size_t QuoteStatusReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += bidirectional_business_header_.decode(data + offset, length - offset);

    wire::require("QuoteStatusReportMessage", offset + 4, length);
    quote_reject_reason_ = wire::nullable_enum<QuoteRejectReason>(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    quote_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    quote_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 4, length);
    trade_id_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("QuoteStatusReportMessage", offset + 4, length);
    contra_broker_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 1, length);
    quote_status_ = static_cast<QuoteStatus>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("QuoteStatusReportMessage", offset + 1, length);
    quote_status_response_to_ = static_cast<QuoteStatusResponseTo>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteStatusReportMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("QuoteStatusReportMessage", offset + 1, length);
    side_optional_ = static_cast<SideOptional>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteStatusReportMessage", offset + 1, length);
    settl_type_optional_ = static_cast<SettlTypeOptional>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    price_8_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("QuoteStatusReportMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteStatusReportMessage", offset + 5, length);
    executing_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteStatusReportMessage", offset + 8, length);
    fixed_rate_percentage_8_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("QuoteStatusReportMessage", offset + 1, length);
    execute_underlying_trade_ = static_cast<ExecuteUnderlyingTrade>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteStatusReportMessage", offset + 2, length);
    days_to_settlement_optional_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    offset += text_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteStatusReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteStatusReportMessage", encoded_size(), capacity);

    offset += bidirectional_business_header_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, quote_reject_reason_ ? static_cast<std::uint32_t>(*quote_reject_reason_) : static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quote_req_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quote_id_));
    offset += 8;

    wire::write_u32_le(data + offset, trade_id_optional_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(contra_broker_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(quote_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(quote_status_response_to_));
    offset += 1;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_optional_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settl_type_optional_));
    offset += 1;

    wire::write_i64_le(data + offset, price_8_optional_ ? static_cast<std::int64_t>(price_8_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', executing_trader_);
    offset += 5;

    wire::write_i64_le(data + offset, fixed_rate_percentage_8_optional_ ? static_cast<std::int64_t>(fixed_rate_percentage_8_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(execute_underlying_trade_));
    offset += 1;

    wire::write_u16_le(data + offset, days_to_settlement_optional_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    offset += text_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteStatusReportMessage::encoded_size() const {
    return bidirectional_business_header_.encoded_size() + 4 + 8 + 8 + 8 + 4 + 4 + 8 + 1 + 1 + 4 + 1 + 1 + 8 + 8 + 10 + 5 + 5 + 8 + 1 + 2 + desk_id_.encoded_size() + memo_.encoded_size() + text_.encoded_size();
}

void QuoteStatusReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteStatusReportMessage::clone() const {
    return std::make_unique<QuoteStatusReportMessage>(*this);
}

void QuoteStatusReportMessage::print(std::ostream& out) const {
    out << "QuoteStatusReportMessage{";
    out << "bidirectional_business_header=";
    bidirectional_business_header_.print(out);
    out << ", quote_reject_reason=";
    print::optional(out, quote_reject_reason_);
    out << ", security_id=";
    out << security_id_;
    out << ", quote_req_id=";
    out << quote_req_id_;
    out << ", quote_id=";
    out << quote_id_;
    out << ", trade_id_optional=";
    print::optional(out, trade_id_optional_);
    out << ", contra_broker=";
    out << contra_broker_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", quote_status=";
    out << quote_status_;
    out << ", quote_status_response_to=";
    out << quote_status_response_to_;
    out << ", account=";
    print::optional(out, account_);
    out << ", side_optional=";
    out << side_optional_;
    out << ", settl_type_optional=";
    out << settl_type_optional_;
    out << ", price_8_optional=";
    print::optional(out, price_8_optional_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", executing_trader=";
    print::text(out, executing_trader_);
    out << ", fixed_rate_percentage_8_optional=";
    print::optional(out, fixed_rate_percentage_8_optional_);
    out << ", execute_underlying_trade=";
    out << execute_underlying_trade_;
    out << ", days_to_settlement_optional=";
    print::optional(out, days_to_settlement_optional_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << ", text=";
    text_.print(out);
    out << '}';
}

bool QuoteStatusReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteStatusReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteStatusReportMessage::operator==(const QuoteStatusReportMessage& other) const {
    return bidirectional_business_header_ == other.bidirectional_business_header_
        && quote_reject_reason_ == other.quote_reject_reason_
        && security_id_ == other.security_id_
        && quote_req_id_ == other.quote_req_id_
        && quote_id_ == other.quote_id_
        && trade_id_optional_ == other.trade_id_optional_
        && contra_broker_ == other.contra_broker_
        && transact_time_ == other.transact_time_
        && quote_status_ == other.quote_status_
        && quote_status_response_to_ == other.quote_status_response_to_
        && account_ == other.account_
        && side_optional_ == other.side_optional_
        && settl_type_optional_ == other.settl_type_optional_
        && price_8_optional_ == other.price_8_optional_
        && order_qty_ == other.order_qty_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && executing_trader_ == other.executing_trader_
        && fixed_rate_percentage_8_optional_ == other.fixed_rate_percentage_8_optional_
        && execute_underlying_trade_ == other.execute_underlying_trade_
        && days_to_settlement_optional_ == other.days_to_settlement_optional_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_
        && text_ == other.text_;
}

bool QuoteStatusReportMessage::operator!=(const QuoteStatusReportMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
