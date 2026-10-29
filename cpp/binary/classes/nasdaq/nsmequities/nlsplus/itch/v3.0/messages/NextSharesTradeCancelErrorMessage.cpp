#include "NextSharesTradeCancelErrorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

NextSharesTradeCancelErrorMessage::NextSharesTradeCancelErrorMessage(MarketCenter market_center, const std::string& issue_symbol, SecurityClass security_class, const std::string& original_trade_control_number, Decimal original_proxy_price, Decimal original_nav_offset_amount, std::uint32_t original_trade_size, const OriginalSaleConditionModifier& original_sale_condition_modifier, std::uint64_t consolidated_volume)
  : market_center_(market_center), issue_symbol_(issue_symbol), security_class_(security_class), original_trade_control_number_(original_trade_control_number), original_proxy_price_(original_proxy_price), original_nav_offset_amount_(original_nav_offset_amount), original_trade_size_(original_trade_size), original_sale_condition_modifier_(original_sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

MarketCenter NextSharesTradeCancelErrorMessage::market_center() const { return market_center_; }
void NextSharesTradeCancelErrorMessage::set_market_center(MarketCenter value) { market_center_ = value; }

const std::string& NextSharesTradeCancelErrorMessage::issue_symbol() const { return issue_symbol_; }
std::string& NextSharesTradeCancelErrorMessage::issue_symbol() { return issue_symbol_; }
void NextSharesTradeCancelErrorMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass NextSharesTradeCancelErrorMessage::security_class() const { return security_class_; }
void NextSharesTradeCancelErrorMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& NextSharesTradeCancelErrorMessage::original_trade_control_number() const { return original_trade_control_number_; }
std::string& NextSharesTradeCancelErrorMessage::original_trade_control_number() { return original_trade_control_number_; }
void NextSharesTradeCancelErrorMessage::set_original_trade_control_number(const std::string& value) { original_trade_control_number_ = value; }

Decimal NextSharesTradeCancelErrorMessage::original_proxy_price() const { return original_proxy_price_; }
void NextSharesTradeCancelErrorMessage::set_original_proxy_price(Decimal value) { original_proxy_price_ = value; }

Decimal NextSharesTradeCancelErrorMessage::original_nav_offset_amount() const { return original_nav_offset_amount_; }
void NextSharesTradeCancelErrorMessage::set_original_nav_offset_amount(Decimal value) { original_nav_offset_amount_ = value; }

std::uint32_t NextSharesTradeCancelErrorMessage::original_trade_size() const { return original_trade_size_; }
void NextSharesTradeCancelErrorMessage::set_original_trade_size(std::uint32_t value) { original_trade_size_ = value; }

const OriginalSaleConditionModifier& NextSharesTradeCancelErrorMessage::original_sale_condition_modifier() const { return original_sale_condition_modifier_; }
OriginalSaleConditionModifier& NextSharesTradeCancelErrorMessage::original_sale_condition_modifier() { return original_sale_condition_modifier_; }
void NextSharesTradeCancelErrorMessage::set_original_sale_condition_modifier(const OriginalSaleConditionModifier& value) { original_sale_condition_modifier_ = value; }

std::uint64_t NextSharesTradeCancelErrorMessage::consolidated_volume() const { return consolidated_volume_; }
void NextSharesTradeCancelErrorMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode NextSharesTradeCancelErrorMessage::type() const { return message_type; }

std::string_view NextSharesTradeCancelErrorMessage::name() const { return "Next Shares Trade Cancel Error Message"; }

std::size_t NextSharesTradeCancelErrorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NextSharesTradeCancelErrorMessage", wire_size, length);

    market_center_ = static_cast<MarketCenter>(wire::read_char(data + offset));
    offset += 1;

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    original_trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    original_proxy_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    original_nav_offset_amount_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    original_trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += original_sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t NextSharesTradeCancelErrorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NextSharesTradeCancelErrorMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(market_center_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_text(data + offset, 10, ' ', original_trade_control_number_);
    offset += 10;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_proxy_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_nav_offset_amount_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_trade_size_));
    offset += 4;

    offset += original_sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t NextSharesTradeCancelErrorMessage::encoded_size() const {
    return wire_size;
}

void NextSharesTradeCancelErrorMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NextSharesTradeCancelErrorMessage::clone() const {
    return std::make_unique<NextSharesTradeCancelErrorMessage>(*this);
}

void NextSharesTradeCancelErrorMessage::print(std::ostream& out) const {
    out << "NextSharesTradeCancelErrorMessage{";
    out << "market_center=";
    out << market_center_;
    out << ", issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", original_trade_control_number=";
    print::text(out, original_trade_control_number_);
    out << ", original_proxy_price=";
    out << original_proxy_price_;
    out << ", original_nav_offset_amount=";
    out << original_nav_offset_amount_;
    out << ", original_trade_size=";
    out << original_trade_size_;
    out << ", original_sale_condition_modifier=";
    original_sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool NextSharesTradeCancelErrorMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NextSharesTradeCancelErrorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NextSharesTradeCancelErrorMessage::operator==(const NextSharesTradeCancelErrorMessage& other) const {
    return market_center_ == other.market_center_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && original_trade_control_number_ == other.original_trade_control_number_
        && original_proxy_price_ == other.original_proxy_price_
        && original_nav_offset_amount_ == other.original_nav_offset_amount_
        && original_trade_size_ == other.original_trade_size_
        && original_sale_condition_modifier_ == other.original_sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool NextSharesTradeCancelErrorMessage::operator!=(const NextSharesTradeCancelErrorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
