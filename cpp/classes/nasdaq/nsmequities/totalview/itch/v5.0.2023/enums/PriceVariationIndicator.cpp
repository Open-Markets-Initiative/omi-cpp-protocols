#include "PriceVariationIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(PriceVariationIndicator value) {
    switch (value) {
        case PriceVariationIndicator::LessThan1Percent: return "Less Than 1 Percent";
        case PriceVariationIndicator::LessThan2Percent: return "Less Than 2 Percent";
        case PriceVariationIndicator::LessThan3Percent: return "Less Than 3 Percent";
        case PriceVariationIndicator::LessThan4Percent: return "Less Than 4 Percent";
        case PriceVariationIndicator::LessThan5Percent: return "Less Than 5 Percent";
        case PriceVariationIndicator::LessThan6Percent: return "Less Than 6 Percent";
        case PriceVariationIndicator::LessThan7Percent: return "Less Than 7 Percent";
        case PriceVariationIndicator::LessThan8Percent: return "Less Than 8 Percent";
        case PriceVariationIndicator::LessThan9Percent: return "Less Than 9 Percent";
        case PriceVariationIndicator::LessThan10Percent: return "Less Than 10 Percent";
        case PriceVariationIndicator::LessThan20Percent: return "Less Than 20 Percent";
        case PriceVariationIndicator::LessThan30Percent: return "Less Than 30 Percent";
        case PriceVariationIndicator::MoreThan30Percent: return "More Than 30 Percent";
        case PriceVariationIndicator::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceVariationIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
