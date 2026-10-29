#include "LongFormTradeCancelErrorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

LongFormTradeCancelErrorMessage::LongFormTradeCancelErrorMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& issue_symbol, SecurityClass security_class, const std::string& original_trade_control_number, Decimal original_trade_price_long, std::uint32_t original_trade_size, const OriginalSaleConditionModifier& original_sale_condition_modifier, std::uint64_t consolidated_volume)
  : originating_market_center_identifier_(originating_market_center_identifier), issue_symbol_(issue_symbol), security_class_(security_class), original_trade_control_number_(original_trade_control_number), original_trade_price_long_(original_trade_price_long), original_trade_size_(original_trade_size), original_sale_condition_modifier_(original_sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

OriginatingMarketCenterIdentifier LongFormTradeCancelErrorMessage::originating_market_center_identifier() const { return originating_market_center_identifier_; }
void LongFormTradeCancelErrorMessage::set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value) { originating_market_center_identifier_ = value; }

const std::string& LongFormTradeCancelErrorMessage::issue_symbol() const { return issue_symbol_; }
std::string& LongFormTradeCancelErrorMessage::issue_symbol() { return issue_symbol_; }
void LongFormTradeCancelErrorMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass LongFormTradeCancelErrorMessage::security_class() const { return security_class_; }
void LongFormTradeCancelErrorMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& LongFormTradeCancelErrorMessage::original_trade_control_number() const { return original_trade_control_number_; }
std::string& LongFormTradeCancelErrorMessage::original_trade_control_number() { return original_trade_control_number_; }
void LongFormTradeCancelErrorMessage::set_original_trade_control_number(const std::string& value) { original_trade_control_number_ = value; }

Decimal LongFormTradeCancelErrorMessage::original_trade_price_long() const { return original_trade_price_long_; }
void LongFormTradeCancelErrorMessage::set_original_trade_price_long(Decimal value) { original_trade_price_long_ = value; }

std::uint32_t LongFormTradeCancelErrorMessage::original_trade_size() const { return original_trade_size_; }
void LongFormTradeCancelErrorMessage::set_original_trade_size(std::uint32_t value) { original_trade_size_ = value; }

const OriginalSaleConditionModifier& LongFormTradeCancelErrorMessage::original_sale_condition_modifier() const { return original_sale_condition_modifier_; }
OriginalSaleConditionModifier& LongFormTradeCancelErrorMessage::original_sale_condition_modifier() { return original_sale_condition_modifier_; }
void LongFormTradeCancelErrorMessage::set_original_sale_condition_modifier(const OriginalSaleConditionModifier& value) { original_sale_condition_modifier_ = value; }

std::uint64_t LongFormTradeCancelErrorMessage::consolidated_volume() const { return consolidated_volume_; }
void LongFormTradeCancelErrorMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode LongFormTradeCancelErrorMessage::type() const { return message_type; }

std::string_view LongFormTradeCancelErrorMessage::name() const { return "Long Form Trade Cancel Error Message"; }

std::size_t LongFormTradeCancelErrorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LongFormTradeCancelErrorMessage", wire_size, length);

    originating_market_center_identifier_ = static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(data + offset));
    offset += 1;

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    original_trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    original_trade_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    original_trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += original_sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t LongFormTradeCancelErrorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongFormTradeCancelErrorMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(originating_market_center_identifier_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_text(data + offset, 10, ' ', original_trade_control_number_);
    offset += 10;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_trade_price_long_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_trade_size_));
    offset += 4;

    offset += original_sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t LongFormTradeCancelErrorMessage::encoded_size() const {
    return wire_size;
}

void LongFormTradeCancelErrorMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LongFormTradeCancelErrorMessage::clone() const {
    return std::make_unique<LongFormTradeCancelErrorMessage>(*this);
}

void LongFormTradeCancelErrorMessage::print(std::ostream& out) const {
    out << "LongFormTradeCancelErrorMessage{";
    out << "originating_market_center_identifier=";
    out << originating_market_center_identifier_;
    out << ", issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", original_trade_control_number=";
    print::text(out, original_trade_control_number_);
    out << ", original_trade_price_long=";
    out << original_trade_price_long_;
    out << ", original_trade_size=";
    out << original_trade_size_;
    out << ", original_sale_condition_modifier=";
    original_sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool LongFormTradeCancelErrorMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LongFormTradeCancelErrorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongFormTradeCancelErrorMessage::operator==(const LongFormTradeCancelErrorMessage& other) const {
    return originating_market_center_identifier_ == other.originating_market_center_identifier_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && original_trade_control_number_ == other.original_trade_control_number_
        && original_trade_price_long_ == other.original_trade_price_long_
        && original_trade_size_ == other.original_trade_size_
        && original_sale_condition_modifier_ == other.original_sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool LongFormTradeCancelErrorMessage::operator!=(const LongFormTradeCancelErrorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
