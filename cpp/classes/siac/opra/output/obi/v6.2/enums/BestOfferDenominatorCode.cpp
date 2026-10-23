#include "BestOfferDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(BestOfferDenominatorCode value) {
    switch (value) {
        case BestOfferDenominatorCode::Ten: return "Ten";
        case BestOfferDenominatorCode::Hundred: return "Hundred";
        case BestOfferDenominatorCode::Thousand: return "Thousand";
        case BestOfferDenominatorCode::TenThousand: return "Ten Thousand";
        case BestOfferDenominatorCode::HundredThousand: return "Hundred Thousand";
        case BestOfferDenominatorCode::Million: return "Million";
        case BestOfferDenominatorCode::TenMillion: return "Ten Million";
        case BestOfferDenominatorCode::HundredMillion: return "Hundred Million";
        case BestOfferDenominatorCode::NoFraction: return "No Fraction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BestOfferDenominatorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
