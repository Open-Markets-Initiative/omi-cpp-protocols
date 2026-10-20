#include "PriceTypeOptional.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(PriceTypeOptional value) {
    switch (value) {
        case PriceTypeOptional::Percentage: return "Percentage";
        case PriceTypeOptional::Pu: return "Pu";
        case PriceTypeOptional::FixedAmount: return "Fixed Amount";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceTypeOptional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
