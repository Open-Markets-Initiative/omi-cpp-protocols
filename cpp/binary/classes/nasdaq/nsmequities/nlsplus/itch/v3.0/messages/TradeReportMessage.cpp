#include "TradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

TradeReportMessage::TradeReportMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& issue_symbol, SecurityClass security_class, const std::string& trade_control_number, Decimal trade_price, std::uint32_t trade_size, const SaleConditionModifier& sale_condition_modifier, std::uint64_t consolidated_volume)
  : originating_market_center_identifier_(originating_market_center_identifier), issue_symbol_(issue_symbol), security_class_(security_class), trade_control_number_(trade_control_number), trade_price_(trade_price), trade_size_(trade_size), sale_condition_modifier_(sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

OriginatingMarketCenterIdentifier TradeReportMessage::originating_market_center_identifier() const { return originating_market_center_identifier_; }
void TradeReportMessage::set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value) { originating_market_center_identifier_ = value; }

const std::string& TradeReportMessage::issue_symbol() const { return issue_symbol_; }
std::string& TradeReportMessage::issue_symbol() { return issue_symbol_; }
void TradeReportMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass TradeReportMessage::security_class() const { return security_class_; }
void TradeReportMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& TradeReportMessage::trade_control_number() const { return trade_control_number_; }
std::string& TradeReportMessage::trade_control_number() { return trade_control_number_; }
void TradeReportMessage::set_trade_control_number(const std::string& value) { trade_control_number_ = value; }

Decimal TradeReportMessage::trade_price() const { return trade_price_; }
void TradeReportMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t TradeReportMessage::trade_size() const { return trade_size_; }
void TradeReportMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

const SaleConditionModifier& TradeReportMessage::sale_condition_modifier() const { return sale_condition_modifier_; }
SaleConditionModifier& TradeReportMessage::sale_condition_modifier() { return sale_condition_modifier_; }
void TradeReportMessage::set_sale_condition_modifier(const SaleConditionModifier& value) { sale_condition_modifier_ = value; }

std::uint64_t TradeReportMessage::consolidated_volume() const { return consolidated_volume_; }
void TradeReportMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode TradeReportMessage::type() const { return message_type; }

std::string_view TradeReportMessage::name() const { return "Trade Report Message"; }

std::size_t TradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReportMessage", wire_size, length);

    originating_market_center_identifier_ = static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(data + offset));
    offset += 1;

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReportMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(originating_market_center_identifier_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_text(data + offset, 10, ' ', trade_control_number_);
    offset += 10;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    offset += sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t TradeReportMessage::encoded_size() const {
    return wire_size;
}

void TradeReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeReportMessage::clone() const {
    return std::make_unique<TradeReportMessage>(*this);
}

void TradeReportMessage::print(std::ostream& out) const {
    out << "TradeReportMessage{";
    out << "originating_market_center_identifier=";
    out << originating_market_center_identifier_;
    out << ", issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", trade_control_number=";
    print::text(out, trade_control_number_);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", sale_condition_modifier=";
    sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool TradeReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReportMessage::operator==(const TradeReportMessage& other) const {
    return originating_market_center_identifier_ == other.originating_market_center_identifier_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && trade_control_number_ == other.trade_control_number_
        && trade_price_ == other.trade_price_
        && trade_size_ == other.trade_size_
        && sale_condition_modifier_ == other.sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool TradeReportMessage::operator!=(const TradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
