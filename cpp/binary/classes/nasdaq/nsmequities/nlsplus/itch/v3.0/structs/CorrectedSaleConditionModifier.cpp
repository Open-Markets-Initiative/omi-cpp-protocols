#include "CorrectedSaleConditionModifier.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

CorrectedSaleConditionModifier::CorrectedSaleConditionModifier(CorrectedSettlementType corrected_settlement_type, CorrectedTradeThroughExemption corrected_trade_through_exemption, CorrectedExtendedHoursOrSoldCode corrected_extended_hours_or_sold_code, CorrectedSpecialSaleCondition corrected_special_sale_condition)
  : corrected_settlement_type_(corrected_settlement_type), corrected_trade_through_exemption_(corrected_trade_through_exemption), corrected_extended_hours_or_sold_code_(corrected_extended_hours_or_sold_code), corrected_special_sale_condition_(corrected_special_sale_condition) {}

CorrectedSettlementType CorrectedSaleConditionModifier::corrected_settlement_type() const { return corrected_settlement_type_; }
void CorrectedSaleConditionModifier::set_corrected_settlement_type(CorrectedSettlementType value) { corrected_settlement_type_ = value; }

CorrectedTradeThroughExemption CorrectedSaleConditionModifier::corrected_trade_through_exemption() const { return corrected_trade_through_exemption_; }
void CorrectedSaleConditionModifier::set_corrected_trade_through_exemption(CorrectedTradeThroughExemption value) { corrected_trade_through_exemption_ = value; }

CorrectedExtendedHoursOrSoldCode CorrectedSaleConditionModifier::corrected_extended_hours_or_sold_code() const { return corrected_extended_hours_or_sold_code_; }
void CorrectedSaleConditionModifier::set_corrected_extended_hours_or_sold_code(CorrectedExtendedHoursOrSoldCode value) { corrected_extended_hours_or_sold_code_ = value; }

CorrectedSpecialSaleCondition CorrectedSaleConditionModifier::corrected_special_sale_condition() const { return corrected_special_sale_condition_; }
void CorrectedSaleConditionModifier::set_corrected_special_sale_condition(CorrectedSpecialSaleCondition value) { corrected_special_sale_condition_ = value; }

std::size_t CorrectedSaleConditionModifier::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CorrectedSaleConditionModifier", wire_size, length);

    corrected_settlement_type_ = static_cast<CorrectedSettlementType>(wire::read_char(data + offset));
    offset += 1;

    corrected_trade_through_exemption_ = static_cast<CorrectedTradeThroughExemption>(wire::read_char(data + offset));
    offset += 1;

    corrected_extended_hours_or_sold_code_ = static_cast<CorrectedExtendedHoursOrSoldCode>(wire::read_char(data + offset));
    offset += 1;

    corrected_special_sale_condition_ = static_cast<CorrectedSpecialSaleCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t CorrectedSaleConditionModifier::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CorrectedSaleConditionModifier", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(corrected_settlement_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(corrected_trade_through_exemption_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(corrected_extended_hours_or_sold_code_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(corrected_special_sale_condition_));
    offset += 1;

    return offset;
}

std::size_t CorrectedSaleConditionModifier::encoded_size() const {
    return wire_size;
}

void CorrectedSaleConditionModifier::print(std::ostream& out) const {
    out << "CorrectedSaleConditionModifier{";
    out << "corrected_settlement_type=";
    out << corrected_settlement_type_;
    out << ", corrected_trade_through_exemption=";
    out << corrected_trade_through_exemption_;
    out << ", corrected_extended_hours_or_sold_code=";
    out << corrected_extended_hours_or_sold_code_;
    out << ", corrected_special_sale_condition=";
    out << corrected_special_sale_condition_;
    out << '}';
}

bool CorrectedSaleConditionModifier::operator==(const CorrectedSaleConditionModifier& other) const {
    return corrected_settlement_type_ == other.corrected_settlement_type_
        && corrected_trade_through_exemption_ == other.corrected_trade_through_exemption_
        && corrected_extended_hours_or_sold_code_ == other.corrected_extended_hours_or_sold_code_
        && corrected_special_sale_condition_ == other.corrected_special_sale_condition_;
}

bool CorrectedSaleConditionModifier::operator!=(const CorrectedSaleConditionModifier& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CorrectedSaleConditionModifier& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
