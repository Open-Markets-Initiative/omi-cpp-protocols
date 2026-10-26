#include "PriceBandMidpointPriceType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

std::string_view to_string(PriceBandMidpointPriceType value) {
    switch (value) {
        case PriceBandMidpointPriceType::LastTradedPrice: return "Last Traded Price";
        case PriceBandMidpointPriceType::ComplementaryLastPrice: return "Complementary Last Price";
        case PriceBandMidpointPriceType::TheoreticalPrice: return "Theoretical Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceBandMidpointPriceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
