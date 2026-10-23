#include "SettlementMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

SettlementMessage::SettlementMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t trade_date, Decimal settlement_price, Issue issue)
  : time_offset_(time_offset), symbol_(symbol), trade_date_(trade_date), settlement_price_(settlement_price), issue_(issue) {}

std::chrono::nanoseconds SettlementMessage::time_offset() const { return time_offset_; }
void SettlementMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& SettlementMessage::symbol() const { return symbol_; }
std::string& SettlementMessage::symbol() { return symbol_; }
void SettlementMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t SettlementMessage::trade_date() const { return trade_date_; }
void SettlementMessage::set_trade_date(std::uint32_t value) { trade_date_ = value; }

Decimal SettlementMessage::settlement_price() const { return settlement_price_; }
void SettlementMessage::set_settlement_price(Decimal value) { settlement_price_ = value; }

Issue SettlementMessage::issue() const { return issue_; }
void SettlementMessage::set_issue(Issue value) { issue_ = value; }

MessageCode SettlementMessage::type() const { return message_type; }

std::string_view SettlementMessage::name() const { return "Settlement Message"; }

std::size_t SettlementMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SettlementMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    trade_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    settlement_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    issue_ = static_cast<Issue>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SettlementMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SettlementMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_date_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(settlement_price_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(issue_));
    offset += 1;

    return offset;
}

std::size_t SettlementMessage::encoded_size() const {
    return wire_size;
}

void SettlementMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SettlementMessage::clone() const {
    return std::make_unique<SettlementMessage>(*this);
}

void SettlementMessage::print(std::ostream& out) const {
    out << "SettlementMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", settlement_price=";
    out << settlement_price_;
    out << ", issue=";
    out << issue_;
    out << '}';
}

bool SettlementMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SettlementMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SettlementMessage::operator==(const SettlementMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && trade_date_ == other.trade_date_
        && settlement_price_ == other.settlement_price_
        && issue_ == other.issue_;
}

bool SettlementMessage::operator!=(const SettlementMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
