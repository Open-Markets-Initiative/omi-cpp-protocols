#include "PriceType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(PriceType value) {
    switch (value) {
        case PriceType::Percentage: return "Percentage";
        case PriceType::Pu: return "Pu";
        case PriceType::FixedAmount: return "Fixed Amount";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
