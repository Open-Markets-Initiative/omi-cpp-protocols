#include "PriceVariationIndicator.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

std::string_view to_string(PriceVariationIndicator value) {
    switch (value) {
        case PriceVariationIndicator::LessThan1: return "Less Than 1%";
        case PriceVariationIndicator::OneToOnePointNineNinePercent: return "One To One Point Nine Nine Percent";
        case PriceVariationIndicator::TwoToTwoPointNineNinePercent: return "Two To Two Point Nine Nine Percent";
        case PriceVariationIndicator::ThreeToThreePointNineNinePercent: return "Three To Three Point Nine Nine Percent";
        case PriceVariationIndicator::FourToFourPointNineNinePercent: return "Four To Four Point Nine Nine Percent";
        case PriceVariationIndicator::FiveToFivePointNineNinePercent: return "Five To Five Point Nine Nine Percent";
        case PriceVariationIndicator::SixToSixPointNineNinePercent: return "Six To Six Point Nine Nine Percent";
        case PriceVariationIndicator::SevenToSevenPointNineNinePercent: return "Seven To Seven Point Nine Nine Percent";
        case PriceVariationIndicator::EightToEightPointNineNinePercent: return "Eight To Eight Point Nine Nine Percent";
        case PriceVariationIndicator::NineToNinePointNineNinePercent: return "Nine To Nine Point Nine Nine Percent";
        case PriceVariationIndicator::TenToNineteenPointNineNinePercent: return "Ten To Nineteen Point Nine Nine Percent";
        case PriceVariationIndicator::TwentyToTwentyNinePointNineNinePercent: return "Twenty To Twenty Nine Point Nine Nine Percent";
        case PriceVariationIndicator::ThirtyPercentOrGreater: return "Thirty Percent Or Greater";
        case PriceVariationIndicator::NoCalculation: return "No Calculation";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceVariationIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::psxequities::totalview::itch::v5_0
