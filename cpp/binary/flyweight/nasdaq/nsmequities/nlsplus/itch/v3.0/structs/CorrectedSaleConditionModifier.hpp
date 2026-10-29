#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/CorrectedSettlementType.hpp"
#include "../enums/CorrectedTradeThroughExemption.hpp"
#include "../enums/CorrectedExtendedHoursOrSoldCode.hpp"
#include "../enums/CorrectedSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The sale condition modifier reported on the corrected trade transaction
class CorrectedSaleConditionModifier {
  public:
    static constexpr const char* name = "CorrectedSaleConditionModifier";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CorrectedSaleConditionModifier(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CorrectedSaleConditionModifier has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    CorrectedSettlementType corrected_settlement_type() const { return static_cast<CorrectedSettlementType>(wire::read_char(at(0))); }

    CorrectedTradeThroughExemption corrected_trade_through_exemption() const { return static_cast<CorrectedTradeThroughExemption>(wire::read_char(at(1))); }

    CorrectedExtendedHoursOrSoldCode corrected_extended_hours_or_sold_code() const { return static_cast<CorrectedExtendedHoursOrSoldCode>(wire::read_char(at(2))); }

    CorrectedSpecialSaleCondition corrected_special_sale_condition() const { return static_cast<CorrectedSpecialSaleCondition>(wire::read_char(at(3))); }

    void print(std::ostream& out) const {
        out << "CorrectedSaleConditionModifier{";
        out << "corrected_settlement_type=";
        out << corrected_settlement_type();
        out << ", corrected_trade_through_exemption=";
        out << corrected_trade_through_exemption();
        out << ", corrected_extended_hours_or_sold_code=";
        out << corrected_extended_hours_or_sold_code();
        out << ", corrected_special_sale_condition=";
        out << corrected_special_sale_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CorrectedSaleConditionModifier& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
