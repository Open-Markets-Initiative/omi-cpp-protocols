#include "QuoteRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

QuoteRequestMessage::QuoteRequestMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::uint64_t security_id, std::uint64_t quote_req_id, std::optional<std::uint64_t> quote_id_optional, std::optional<std::uint32_t> trade_id_optional, std::uint32_t contra_broker, std::chrono::nanoseconds transact_time, Decimal price_8, SettlType settl_type, ExecuteUnderlyingTrade execute_underlying_trade, std::uint64_t order_qty, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, Decimal fixed_rate_percentage_8, std::uint16_t days_to_settlement, const SidesGroups& sides_groups, const DeskId& desk_id, const Memo& memo)
  : bidirectional_business_header_(bidirectional_business_header), security_id_(security_id), quote_req_id_(quote_req_id), quote_id_optional_(quote_id_optional), trade_id_optional_(trade_id_optional), contra_broker_(contra_broker), transact_time_(transact_time), price_8_(price_8), settl_type_(settl_type), execute_underlying_trade_(execute_underlying_trade), order_qty_(order_qty), sender_location_(sender_location), entering_trader_(entering_trader), executing_trader_(executing_trader), fixed_rate_percentage_8_(fixed_rate_percentage_8), days_to_settlement_(days_to_settlement), sides_groups_(sides_groups), desk_id_(desk_id), memo_(memo) {}

const BidirectionalBusinessHeader& QuoteRequestMessage::bidirectional_business_header() const { return bidirectional_business_header_; }
BidirectionalBusinessHeader& QuoteRequestMessage::bidirectional_business_header() { return bidirectional_business_header_; }
void QuoteRequestMessage::set_bidirectional_business_header(const BidirectionalBusinessHeader& value) { bidirectional_business_header_ = value; }

std::uint64_t QuoteRequestMessage::security_id() const { return security_id_; }
void QuoteRequestMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t QuoteRequestMessage::quote_req_id() const { return quote_req_id_; }
void QuoteRequestMessage::set_quote_req_id(std::uint64_t value) { quote_req_id_ = value; }

std::optional<std::uint64_t> QuoteRequestMessage::quote_id_optional() const { return quote_id_optional_; }
void QuoteRequestMessage::set_quote_id_optional(std::optional<std::uint64_t> value) { quote_id_optional_ = value; }

std::optional<std::uint32_t> QuoteRequestMessage::trade_id_optional() const { return trade_id_optional_; }
void QuoteRequestMessage::set_trade_id_optional(std::optional<std::uint32_t> value) { trade_id_optional_ = value; }

std::uint32_t QuoteRequestMessage::contra_broker() const { return contra_broker_; }
void QuoteRequestMessage::set_contra_broker(std::uint32_t value) { contra_broker_ = value; }

std::chrono::nanoseconds QuoteRequestMessage::transact_time() const { return transact_time_; }
void QuoteRequestMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

Decimal QuoteRequestMessage::price_8() const { return price_8_; }
void QuoteRequestMessage::set_price_8(Decimal value) { price_8_ = value; }

SettlType QuoteRequestMessage::settl_type() const { return settl_type_; }
void QuoteRequestMessage::set_settl_type(SettlType value) { settl_type_ = value; }

ExecuteUnderlyingTrade QuoteRequestMessage::execute_underlying_trade() const { return execute_underlying_trade_; }
void QuoteRequestMessage::set_execute_underlying_trade(ExecuteUnderlyingTrade value) { execute_underlying_trade_ = value; }

std::uint64_t QuoteRequestMessage::order_qty() const { return order_qty_; }
void QuoteRequestMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

const std::string& QuoteRequestMessage::sender_location() const { return sender_location_; }
std::string& QuoteRequestMessage::sender_location() { return sender_location_; }
void QuoteRequestMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& QuoteRequestMessage::entering_trader() const { return entering_trader_; }
std::string& QuoteRequestMessage::entering_trader() { return entering_trader_; }
void QuoteRequestMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const std::string& QuoteRequestMessage::executing_trader() const { return executing_trader_; }
std::string& QuoteRequestMessage::executing_trader() { return executing_trader_; }
void QuoteRequestMessage::set_executing_trader(const std::string& value) { executing_trader_ = value; }

Decimal QuoteRequestMessage::fixed_rate_percentage_8() const { return fixed_rate_percentage_8_; }
void QuoteRequestMessage::set_fixed_rate_percentage_8(Decimal value) { fixed_rate_percentage_8_ = value; }

std::uint16_t QuoteRequestMessage::days_to_settlement() const { return days_to_settlement_; }
void QuoteRequestMessage::set_days_to_settlement(std::uint16_t value) { days_to_settlement_ = value; }

const SidesGroups& QuoteRequestMessage::sides_groups() const { return sides_groups_; }
SidesGroups& QuoteRequestMessage::sides_groups() { return sides_groups_; }
void QuoteRequestMessage::set_sides_groups(const SidesGroups& value) { sides_groups_ = value; }

const DeskId& QuoteRequestMessage::desk_id() const { return desk_id_; }
DeskId& QuoteRequestMessage::desk_id() { return desk_id_; }
void QuoteRequestMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& QuoteRequestMessage::memo() const { return memo_; }
Memo& QuoteRequestMessage::memo() { return memo_; }
void QuoteRequestMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode QuoteRequestMessage::type() const { return message_type; }

std::string_view QuoteRequestMessage::name() const { return "Quote Request Message"; }

std::size_t QuoteRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += bidirectional_business_header_.decode(data + offset, length - offset);

    wire::require("QuoteRequestMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 8, length);
    quote_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 8, length);
    quote_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 4, length);
    trade_id_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("QuoteRequestMessage", offset + 4, length);
    contra_broker_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("QuoteRequestMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 8, length);
    price_8_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 1, length);
    settl_type_ = static_cast<SettlType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteRequestMessage", offset + 1, length);
    execute_underlying_trade_ = static_cast<ExecuteUnderlyingTrade>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteRequestMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("QuoteRequestMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteRequestMessage", offset + 5, length);
    executing_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteRequestMessage", offset + 8, length);
    fixed_rate_percentage_8_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    wire::require("QuoteRequestMessage", offset + 2, length);
    days_to_settlement_ = wire::read_u16_le(data + offset);
    offset += 2;

    offset += sides_groups_.decode(data + offset, length - offset);

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteRequestMessage", encoded_size(), capacity);

    offset += bidirectional_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quote_req_id_));
    offset += 8;

    wire::write_u64_le(data + offset, quote_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, trade_id_optional_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(contra_broker_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_8_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(settl_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(execute_underlying_trade_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', executing_trader_);
    offset += 5;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(fixed_rate_percentage_8_.mantissa()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(days_to_settlement_));
    offset += 2;

    offset += sides_groups_.encode(data + offset, capacity - offset);

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteRequestMessage::encoded_size() const {
    return bidirectional_business_header_.encoded_size() + 8 + 8 + 8 + 4 + 4 + 8 + 8 + 1 + 1 + 8 + 10 + 5 + 5 + 8 + 2 + sides_groups_.encoded_size() + desk_id_.encoded_size() + memo_.encoded_size();
}

void QuoteRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteRequestMessage::clone() const {
    return std::make_unique<QuoteRequestMessage>(*this);
}

void QuoteRequestMessage::print(std::ostream& out) const {
    out << "QuoteRequestMessage{";
    out << "bidirectional_business_header=";
    bidirectional_business_header_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", quote_req_id=";
    out << quote_req_id_;
    out << ", quote_id_optional=";
    print::optional(out, quote_id_optional_);
    out << ", trade_id_optional=";
    print::optional(out, trade_id_optional_);
    out << ", contra_broker=";
    out << contra_broker_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", price_8=";
    out << price_8_;
    out << ", settl_type=";
    out << settl_type_;
    out << ", execute_underlying_trade=";
    out << execute_underlying_trade_;
    out << ", order_qty=";
    out << order_qty_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", executing_trader=";
    print::text(out, executing_trader_);
    out << ", fixed_rate_percentage_8=";
    out << fixed_rate_percentage_8_;
    out << ", days_to_settlement=";
    out << days_to_settlement_;
    out << ", sides_groups=";
    sides_groups_.print(out);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool QuoteRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteRequestMessage::operator==(const QuoteRequestMessage& other) const {
    return bidirectional_business_header_ == other.bidirectional_business_header_
        && security_id_ == other.security_id_
        && quote_req_id_ == other.quote_req_id_
        && quote_id_optional_ == other.quote_id_optional_
        && trade_id_optional_ == other.trade_id_optional_
        && contra_broker_ == other.contra_broker_
        && transact_time_ == other.transact_time_
        && price_8_ == other.price_8_
        && settl_type_ == other.settl_type_
        && execute_underlying_trade_ == other.execute_underlying_trade_
        && order_qty_ == other.order_qty_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && executing_trader_ == other.executing_trader_
        && fixed_rate_percentage_8_ == other.fixed_rate_percentage_8_
        && days_to_settlement_ == other.days_to_settlement_
        && sides_groups_ == other.sides_groups_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool QuoteRequestMessage::operator!=(const QuoteRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
