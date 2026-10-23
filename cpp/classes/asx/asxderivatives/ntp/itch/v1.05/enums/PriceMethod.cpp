#include "PriceMethod.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(PriceMethod value) {
    switch (value) {
        case PriceMethod::NetPrice: return "Net Price";
        case PriceMethod::YieldDifference: return "Yield Difference";
        case PriceMethod::Individual: return "Individual";
        case PriceMethod::AveragePrice: return "Average Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
