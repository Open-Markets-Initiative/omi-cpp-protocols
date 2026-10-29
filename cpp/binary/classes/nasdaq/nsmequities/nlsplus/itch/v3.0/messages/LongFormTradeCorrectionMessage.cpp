#include "LongFormTradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

LongFormTradeCorrectionMessage::LongFormTradeCorrectionMessage(OriginatingMarketCenterIdentifier originating_market_center_identifier, const std::string& issue_symbol, SecurityClass security_class, const std::string& original_trade_control_number, Decimal original_trade_price_long, std::uint32_t original_trade_size, const OriginalSaleConditionModifier& original_sale_condition_modifier, const std::string& corrected_trade_control_number, Decimal corrected_trade_price_long, std::uint32_t corrected_trade_size, const CorrectedSaleConditionModifier& corrected_sale_condition_modifier, std::uint64_t consolidated_volume)
  : originating_market_center_identifier_(originating_market_center_identifier), issue_symbol_(issue_symbol), security_class_(security_class), original_trade_control_number_(original_trade_control_number), original_trade_price_long_(original_trade_price_long), original_trade_size_(original_trade_size), original_sale_condition_modifier_(original_sale_condition_modifier), corrected_trade_control_number_(corrected_trade_control_number), corrected_trade_price_long_(corrected_trade_price_long), corrected_trade_size_(corrected_trade_size), corrected_sale_condition_modifier_(corrected_sale_condition_modifier), consolidated_volume_(consolidated_volume) {}

OriginatingMarketCenterIdentifier LongFormTradeCorrectionMessage::originating_market_center_identifier() const { return originating_market_center_identifier_; }
void LongFormTradeCorrectionMessage::set_originating_market_center_identifier(OriginatingMarketCenterIdentifier value) { originating_market_center_identifier_ = value; }

const std::string& LongFormTradeCorrectionMessage::issue_symbol() const { return issue_symbol_; }
std::string& LongFormTradeCorrectionMessage::issue_symbol() { return issue_symbol_; }
void LongFormTradeCorrectionMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass LongFormTradeCorrectionMessage::security_class() const { return security_class_; }
void LongFormTradeCorrectionMessage::set_security_class(SecurityClass value) { security_class_ = value; }

const std::string& LongFormTradeCorrectionMessage::original_trade_control_number() const { return original_trade_control_number_; }
std::string& LongFormTradeCorrectionMessage::original_trade_control_number() { return original_trade_control_number_; }
void LongFormTradeCorrectionMessage::set_original_trade_control_number(const std::string& value) { original_trade_control_number_ = value; }

Decimal LongFormTradeCorrectionMessage::original_trade_price_long() const { return original_trade_price_long_; }
void LongFormTradeCorrectionMessage::set_original_trade_price_long(Decimal value) { original_trade_price_long_ = value; }

std::uint32_t LongFormTradeCorrectionMessage::original_trade_size() const { return original_trade_size_; }
void LongFormTradeCorrectionMessage::set_original_trade_size(std::uint32_t value) { original_trade_size_ = value; }

const OriginalSaleConditionModifier& LongFormTradeCorrectionMessage::original_sale_condition_modifier() const { return original_sale_condition_modifier_; }
OriginalSaleConditionModifier& LongFormTradeCorrectionMessage::original_sale_condition_modifier() { return original_sale_condition_modifier_; }
void LongFormTradeCorrectionMessage::set_original_sale_condition_modifier(const OriginalSaleConditionModifier& value) { original_sale_condition_modifier_ = value; }

const std::string& LongFormTradeCorrectionMessage::corrected_trade_control_number() const { return corrected_trade_control_number_; }
std::string& LongFormTradeCorrectionMessage::corrected_trade_control_number() { return corrected_trade_control_number_; }
void LongFormTradeCorrectionMessage::set_corrected_trade_control_number(const std::string& value) { corrected_trade_control_number_ = value; }

Decimal LongFormTradeCorrectionMessage::corrected_trade_price_long() const { return corrected_trade_price_long_; }
void LongFormTradeCorrectionMessage::set_corrected_trade_price_long(Decimal value) { corrected_trade_price_long_ = value; }

std::uint32_t LongFormTradeCorrectionMessage::corrected_trade_size() const { return corrected_trade_size_; }
void LongFormTradeCorrectionMessage::set_corrected_trade_size(std::uint32_t value) { corrected_trade_size_ = value; }

const CorrectedSaleConditionModifier& LongFormTradeCorrectionMessage::corrected_sale_condition_modifier() const { return corrected_sale_condition_modifier_; }
CorrectedSaleConditionModifier& LongFormTradeCorrectionMessage::corrected_sale_condition_modifier() { return corrected_sale_condition_modifier_; }
void LongFormTradeCorrectionMessage::set_corrected_sale_condition_modifier(const CorrectedSaleConditionModifier& value) { corrected_sale_condition_modifier_ = value; }

std::uint64_t LongFormTradeCorrectionMessage::consolidated_volume() const { return consolidated_volume_; }
void LongFormTradeCorrectionMessage::set_consolidated_volume(std::uint64_t value) { consolidated_volume_ = value; }

MessageCode LongFormTradeCorrectionMessage::type() const { return message_type; }

std::string_view LongFormTradeCorrectionMessage::name() const { return "Long Form Trade Correction Message"; }

std::size_t LongFormTradeCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LongFormTradeCorrectionMessage", wire_size, length);

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

    corrected_trade_control_number_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    corrected_trade_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    corrected_trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += corrected_sale_condition_modifier_.decode(data + offset, length - offset);

    consolidated_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t LongFormTradeCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongFormTradeCorrectionMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 10, ' ', corrected_trade_control_number_);
    offset += 10;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(corrected_trade_price_long_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(corrected_trade_size_));
    offset += 4;

    offset += corrected_sale_condition_modifier_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_volume_));
    offset += 8;

    return offset;
}

std::size_t LongFormTradeCorrectionMessage::encoded_size() const {
    return wire_size;
}

void LongFormTradeCorrectionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LongFormTradeCorrectionMessage::clone() const {
    return std::make_unique<LongFormTradeCorrectionMessage>(*this);
}

void LongFormTradeCorrectionMessage::print(std::ostream& out) const {
    out << "LongFormTradeCorrectionMessage{";
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
    out << ", corrected_trade_control_number=";
    print::text(out, corrected_trade_control_number_);
    out << ", corrected_trade_price_long=";
    out << corrected_trade_price_long_;
    out << ", corrected_trade_size=";
    out << corrected_trade_size_;
    out << ", corrected_sale_condition_modifier=";
    corrected_sale_condition_modifier_.print(out);
    out << ", consolidated_volume=";
    out << consolidated_volume_;
    out << '}';
}

bool LongFormTradeCorrectionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LongFormTradeCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongFormTradeCorrectionMessage::operator==(const LongFormTradeCorrectionMessage& other) const {
    return originating_market_center_identifier_ == other.originating_market_center_identifier_
        && issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && original_trade_control_number_ == other.original_trade_control_number_
        && original_trade_price_long_ == other.original_trade_price_long_
        && original_trade_size_ == other.original_trade_size_
        && original_sale_condition_modifier_ == other.original_sale_condition_modifier_
        && corrected_trade_control_number_ == other.corrected_trade_control_number_
        && corrected_trade_price_long_ == other.corrected_trade_price_long_
        && corrected_trade_size_ == other.corrected_trade_size_
        && corrected_sale_condition_modifier_ == other.corrected_sale_condition_modifier_
        && consolidated_volume_ == other.consolidated_volume_;
}

bool LongFormTradeCorrectionMessage::operator!=(const LongFormTradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
