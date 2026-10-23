#include "UnderlyingPriceDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(UnderlyingPriceDenominatorCode value) {
    switch (value) {
        case UnderlyingPriceDenominatorCode::Ten: return "Ten";
        case UnderlyingPriceDenominatorCode::Hundred: return "Hundred";
        case UnderlyingPriceDenominatorCode::Thousand: return "Thousand";
        case UnderlyingPriceDenominatorCode::TenThousand: return "Ten Thousand";
        case UnderlyingPriceDenominatorCode::HundredThousand: return "Hundred Thousand";
        case UnderlyingPriceDenominatorCode::Million: return "Million";
        case UnderlyingPriceDenominatorCode::TenMillion: return "Ten Million";
        case UnderlyingPriceDenominatorCode::HundredMillion: return "Hundred Million";
        case UnderlyingPriceDenominatorCode::NoFraction: return "No Fraction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnderlyingPriceDenominatorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
