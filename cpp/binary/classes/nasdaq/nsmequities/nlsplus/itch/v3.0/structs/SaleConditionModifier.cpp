#include "SaleConditionModifier.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

SaleConditionModifier::SaleConditionModifier(SettlementType settlement_type, TradeThroughExemption trade_through_exemption, ExtendedHoursOrSoldCode extended_hours_or_sold_code, SpecialSaleCondition special_sale_condition)
  : settlement_type_(settlement_type), trade_through_exemption_(trade_through_exemption), extended_hours_or_sold_code_(extended_hours_or_sold_code), special_sale_condition_(special_sale_condition) {}

SettlementType SaleConditionModifier::settlement_type() const { return settlement_type_; }
void SaleConditionModifier::set_settlement_type(SettlementType value) { settlement_type_ = value; }

TradeThroughExemption SaleConditionModifier::trade_through_exemption() const { return trade_through_exemption_; }
void SaleConditionModifier::set_trade_through_exemption(TradeThroughExemption value) { trade_through_exemption_ = value; }

ExtendedHoursOrSoldCode SaleConditionModifier::extended_hours_or_sold_code() const { return extended_hours_or_sold_code_; }
void SaleConditionModifier::set_extended_hours_or_sold_code(ExtendedHoursOrSoldCode value) { extended_hours_or_sold_code_ = value; }

SpecialSaleCondition SaleConditionModifier::special_sale_condition() const { return special_sale_condition_; }
void SaleConditionModifier::set_special_sale_condition(SpecialSaleCondition value) { special_sale_condition_ = value; }

std::size_t SaleConditionModifier::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SaleConditionModifier", wire_size, length);

    settlement_type_ = static_cast<SettlementType>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exemption_ = static_cast<TradeThroughExemption>(wire::read_char(data + offset));
    offset += 1;

    extended_hours_or_sold_code_ = static_cast<ExtendedHoursOrSoldCode>(wire::read_char(data + offset));
    offset += 1;

    special_sale_condition_ = static_cast<SpecialSaleCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SaleConditionModifier::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SaleConditionModifier", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(settlement_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exemption_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(extended_hours_or_sold_code_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(special_sale_condition_));
    offset += 1;

    return offset;
}

std::size_t SaleConditionModifier::encoded_size() const {
    return wire_size;
}

void SaleConditionModifier::print(std::ostream& out) const {
    out << "SaleConditionModifier{";
    out << "settlement_type=";
    out << settlement_type_;
    out << ", trade_through_exemption=";
    out << trade_through_exemption_;
    out << ", extended_hours_or_sold_code=";
    out << extended_hours_or_sold_code_;
    out << ", special_sale_condition=";
    out << special_sale_condition_;
    out << '}';
}

bool SaleConditionModifier::operator==(const SaleConditionModifier& other) const {
    return settlement_type_ == other.settlement_type_
        && trade_through_exemption_ == other.trade_through_exemption_
        && extended_hours_or_sold_code_ == other.extended_hours_or_sold_code_
        && special_sale_condition_ == other.special_sale_condition_;
}

bool SaleConditionModifier::operator!=(const SaleConditionModifier& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SaleConditionModifier& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
