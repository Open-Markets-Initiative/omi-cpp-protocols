#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/OriginalSettlementType.hpp"
#include "../enums/OriginalTradeThroughExemption.hpp"
#include "../enums/OriginalExtendedHoursOrSoldCode.hpp"
#include "../enums/OriginalSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The sale condition modifier reported on the original trade transaction
class OriginalSaleConditionModifier {
  public:
    static constexpr const char* name = "OriginalSaleConditionModifier";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OriginalSaleConditionModifier(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OriginalSaleConditionModifier has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    OriginalSettlementType original_settlement_type() const { return static_cast<OriginalSettlementType>(wire::read_char(at(0))); }

    OriginalTradeThroughExemption original_trade_through_exemption() const { return static_cast<OriginalTradeThroughExemption>(wire::read_char(at(1))); }

    OriginalExtendedHoursOrSoldCode original_extended_hours_or_sold_code() const { return static_cast<OriginalExtendedHoursOrSoldCode>(wire::read_char(at(2))); }

    OriginalSpecialSaleCondition original_special_sale_condition() const { return static_cast<OriginalSpecialSaleCondition>(wire::read_char(at(3))); }

    void print(std::ostream& out) const {
        out << "OriginalSaleConditionModifier{";
        out << "original_settlement_type=";
        out << original_settlement_type();
        out << ", original_trade_through_exemption=";
        out << original_trade_through_exemption();
        out << ", original_extended_hours_or_sold_code=";
        out << original_extended_hours_or_sold_code();
        out << ", original_special_sale_condition=";
        out << original_special_sale_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OriginalSaleConditionModifier& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
