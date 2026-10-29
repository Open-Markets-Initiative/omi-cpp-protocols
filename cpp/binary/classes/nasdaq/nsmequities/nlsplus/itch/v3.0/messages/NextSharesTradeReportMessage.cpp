#include "NextSharesTradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

NextSharesTradeReportMessage::NextSharesTradeReportMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& next_shares_symbol, SecurityClass security_class, const std::string& trade_control_number, Decimal proxy_price, std::uint32_t trade_size, Decimal nav_offset_amount, const SaleConditionModifier& sale_condition_modifier, std::uint64_t consolidated_volume)
  : originating_market_center_identifier_(originating_market_center_identifier), next_shares_symbol_(next_shares_symbol), security_class_(security_class), trade_control_number_(trade_control_number), proxy_price_(proxy_price), trade_size_(trade_size), nav_offset_amount_(nav_offset_amount), sale_condition_modifier_(sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

OriginatingMarketCenterIdentifier NextSharesTradeReportMessage::originating_market_center_identifier() const { return originating_market_center_identifier_; }
void NextSharesTradeReportMessage::set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value) { originating_market_center_identifier_ = value; }

const std::string& NextSharesTradeReportMessage::next_shares_symbol() const { return next_shares_symbol_; }
std::string& NextSharesTradeReportMessage::next_shares_symbol() { return next_shares_symbol_; }
void NextSharesTradeReportMessage::set_next_shares_symbol(const std::string& value) { next_shares_symbol_ = value; }

SecurityClass NextSharesTradeReportMessage::security_class() const { return security_class_; }
void NextSharesTradeReportMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& NextSharesTradeReportMessage::trade_control_number() const { return trade_control_number_; }
std::string& NextSharesTradeReportMessage::trade_control_number() { return trade_control_number_; }
void NextSharesTradeReportMessage::set_trade_control_number(const std::string& value) { trade_control_number_ = value; }

Decimal NextSharesTradeReportMessage::proxy_price() const { return proxy_price_; }
void NextSharesTradeReportMessage::set_proxy_price(Decimal value) { proxy_price_ = value; }

std::uint32_t NextSharesTradeReportMessage::trade_size() const { return trade_size_; }
void NextSharesTradeReportMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

Decimal NextSharesTradeReportMessage::nav_offset_amount() const { return nav_offset_amount_; }
void NextSharesTradeReportMessage::set_nav_offset_amount(Decimal value) { nav_offset_amount_ = value; }

const SaleConditionModifier& NextSharesTradeReportMessage::sale_condition_modifier() const { return sale_condition_modifier_; }
SaleConditionModifier& NextSharesTradeReportMessage::sale_condition_modifier() { return sale_condition_modifier_; }
void NextSharesTradeReportMessage::set_sale_condition_modifier(const SaleConditionModifier& value) { sale_condition_modifier_ = value; }

std::uint64_t NextSharesTradeReportMessage::consolidated_volume() const { return consolidated_volume_; }
void NextSharesTradeReportMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode NextSharesTradeReportMessage::type() const { return message_type; }

std::string_view NextSharesTradeReportMessage::name() const { return "Next Shares Trade Report Message"; }

std::size_t NextSharesTradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NextSharesTradeReportMessage", wire_size, length);

    originating_market_center_identifier_ = static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(data + offset));
    offset += 1;

    next_shares_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    proxy_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    nav_offset_amount_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    offset += sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t NextSharesTradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NextSharesTradeReportMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(originating_market_center_identifier_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', next_shares_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_text(data + offset, 10, ' ', trade_control_number_);
    offset += 10;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(proxy_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nav_offset_amount_.mantissa()));
    offset += 4;

    offset += sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t NextSharesTradeReportMessage::encoded_size() const {
    return wire_size;
}

void NextSharesTradeReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NextSharesTradeReportMessage::clone() const {
    return std::make_unique<NextSharesTradeReportMessage>(*this);
}

void NextSharesTradeReportMessage::print(std::ostream& out) const {
    out << "NextSharesTradeReportMessage{";
    out << "originating_market_center_identifier=";
    out << originating_market_center_identifier_;
    out << ", next_shares_symbol=";
    print::text(out, next_shares_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", trade_control_number=";
    print::text(out, trade_control_number_);
    out << ", proxy_price=";
    out << proxy_price_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", nav_offset_amount=";
    out << nav_offset_amount_;
    out << ", sale_condition_modifier=";
    sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool NextSharesTradeReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NextSharesTradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NextSharesTradeReportMessage::operator==(const NextSharesTradeReportMessage& other) const {
    return originating_market_center_identifier_ == other.originating_market_center_identifier_
        && next_shares_symbol_ == other.next_shares_symbol_
        && security_class_ == other.security_class_
        && trade_control_number_ == other.trade_control_number_
        && proxy_price_ == other.proxy_price_
        && trade_size_ == other.trade_size_
        && nav_offset_amount_ == other.nav_offset_amount_
        && sale_condition_modifier_ == other.sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool NextSharesTradeReportMessage::operator!=(const NextSharesTradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
