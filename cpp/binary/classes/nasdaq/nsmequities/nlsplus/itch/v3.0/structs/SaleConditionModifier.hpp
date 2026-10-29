#pragma once

#include <cstddef>
#include <ostream>

#include "../enums/ExtendedHoursOrSoldCode.hpp"
#include "../enums/SettlementType.hpp"
#include "../enums/SpecialSaleCondition.hpp"
#include "../enums/TradeThroughExemption.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Sale condition modifier, consisting of four levels
class SaleConditionModifier {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    SaleConditionModifier() = default;
    SaleConditionModifier(SettlementType settlement_type, TradeThroughExemption trade_through_exemption, ExtendedHoursOrSoldCode extended_hours_or_sold_code, SpecialSaleCondition special_sale_condition);

    // Settlement Type: Used for Settlement Type information
    SettlementType settlement_type() const;
    void set_settlement_type(SettlementType value);

    // Trade Through Exemption: Used for Sec Regulation Nms Trade Through Exemption codes
    TradeThroughExemption trade_through_exemption() const;
    void set_trade_through_exemption(TradeThroughExemption value);

    // Extended Hours Or Sold Code: Used for Extended Hours or Sold codes
    ExtendedHoursOrSoldCode extended_hours_or_sold_code() const;
    void set_extended_hours_or_sold_code(ExtendedHoursOrSoldCode value);

    // Special Sale Condition: Used for special sale condition codes. This field is case
    // sensitive
    SpecialSaleCondition special_sale_condition() const;
    void set_special_sale_condition(SpecialSaleCondition value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SaleConditionModifier& other) const;
    bool operator!=(const SaleConditionModifier& other) const;

  private:
    SettlementType settlement_type_{};
    TradeThroughExemption trade_through_exemption_{};
    ExtendedHoursOrSoldCode extended_hours_or_sold_code_{};
    SpecialSaleCondition special_sale_condition_{};
};

std::ostream& operator<<(std::ostream& out, const SaleConditionModifier& value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
