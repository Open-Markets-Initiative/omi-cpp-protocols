#include "PriceLimitType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(PriceLimitType value) {
    switch (value) {
        case PriceLimitType::PriceUnit: return "Price Unit";
        case PriceLimitType::Ticks: return "Ticks";
        case PriceLimitType::Percentage: return "Percentage";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceLimitType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
