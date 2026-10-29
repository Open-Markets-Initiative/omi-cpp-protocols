#include "ProductComplex.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::string_view to_string(ProductComplex value) {
    switch (value) {
        case ProductComplex::StandardOptionStrategy: return "Standard Option Strategy";
        case ProductComplex::NonStandardOptionStrategy: return "Non Standard Option Strategy";
        case ProductComplex::VolatilityStrategy: return "Volatility Strategy";
        case ProductComplex::FuturesSpread: return "Futures Spread";
        case ProductComplex::InterProductSpread: return "Inter Product Spread";
        case ProductComplex::StandardFuturesStrategy: return "Standard Futures Strategy";
        case ProductComplex::PackAndBundle: return "Pack And Bundle";
        case ProductComplex::Strip: return "Strip";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ProductComplex value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v6_0
