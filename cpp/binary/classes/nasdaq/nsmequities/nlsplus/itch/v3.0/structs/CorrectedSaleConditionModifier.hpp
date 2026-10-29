#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/CorrectedExtendedHoursOrSoldCode.hpp"
#include "../enums/CorrectedSettlementType.hpp"
#include "../enums/CorrectedSpecialSaleCondition.hpp"
#include "../enums/CorrectedTradeThroughExemption.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The sale condition modifier reported on the corrected trade transaction
class CorrectedSaleConditionModifier {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    CorrectedSaleConditionModifier() = default;
    CorrectedSaleConditionModifier(CorrectedSettlementType corrected_settlement_type, CorrectedTradeThroughExemption corrected_trade_through_exemption, CorrectedExtendedHoursOrSoldCode corrected_extended_hours_or_sold_code, CorrectedSpecialSaleCondition corrected_special_sale_condition);

    // Corrected Settlement Type: Used for Settlement Type information
    CorrectedSettlementType corrected_settlement_type() const;
    void set_corrected_settlement_type(CorrectedSettlementType value);

    // Corrected Trade Through Exemption: Used for Sec Regulation Nms Trade Through Exemption
    // codes
    CorrectedTradeThroughExemption corrected_trade_through_exemption() const;
    void set_corrected_trade_through_exemption(CorrectedTradeThroughExemption value);

    // Corrected Extended Hours Or Sold Code: Used for Extended Hours or Sold codes
    CorrectedExtendedHoursOrSoldCode corrected_extended_hours_or_sold_code() const;
    void set_corrected_extended_hours_or_sold_code(CorrectedExtendedHoursOrSoldCode value);

    // Corrected Special Sale Condition: Used for special sale condition codes. This field is
    // case sensitive
    CorrectedSpecialSaleCondition corrected_special_sale_condition() const;
    void set_corrected_special_sale_condition(CorrectedSpecialSaleCondition value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CorrectedSaleConditionModifier& other) const;
    bool operator!=(const CorrectedSaleConditionModifier& other) const;

  private:
    CorrectedSettlementType corrected_settlement_type_{};
    CorrectedTradeThroughExemption corrected_trade_through_exemption_{};
    CorrectedExtendedHoursOrSoldCode corrected_extended_hours_or_sold_code_{};
    CorrectedSpecialSaleCondition corrected_special_sale_condition_{};
};

std::ostream& operator<<(std::ostream& out, const CorrectedSaleConditionModifier& value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
