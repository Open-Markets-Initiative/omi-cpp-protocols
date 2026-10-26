#include "AdoptedPricingMethod.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(AdoptedPricingMethod value) {
    switch (value) {
        case AdoptedPricingMethod::ItayoseMethod: return "Itayose Method";
        case AdoptedPricingMethod::QuoteDisplayed: return "Quote Displayed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AdoptedPricingMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
