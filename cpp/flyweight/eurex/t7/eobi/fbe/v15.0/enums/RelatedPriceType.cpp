#include "RelatedPriceType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(RelatedPriceType value) {
    switch (value) {
        case RelatedPriceType::Basis: return "Basis";
        case RelatedPriceType::CustomUnderlyingPrice: return "Custom Underlying Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RelatedPriceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
