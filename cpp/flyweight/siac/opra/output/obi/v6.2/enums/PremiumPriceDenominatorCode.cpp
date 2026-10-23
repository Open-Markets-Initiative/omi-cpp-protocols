#include "PremiumPriceDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(PremiumPriceDenominatorCode value) {
    switch (value) {
        case PremiumPriceDenominatorCode::Ten: return "Ten";
        case PremiumPriceDenominatorCode::Hundred: return "Hundred";
        case PremiumPriceDenominatorCode::Thousand: return "Thousand";
        case PremiumPriceDenominatorCode::TenThousand: return "Ten Thousand";
        case PremiumPriceDenominatorCode::HundredThousand: return "Hundred Thousand";
        case PremiumPriceDenominatorCode::Million: return "Million";
        case PremiumPriceDenominatorCode::TenMillion: return "Ten Million";
        case PremiumPriceDenominatorCode::NoFraction: return "No Fraction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PremiumPriceDenominatorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
