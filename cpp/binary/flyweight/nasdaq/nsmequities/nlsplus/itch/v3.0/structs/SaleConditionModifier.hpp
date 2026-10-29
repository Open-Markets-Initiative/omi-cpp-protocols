#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SettlementType.hpp"
#include "../enums/TradeThroughExemption.hpp"
#include "../enums/ExtendedHoursOrSoldCode.hpp"
#include "../enums/SpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Sale condition modifier, consisting of four levels
class SaleConditionModifier {
  public:
    static constexpr const char* name = "SaleConditionModifier";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SaleConditionModifier(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SaleConditionModifier has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    SettlementType settlement_type() const { return static_cast<SettlementType>(wire::read_char(at(0))); }

    TradeThroughExemption trade_through_exemption() const { return static_cast<TradeThroughExemption>(wire::read_char(at(1))); }

    ExtendedHoursOrSoldCode extended_hours_or_sold_code() const { return static_cast<ExtendedHoursOrSoldCode>(wire::read_char(at(2))); }

    SpecialSaleCondition special_sale_condition() const { return static_cast<SpecialSaleCondition>(wire::read_char(at(3))); }

    void print(std::ostream& out) const {
        out << "SaleConditionModifier{";
        out << "settlement_type=";
        out << settlement_type();
        out << ", trade_through_exemption=";
        out << trade_through_exemption();
        out << ", extended_hours_or_sold_code=";
        out << extended_hours_or_sold_code();
        out << ", special_sale_condition=";
        out << special_sale_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SaleConditionModifier& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
