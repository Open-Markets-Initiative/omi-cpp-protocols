#include "PriceScaleCode.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(PriceScaleCode value) {
    switch (value) {
        case PriceScaleCode::LowPricedSecurities: return "Low Priced Securities";
        case PriceScaleCode::MediumPricedSecurities: return "Medium Priced Securities";
        case PriceScaleCode::HighPricedSecurities: return "High Priced Securities";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceScaleCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
