#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/OriginalExtendedHoursOrSoldCode.hpp"
#include "../enums/OriginalSettlementType.hpp"
#include "../enums/OriginalSpecialSaleCondition.hpp"
#include "../enums/OriginalTradeThroughExemption.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The sale condition modifier reported on the original trade transaction
class OriginalSaleConditionModifier {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    OriginalSaleConditionModifier() = default;
    OriginalSaleConditionModifier(OriginalSettlementType original_settlement_type, OriginalTradeThroughExemption original_trade_through_exemption, OriginalExtendedHoursOrSoldCode original_extended_hours_or_sold_code, OriginalSpecialSaleCondition original_special_sale_condition);

    // Original Settlement Type: Used for Settlement Type information
    OriginalSettlementType original_settlement_type() const;
    void set_original_settlement_type(OriginalSettlementType value);

    // Original Trade Through Exemption: Used for Sec Regulation Nms Trade Through Exemption
    // codes
    OriginalTradeThroughExemption original_trade_through_exemption() const;
    void set_original_trade_through_exemption(OriginalTradeThroughExemption value);

    // Original Extended Hours Or Sold Code: Used for Extended Hours or Sold codes
    OriginalExtendedHoursOrSoldCode original_extended_hours_or_sold_code() const;
    void set_original_extended_hours_or_sold_code(OriginalExtendedHoursOrSoldCode value);

    // Original Special Sale Condition: Used for special sale condition codes. This field is
    // case sensitive
    OriginalSpecialSaleCondition original_special_sale_condition() const;
    void set_original_special_sale_condition(OriginalSpecialSaleCondition value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const OriginalSaleConditionModifier& other) const;
    bool operator!=(const OriginalSaleConditionModifier& other) const;

  private:
    OriginalSettlementType original_settlement_type_{};
    OriginalTradeThroughExemption original_trade_through_exemption_{};
    OriginalExtendedHoursOrSoldCode original_extended_hours_or_sold_code_{};
    OriginalSpecialSaleCondition original_special_sale_condition_{};
};

std::ostream& operator<<(std::ostream& out, const OriginalSaleConditionModifier& value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
