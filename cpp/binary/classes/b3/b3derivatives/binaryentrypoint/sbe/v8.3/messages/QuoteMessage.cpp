#include "QuoteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

QuoteMessage::QuoteMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::uint64_t security_id, std::uint64_t quote_req_id, std::uint64_t quote_id, std::chrono::nanoseconds transact_time, std::optional<Decimal> price_8_optional, std::uint64_t order_qty, Side side, SettlType settl_type, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, Decimal fixed_rate_percentage_8, ExecuteUnderlyingTrade execute_underlying_trade, std::uint16_t days_to_settlement, std::optional<std::uint32_t> trading_sub_account, const DeskId& desk_id, const Memo& memo)
  : bidirectional_business_header_(bidirectional_business_header), security_id_(security_id), quote_req_id_(quote_req_id), quote_id_(quote_id), transact_time_(transact_time), price_8_optional_(price_8_optional), order_qty_(order_qty), side_(side), settl_type_(settl_type), account_(account), sender_location_(sender_location), entering_trader_(entering_trader), executing_trader_(executing_trader), fixed_rate_percentage_8_(fixed_rate_percentage_8), execute_underlying_trade_(execute_underlying_trade), days_to_settlement_(days_to_settlement), trading_sub_account_(trading_sub_account), desk_id_(desk_id), memo_(memo) {}

const BidirectionalBusinessHeader& QuoteMessage::bidirectional_business_header() const { return bidirectional_business_header_; }
BidirectionalBusinessHeader& QuoteMessage::bidirectional_business_header() { return bidirectional_business_header_; }
void QuoteMessage::set_bidirectional_business_header(const BidirectionalBusinessHeader& value) { bidirectional_business_header_ = value; }

std::uint64_t QuoteMessage::security_id() const { return security_id_; }
void QuoteMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t QuoteMessage::quote_req_id() const { return quote_req_id_; }
void QuoteMessage::set_quote_req_id(std::uint64_t value) { quote_req_id_ = value; }

std::uint64_t QuoteMessage::quote_id() const { return quote_id_; }
void QuoteMessage::set_quote_id(std::uint64_t value) { quote_id_ = value; }

std::chrono::nanoseconds QuoteMessage::transact_time() const { return transact_time_; }
void QuoteMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::optional<Decimal> QuoteMessage::price_8_optional() const { return price_8_optional_; }
void QuoteMessage::set_price_8_optional(std::optional<Decimal> value) { price_8_optional_ = value; }

std::uint64_t QuoteMessage::order_qty() const { return order_qty_; }
void QuoteMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

Side QuoteMessage::side() const { return side_; }
void QuoteMessage::set_side(Side value) { side_ = value; }

SettlType QuoteMessage::settl_type() const { return settl_type_; }
void QuoteMessage::set_settl_type(SettlType value) { settl_type_ = value; }

std::optional<std::uint32_t> QuoteMessage::account() const { return account_; }
void QuoteMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

const std::string& QuoteMessage::sender_location() const { return sender_location_; }
std::string& QuoteMessage::sender_location() { return sender_location_; }
void QuoteMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& QuoteMessage::entering_trader() const { return entering_trader_; }
std::string& QuoteMessage::entering_trader() { return entering_trader_; }
void QuoteMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

const std::string& QuoteMessage::executing_trader() const { return executing_trader_; }
std::string& QuoteMessage::executing_trader() { return executing_trader_; }
void QuoteMessage::set_executing_trader(const std::string& value) { executing_trader_ = value; }

Decimal QuoteMessage::fixed_rate_percentage_8() const { return fixed_rate_percentage_8_; }
void QuoteMessage::set_fixed_rate_percentage_8(Decimal value) { fixed_rate_percentage_8_ = value; }

ExecuteUnderlyingTrade QuoteMessage::execute_underlying_trade() const { return execute_underlying_trade_; }
void QuoteMessage::set_execute_underlying_trade(ExecuteUnderlyingTrade value) { execute_underlying_trade_ = value; }

std::uint16_t QuoteMessage::days_to_settlement() const { return days_to_settlement_; }
void QuoteMessage::set_days_to_settlement(std::uint16_t value) { days_to_settlement_ = value; }

std::optional<std::uint32_t> QuoteMessage::trading_sub_account() const { return trading_sub_account_; }
void QuoteMessage::set_trading_sub_account(std::optional<std::uint32_t> value) { trading_sub_account_ = value; }

const DeskId& QuoteMessage::desk_id() const { return desk_id_; }
DeskId& QuoteMessage::desk_id() { return desk_id_; }
void QuoteMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& QuoteMessage::memo() const { return memo_; }
Memo& QuoteMessage::memo() { return memo_; }
void QuoteMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode QuoteMessage::type() const { return message_type; }

std::string_view QuoteMessage::name() const { return "Quote Message"; }

std::size_t QuoteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += bidirectional_business_header_.decode(data + offset, length - offset);

    wire::require("QuoteMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteMessage", offset + 8, length);
    quote_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteMessage", offset + 8, length);
    quote_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("QuoteMessage", offset + 8, length);
    price_8_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("QuoteMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("QuoteMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteMessage", offset + 1, length);
    settl_type_ = static_cast<SettlType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("QuoteMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("QuoteMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteMessage", offset + 5, length);
    executing_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("QuoteMessage", offset + 8, length);
    fixed_rate_percentage_8_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    wire::require("QuoteMessage", offset + 1, length);
    execute_underlying_trade_ = static_cast<ExecuteUnderlyingTrade>(wire::read_char(data + offset));
    offset += 1;

    wire::require("QuoteMessage", offset + 2, length);
    days_to_settlement_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("QuoteMessage", offset + 4, length);
    trading_sub_account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteMessage", encoded_size(), capacity);

    offset += bidirectional_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quote_req_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quote_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, price_8_optional_ ? static_cast<std::int64_t>(price_8_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settl_type_));
    offset += 1;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', executing_trader_);
    offset += 5;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(fixed_rate_percentage_8_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(execute_underlying_trade_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(days_to_settlement_));
    offset += 2;

    wire::write_u32_le(data + offset, trading_sub_account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t QuoteMessage::encoded_size() const {
    return bidirectional_business_header_.encoded_size() + 8 + 8 + 8 + 8 + 8 + 8 + 1 + 1 + 4 + 10 + 5 + 5 + 8 + 1 + 2 + 4 + desk_id_.encoded_size() + memo_.encoded_size();
}

void QuoteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteMessage::clone() const {
    return std::make_unique<QuoteMessage>(*this);
}

void QuoteMessage::print(std::ostream& out) const {
    out << "QuoteMessage{";
    out << "bidirectional_business_header=";
    bidirectional_business_header_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", quote_req_id=";
    out << quote_req_id_;
    out << ", quote_id=";
    out << quote_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", price_8_optional=";
    print::optional(out, price_8_optional_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", side=";
    out << side_;
    out << ", settl_type=";
    out << settl_type_;
    out << ", account=";
    print::optional(out, account_);
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", executing_trader=";
    print::text(out, executing_trader_);
    out << ", fixed_rate_percentage_8=";
    out << fixed_rate_percentage_8_;
    out << ", execute_underlying_trade=";
    out << execute_underlying_trade_;
    out << ", days_to_settlement=";
    out << days_to_settlement_;
    out << ", trading_sub_account=";
    print::optional(out, trading_sub_account_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool QuoteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteMessage::operator==(const QuoteMessage& other) const {
    return bidirectional_business_header_ == other.bidirectional_business_header_
        && security_id_ == other.security_id_
        && quote_req_id_ == other.quote_req_id_
        && quote_id_ == other.quote_id_
        && transact_time_ == other.transact_time_
        && price_8_optional_ == other.price_8_optional_
        && order_qty_ == other.order_qty_
        && side_ == other.side_
        && settl_type_ == other.settl_type_
        && account_ == other.account_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && executing_trader_ == other.executing_trader_
        && fixed_rate_percentage_8_ == other.fixed_rate_percentage_8_
        && execute_underlying_trade_ == other.execute_underlying_trade_
        && days_to_settlement_ == other.days_to_settlement_
        && trading_sub_account_ == other.trading_sub_account_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool QuoteMessage::operator!=(const QuoteMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
