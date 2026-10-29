#include "LongFormTradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

LongFormTradeReportMessage::LongFormTradeReportMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& issue_symbol, SecurityClass security_class, const std::string& trade_control_number, Decimal trade_price_long, std::uint32_t trade_size, const SaleConditionModifier& sale_condition_modifier, std::uint64_t consolidated_volume)
  : originating_market_center_identifier_(originating_market_center_identifier), issue_symbol_(issue_symbol), security_class_(security_class), trade_control_number_(trade_control_number), trade_price_long_(trade_price_long), trade_size_(trade_size), sale_condition_modifier_(sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

OriginatingMarketCenterIdentifier LongFormTradeReportMessage::originating_market_center_identifier() const { return originating_market_center_identifier_; }
void LongFormTradeReportMessage::set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value) { originating_market_center_identifier_ = value; }

const std::string& LongFormTradeReportMessage::issue_symbol() const { return issue_symbol_; }
std::string& LongFormTradeReportMessage::issue_symbol() { return issue_symbol_; }
void LongFormTradeReportMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass LongFormTradeReportMessage::security_class() const { return security_class_; }
void LongFormTradeReportMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& LongFormTradeReportMessage::trade_control_number() const { return trade_control_number_; }
std::string& LongFormTradeReportMessage::trade_control_number() { return trade_control_number_; }
void LongFormTradeReportMessage::set_trade_control_number(const std::string& value) { trade_control_number_ = value; }

Decimal LongFormTradeReportMessage::trade_price_long() const { return trade_price_long_; }
void LongFormTradeReportMessage::set_trade_price_long(Decimal value) { trade_price_long_ = value; }

std::uint32_t LongFormTradeReportMessage::trade_size() const { return trade_size_; }
void LongFormTradeReportMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

const SaleConditionModifier& LongFormTradeReportMessage::sale_condition_modifier() const { return sale_condition_modifier_; }
SaleConditionModifier& LongFormTradeReportMessage::sale_condition_modifier() { return sale_condition_modifier_; }
void LongFormTradeReportMessage::set_sale_condition_modifier(const SaleConditionModifier& value) { sale_condition_modifier_ = value; }

std::uint64_t LongFormTradeReportMessage::consolidated_volume() const { return consolidated_volume_; }
void LongFormTradeReportMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode LongFormTradeReportMessage::type() const { return message_type; }

std::string_view LongFormTradeReportMessage::name() const { return "Long Form Trade Report Message"; }

std::size_t LongFormTradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LongFormTradeReportMessage", wire_size, length);

    originating_market_center_identifier_ = static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(data + offset));
    offset += 1;

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    trade_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t LongFormTradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongFormTradeReportMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(originating_market_center_identifier_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_text(data + offset, 10, ' ', trade_control_number_);
    offset += 10;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_long_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    offset += sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t LongFormTradeReportMessage::encoded_size() const {
    return wire_size;
}

void LongFormTradeReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LongFormTradeReportMessage::clone() const {
    return std::make_unique<LongFormTradeReportMessage>(*this);
}

void LongFormTradeReportMessage::print(std::ostream& out) const {
    out << "LongFormTradeReportMessage{";
    out << "originating_market_center_identifier=";
    out << originating_market_center_identifier_;
    out << ", issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", trade_control_number=";
    print::text(out, trade_control_number_);
    out << ", trade_price_long=";
    out << trade_price_long_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", sale_condition_modifier=";
    sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool LongFormTradeReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LongFormTradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongFormTradeReportMessage::operator==(const LongFormTradeReportMessage& other) const {
    return originating_market_center_identifier_ == other.originating_market_center_identifier_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && trade_control_number_ == other.trade_control_number_
        && trade_price_long_ == other.trade_price_long_
        && trade_size_ == other.trade_size_
        && sale_condition_modifier_ == other.sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool LongFormTradeReportMessage::operator!=(const LongFormTradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
