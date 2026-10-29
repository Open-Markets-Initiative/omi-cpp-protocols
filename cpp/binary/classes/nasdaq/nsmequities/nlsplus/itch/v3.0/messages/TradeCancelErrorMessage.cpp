#include "TradeCancelErrorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

TradeCancelErrorMessage::TradeCancelErrorMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& issue_symbol, SecurityClass security_class, const std::string& original_trade_control_number, Decimal original_trade_price, std::uint32_t original_trade_size, const OriginalSaleConditionModifier& original_sale_condition_modifier, std::uint64_t consolidated_volume)
  : originating_market_center_identifier_(originating_market_center_identifier), issue_symbol_(issue_symbol), security_class_(security_class), original_trade_control_number_(original_trade_control_number), original_trade_price_(original_trade_price), original_trade_size_(original_trade_size), original_sale_condition_modifier_(original_sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

OriginatingMarketCenterIdentifier TradeCancelErrorMessage::originating_market_center_identifier() const { return originating_market_center_identifier_; }
void TradeCancelErrorMessage::set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value) { originating_market_center_identifier_ = value; }

const std::string& TradeCancelErrorMessage::issue_symbol() const { return issue_symbol_; }
std::string& TradeCancelErrorMessage::issue_symbol() { return issue_symbol_; }
void TradeCancelErrorMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass TradeCancelErrorMessage::security_class() const { return security_class_; }
void TradeCancelErrorMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& TradeCancelErrorMessage::original_trade_control_number() const { return original_trade_control_number_; }
std::string& TradeCancelErrorMessage::original_trade_control_number() { return original_trade_control_number_; }
void TradeCancelErrorMessage::set_original_trade_control_number(const std::string& value) { original_trade_control_number_ = value; }

Decimal TradeCancelErrorMessage::original_trade_price() const { return original_trade_price_; }
void TradeCancelErrorMessage::set_original_trade_price(Decimal value) { original_trade_price_ = value; }

std::uint32_t TradeCancelErrorMessage::original_trade_size() const { return original_trade_size_; }
void TradeCancelErrorMessage::set_original_trade_size(std::uint32_t value) { original_trade_size_ = value; }

const OriginalSaleConditionModifier& TradeCancelErrorMessage::original_sale_condition_modifier() const { return original_sale_condition_modifier_; }
OriginalSaleConditionModifier& TradeCancelErrorMessage::original_sale_condition_modifier() { return original_sale_condition_modifier_; }
void TradeCancelErrorMessage::set_original_sale_condition_modifier(const OriginalSaleConditionModifier& value) { original_sale_condition_modifier_ = value; }

std::uint64_t TradeCancelErrorMessage::consolidated_volume() const { return consolidated_volume_; }
void TradeCancelErrorMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode TradeCancelErrorMessage::type() const { return message_type; }

std::string_view TradeCancelErrorMessage::name() const { return "Trade Cancel Error Message"; }

std::size_t TradeCancelErrorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelErrorMessage", wire_size, length);

    originating_market_center_identifier_ = static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(data + offset));
    offset += 1;

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    original_trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    original_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    original_trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += original_sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeCancelErrorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelErrorMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(originating_market_center_identifier_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_text(data + offset, 10, ' ', original_trade_control_number_);
    offset += 10;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_trade_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_trade_size_));
    offset += 4;

    offset += original_sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t TradeCancelErrorMessage::encoded_size() const {
    return wire_size;
}

void TradeCancelErrorMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeCancelErrorMessage::clone() const {
    return std::make_unique<TradeCancelErrorMessage>(*this);
}

void TradeCancelErrorMessage::print(std::ostream& out) const {
    out << "TradeCancelErrorMessage{";
    out << "originating_market_center_identifier=";
    out << originating_market_center_identifier_;
    out << ", issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", original_trade_control_number=";
    print::text(out, original_trade_control_number_);
    out << ", original_trade_price=";
    out << original_trade_price_;
    out << ", original_trade_size=";
    out << original_trade_size_;
    out << ", original_sale_condition_modifier=";
    original_sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool TradeCancelErrorMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeCancelErrorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelErrorMessage::operator==(const TradeCancelErrorMessage& other) const {
    return originating_market_center_identifier_ == other.originating_market_center_identifier_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && original_trade_control_number_ == other.original_trade_control_number_
        && original_trade_price_ == other.original_trade_price_
        && original_trade_size_ == other.original_trade_size_
        && original_sale_condition_modifier_ == other.original_sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool TradeCancelErrorMessage::operator!=(const TradeCancelErrorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
