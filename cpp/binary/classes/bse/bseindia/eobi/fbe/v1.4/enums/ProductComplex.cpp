#include "ProductComplex.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(ProductComplex value) {
    switch (value) {
        case ProductComplex::FuturesSpread: return "Futures Spread";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ProductComplex value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
