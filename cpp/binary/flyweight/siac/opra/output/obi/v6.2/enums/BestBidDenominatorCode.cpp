#include "BestBidDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(BestBidDenominatorCode value) {
    switch (value) {
        case BestBidDenominatorCode::Ten: return "Ten";
        case BestBidDenominatorCode::Hundred: return "Hundred";
        case BestBidDenominatorCode::Thousand: return "Thousand";
        case BestBidDenominatorCode::TenThousand: return "Ten Thousand";
        case BestBidDenominatorCode::HundredThousand: return "Hundred Thousand";
        case BestBidDenominatorCode::Million: return "Million";
        case BestBidDenominatorCode::TenMillion: return "Ten Million";
        case BestBidDenominatorCode::HundredMillion: return "Hundred Million";
        case BestBidDenominatorCode::NoFraction: return "No Fraction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BestBidDenominatorCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
