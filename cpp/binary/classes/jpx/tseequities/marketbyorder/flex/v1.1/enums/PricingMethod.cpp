#include "PricingMethod.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(PricingMethod value) {
    switch (value) {
        case PricingMethod::ItayoseMethod: return "Itayose Method";
        case PricingMethod::ZarabaMethod: return "Zaraba Method";
        case PricingMethod::SellSpecialQuoteDisplayed: return "Sell Special Quote Displayed";
        case PricingMethod::BuySpecialQuoteDisplayed: return "Buy Special Quote Displayed";
        case PricingMethod::SellSequentialTradeQuoteDisplayed: return "Sell Sequential Trade Quote Displayed";
        case PricingMethod::BuySequentialTradeQuoteDisplayed: return "Buy Sequential Trade Quote Displayed";
        case PricingMethod::OtherThanTheAbove: return "Other Than The Above";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PricingMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
