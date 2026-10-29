#include "OriginalSaleConditionModifier.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

OriginalSaleConditionModifier::OriginalSaleConditionModifier(OriginalSettlementType original_settlement_type, OriginalTradeThroughExemption original_trade_through_exemption, OriginalExtendedHoursOrSoldCode original_extended_hours_or_sold_code, OriginalSpecialSaleCondition original_special_sale_condition)
  : original_settlement_type_(original_settlement_type), original_trade_through_exemption_(original_trade_through_exemption), original_extended_hours_or_sold_code_(original_extended_hours_or_sold_code), original_special_sale_condition_(original_special_sale_condition) {}

OriginalSettlementType OriginalSaleConditionModifier::original_settlement_type() const { return original_settlement_type_; }
void OriginalSaleConditionModifier::set_original_settlement_type(OriginalSettlementType value) { original_settlement_type_ = value; }

OriginalTradeThroughExemption OriginalSaleConditionModifier::original_trade_through_exemption() const { return original_trade_through_exemption_; }
void OriginalSaleConditionModifier::set_original_trade_through_exemption(OriginalTradeThroughExemption value) { original_trade_through_exemption_ = value; }

OriginalExtendedHoursOrSoldCode OriginalSaleConditionModifier::original_extended_hours_or_sold_code() const { return original_extended_hours_or_sold_code_; }
void OriginalSaleConditionModifier::set_original_extended_hours_or_sold_code(OriginalExtendedHoursOrSoldCode value) { original_extended_hours_or_sold_code_ = value; }

OriginalSpecialSaleCondition OriginalSaleConditionModifier::original_special_sale_condition() const { return original_special_sale_condition_; }
void OriginalSaleConditionModifier::set_original_special_sale_condition(OriginalSpecialSaleCondition value) { original_special_sale_condition_ = value; }

std::size_t OriginalSaleConditionModifier::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OriginalSaleConditionModifier", wire_size, length);

    original_settlement_type_ = static_cast<OriginalSettlementType>(wire::read_char(data + offset));
    offset += 1;

    original_trade_through_exemption_ = static_cast<OriginalTradeThroughExemption>(wire::read_char(data + offset));
    offset += 1;

    original_extended_hours_or_sold_code_ = static_cast<OriginalExtendedHoursOrSoldCode>(wire::read_char(data + offset));
    offset += 1;

    original_special_sale_condition_ = static_cast<OriginalSpecialSaleCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OriginalSaleConditionModifier::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OriginalSaleConditionModifier", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(original_settlement_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(original_trade_through_exemption_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(original_extended_hours_or_sold_code_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(original_special_sale_condition_));
    offset += 1;

    return offset;
}

std::size_t OriginalSaleConditionModifier::encoded_size() const {
    return wire_size;
}

void OriginalSaleConditionModifier::print(std::ostream& out) const {
    out << "OriginalSaleConditionModifier{";
    out << "original_settlement_type=";
    out << original_settlement_type_;
    out << ", original_trade_through_exemption=";
    out << original_trade_through_exemption_;
    out << ", original_extended_hours_or_sold_code=";
    out << original_extended_hours_or_sold_code_;
    out << ", original_special_sale_condition=";
    out << original_special_sale_condition_;
    out << '}';
}

bool OriginalSaleConditionModifier::operator==(const OriginalSaleConditionModifier& other) const {
    return original_settlement_type_ == other.original_settlement_type_
        && original_trade_through_exemption_ == other.original_trade_through_exemption_
        && original_extended_hours_or_sold_code_ == other.original_extended_hours_or_sold_code_
        && original_special_sale_condition_ == other.original_special_sale_condition_;
}

bool OriginalSaleConditionModifier::operator!=(const OriginalSaleConditionModifier& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OriginalSaleConditionModifier& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
