#include "Product.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(Product value) {
    switch (value) {
        case Product::Commodity: return "Commodity";
        case Product::Corporate: return "Corporate";
        case Product::Currency: return "Currency";
        case Product::Equity: return "Equity";
        case Product::Government: return "Government";
        case Product::Index: return "Index";
        case Product::EconomicIndicator: return "Economic Indicator";
        case Product::Multileg: return "Multileg";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Product value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
